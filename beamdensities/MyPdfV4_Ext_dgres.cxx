/***************************************************************************** 
 * Project: RooFit                                                           * 
 *                                                                           * 
 * This code was autogenerated by RooClassFactory                            * 
 *****************************************************************************/ 

// Your description goes here... 

#include "Riostream.h" 
#include "MyPdfV4_Ext_dgres.h" 
#include "RooAbsReal.h" 
#include "RooAbsCategory.h" 
#include <math.h> 
#include "TMath.h" 
#include "TMatrix.h"

ClassImp(MyPdfV4_Ext_dgres) 

 MyPdfV4_Ext_dgres::MyPdfV4_Ext_dgres(const char *name, const char *title, 
                        RooAbsReal& _xVar ,
                        RooAbsReal& _yVar,
                        RooAbsReal& _x0,
                        RooAbsReal& _y0 ,
                        RooAbsReal& _w1 ,
                        RooAbsReal& _rho_N1 ,
                        RooAbsReal& _xWidthN1 ,
                        RooAbsReal& _yWidthN1 ,
                        RooAbsReal& _rho_W1 ,
                        RooAbsReal& _xWidthW1 ,
                        RooAbsReal& _yWidthW1 ,
                        RooAbsReal& _w2 ,
                        RooAbsReal& _xWidthN2 ,
                        RooAbsReal& _xWidthW2) :
   RooAbsPdf(name,title), 
   xVar ("xVar","xVar",this,_xVar ),
    yVar("yVar","yVar",this,_yVar),
    x0("x0","x0",this,_x0),
    y0 ("y0","y0",this,_y0 ),
    w1 ("w1","w1",this,_w1 ),
    rho_N1 ("rho_N1","rho_N1",this,_rho_N1 ),
    xWidthN1 ("xWidthN1","xWidthN1",this,_xWidthN1 ),
    yWidthN1 ("yWidthN1","yWidthN1",this,_yWidthN1 ),
    rho_W1 ("rho_W1","rho_W1",this,_rho_W1 ),
    xWidthW1 ("xWidthW1","xWidthW1",this,_xWidthW1 ),
    yWidthW1 ("yWidthW1","yWidthW1",this,_yWidthW1 ),
    w2 ("w2","w2",this,_w2 ),
    xWidthN2 ("xWidthN2","xWidthN2",this,_xWidthN2 ),
    xWidthW2("xWidthW2","xWidthW2",this,_xWidthW2)
 { 
 } 


 MyPdfV4_Ext_dgres::MyPdfV4_Ext_dgres(const MyPdfV4_Ext_dgres& other, const char* name) :  
   RooAbsPdf(other,name), 
   xVar ("xVar",this,other.xVar ),
    yVar("yVar",this,other.yVar),
    x0("x0",this,other.x0),
    y0 ("y0",this,other.y0 ),
    w1 ("w1",this,other.w1 ),
    rho_N1 ("rho_N1",this,other.rho_N1 ),
    xWidthN1 ("xWidthN1",this,other.xWidthN1 ),
    yWidthN1 ("yWidthN1",this,other.yWidthN1 ),
    rho_W1 ("rho_W1",this,other.rho_W1 ),
    xWidthW1 ("xWidthW1",this,other.xWidthW1 ),
    yWidthW1 ("yWidthW1",this,other.yWidthW1 ),
    w2 ("w2",this,other.w2 ),
    xWidthN2 ("xWidthN2" ,this,other.xWidthN2 ),
    xWidthW2("xWidthW2",this,other.xWidthW2)
 { 
 } 



 Double_t MyPdfV4_Ext_dgres::evaluate() const 
 { 
   // ENTER EXPRESSION IN TERMS OF VARIABLE ARGUMENTS HERE 

 TMatrix beamN1(2,2) ;
   beamN1(0,0) = TMath::Power(xWidthN1,2.0); 
   beamN1(1,1) = TMath::Power(yWidthN1,2.0); 
   beamN1(1,0) = rho_N1*xWidthN1*yWidthN1;
   beamN1(0,1) = rho_N1*xWidthN1*yWidthN1;
   TMatrix beamW1(2,2) ;
   beamW1(0,0) = TMath::Power(xWidthW1,2.0); 
   beamW1(1,1) = TMath::Power(yWidthW1,2.0); 
   beamW1(1,0) = rho_W1*xWidthW1*yWidthW1;
   beamW1(0,1) = rho_W1*xWidthW1*yWidthW1;
   TMatrix beamW1_Inv(TMatrix::kInverted,beamW1);
   TMatrix beamN1_Inv(TMatrix::kInverted,beamN1);
   TMatrix beamN2MargInv(2,2) ;
   beamN2MargInv(1,1) = 0.;
   beamN2MargInv(0,0) = 1./TMath::Power(xWidthN2,2.0);
   beamN2MargInv(0,1) = 0.;
   beamN2MargInv(1,0) = 0.;   
   TMatrix beamW2MargInv(2,2) ;
   beamW2MargInv(1,1) = 0.;
   beamW2MargInv(0,0) = 1./TMath::Power(xWidthW2,2.0);
   beamW2MargInv(0,1) = 0.;
   beamW2MargInv(1,0) = 0.;


   TMatrix vtxRes1(2,2);
   vtxRes1(0,0) = 0.322;//0.295;//0.297;//1.33;//0.00363*0.00363;
   vtxRes1(1,1) = 0.322;//0.295;//0.297;//1.33;//0.00363*0.00363;
   vtxRes1(0,1) = 0.;
   vtxRes1(1,0) = 0.;

   TMatrix vtxRes2(2,2);
   vtxRes2(0,0) = 0.917;//0.878;//0.892;//1.33;//0.00363*0.00363;
   vtxRes2(1,1) = 0.917;//0.878;//0.892;//1.33;//0.00363*0.00363;
   vtxRes2(0,1) = 0.;
   vtxRes2(1,0) = 0.;
   TMatrix sigmaN1N2FinalInv1(2,2) ;
   TMatrix sigmaN1W2FinalInv1(2,2) ;
   TMatrix sigmaW1N2FinalInv1(2,2) ;
   TMatrix sigmaW1W2FinalInv1(2,2) ;
   
   TMatrix sigmaN1N2FinalInv2(2,2) ;
   TMatrix sigmaN1W2FinalInv2(2,2) ;
   TMatrix sigmaW1N2FinalInv2(2,2) ;
   TMatrix sigmaW1W2FinalInv2(2,2) ;

   sigmaN1N2FinalInv1 = ((beamN1_Inv+beamN2MargInv).Invert()+vtxRes1).Invert();
   sigmaN1W2FinalInv1 = ((beamN1_Inv+beamW2MargInv).Invert()+vtxRes1).Invert();
   sigmaW1N2FinalInv1 = ((beamW1_Inv+beamN2MargInv).Invert()+vtxRes1).Invert(); 
   sigmaW1W2FinalInv1 = ((beamW1_Inv+beamW2MargInv).Invert()+vtxRes1).Invert();

   sigmaN1N2FinalInv2 = ((beamN1_Inv+beamN2MargInv).Invert()+vtxRes2).Invert();
   sigmaN1W2FinalInv2 = ((beamN1_Inv+beamW2MargInv).Invert()+vtxRes2).Invert();
   sigmaW1N2FinalInv2 = ((beamW1_Inv+beamN2MargInv).Invert()+vtxRes2).Invert(); 
   sigmaW1W2FinalInv2 = ((beamW1_Inv+beamW2MargInv).Invert()+vtxRes2).Invert();
 

   fit1FuncN1N2->SetParameter(0,sigmaN1N2FinalInv1(0,0));
    fit1FuncN1N2->SetParameter(1,sigmaN1N2FinalInv1(1,1));
    fit1FuncN1N2->SetParameter(2,sigmaN1N2FinalInv1(1,0));
    fit1FuncN1N2->SetParameter(3,(sigmaN1N2FinalInv1.Invert()).Determinant());
    fit1FuncN1N2->SetParameter(4,w1*w2);
    //fitFuncN1N2->Print();

    fit1FuncN1W2->SetParameter(0,sigmaN1W2FinalInv1(0,0));
    fit1FuncN1W2->SetParameter(1,sigmaN1W2FinalInv1(1,1));
    fit1FuncN1W2->SetParameter(2,sigmaN1W2FinalInv1(1,0));
    fit1FuncN1W2->SetParameter(3,(sigmaN1W2FinalInv1.Invert()).Determinant());
    fit1FuncN1W2->SetParameter(4,w1*(1.-w2));
    //fitFuncN1W2->Print();

    fit1FuncW1N2->SetParameter(0,sigmaW1N2FinalInv1(0,0));
    fit1FuncW1N2->SetParameter(1,sigmaW1N2FinalInv1(1,1));
    fit1FuncW1N2->SetParameter(2,sigmaW1N2FinalInv1(1,0));
    fit1FuncW1N2->SetParameter(3,(sigmaW1N2FinalInv1.Invert()).Determinant());
    fit1FuncW1N2->SetParameter(4,w2*(1.-w1));
    //fitFuncW1N2->Print();

    fit1FuncW1W2->SetParameter(0,sigmaW1W2FinalInv1(0,0));
    fit1FuncW1W2->SetParameter(1,sigmaW1W2FinalInv1(1,1));
    fit1FuncW1W2->SetParameter(2,sigmaW1W2FinalInv1(1,0));
    fit1FuncW1W2->SetParameter(3,(sigmaW1W2FinalInv1.Invert()).Determinant());
    fit1FuncW1W2->SetParameter(4,(1.-w2)*(1.-w1));
    //fitFuncW1W2->Print();
    
   fit2FuncN1N2->SetParameter(0,sigmaN1N2FinalInv2(0,0));
    fit2FuncN1N2->SetParameter(1,sigmaN1N2FinalInv2(1,1));
    fit2FuncN1N2->SetParameter(2,sigmaN1N2FinalInv2(1,0));
    fit2FuncN1N2->SetParameter(3,(sigmaN1N2FinalInv2.Invert()).Determinant());
    fit2FuncN1N2->SetParameter(4,w1*w2);
    //fitFuncN1N2->Print();

    fit2FuncN1W2->SetParameter(0,sigmaN1W2FinalInv2(0,0));
    fit2FuncN1W2->SetParameter(1,sigmaN1W2FinalInv2(1,1));
    fit2FuncN1W2->SetParameter(2,sigmaN1W2FinalInv2(1,0));
    fit2FuncN1W2->SetParameter(3,(sigmaN1W2FinalInv2.Invert()).Determinant());
    fit2FuncN1W2->SetParameter(4,w1*(1.-w2));
    //fitFuncN1W2->Print();

    fit2FuncW1N2->SetParameter(0,sigmaW1N2FinalInv2(0,0));
    fit2FuncW1N2->SetParameter(1,sigmaW1N2FinalInv2(1,1));
    fit2FuncW1N2->SetParameter(2,sigmaW1N2FinalInv2(1,0));
    fit2FuncW1N2->SetParameter(3,(sigmaW1N2FinalInv2.Invert()).Determinant());
    fit2FuncW1N2->SetParameter(4,w2*(1.-w1));
    //fitFuncW1N2->Print();

    fit2FuncW1W2->SetParameter(0,sigmaW1W2FinalInv2(0,0));
    fit2FuncW1W2->SetParameter(1,sigmaW1W2FinalInv2(1,1));
    fit2FuncW1W2->SetParameter(2,sigmaW1W2FinalInv2(1,0));
    fit2FuncW1W2->SetParameter(3,(sigmaW1W2FinalInv2.Invert()).Determinant());
    fit2FuncW1W2->SetParameter(4,(1.-w2)*(1.-w1));
    //fitFuncW1W2->Print();
    

    double combVal1 = ((fit1FuncN1N2->Eval(xVar-x0,yVar-y0)) + (fit1FuncN1W2->Eval(xVar-x0,yVar-y0)) + (fit1FuncW1N2->Eval(xVar-x0,yVar-y0)) + (fit1FuncW1W2->Eval(xVar-x0,yVar-y0)));
    
    double combVal2 = ((fit2FuncN1N2->Eval(xVar-x0,yVar-y0)) + (fit2FuncN1W2->Eval(xVar-x0,yVar-y0)) + (fit2FuncW1N2->Eval(xVar-x0,yVar-y0)) + (fit2FuncW1W2->Eval(xVar-x0,yVar-y0)));

    //double combVal = (1.-0.256)*combVal1 + 0.256*combVal2;
    //double combVal = (1.-0.248)*combVal1 + 0.248*combVal2;
    double combVal = (1.-0.249)*combVal1 + 0.249*combVal2;
   return combVal ;
   //return 1.0 ; 
 } 



