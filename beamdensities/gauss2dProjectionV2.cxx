/***************************************************************************** 
 * Project: RooFit                                                           * 
 *                                                                           * 
 * This code was autogenerated by RooClassFactory                            * 
 *****************************************************************************/ 

// Your description goes here... 

#include "Riostream.h" 

#include "gauss2dProjectionV2.h" 
#include "RooAbsReal.h" 
#include "RooAbsCategory.h"
#include <math.h> 
#include "TMath.h"
#include "TF2.h"

 

ClassImp(gauss2dProjectionV2) 

 gauss2dProjectionV2::gauss2dProjectionV2(const char *name, const char *title, 
                        RooAbsReal& _x,
                        RooAbsReal& _y,
                        RooAbsReal& _n1,
                        RooAbsReal& _x_Width1,
                        RooAbsReal& _y_Width1,
                        RooAbsReal& _rho1,
                        RooAbsReal& _n2,
                        RooAbsReal& _x_Width2,
                        RooAbsReal& _y_Width2,
                        RooAbsReal& _rho2) :
   RooAbsPdf(name,title), 
   x("x","x",this,_x),
   y("y","y",this,_y),
   n1("n1","n1",this,_n1),
   x_Width1("x_Width1","x_Width1",this,_x_Width1),
   y_Width1("y_Width1","y_Width1",this,_y_Width1),
   rho1("rho1","rho1",this,_rho1),
   n2("n2","n2",this,_n2),
   x_Width2("x_Width2","x_Width2",this,_x_Width2),
   y_Width2("y_Width2","y_Width2",this,_y_Width2),
   rho2("rho2","rho2",this,_rho2)
 { 
 } 


 gauss2dProjectionV2::gauss2dProjectionV2(const gauss2dProjectionV2& other, const char* name) :  
   RooAbsPdf(other,name), 
   x("x",this,other.x),
   y("y",this,other.y),
   n1("n1",this,other.n1),
   x_Width1("x_Width1",this,other.x_Width1),
   y_Width1("y_Width1",this,other.y_Width1),
   rho1("rho1",this,other.rho1),
   n2("n2",this,other.n2),
   x_Width2("x_Width2",this,other.x_Width2),
   y_Width2("y_Width2",this,other.y_Width2),
   rho2("rho2",this,other.rho2)
 { 
 } 



 Double_t gauss2dProjectionV2::evaluate() const 
 { 
   // ENTER EXPRESSION IN TERMS OF VARIABLE ARGUMENTS HERE 
   //TF2 *twodGauss = new TF2("twodGauss","exp(-0.5*((x[0])/[0])^2-0.5*TMath::Power(((x[1])/[1]),2)-2*[2]*(x[0])*(x[1])/([0]*[1]))",-15,15,-15,15);
   //twodGauss->SetParameter(0,x_Width1);
   //twodGauss->SetParameter(1,y_Width1);
   //twodGauss->SetParameter(2,rho1);

 
   /*twodGauss1->SetParameter(0,x_Width1);
    twodGauss1->SetParameter(1,TMath::Sqrt(TMath::Power(y_Width1,2.0)+0.49));
    twodGauss1->SetParameter(2,rho1);
    twodGauss1->SetParameter(3,x_Width2); 
    twodGauss1->SetParameter(4,TMath::Sqrt(TMath::Power(x_Width1,2.0)*TMath::Power(x_Width2,2.0)/(TMath::Power(x_Width2,2.0)+(TMath::Power(x_Width1,2.0)*(1-TMath::Power(rho1,2.0))))+0.49)); */
   
    TMatrixDSym beam1(2);
    beam1(0,0) = TMath::Power(x_Width1,2.0); 
    beam1(1,1) = TMath::Power(y_Width1,2.0); 
    beam1(1,0) = rho1*x_Width1*y_Width1;
    beam1(0,1) = rho1*x_Width1*y_Width1;
    TMatrixDSym beam2MargInv(2);
    beam2MargInv(0,0) = 1./TMath::Power(x_Width2,2.0);
    beam2MargInv(1,1) = 0.;
    beam2MargInv(0,1) = 0.;
    beam2MargInv(1,0) = 0.;
    TMatrixDSym vtxRes(2);
    vtxRes(0,0) = 0.49;
    vtxRes(1,1) = 0.49;
    vtxRes(0,1) = 0.;
    vtxRes(1,0) = 0.;
    TMatrixDSym sigmaFinalInv(2);
    sigmaFinalInv = ((beam1.Invert()+beam2MargInv).Invert()+vtxRes).Invert();
    fitFunc->SetParameter(0,sigmaFinalInv(0,0));
    fitFunc->SetParameter(1,sigmaFinalInv(1,1));
    fitFunc->SetParameter(2,sigmaFinalInv(1,0));
    fitFunc->SetParameter(3,sigmaFinalInv.Invert().Determinant());
    
    // std::cout<<<<std::endl;//sigmaFinal(0,0)<<"  "<<sigmaFinal(0,0)<<"  "<<sigmaFinal(1,0)<<"  "<<sigmaFinal(0,1)<<std::endl;
    //double a=5*x_Width1;
   //TF2 *twodGaussProj = new TF2("twodGaussProj","exp(-0.5*((x[0])/[0])^2-0.5*TMath::Power(((x[1])/[1]),2)-2*[2]*(x[0])*(x[1])/([0]*[1]))",-15,15,-15,15);
   //twodGaussProj->SetParameter(0,x_Width2);
   //twodGaussProj->SetParameter(1,y_Width2);
   //twodGaussProj->SetParameter(2,rho2);
    
    
    
   //  return n2*(twodGaussProj->Integral(x,x+0.00000001,-15,15))* n1*twodGauss->Eval(x,y); 

   //return twodGauss1->Eval(x,y);
    return fitFunc->Eval(x,y);

 } 


