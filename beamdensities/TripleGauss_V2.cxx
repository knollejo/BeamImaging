/*****************************************************************************
 * Project: RooFit                                                           *
 *                                                                           *
 * This code was autogenerated by RooClassFactory                            *
 *****************************************************************************/

// Your description goes here...

#include "Riostream.h"

#include "TripleGauss_V2.h"
#include "RooAbsReal.h"
#include "RooAbsCategory.h"
#include <math.h>
#include "TMath.h"
#include "TMatrix.h"
ClassImp(TripleGauss_V2)

 TripleGauss_V2::TripleGauss_V2(const char *name, const char *title,
             RooAbsReal& _xVar,
             RooAbsReal& _yVar,
             RooAbsReal& _x0,
             RooAbsReal& _y0,
             RooAbsReal& _theta1,
             RooAbsReal& _phi1,
             RooAbsReal& _rho_N1,
             RooAbsReal& _xWidthN1,
             RooAbsReal& _yWidthN1,
             RooAbsReal& _rho_M1,
             RooAbsReal& _xWidthM1,
             RooAbsReal& _yWidthM1,
             RooAbsReal& _rho_W1,
             RooAbsReal& _xWidthW1,
             RooAbsReal& _yWidthW1,
             RooAbsReal& _theta2,
             RooAbsReal& _phi2,
             RooAbsReal& _yWidthN2,
             RooAbsReal& _yWidthM2,
             RooAbsReal& _yWidthW2,
             RooAbsReal& _vtxRes):
    RooAbsPdf(name,title),
    xVar ("xVar","xVar",this,_xVar),
    yVar ("yVar","yVar",this,_yVar),
    x0 ("x0","x0",this,_x0),
    y0 ("y0","y0",this,_y0),
    theta1 ("theta1","theta1",this,_theta1),
    phi1 ("phi1","phi1",this,_phi1),
    rho_N1 ("rho_N1","rho_N1",this,_rho_N1),
    xWidthN1 ("xWidthN1","xWidthN1",this,_xWidthN1),
    yWidthN1 ("yWidthN1","yWidthN1",this,_yWidthN1),
    rho_M1 ("rho_M1","rho_M1",this,_rho_M1),
    xWidthM1 ("xWidthM1","xWidthM1",this,_xWidthM1),
    yWidthM1 ("yWidthM1","yWidthM1",this,_yWidthM1),
    rho_W1 ("rho_W1","rho_W1",this,_rho_W1),
    xWidthW1 ("xWidthW1","xWidthW1",this,_xWidthW1),
    yWidthW1 ("yWidthW1","yWidthW1",this,_yWidthW1),
    theta2 ("theta2","theta2",this,_theta2),
    phi2 ("phi2","phi2",this,_phi2),
    yWidthN2 ("yWidthN2","yWidthN2",this,_yWidthN2),
    yWidthM2 ("yWidthM2","yWidthM2",this,_yWidthM2),
    yWidthW2 ("yWidthW2","yWidthW2",this,_yWidthW2),
    vtxRes ("vtxRes","vtxRes",this,_vtxRes)
 {
 }


 TripleGauss_V2::TripleGauss_V2(const TripleGauss_V2& other, const char* name) :
    RooAbsPdf(other,name),
    xVar("xVar",this,other.xVar),
    yVar("yVar",this,other.yVar),
    x0("x0",this,other.x0),
    y0("y0",this,other.y0),
    theta1("theta1",this,other.theta1),
    phi1("phi1",this,other.phi1),
    rho_N1("rho_N1",this,other.rho_N1),
    xWidthN1("xWidthN1",this,other.xWidthN1),
    yWidthN1("yWidthN1",this,other.yWidthN1),
    rho_M1("rho_M1",this,other.rho_M1),
    xWidthM1("xWidthM1",this,other.xWidthM1),
    yWidthM1("yWidthM1",this,other.yWidthM1),
    rho_W1("rho_W1",this,other.rho_W1),
    xWidthW1("xWidthW1",this,other.xWidthW1),
    yWidthW1("yWidthW1",this,other.yWidthW1),
    theta2("theta2",this,other.theta2),
    phi2("phi2",this,other.phi2),
    yWidthN2("yWidthN2",this,other.yWidthN2),
    yWidthM2("yWidthM2",this,other.yWidthM2),
    yWidthW2("yWidthW2",this,other.yWidthW2),
    vtxRes("vtxRes",this,other.vtxRes)
 {
 }



 Double_t TripleGauss_V2::evaluate() const
 {
   // ENTER EXPRESSION IN TERMS OF VARIABLE ARGUMENTS HERE

   double wN1 = sin(theta1)*sin(theta1)*cos(phi1)*cos(phi1);
   double wM1 = sin(theta1)*sin(theta1)*sin(phi1)*sin(phi1);
   double wW1 = cos(theta1)*cos(theta1);
   double wN2 = sin(theta2)*sin(theta2)*cos(phi2)*cos(phi2);
   double wM2 = sin(theta2)*sin(theta2)*sin(phi2)*sin(phi2);
   double wW2 = cos(theta2)*cos(theta2);

   TMatrix beamN1(2,2);
   beamN1(0,0) = TMath::Power(xWidthN1,2.0);
   beamN1(1,1) = TMath::Power(yWidthN1,2.0);
   beamN1(1,0) = rho_N1*xWidthN1*yWidthN1;
   beamN1(0,1) = rho_N1*xWidthN1*yWidthN1;
   TMatrix beamM1(2,2);
   beamN1(0,0) = TMath::Power(xWidthM1,2.0);
   beamN1(1,1) = TMath::Power(yWidthM1,2.0);
   beamN1(1,0) = rho_M1*xWidthM1*yWidthM1;
   beamN1(0,1) = rho_M1*xWidthM1*yWidthM1;
   TMatrix beamW1(2,2);
   beamW1(0,0) = TMath::Power(xWidthW1,2.0);
   beamW1(1,1) = TMath::Power(yWidthW1,2.0);
   beamW1(1,0) = rho_W1*xWidthW1*yWidthW1;
   beamW1(0,1) = rho_W1*xWidthW1*yWidthW1;
   TMatrix beamN1_Inv(TMatrix::kInverted,beamN1);
   TMatrix beamM1_Inv(TMatrix::kInverted,beamM1);
   TMatrix beamW1_Inv(TMatrix::kInverted,beamW1);
   TMatrix beamN2MargInv(2,2);
   beamN2MargInv(0,0) = 1./TMath::Power(yWidthN2,2.0);
   beamN2MargInv(1,1) = 0.;
   beamN2MargInv(0,1) = 0.;
   beamN2MargInv(1,0) = 0.;
   TMatrix beamM2MargInv(2,2);
   beamN2MargInv(0,0) = 1./TMath::Power(yWidthM2,2.0);
   beamN2MargInv(1,1) = 0.;
   beamN2MargInv(0,1) = 0.;
   beamN2MargInv(1,0) = 0.;
   TMatrix beamW2MargInv(2,2);
   beamW2MargInv(0,0) = 1./TMath::Power(yWidthW2,2.0);
   beamW2MargInv(1,1) = 0.;
   beamW2MargInv(0,1) = 0.;
   beamW2MargInv(1,0) = 0.;
   TMatrix vtxResSq(2,2);
   vtxResSq(0,0) = TMath::Power(vtxRes,2.0);
   vtxResSq(1,1) = TMath::Power(vtxRes,2.0);
   vtxResSq(0,1) = 0.;
   vtxResSq(1,0) = 0.;
   TMatrix sigmaN1N2FinalInv(2,2);
   TMatrix sigmaN1M2FinalInv(2,2);
   TMatrix sigmaN1W2FinalInv(2,2);
   TMatrix sigmaM1N2FinalInv(2,2);
   TMatrix sigmaM1M2FinalInv(2,2);
   TMatrix sigmaM1W2FinalInv(2,2);
   TMatrix sigmaW1N2FinalInv(2,2);
   TMatrix sigmaW1M2FinalInv(2,2);
   TMatrix sigmaW1W2FinalInv(2,2);
   sigmaN1N2FinalInv = ((beamN1_Inv+beamN2MargInv).Invert()+vtxResSq).Invert();
   sigmaN1M2FinalInv = ((beamN1_Inv+beamM2MargInv).Invert()+vtxResSq).Invert();
   sigmaN1W2FinalInv = ((beamN1_Inv+beamW2MargInv).Invert()+vtxResSq).Invert();
   sigmaM1N2FinalInv = ((beamM1_Inv+beamN2MargInv).Invert()+vtxResSq).Invert();
   sigmaM1M2FinalInv = ((beamM1_Inv+beamM2MargInv).Invert()+vtxResSq).Invert();
   sigmaM1W2FinalInv = ((beamM1_Inv+beamW2MargInv).Invert()+vtxResSq).Invert();
   sigmaW1N2FinalInv = ((beamW1_Inv+beamN2MargInv).Invert()+vtxResSq).Invert();
   sigmaW1M2FinalInv = ((beamW1_Inv+beamM2MargInv).Invert()+vtxResSq).Invert();
   sigmaW1W2FinalInv = ((beamW1_Inv+beamW2MargInv).Invert()+vtxResSq).Invert();

   fitFuncN1N2->SetParameter(0,sigmaN1N2FinalInv(0,0));
   fitFuncN1N2->SetParameter(1,sigmaN1N2FinalInv(1,1));
   fitFuncN1N2->SetParameter(2,sigmaN1N2FinalInv(1,0));
   fitFuncN1N2->SetParameter(3,(sigmaN1N2FinalInv.Invert()).Determinant());
   fitFuncN1N2->SetParameter(4,wN1*wN2);

   fitFuncN1M2->SetParameter(0,sigmaN1M2FinalInv(0,0));
   fitFuncN1M2->SetParameter(1,sigmaN1M2FinalInv(1,1));
   fitFuncN1M2->SetParameter(2,sigmaN1M2FinalInv(1,0));
   fitFuncN1M2->SetParameter(3,(sigmaN1M2FinalInv.Invert()).Determinant());
   fitFuncN1M2->SetParameter(4,wN1*wM2);

   fitFuncN1W2->SetParameter(0,sigmaN1W2FinalInv(0,0));
   fitFuncN1W2->SetParameter(1,sigmaN1W2FinalInv(1,1));
   fitFuncN1W2->SetParameter(2,sigmaN1W2FinalInv(1,0));
   fitFuncN1W2->SetParameter(3,(sigmaN1W2FinalInv.Invert()).Determinant());
   fitFuncN1W2->SetParameter(4,wN1*wW2);

   fitFuncM1N2->SetParameter(0,sigmaM1N2FinalInv(0,0));
   fitFuncM1N2->SetParameter(1,sigmaM1N2FinalInv(1,1));
   fitFuncM1N2->SetParameter(2,sigmaM1N2FinalInv(1,0));
   fitFuncM1N2->SetParameter(3,(sigmaM1N2FinalInv.Invert()).Determinant());
   fitFuncM1N2->SetParameter(4,wM1*wN2);

   fitFuncM1M2->SetParameter(0,sigmaM1M2FinalInv(0,0));
   fitFuncM1M2->SetParameter(1,sigmaM1M2FinalInv(1,1));
   fitFuncM1M2->SetParameter(2,sigmaM1M2FinalInv(1,0));
   fitFuncM1M2->SetParameter(3,(sigmaM1M2FinalInv.Invert()).Determinant());
   fitFuncM1M2->SetParameter(4,wM1*wM2);

   fitFuncM1W2->SetParameter(0,sigmaM1W2FinalInv(0,0));
   fitFuncM1W2->SetParameter(1,sigmaM1W2FinalInv(1,1));
   fitFuncM1W2->SetParameter(2,sigmaM1W2FinalInv(1,0));
   fitFuncM1W2->SetParameter(3,(sigmaM1W2FinalInv.Invert()).Determinant());
   fitFuncM1W2->SetParameter(4,wM1*wW2);

   fitFuncW1N2->SetParameter(0,sigmaW1N2FinalInv(0,0));
   fitFuncW1N2->SetParameter(1,sigmaW1N2FinalInv(1,1));
   fitFuncW1N2->SetParameter(2,sigmaW1N2FinalInv(1,0));
   fitFuncW1N2->SetParameter(3,(sigmaW1N2FinalInv.Invert()).Determinant());
   fitFuncW1N2->SetParameter(4,wW1*wN2);

   fitFuncW1M2->SetParameter(0,sigmaW1M2FinalInv(0,0));
   fitFuncW1M2->SetParameter(1,sigmaW1M2FinalInv(1,1));
   fitFuncW1M2->SetParameter(2,sigmaW1M2FinalInv(1,0));
   fitFuncW1M2->SetParameter(3,(sigmaW1M2FinalInv.Invert()).Determinant());
   fitFuncW1M2->SetParameter(4,wW1*wM2);

   fitFuncW1W2->SetParameter(0,sigmaW1W2FinalInv(0,0));
   fitFuncW1W2->SetParameter(1,sigmaW1W2FinalInv(1,1));
   fitFuncW1W2->SetParameter(2,sigmaW1W2FinalInv(1,0));
   fitFuncW1W2->SetParameter(3,(sigmaW1W2FinalInv.Invert()).Determinant());
   fitFuncW1W2->SetParameter(4,wW1*wW2);

   double combVal = fitFuncN1N2->Eval(xVar-x0,yVar-y0)
                  + fitFuncN1M2->Eval(xVar-x0,yVar-y0)
                  + fitFuncN1W2->Eval(xVar-x0,yVar-y0)
                  + fitFuncM1N2->Eval(xVar-x0,yVar-y0)
                  + fitFuncM1M2->Eval(xVar-x0,yVar-y0)
                  + fitFuncM1W2->Eval(xVar-x0,yVar-y0)
                  + fitFuncW1N2->Eval(xVar-x0,yVar-y0)
                  + fitFuncW1M2->Eval(xVar-x0,yVar-y0)
                  + fitFuncW1W2->Eval(xVar-x0,yVar-y0);

   return combVal;
 }
