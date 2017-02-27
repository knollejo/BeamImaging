#include "../../beamdensities/MyPdfV3_Ext.h"
#include "../../beamdensities/MyPdfV4_Ext.h"
#include "RooRealVar.h"
#include "TH2D.h"
#include "TFile.h"

using namespace RooFit;

void createBeamImage_SupG() {

    double scaling = 0.00458;
    int nbins = 5*19;

    RooRealVar xVar("xVar","xVar",-10.0,10.0);
    RooRealVar yVar("yVar","yVar",-10.0,10.0);
    xVar.setBins(10000,"cache");
    yVar.setBins(10000,"cache");

    RooRealVar y0_1("y0_1","y0_1",0.0);
    RooRealVar x0_1("x0_1","x0_1",0.0);
    RooRealVar y0_2("y0_2","y0_2",0.0);
    RooRealVar x0_2("x0_2","x0_2",0.0);

    RooRealVar y0_12("y0_12","y0_12",0.0);
    RooRealVar x0_12("x0_12","x0_12",0.0);
    RooRealVar y0_22("y0_22","y0_22",0.0);
    RooRealVar x0_22("x0_22","x0_22",0.0);

    RooRealVar yWidthN1("yWidthN1","yWidthN1",1.3,3.0);
    RooRealVar xWidthN1("xWidthN1","xWidthN1",1.3,3.0);
    RooRealVar rho_N1("rho_N1","rho_N1",-0.48,0.48);
    RooRealVar yWidth1Diff("yWidth1Diff","yWidth1Diff",0.01,1.7);
    RooRealVar xWidth1Diff("xWidth1Diff","xWidth1Diff",0.01,1.7);
    RooFormulaVar yWidthW1("yWidthW1","yWidthN1+yWidth1Diff",RooArgSet(yWidthN1,yWidth1Diff));
    RooFormulaVar xWidthW1("xWidthW1","xWidthN1+xWidth1Diff",RooArgSet(xWidthN1,xWidth1Diff));
    RooRealVar rho_W1("rho_W1","rho_W1",-0.48,0.48);
    RooRealVar w1("w1","w1",-1.0,0.0);

    RooRealVar yWidthN2("yWidthN2","yWidthN2",1.3,3.0);
    RooRealVar xWidthN2("xWidthN2","xWidthN2",1.3,3.0);
    RooRealVar rho_N2("rho_N2","rho_N2",-0.48,0.48);
    RooRealVar yWidth2Diff("yWidth2Diff","yWidth2Diff",0.01,1.7);
    RooRealVar xWidth2Diff("xWidth2Diff","xWidth2Diff",0.01,1.7);
    RooFormulaVar yWidthW2("yWidthW2","yWidthN2+yWidth2Diff",RooArgSet(yWidthN2,yWidth2Diff));
    RooFormulaVar xWidthW2("xWidthW2","xWidthN2+xWidth2Diff",RooArgSet(xWidthN2,xWidth2Diff));
    RooRealVar rho_W2("rho_W2","rho_W2",-0.48,0.48);
    RooRealVar w2("w2","w2",-1.0,0.0);

    RooRealVar vtxRes("vtxRes","vtxRes",0.00356/scaling);

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

    MyPdfV3_Ext beam1RestVerticesUnfold_XScan("beam1RestVerticesUnfold_Xscan","beam1RestVerticesUnfold_Xscan",xVar,yVar,x0_1,y0_1,w1,rho_N1,xWidthN1,yWidthN1,rho_W1,xWidthW1,yWidthW1,w2,yWidthN2,yWidthW2,vtxRes);
    MyPdfV4_Ext beam1RestVerticesUnfold_YScan("beam1RestVerticesUnfold_Yscan","beam1RestVerticesUnfold_Yscan",xVar,yVar,x0_2,y0_2,w1,rho_N1,xWidthN1,yWidthN1,rho_W1,xWidthW1,yWidthW1,w2,xWidthN2,xWidthW2,vtxRes);
    MyPdfV3_Ext beam2RestVerticesUnfold_XScan("beam2RestVerticesUnfold_Xscan","beam2RestVerticesUnfold_Xscan",xVar,yVar,x0_12,y0_12,w2,rho_N2,xWidthN2,yWidthN2,rho_W2,xWidthW2,yWidthW2,w1,yWidthN1,yWidthW1,vtxRes);
    MyPdfV4_Ext beam2RestVerticesUnfold_YScan("beam2RestVerticesUnfold_Yscan","beam2RestVerticesUnfold_Yscan",xVar,yVar,x0_22,y0_22,w2,rho_N2,xWidthN2,yWidthN2,rho_W2,xWidthW2,yWidthW2,w1,xWidthN1,xWidthW1,vtxRes);

    TH2D* hmodelX1 = (TH2D*)beam1RestVerticesUnfold_XScan.createHistogram("hmodelX1",xVar,Binning(nbins),YVar(yVar,Binning(nbins)));
    TH2D* hmodelY1 = (TH2D*)beam1RestVerticesUnfold_YScan.createHistogram("hmodelY1",xVar,Binning(nbins),YVar(yVar,Binning(nbins)));
    TH2D* hmodelX2 = (TH2D*)beam2RestVerticesUnfold_XScan.createHistogram("hmodelX2",xVar,Binning(nbins),YVar(yVar,Binning(nbins)));
    TH2D* hmodelY2 = (TH2D*)beam2RestVerticesUnfold_YScan.createHistogram("hmodelY2",xVar,Binning(nbins),YVar(yVar,Binning(nbins)));

    TH2D* modelHistX1 = new TH2D("modelHistX1","modelHistX1",nbins,-10*scaling,10*scaling,nbins,-10*scaling,10*scaling);
    TH2D* modelHistY1 = new TH2D("modelHistY1","modelHistY1",nbins,-10*scaling,10*scaling,nbins,-10*scaling,10*scaling);
    TH2D* modelHistX2 = new TH2D("modelHistX2","modelHistX2",nbins,-10*scaling,10*scaling,nbins,-10*scaling,10*scaling);
    TH2D* modelHistY2 = new TH2D("modelHistY2","modelHistY2",nbins,-10*scaling,10*scaling,nbins,-10*scaling,10*scaling);

    for(int xs=0; xs<hmodelX1->GetXaxis()->GetNbins(); xs++) {
        for(int ys=0; ys<hmodelX1->GetYaxis()->GetNbins(); ys++) {
            modelHistX1->SetBinContent(xs,ys,hmodelX1->GetBinContent(xs,ys));
            modelHistY1->SetBinContent(xs,ys,hmodelY1->GetBinContent(xs,ys));
            modelHistX2->SetBinContent(xs,ys,hmodelX2->GetBinContent(xs,ys));
            modelHistY2->SetBinContent(xs,ys,hmodelY2->GetBinContent(xs,ys));
        }
    }

    modelHistX1->SetOption("Colz");
    modelHistY1->SetOption("Colz");
    modelHistX2->SetOption("Colz");
    modelHistY2->SetOption("Colz");

    modelHistX1->SetTitle("Beam Image X1");
    modelHistY1->SetTitle("Beam Image Y1");
    modelHistX2->SetTitle("Beam Image X2");
    modelHistY2->SetTitle("Beam Image Y2");

    modelHistX1->GetXaxis()->SetTitle("[cm]");
    modelHistX1->GetYaxis()->SetTitle("[cm]");
    modelHistX2->GetXaxis()->SetTitle("[cm]");
    modelHistX2->GetYaxis()->SetTitle("[cm]");

    modelHistY1->GetXaxis()->SetTitle("[cm]");
    modelHistY1->GetYaxis()->SetTitle("[cm]");
    modelHistY2->GetXaxis()->SetTitle("[cm]");
    modelHistY2->GetYaxis()->SetTitle("[cm]");

    TFile * output = new TFile("SimulatedBeamImage_SupG.root","recreate");

    modelHistX1->Write("modelHistX1");
    modelHistY1->Write("modelHistY1");
    modelHistX2->Write("modelHistX2");
    modelHistY2->Write("modelHistY2");

    output->Write();

}
