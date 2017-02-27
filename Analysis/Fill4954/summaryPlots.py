from sys import argv as __ARGV__
__ARGV__.append('-b')

from computeChiSquares import computeChiSquares
from gatherFromToys import gatherFromToys
from array import array
from ROOT import TFile, TColor, TCanvas, TLatex, TPaveText, TH2D, gStyle

bunchcrossings = ('41', '281', '872', '1783', '2063')
beamshapes = ('SG', 'DG', 'SupG', 'TG')
shapeNames = {'SG': 'Single Gaussian', \
              'DG': 'Double Gaussian', \
              'SupG': 'Super Gaussian', \
              'TG': 'Triple Gaussian'}

def kBird():
    red = array('d', [0.2082, 0.0592, 0.0780, 0.0232, 0.1802, 0.5301, 0.8186, 0.9956, 0.9764])
    green = array('d', [0.1664, 0.3599, 0.5041, 0.6419, 0.7178, 0.7492, 0.7328, 0.7862, 0.9832])
    blue = array('d',  [0.5293, 0.8684, 0.8385, 0.7914, 0.6425, 0.4662, 0.3499, 0.1968, 0.0539])
    stops = array('d', [0.0, 0.125, 0.25, 0.375, 0.5, 0.625, 0.75, 0.875, 1.0])
    TColor.CreateGradientColorTable(9, stops, red, green, blue, 255)

def drawCMS(wip=False):
    text = TLatex()
    text.SetNDC()
    text.SetTextFont(62)
    text.SetTextSize(0.0375)
    text.SetTextAlign(31)
    text.DrawLatex(0.9,0.92,'2016 (13 TeV)')
    text.SetTextAlign()
    if wip:
        text.DrawLatex(0.15,0.92,'#bf{#scale[0.75]{#it{Work in Progress}}}')
    else:
        text.DrawLatex(0.15,0.92,'CMS #bf{#scale[0.75]{#it{Preliminary}}}')

def residualPlots(crossings, shapes, chiSq, dof):
    kBird()
    c = TColor(10000,0.1686,0.1333,0.4314)
    components = ('X1', 'Y1', 'X2', 'Y2')
    for shape in shapes:
        for bx in crossings:
            f = TFile.Open('DataAnalysisBunch'+bx+shape+'_new_StronRescale.root')
            if not f:
                continue
            for comp in components:
                hist = f.Get('res'+comp)
                hist.SetTitle('')
                hist.SetName(bx+shape+'_res'+comp)
                canvas = TCanvas('c_'+hist.GetName(), '', 600, 600)
                canvas.SetFrameFillColor(10000)
                hist.Draw("COLZ0")
                canvas.Update()
                hist.GetXaxis().SetTitle('x [cm]')
                hist.GetXaxis().SetLabelSize(0.025)
                hist.GetYaxis().SetTitle('y [cm]')
                hist.GetYaxis().SetLabelSize(0.025)
                hist.GetYaxis().SetTitleOffset(1.3)
                hist.GetZaxis().SetTitle('Pulls')
                hist.GetZaxis().SetLabelSize(0.025)
                hist.GetZaxis().SetTitleOffset(0.9)
                hist.GetZaxis().SetRangeUser(-5.0,5.0)
                palette = hist.GetListOfFunctions().FindObject('palette')
                palette.SetX2NDC(0.929)
                pave = TPaveText(0.65, 0.79, 0.88, 0.88, 'NDC')
                pave.SetTextFont(42)
                pave.SetTextSize(0.025)
                pave.AddText('Scan '+comp+', BX '+bx)
                pave.AddText(shapeNames[shape]+' fit')
                redChiSq = chiSq[shape][bx] / dof[shape][bx]
                pave.AddText('#chi^{2}/d.o.f. = %6.4f'%(redChiSq))
                pave.Draw('same')
                drawCMS(wip=True)
                canvas.Modified()
                canvas.Update()
                canvas.SaveAs('summaryPlots/'+canvas.GetName()+'.pdf')
                canvas.SaveAs('summaryPlots/'+canvas.GetName()+'.C')

def makeShapesCrossingsHist(crossings, shapes, name):
    kBird()
    gStyle.SetOptStat(0)
    nShapes = len(shapes)
    nCrossings = len(crossings)
    hist = TH2D(name, '', nCrossings, 0, nCrossings-1, \
                             nShapes, 0, nShapes-1)
    for i, bx in enumerate(crossings):
        hist.GetXaxis().SetBinLabel(i+1, bx)
    for j, shape in enumerate(shapes):
        hist.GetYaxis().SetBinLabel(nShapes-j, shape)
    return hist

def chiSqPlot(crossings, shapes, chiSq, dof):
    nShapes = len(shapes)
    hist = makeShapesCrossingsHist(crossings, shapes, 'chisq')
    for i, bx in enumerate(crossings):
        for j, shape in enumerate(shapes):
            if chiSq[shape][bx]:
                redChiSq = chiSq[shape][bx] / dof[shape][bx]
                hist.SetBinContent(i+1, nShapes-j, redChiSq)
    canvas = TCanvas('c_'+hist.GetName(), '', 600, 600)
    hist.Draw('TEXTCOLZ')
    canvas.Update()
    hist.GetXaxis().SetNdivisions(len(crossings), False)
    hist.GetYaxis().SetNdivisions(nShapes, False)
    hist.GetZaxis().SetTitle('#chi^{2} / d.o.f.')
    hist.GetZaxis().SetLabelSize(0.025)
    hist.GetZaxis().SetTitleOffset(0.5)
    hist.GetZaxis().SetRangeUser(1.05,1.12)
    hist.GetZaxis().CenterTitle()
    hist.GetZaxis().SetNdivisions(1, False)
    palette = hist.GetListOfFunctions().FindObject('palette')
    palette.SetX2NDC(0.929)
    drawCMS(wip=True)
    canvas.Modified()
    canvas.Update()
    canvas.SaveAs('summaryPlots/'+canvas.GetName()+'.pdf')
    canvas.SaveAs('summaryPlots/'+canvas.GetName()+'.C')

def correctionPlot(crossings, shapes, overDiff):
    nShapes = len(shapes)
    hist = makeShapesCrossingsHist(crossings, shapes, 'corrections')
    for i, bx in enumerate(crossings):
        for j, shape in enumerate(shapes):
            if overDiff[shape][bx]:
                correction = -100.0 * overDiff[shape][bx]
                hist.SetBinContent(i+1, nShapes-j, correction)
            else:
                hist.SetBinContent(i+1, nShapes-j, -1e6)
    canvas = TCanvas('c_'+hist.GetName(), '', 600, 600)
    hist.Draw('TEXTCOLZ')
    canvas.Update()
    hist.GetXaxis().SetNdivisions(len(crossings), False)
    hist.GetYaxis().SetNdivisions(nShapes, False)
    hist.GetZaxis().SetTitle('correction for XY correlations [%]')
    hist.GetZaxis().SetLabelSize(0.025)
    hist.GetZaxis().SetTitleOffset(0.5)
    hist.GetZaxis().SetRangeUser(-1.2,0.0)
    hist.GetZaxis().CenterTitle()
    hist.GetZaxis().SetNdivisions(1, False)
    palette = hist.GetListOfFunctions().FindObject('palette')
    palette.SetX2NDC(0.929)
    drawCMS(wip=True)
    canvas.Modified()
    canvas.Update()
    canvas.SaveAs('summaryPlots/'+canvas.GetName()+'.pdf')
    canvas.SaveAs('summaryPlots/'+canvas.GetName()+'.C')

def summaryPlots(crossings, shapes):
    chiSq, dof = computeChiSquares(crossings, shapes)
    #overDiff = gatherFromToys(crossings, shapes)
    #residualPlots(crossings, shapes, chiSq, dof)
    chiSqPlot(crossings, shapes, chiSq, dof)
    #correctionPlot(crossings, shapes, overDiff)

if __name__ == '__main__':
    summaryPlots(bunchcrossings, beamshapes)