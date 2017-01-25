/*****************************************************************************
 * Project: RooFit                                                           *
 *                                                                           *
  * This code was autogenerated by RooClassFactory                            * 
 *****************************************************************************/

#ifndef GAUSS2DPROJECTIONV2
#define GAUSS2DPROJECTIONV2

#include "RooArgList.h" 
#include "RooMultiVarGaussian.h"
#include "RooAbsPdf.h"
#include "RooRealProxy.h"
#include "RooCategoryProxy.h"
#include "RooAbsReal.h"
#include "RooAbsCategory.h"
#include "TF2.h"
#include "TMatrixDSym.h"

class gauss2dProjectionV2 : public RooAbsPdf {
public:
  gauss2dProjectionV2() {} ; 
  gauss2dProjectionV2(const char *name, const char *title,
	      RooAbsReal& _x,
	      RooAbsReal& _y,
	      RooAbsReal& _n1,
	      RooAbsReal& _x_Width1,
	      RooAbsReal& _y_Width1,
	      RooAbsReal& _rho1,
	      RooAbsReal& _n2,
	      RooAbsReal& _x_Width2,
	      RooAbsReal& _y_Width2,
	      RooAbsReal& _rho2);
  gauss2dProjectionV2(const gauss2dProjectionV2& other, const char* name=0) ;
  virtual TObject* clone(const char* newname) const { return new gauss2dProjectionV2(*this,newname); }
  double pi = 3.1415926535;
  //TF2 *twodGauss = new TF2("twodGauss","exp(-0.5*((x[0])/[0])^2-0.5*TMath::Power(((x[1])/[1]),2)-2*[2]*(x[0])*(x[1])/([0]*[1]))",-15,15,-15,15);
  // TF2 *twodGaussProj = new TF2("twodGaussProj","exp(-0.5*((x[0])/[0])^2-0.5*TMath::Power(((x[1])/[1]),2)-2*[2]*(x[0])*(x[1])/([0]*[1]))",-15,15,-15,15);
  //TF2 *twodGauss1 = new TF2("twodGauss1","1/([0]*[1]*[3]*TMath::Sqrt(2*3.14159*(1-TMath::Power([2],2.0))))*TMath::Exp(-0.5/(1-TMath::Power([2],2.0))*(TMath::Power((x[0])/[4],2.0)+TMath::Power(((x[1])/[1]),2.0)-2*[2]*(x[0])*(x[1])/([0]*[1])))",-11,11,-11,11);
  
   TF2 *fitFunc = new TF2("fitFunc","100./(TMath::Sqrt([3]*2*3.141593))*exp(-0.5*(TMath::Power(x[0],2.0)*[0]+TMath::Power(x[1],2.0)*[1]+2*[2]*x[0]*x[1]))",-15,15,-15,15);

  //TMatrixDSym a(2);
  //RooMultiVarGaussian mvG("mvG",RooArgList(x,y),a);
  
  inline virtual ~gauss2dProjectionV2() { }

protected:

  RooRealProxy x ;
  RooRealProxy y ;
  RooRealProxy n1 ;
  RooRealProxy x_Width1 ;
  RooRealProxy y_Width1 ;
  RooRealProxy rho1 ;
  RooRealProxy n2 ;
  RooRealProxy x_Width2 ;
  RooRealProxy y_Width2 ;
  RooRealProxy rho2 ;
  
  Double_t evaluate() const ;

private:

  ClassDef(gauss2dProjectionV2,1) // Your description goes here...
};
 
#endif