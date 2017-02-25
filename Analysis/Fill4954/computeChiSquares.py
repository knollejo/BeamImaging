from ROOT import TFile

bunchcrossings = ('41', '281', '872', '1783', '2063')
beamshapes = ('SG', 'DG', 'SupG')

def computeChiSquares(crossings, shapes):
    components = ('X1', 'Y1', 'X2', 'Y2')
    chiSq = {}
    dof = {}
    for shape in shapes:
        chiSq[shape] = {}
        dof[shape] = {}
        for bx in crossings:
            chiSq[shape][bx] = {}
            dof[shape][bx] = {}
            f = TFile.Open('DataAnalysisBunch'+bx+shape+'_new_StronRescale.root')
            for comp in components:
                c = 0.0
                d = 0
                res = f.Get('res'+comp)
                for x in range(res.GetXaxis().GetNbins()):
                    for y in range(res.GetYaxis().GetNbins()):
                        c += res.GetBinContent(x,y) ** 2
                        if res.GetBinContent(x,y):
                            d += 1
                chiSq[shape][bx][comp] = c
                dof[shape][bx][comp] = d
    print
    for comp in components:
        print
        print comp,
        for bx in crossings:
            print ';', bx,
        print
        for shape in shapes:
            print shape,
            for bx in crossings:
                print ';', chiSq[shape][bx][comp]/dof[shape][bx][comp],
            print
        print
    print

if __name__ == '__main__':
    computeChiSquares(bunchcrossings, beamshapes)
