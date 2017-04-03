from ROOT import gSystem, gStyle, TFile, RooAbsReal, RooDataHist, RooArgList, \
                 RooCategory, RooSimultaneous, RooArgSet, RooFit, TH1F, TH2D, \
                 TRandom3

def writeToHist(num, label):
    hist = TH1F('h_'+label, label, 100, num-1.0, num+1.0)
    hist.Fill(num)
    return hist

def shapeFitter(model, bcid, datafile, prefix, suffix, vtxres, scaling):
    for template in model.Templates:
        gSystem.Load('../../beamdensities/'+template+'.so')
    gStyle.SetOptStat(0)
    name = prefix + '_' + model.Shortname + '_' + bcid + '_' + suffix

    ic = [('1','X'),('1','Y'),('2','X'),('2','Y')]

    f = TFile.Open(datafile)
    beamImagingHist = [f.Get('Beam'+i+'Move'+c+'_bunch'+bcid+'Add') for (i,c) \
                       in [('2', 'X'), ('2', 'Y'), ('1', 'X'), ('1', 'Y')]]
    RooAbsReal.defaultIntegratorConfig().setEpsAbs(1.0e-7)
    RooAbsReal.defaultIntegratorConfig().setEpsRel(1.0e-7)
    model.setVertexResolution(vtxres / scaling)
    modelFunctions = model.getModelFunctions()
    dataHist = [RooDataHist('scan'+c+'Beam'+i+'RestDataHist', 'scan'+c+'Beam' \
                +i+'RestDataHist', RooArgList(model.xVar(), model.yVar()), \
                beamImagingHist[j]) for j, (i,c) in enumerate(ic)]
    sample = RooCategory('sample', 'sample')
    for (i,c) in ic:
        sample.defineType(c+'_ScanData_Beam'+i+'Rest')
    combData = RooDataHist('combData', 'combined data', \
               RooArgList(model.xVar(), model.yVar()), RooFit.Index(sample), \
               RooFit.Import('X_ScanData_Beam1Rest', dataHist[0]), \
               RooFit.Import('Y_ScanData_Beam1Rest', dataHist[1]), \
               RooFit.Import('X_ScanData_Beam2Rest', dataHist[2]), \
               RooFit.Import('Y_ScanData_Beam2Rest', dataHist[3]))
    simPdf = RooSimultaneous('simPdf', 'simultaneous pdf', sample)
    for j, (i,c) in enumerate(ic):
        simPdf.addPdf(modelFunctions[j], c+'_ScanData_Beam'+i+'Rest')
    result = simPdf.fitTo(combData, RooFit.PrintLevel(3), RooFit.Verbose(1), \
                          RooFit.Save())

    multBeam = model.funcOverlap()
    listOfHists = []
    for par in model.Parameter:
        val = model.computeValue(par)
        err = model.computeValue(par)
        if not val or not err:
            continue
        for (num, label) in [(val, ''), (err, '_error')]:
            listOfHists.append(writeToHist(num, par+label))
    listOfHists.append(writeToHist(multBeam.Integral(-30, 30, -30, 30), \
                       'overlapInt'))
    try:
        integ = TH1F('h_integ', 'Overlap Distribution', 1000, 0.0, 1.0)
        rand = TRandom3()
        rand.SetSeed(0)
        for k in range(1000):
            multBeam = model.assignToOverlap(multBeam, random=rand)
            val = multBeam.Integral(-30, 30, -30, 30)
            print val
            integ.Fill(val)
        listOfHists.append(integ)
    except:
        print 'Error in random variations'

    nbins = 5 * 19
    hmodel = [modelFunctions[j].createHistogram('hmodel'+c+i, \
              model.xVar(), RooFit.Binning(nbins), RooFit.YVar(model.yVar(), \
              RooFit.Binning(nbins))) for j, (i,c) in enumerate(ic)]
    hdata = [dataHist[j].createHistogram('hdata'+c+i, model.xVar(), \
             RooFit.Binning(nbins), RooFit.YVar(model.yVar(), \
             RooFit.Binning(nbins))) for j, (i,c) in enumerate(ic)]
    scRes = [TH2D('BeamImage'+c+i, 'BeamImage'+c+i, nbins, -10*scaling, \
             10*scaling, nbins, -10*scaling, 10*scaling) for i,c in ic]
    scDat = [TH2D('dataHist'+c+i, 'dataHist'+c+i, nbins, -10*scaling, \
             10*scaling, nbins, -10*scaling, 10*scaling) for i,c in ic]
    scMod = [TH2D('modelHist'+c+i, 'modelHist'+c+i, nbins, -10*scaling, \
             10*scaling, nbins, -10*scaling, 10*scaling) for i,c in ic]
    for i in range(len(hdata)):
        chi2 = 0.0
        dof = 0
        hmodel[i].Scale(hdata[i].Integral())
        for j in range(hdata[i].GetXaxis().GetNbins()):
            for k in range(hdata[i].GetYaxis().GetNbins()):
                valDat = hdata[i].GetBinContent(j, k)
                errDat = hdata[i].GetBinError(j, k)
                if errDat > 0.0 and valDat > 0.0:
                    valMod = hmodel[i].GetBinContent(j, k)
                    scDat[i].SetBinContent(j, k, valDat)
                    scMod[i].SetBinContent(j, k, valMod)
                    valDiff = valDat - valMod
                    scRes[i].SetBinContent(j, k, valDiff / errDat)
                    dof += 1
                    chi2 += (valDiff / errDat) ** 2
        n, c = ic[i]
        listOfHists.append(writeToHist(chi2, 'chi2'+c+n))
        listOfHists.append(writeToHist(dof, 'dof'+c+n))
        print 'chi2 '+c+n+':', chi2
        print 'dof '+c+n+':', dof
    for hist in hmodel + hdata + scRes + scDat + scMod:
        listOfHists.append(hist)

    outputfile = TFile(name+'.root', 'RECREATE')
    for hist in listOfHists:
        hist.Write()
    result.Write('fitResult')
    outputfile.Write()
    outputfile.Close()
