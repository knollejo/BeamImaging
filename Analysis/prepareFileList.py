def prepareFileList(directories, outputname, times):
    from pickle import dump
    from os import listdir, stat, mkdir
    from os.path import exists
    from ROOT import TFile

    files = {name: [] for name in times}
    for directory in directories:
        print '<<< Enter directory', directory
        allfiles = listdir(directory)
        for filename in allfiles:
            if not filename.endswith('.root'):
                continue
            if stat(directory+'/'+filename).st_size <= 0:
                continue
            try:
                f = TFile(directory+'/'+filename)
                t = f.Get('lumi/tree')
                for name, (bg, ed) in times.iteritems():
                    n = t.GetEntries('timeStamp_begin>'+str(bg)+' && '+ \
                                    'timeStamp_end<'+str(ed))
                    if n > 0:
                        files[name].append(directory+'/'+filename)
            except:
                continue
    if not exists('filelist'):
        mkdir('filelist')
    for name in files:
        with open('filelist/'+outputname+'_'+name+'.txt', 'w') as f:
            f.write('\n'.join(files[name]))
            print '<<< Found', len(files[name]), 'files for', name

def main():
    from sys import argv as __ARGV__
    __ARGV__.append('-b')

    from argparse import ArgumentParser
    from json import load as decode
    from re import match

    parser = ArgumentParser(description='Make list of ROOT files')
    parser.add_argument('-b', action='store_true', help='enable batch mode')
    parser.add_argument('json', nargs=1, help='specify JSON file containing '+ \
                        'config information')
    args = parser.parse_args()

    with open(args.json[0]) as f:
        json = decode(f)
    name = str(json['prefix'])
    directories = [json['sourcepath']+'/'+d for d in json['sourcedirectories']]
    times = {name[4:6]: (json[name][0], json[name[0:10]+'End'][-1]) for name \
             in json if match('^scan[12][XY]MoveBegin$', name)}
    print times
    prepareFileList(directories, name, times)

if __name__ == '__main__':
    main()
