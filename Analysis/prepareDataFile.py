def prepareDataFile(listfile, times, minTrk, nbins, bcids, scaling, offsetx, \
                    offsety, outputpath, outputname):
    from array import array
    from itertools import product
    from os import mkdir
    from os.path import exists
    from ROOT import TChain, TH1F, TH2F, TFile

    chain = {name: TChain('lumi/tree') for name in listfile}
    for name, filename in listfile.iteritems():
        with open(filename) as f:
            for line in f:
                chain[name].Add(line.strip())

    values = {name: array(t, v) for (name, t, v) in [ \
              ('bunchCrossing', 'i', [0]), \
              ('nVtx', 'i', [0]), \
              ('vtx_nTrk', 'i', [0]*200), \
              ('vtx_x', 'f', [0.0]*200), \
              ('vtx_y', 'f', [0.0]*200), \
              ('vtx_xError', 'f', [0.0]*200), \
              ('vtx_yError', 'f', [0.0]*200), \
              ('vtx_isGood', 'b', [0]*200), \
              ('vtx_isValid', 'b', [0]*200), \
              ('vtx_isFake', 'b', [0]*200), \
              ('timeStamp_begin', 'I', [0]), \
              ('timeStamp_end', 'I', [0])]}
    for ch in chain.itervalues():
        for field in values:
            ch.SetBranchAddress(field, values[field])

    histos = {c+'Error': TH1F(c+'Error_hist', c+'Error_hist', 1000, 0.0, 0.1) \
              for c in ['x', 'y']}
    def moveName(i, c, b):
        return 'Beam' + i + 'Move' + c + '_bunch' + b + 'Add'
    histos.update({name: TH2F(name, name, nbins, -10.0, 10.0, nbins, -10.0, \
                   10.0) for name in [moveName(i, c, b) for i in ['1', '2'] \
                   for c in ['X', 'Y'] for b in bcids]})

    for name, ch in chain.iteritems():
        nEntries = ch.GetEntries()
        print '<<< Start to process', name, 'with', nEntries, 'events'
        for i in range(nEntries):
            if i % 10000 == 0:
                print '<<< Now at event', i
            ch.GetEntry(i)
            if values['nVtx'][0] <= 0:
                continue
            if not str(values['bunchCrossing']) in bcids:
                continue
            for j in range(values['nVtx'][0]):
                if not values['vtx_isGood'][j]:
                    continue
                if values['vtx_isFake'][j]:
                    continue
                if values['vtx_nTrk'][j] <= minTrk:
                    continue
                histos['xError'].Fill(values['vtx_xError'][j])
                histos['yError'].Fill(values['vtx_yError'][j])
                xVtx = (values['vtx_x'][j] + offsetx) / scaling
                yVtx = (values['vtx_y'][j] + offsety) / scaling
                for begin, end in zip(times['Scan'+name+'MoveBegin'], \
                                      times['Scan'+name+'MoveEnd']):
                    if values['timeStamp_begin'] < begin:
                        continue
                    if values['timeStamp_end'] > end:
                        continue
                    histos[moveName(name[0], name[1], \
                           str(values['bunchCrossing']))].Fill(xVtx, yVtx)

    if not exists(outputpath):
        mkdir(outputpath)
    outputfile = TFile(outputpath+'/'+outputname+'.root', 'RECREATE')
    for hist in histos:
        hist.Write()
    outputfile.Write()
    outputfile.Close()

def main():
    from sys import argv as __ARGV__
    __ARGV__.append('-b')

    from tools import loadJson
    from argparse import ArgumentParser
    from re import match

    parser = ArgumentParser(description='Extract Beam Imaging data from ROOT '+ \
                            'files')
    parser.add_argument('-b', action='store_true', help='enable batch mode')
    parser.add_argument('json', nargs=1, help='specify JSON file containing '+ \
                        'config information')
    args = parser.parse_args()

    json = loadJson(args.json[0])
    listfile = {name: 'filelist/'+str(json['prefix'])+'_'+name+'.txt' for \
                name in ['1X', '1Y', '2X', '2Y']}
    times = {name: json[name] for name in json if \
             match('^scan[12][XY]Move(Begin|End)$', name)}
    minTrk = int(json['minTrk'])
    nbins = int(json['nbins'])
    bcids = [str(bx) for bx in json['bunchCrossings']]
    scaling = float(json['scaling'])
    offsetx = float(json['offsetx'])
    offsety = float(json['offsety'])
    outputpath = str(json['datapath'])
    outputname = str(json['prefix'] )+ '_' + str(json['suffix'])

    prepareDataFile(listfile, times, minTrk, nbins, bcids, scaling, offsetx, \
                        offsety, outputpath, outputname)

if __name__ == '__main__':
    main()
