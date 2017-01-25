/***************************************************************************** 
 * Project: RooFit                                                           * 
 *                                                                           * 
 * This code was autogenerated by RooClassFactory                            * 
 *****************************************************************************/ 

// Your description goes here... 

#include "Riostream.h" 

#include "MyPdfV3.h" 
#include "RooAbsReal.h" 
#include "RooAbsCategory.h" 
#include <math.h> 
#include "TMath.h" 
#include "TMatrix.h"
ClassImp(MyPdfV3) 

 MyPdfV3::MyPdfV3(const char *name, const char *title, 
                        RooAbsReal& _x,
                        RooAbsReal& _y,
                        RooAbsReal& _wNW1,
                        RooAbsReal& __rhoN1,
                        RooAbsReal& _sigxN1,
                        RooAbsReal& _sigyN1,
                        RooAbsReal& __rhoW1,
                        RooAbsReal& _sigxW1,
                        RooAbsReal& _sigyW1,
                        RooAbsReal& _wNW2,
                        RooAbsReal& _sigyN2,
                        RooAbsReal& _sigyW2) :
   RooAbsPdf(name,title), 
   x("x","x",this,_x),
   y("y","y",this,_y),
   wNW1("wNW1","wNW1",this,_wNW1),
   _rhoN1("_rhoN1","_rhoN1",this,__rhoN1),
   sigxN1("sigxN1","sigxN1",this,_sigxN1),
   sigyN1("sigyN1","sigyN1",this,_sigyN1),
   _rhoW1("_rhoW1","_rhoW1",this,__rhoW1),
   sigxW1("sigxW1","sigxW1",this,_sigxW1),
   sigyW1("sigyW1","sigyW1",this,_sigyW1),
   wNW2("wNW2","wNW2",this,_wNW2),
   sigyN2("sigyN2","sigyN2",this,_sigyN2),
   sigyW2("sigyW2","sigyW2",this,_sigyW2)
 { 
 } 


 MyPdfV3::MyPdfV3(const MyPdfV3& other, const char* name) :  
   RooAbsPdf(other,name), 
   x("x",this,other.x),
   y("y",this,other.y),
   wNW1("wNW1",this,other.wNW1),
   _rhoN1("_rhoN1",this,other._rhoN1),
   sigxN1("sigxN1",this,other.sigxN1),
   sigyN1("sigyN1",this,other.sigyN1),
   _rhoW1("_rhoW1",this,other._rhoW1),
   sigxW1("sigxW1",this,other.sigxW1),
   sigyW1("sigyW1",this,other.sigyW1),
   wNW2("wNW2",this,other.wNW2),
   sigyN2("sigyN2",this,other.sigyN2),
   sigyW2("sigyW2",this,other.sigyW2)
 { 
 } 



 Double_t MyPdfV3::evaluate() const 
 { 
   // ENTER EXPRESSION IN TERMS OF VARIABLE ARGUMENTS HERE 

   TMatrix beamN1(2,2) ;
   beamN1(0,0) = TMath::Power(sigxN1,2.0); 
   beamN1(1,1) = TMath::Power(sigyN1,2.0); 
   beamN1(1,0) = _rhoN1*sigxN1*sigyN1;
   beamN1(0,1) = _rhoN1*sigxN1*sigyN1;
   TMatrix beamW1(2,2) ;
   beamW1(0,0) = TMath::Power(sigxW1,2.0); 
   beamW1(1,1) = TMath::Power(sigyW1,2.0); 
   beamW1(1,0) = _rhoW1*sigxW1*sigyW1;
   beamW1(0,1) = _rhoW1*sigxW1*sigyW1;
   TMatrix beamW1_Inv(TMatrix::kInverted,beamW1);
   TMatrix beamN1_Inv(TMatrix::kInverted,beamN1);
   TMatrix beamN2MargInv(2,2) ;
   beamN2MargInv(0,0) = 0.;
   beamN2MargInv(1,1) = 1./TMath::Power(sigyN2,2.0);
   beamN2MargInv(0,1) = 0.;
   beamN2MargInv(1,0) = 0.;   
   TMatrix beamW2MargInv(2,2) ;
   beamW2MargInv(0,0) = 0.;
   beamW2MargInv(1,1) = 1./TMath::Power(sigyW2,2.0);
   beamW2MargInv(0,1) = 0.;
   beamW2MargInv(1,0) = 0.;
   TMatrix vtxRes(2,2);
   vtxRes(0,0) = 0.49;
   vtxRes(1,1) = 0.49;
   vtxRes(0,1) = 0.;
   vtxRes(1,0) = 0.;
   TMatrix sigmaN1N2FinalInv(2,2) ;
   TMatrix sigmaN1W2FinalInv(2,2) ;
   TMatrix sigmaW1N2FinalInv(2,2) ;
   TMatrix sigmaW1W2FinalInv(2,2) ;
   sigmaN1N2FinalInv = ((beamN1_Inv+beamN2MargInv).Invert()+vtxRes).Invert();
   sigmaN1W2FinalInv = ((beamN1_Inv+beamW2MargInv).Invert()+vtxRes).Invert();
   sigmaW1N2FinalInv = ((beamW1_Inv+beamN2MargInv).Invert()+vtxRes).Invert();
   sigmaW1W2FinalInv = ((beamW1_Inv+beamW2MargInv).Invert()+vtxRes).Invert();

   fitFuncN1N2->SetParameter(0,sigmaN1N2FinalInv(0,0));
    fitFuncN1N2->SetParameter(1,sigmaN1N2FinalInv(1,1));
    fitFuncN1N2->SetParameter(2,sigmaN1N2FinalInv(1,0));
    fitFuncN1N2->SetParameter(3,(sigmaN1N2FinalInv.Invert()).Determinant());
    fitFuncN1N2->SetParameter(4,wNW1*wNW2);

    /*sigmaN1N2FinalInv.Print();
    sigmaN1N2FinalInv.Invert();
    sigmaN1N2FinalInv.Print();
    sigmaN1N2FinalInv.Invert();
    sigmaN1N2FinalInv.Print();*/

    fitFuncN1W2->SetParameter(0,sigmaN1W2FinalInv(0,0));
    fitFuncN1W2->SetParameter(1,sigmaN1W2FinalInv(1,1));
    fitFuncN1W2->SetParameter(2,sigmaN1W2FinalInv(1,0));
    fitFuncN1W2->SetParameter(3,(sigmaN1W2FinalInv.Invert()).Determinant());
    fitFuncN1W2->SetParameter(4,wNW1*(1.-wNW2));

    fitFuncW1N2->SetParameter(0,sigmaW1N2FinalInv(0,0));
    fitFuncW1N2->SetParameter(1,sigmaW1N2FinalInv(1,1));
    fitFuncW1N2->SetParameter(2,sigmaW1N2FinalInv(1,0));
    fitFuncW1N2->SetParameter(3,(sigmaW1N2FinalInv.Invert()).Determinant());
    fitFuncW1N2->SetParameter(4,wNW2*(1.-wNW1));
    
    fitFuncW1W2->SetParameter(0,sigmaW1W2FinalInv(0,0));
    fitFuncW1W2->SetParameter(1,sigmaW1W2FinalInv(1,1));
    fitFuncW1W2->SetParameter(2,sigmaW1W2FinalInv(1,0));
    fitFuncW1W2->SetParameter(3,(sigmaW1W2FinalInv.Invert()).Determinant());
    fitFuncW1W2->SetParameter(4,(1.-wNW2)*(1.-wNW1));
    
    double combVal = (fitFuncN1N2->Eval(x,y)) + (fitFuncN1W2->Eval(x,y)) + (fitFuncW1N2->Eval(x,y)) + (fitFuncW1W2->Eval(x,y));
    
   return combVal ; 
 } 


