from ROOT import TFile

bunchcrossings = ('41', '281', '872', '1783', '2063')
beamshapes = ('DG', 'SupG')

def gatherFromToys(crossings, shapes):
    overDiff = {}
    for shape in shapes:
        overDiff[shape] = {}
        for bx in crossings:
            f = TFile.Open('overlapDiff_TOYS_2016_'+bx+shape+'.root')
            hist = f.Get('overDiff')
            overDiff[shape][bx] = hist.GetMean()
    print
    print
    print '',
    for bx in crossings:
        print ';', bx,
    print
    for shape in shapes:
        print shape,
        for bx in crossings:
            print ';', overDiff[shape][bx],
        print
    print
    print

if __name__ == '__main__':
    gatherFromToys(bunchcrossings, beamshapes)
