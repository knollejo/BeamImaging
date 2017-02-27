#include "../../beamdensities/MyPdfV3_Ext.h"
#include "../../beamdensities/MyPdfV4_Ext.h"
#include "../../beamdensities/SingleGauss_V1.h"
#include "../../beamdensities/SingleGauss_V2.h"
#include "RooRealVar.h"
#include "TH2D.h"
#include "TFile.h"

using namespace RooFit;

void simulateSupGtoSG() {

    double scaling = 0.00458;
    int nbins = 5*19;
    gStyle->SetOptStat(0);

    RooAbsReal::defaultIntegratorConfig()->setEpsAbs(1e-7);
    RooAbsReal::defaultIntegratorConfig()->setEpsRel(1e-7);

    RooRealVar xVar("xVar","xVar",-10.0,10.0);
    RooRealVar yVar("yVar","yVar",-10.0,10.0);
    xVar.setBins(10000,"cache");
    yVar.setBins(10000,"cache");

    RooRealVar y0_1("y0_1","y0_1",-0.5,0.5);
    RooRealVar x0_1("x0_1","x0_1",-0.5,0.5);
    RooRealVar y0_2("y0_2","y0_2",-0.5,0.5);
    RooRealVar x0_2("x0_2","x0_2",-0.5,0.5);

    RooRealVar y0_12("y0_12","y0_12",-0.5,0.5);
    RooRealVar x0_12("x0_12","x0_12",-0.5,0.5);
    RooRealVar y0_22("y0_22","y0_22",-0.5,0.5);
    RooRealVar x0_22("x0_22","x0_22",-0.5,0.5);

    RooRealVar yWidthN1("yWidthN1","yWidthN1",1.3,4.0);
    RooRealVar xWidthN1("xWidthN1","xWidthN1",1.3,4.0);
    RooRealVar rho_N1("rho_N1","rho_N1",-0.48,0.48);
    RooRealVar yWidth1Diff("yWidth1Diff","yWidth1Diff",0.01,1.7);
    RooRealVar xWidth1Diff("xWidth1Diff","xWidth1Diff",0.01,1.7);
    RooFormulaVar yWidthW1("yWidthW1","yWidthN1+yWidth1Diff",RooArgSet(yWidthN1,yWidth1Diff));
    RooFormulaVar xWidthW1("xWidthW1","xWidthN1+xWidth1Diff",RooArgSet(xWidthN1,xWidth1Diff));
    RooRealVar rho_W1("rho_W1","rho_W1",-0.48,0.48);
    RooRealVar w1("w1","w1",-1.0,0.0);

    RooRealVar yWidthN2("yWidthN2","yWidthN2",1.3,4.0);
    RooRealVar xWidthN2("xWidthN2","xWidthN2",1.3,4.0);
    RooRealVar rho_N2("rho_N2","rho_N2",-0.48,0.48);
    RooRealVar yWidth2Diff("yWidth2Diff","yWidth2Diff",0.01,1.7);
    RooRealVar xWidth2Diff("xWidth2Diff","xWidth2Diff",0.01,1.7);
    RooFormulaVar yWidthW2("yWidthW2","yWidthN2+yWidth2Diff",RooArgSet(yWidthN2,yWidth2Diff));
    RooFormulaVar xWidthW2("xWidthW2","xWidthN2+xWidth2Diff",RooArgSet(xWidthN2,xWidth2Diff));
    RooRealVar rho_W2("rho_W2","rho_W2",-0.48,0.48);
    RooRealVar w2("w2","w2",-1.0,0.0);

    RooRealVar vtxRes("vtxRes","vtxRes",0.00356/scaling);
    vtxRes.setConstant();

    xWidthN1.setVal(2.0);
    yWidthN1.setVal(2.0);
    rho_N1.setVal(0.0);
    xWidth1Diff.setVal(0.4);
    yWidth1Diff.setVal(0.4);
    rho_W1.setVal(0.0);
    w1.setVal(-1.0);

    xWidthN2.setVal(2.0);
    yWidthN2.setVal(2.0);
    rho_N2.setVal(0.0);
    xWidth2Diff.setVal(0.4);
    yWidth2Diff.setVal(0.4);
    rho_W2.setVal(0.0);
    w2.setVal(-1.0);

    MyPdfV3_Ext beam1RestVerticesUnfold_XScan_SupG("beam1RestVerticesUnfold_Xscan_SupG","beam1RestVerticesUnfold_Xscan_SupG",xVar,yVar,x0_1,y0_1,w1,rho_N1,xWidthN1,yWidthN1,rho_W1,xWidthW1,yWidthW1,w2,yWidthN2,yWidthW2,vtxRes);
    MyPdfV4_Ext beam1RestVerticesUnfold_YScan_SupG("beam1RestVerticesUnfold_Yscan_SupG","beam1RestVerticesUnfold_Yscan_SupG",xVar,yVar,x0_2,y0_2,w1,rho_N1,xWidthN1,yWidthN1,rho_W1,xWidthW1,yWidthW1,w2,xWidthN2,xWidthW2,vtxRes);
    MyPdfV3_Ext beam2RestVerticesUnfold_XScan_SupG("beam2RestVerticesUnfold_Xscan_SupG","beam2RestVerticesUnfold_Xscan_SupG",xVar,yVar,x0_12,y0_12,w2,rho_N2,xWidthN2,yWidthN2,rho_W2,xWidthW2,yWidthW2,w1,yWidthN1,yWidthW1,vtxRes);
    MyPdfV4_Ext beam2RestVerticesUnfold_YScan_SupG("beam2RestVerticesUnfold_Yscan_SupG","beam2RestVerticesUnfold_Yscan_SupG",xVar,yVar,x0_22,y0_22,w2,rho_N2,xWidthN2,yWidthN2,rho_W2,xWidthW2,yWidthW2,w1,xWidthN1,xWidthW1,vtxRes);

    RooDataSet* simulatedSupGX1 = beam1RestVerticesUnfold_XScan_SupG.generate(RooArgSet(xVar,yVar),1000000);
    RooDataSet* simulatedSupGY1 = beam1RestVerticesUnfold_YScan_SupG.generate(RooArgSet(xVar,yVar),1000000);
    RooDataSet* simulatedSupGX2 = beam2RestVerticesUnfold_XScan_SupG.generate(RooArgSet(xVar,yVar),1000000);
    RooDataSet* simulatedSupGY2 = beam2RestVerticesUnfold_YScan_SupG.generate(RooArgSet(xVar,yVar),1000000);

    TH2D* hmodelSupGX1 = (TH2D*)simulatedSupGX1->createHistogram("hmodelSupGX1",xVar,Binning(nbins),YVar(yVar,Binning(nbins)));
    TH2D* hmodelSupGY1 = (TH2D*)simulatedSupGY1->createHistogram("hmodelSupGY1",xVar,Binning(nbins),YVar(yVar,Binning(nbins)));
    TH2D* hmodelSupGX2 = (TH2D*)simulatedSupGX2->createHistogram("hmodelSupGX2",xVar,Binning(nbins),YVar(yVar,Binning(nbins)));
    TH2D* hmodelSupGY2 = (TH2D*)simulatedSupGY2->createHistogram("hmodelSupGY2",xVar,Binning(nbins),YVar(yVar,Binning(nbins)));

    xWidthN1.setVal(2.15);
    yWidthN1.setVal(2.15);
    rho_N1.setVal(0.0);
    xWidthN2.setVal(2.15);
    yWidthN2.setVal(2.15);
    rho_N2.setVal(0.0);

    SingleGauss_V1 beam1RestVerticesUnfold_XScan_SG("beam1RestVerticesUnfold_Xscan_SG","beam1RestVerticesUnfold_Xscan_SG",xVar,yVar,x0_1,y0_1,rho_N1,xWidthN1,yWidthN1,yWidthN2,vtxRes);
    SingleGauss_V2 beam1RestVerticesUnfold_YScan_SG("beam1RestVerticesUnfold_Yscan_SG","beam1RestVerticesUnfold_Yscan_SG",xVar,yVar,x0_2,y0_2,rho_N1,xWidthN1,yWidthN1,xWidthN2,vtxRes);
    SingleGauss_V1 beam2RestVerticesUnfold_XScan_SG("beam2RestVerticesUnfold_Xscan_SG","beam2RestVerticesUnfold_Xscan_SG",xVar,yVar,x0_12,y0_12,rho_N2,xWidthN2,yWidthN2,yWidthN1,vtxRes);
    SingleGauss_V2 beam2RestVerticesUnfold_YScan_SG("beam2RestVerticesUnfold_Yscan_SG","beam2RestVerticesUnfold_Yscan_SG",xVar,yVar,x0_22,y0_22,rho_N2,xWidthN2,yWidthN2,xWidthN1,vtxRes);

    RooDataHist *scanXBeam1RestDataHist = new RooDataHist("scanXBeam1RestDataHist","scanXBeam1RestDataHist",RooArgList(xVar,yVar),hmodelSupGX1);
    RooDataHist *scanYBeam1RestDataHist = new RooDataHist("scanYBeam1RestDataHist","scanYBeam1RestDataHist",RooArgList(xVar,yVar),hmodelSupGX1);
    RooDataHist *scanXBeam2RestDataHist = new RooDataHist("scanXBeam2RestDataHist","scanXBeam2RestDataHist",RooArgList(xVar,yVar),hmodelSupGX1);
    RooDataHist *scanYBeam2RestDataHist = new RooDataHist("scanYBeam2RestDataHist","scanYBeam2RestDataHist",RooArgList(xVar,yVar),hmodelSupGX1);

    RooCategory sample("sample","sample");
    sample.defineType("X_ScanData_Beam1Rest");
    sample.defineType("Y_ScanData_Beam1Rest");
    sample.defineType("X_ScanData_Beam2Rest");
    sample.defineType("Y_ScanData_Beam2Rest");
    RooDataHist combData("combData","combined data",RooArgSet(xVar,yVar),Index(sample),Import("X_ScanData_Beam1Rest",*scanXBeam1RestDataHist),Import("Y_ScanData_Beam1Rest",*scanYBeam1RestDataHist),Import("X_ScanData_Beam2Rest",*scanXBeam2RestDataHist),Import("Y_ScanData_Beam2Rest",*scanYBeam2RestDataHist));

    RooSimultaneous simPdf("simPdf","simultaneous pdf",sample) ;
    simPdf.addPdf(beam1RestVerticesUnfold_XScan_SG,"X_ScanData_Beam1Rest");
    simPdf.addPdf(beam1RestVerticesUnfold_YScan_SG,"Y_ScanData_Beam1Rest");
    simPdf.addPdf(beam2RestVerticesUnfold_XScan_SG,"X_ScanData_Beam2Rest");
    simPdf.addPdf(beam2RestVerticesUnfold_YScan_SG,"Y_ScanData_Beam2Rest");

    RooFitResult* r= simPdf.fitTo(combData,RooFit::PrintLevel(3),RooFit::Verbose(1),RooFit::Save());

    TH2D* hfitSGX1 = (TH2D*)beam1RestVerticesUnfold_XScan_SG.createHistogram("hfitSGX1",xVar,Binning(nbins),YVar(yVar,Binning(nbins)));
    TH2D* hfitSGY1 = (TH2D*)beam1RestVerticesUnfold_YScan_SG.createHistogram("hfitSGY1",xVar,Binning(nbins),YVar(yVar,Binning(nbins)));
    TH2D* hfitSGX2 = (TH2D*)beam2RestVerticesUnfold_XScan_SG.createHistogram("hfitSGX2",xVar,Binning(nbins),YVar(yVar,Binning(nbins)));
    TH2D* hfitSGY2 = (TH2D*)beam2RestVerticesUnfold_YScan_SG.createHistogram("hfitSGY2",xVar,Binning(nbins),YVar(yVar,Binning(nbins)));

    hfitSGX1->Scale(hmodelSupGX1->Integral());
    hfitSGY1->Scale(hmodelSupGY1->Integral());
    hfitSGX2->Scale(hmodelSupGX2->Integral());
    hfitSGY2->Scale(hmodelSupGY2->Integral());

    TH2D* resX1 = new TH2D("BeamImageX1","BeamImageX1",nbins,-10*scaling,10*scaling,nbins,-10*scaling,10*scaling);
    TH2D* resY1 = new TH2D("BeamImageY1","BeamImageY1",nbins,-10*scaling,10*scaling,nbins,-10*scaling,10*scaling);
    TH2D* resX2 = new TH2D("BeamImageX2","BeamImageX2",nbins,-10*scaling,10*scaling,nbins,-10*scaling,10*scaling);
    TH2D* resY2 = new TH2D("BeamImageY2","BeamImageY2",nbins,-10*scaling,10*scaling,nbins,-10*scaling,10*scaling);

    TH2D* dataHistX1 = new TH2D("dataHistX1","dataHistX1",nbins,-10*scaling,10*scaling,nbins,-10*scaling,10*scaling);
    TH2D* dataHistY1 = new TH2D("dataHistY1","dataHistY1",nbins,-10*scaling,10*scaling,nbins,-10*scaling,10*scaling);
    TH2D* dataHistX2 = new TH2D("dataHistX2","dataHistX2",nbins,-10*scaling,10*scaling,nbins,-10*scaling,10*scaling);
    TH2D* dataHistY2 = new TH2D("dataHistY2","dataHistY2",nbins,-10*scaling,10*scaling,nbins,-10*scaling,10*scaling);

    TH2D* modelHistX1 = new TH2D("modelHistX1","modelHistX1",nbins,-10*scaling,10*scaling,nbins,-10*scaling,10*scaling);
    TH2D* modelHistY1 = new TH2D("modelHistY1","modelHistY1",nbins,-10*scaling,10*scaling,nbins,-10*scaling,10*scaling);
    TH2D* modelHistX2 = new TH2D("modelHistX2","modelHistX2",nbins,-10*scaling,10*scaling,nbins,-10*scaling,10*scaling);
    TH2D* modelHistY2 = new TH2D("modelHistY2","modelHistY2",nbins,-10*scaling,10*scaling,nbins,-10*scaling,10*scaling);

    for(int xs=0; xs<hmodelSupGX1->GetXaxis()->GetNbins(); xs++) {
        for(int ys=0; ys<hmodelSupGX1->GetYaxis()->GetNbins(); ys++) {
            if(true || (hmodelSupGX1->GetBinError(xs,ys)>0. && hmodelSupGX1->GetBinContent(xs,ys)>0.)) {
                double valDiffX1;
                double statErrX1;
                dataHistX1->SetBinContent(xs,ys,hmodelSupGX1->GetBinContent(xs,ys));
                modelHistX1->SetBinContent(xs,ys,hfitSGX1->GetBinContent(xs,ys));
                valDiffX1 = dataHistX1->GetBinContent(xs,ys) - modelHistX1->GetBinContent(xs,ys);
                statErrX1 = dataHistX1->GetBinError(xs,ys);
                resX1->SetBinContent(xs,ys,valDiffX1/statErrX1);
            }
            if(true || (hmodelSupGY1->GetBinError(xs,ys)>0. &&  hmodelSupGY1->GetBinContent(xs,ys)>0.)) {
                double valDiffY1;
                double statErrY1;
                dataHistY1->SetBinContent(xs,ys,hmodelSupGY1->GetBinContent(xs,ys));
                modelHistY1->SetBinContent(xs,ys,hfitSGY1->GetBinContent(xs,ys));
                valDiffY1 = dataHistY1->GetBinContent(xs,ys) - modelHistY1->GetBinContent(xs,ys);
                statErrY1 = dataHistY1->GetBinError(xs,ys);
                resY1->SetBinContent(xs,ys,valDiffY1/statErrY1);
            }
            if(true || (hmodelSupGX2->GetBinError(xs,ys)>0. &&  hmodelSupGX2->GetBinContent(xs,ys)>0.)) {
                double valDiffX2;
                double statErrX2;
                dataHistX2->SetBinContent(xs,ys,hmodelSupGX2->GetBinContent(xs,ys));
                modelHistX2->SetBinContent(xs,ys,hfitSGX2->GetBinContent(xs,ys));
                valDiffX2 = dataHistX2->GetBinContent(xs,ys) - modelHistX2->GetBinContent(xs,ys);
                statErrX2 = dataHistX2->GetBinError(xs,ys);
                resX2->SetBinContent(xs,ys,valDiffX2/statErrX2);
            }
            if(true || (hmodelSupGY2->GetBinError(xs,ys)>0. &&  hmodelSupGY2->GetBinContent(xs,ys)>0.)) {
                double valDiffY2;
            	double statErrY2;
                dataHistY2->SetBinContent(xs,ys,hmodelSupGY2->GetBinContent(xs,ys));
                modelHistY2->SetBinContent(xs,ys,hfitSGY2->GetBinContent(xs,ys));
                valDiffY2 = dataHistY2->GetBinContent(xs,ys) - modelHistY2->GetBinContent(xs,ys);
                statErrY2 = dataHistY2->GetBinError(xs,ys);
                resY2->SetBinContent(xs,ys,valDiffY2/statErrY2);
            }
        }
    }

    resX1->SetOption("Colz");
    resY1->SetOption("Colz");
    resX2->SetOption("Colz");
    resY2->SetOption("Colz");
    resX1->SetTitle("Beam Image X1");
    resY1->SetTitle("Beam Image Y1");
    resX2->SetTitle("Beam Image X2");
    resY2->SetTitle("Beam Image Y2");

    resX1->GetXaxis()->SetTitle("[cm]");
    resX1->GetYaxis()->SetTitle("[cm]");
    resX2->GetXaxis()->SetTitle("[cm]");
    resX2->GetYaxis()->SetTitle("[cm]");

    resY1->GetXaxis()->SetTitle("[cm]");
    resY1->GetYaxis()->SetTitle("[cm]");
    resY2->GetXaxis()->SetTitle("[cm]");
    resY2->GetYaxis()->SetTitle("[cm]");

    TFile *fAna = new TFile("SimulatedSuperGaussInterpretedSingleGauss.root","recreate");

    resX1->Write("resX1");
    resY1->Write("resY1");
    resX2->Write("resX2");
    resY2->Write("resY2");

    dataHistX1->Write("dataHistX1");
    dataHistY1->Write("dataHistY1");
    dataHistX2->Write("dataHistX2");
    dataHistY2->Write("dataHistY2");

    modelHistX1->Write("modelHistX1");
    modelHistY1->Write("modelHistY1");
    modelHistX2->Write("modelHistX2");
    modelHistY2->Write("modelHistY2");

    fAna->Write();

}
