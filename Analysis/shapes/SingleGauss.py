from math import pi, exp
from itertools import product
from ROOT import RooRealVar, TF2

class SingleGauss:
    """Beam shapes modelled with single Gaussian"""

    Shortname = 'SG'
    Variables = {}
    Parameter = {}
    Templates = ('SingleGauss_V1', 'SingleGauss_V2')

    def __init__(self, uncorrelated=False):
        sXY = ('x', 'y')
        s12 = ('1', '2')
        self.Variables = {name: RooRealVar(name, name, -10.0, 10.0) for name \
                          in [c+'Var' for c in sXY]}
        pos0 = {name: RooRealVar(name, name, -0.5, 0.5) for name in [c+'0'+i+j \
                for c in sXY for i in s12 for j in s12]}
        widthN = {name: RooRealVar(name, name, 1.3, 3.0) for name in \
                  [c+'WidthN'+i for c in sXY for i in s12]}
        rhoN = {name: RooRealVar(name, name, -0.48, 0.48) for name in \
                ['rhoN'+i for i in s12]}
        wN = {name: RooRealVar(name, name, 0.0, 1.0) for name in ['w'+i+'N' \
              for i in s12]}
        res = {'vtxRes': RooRealVar('vtxRes', 'vtxRes', 0.0, 5.0)}
        for v in self.Variables.itervalues():
            v.setBins(10000, 'cache')
        for w in wN.itervalues():
            w.setVal(0.0)
            w.setConstant()
        if uncorrelated:
            for rho in rhoN.itervalues():
                rho.setVal(0.0)
                rho.setConstant()
        for d in (pos0, widthN, rhoN, wN, res):
            self.Parameter.update(d)

    def xVar(self):
        return self.Variables['xVar']

    def yVar(self):
        return self.Variables['yVar']

    def setVertexResolution(self, vtxres, constant=True):
        try:
            self.Parameter['vtxRes'].setVal(vtxres)
            self.Parameter['vtxRes'].setConstant(constant)
            return True
        except:
            return False

    def getModelFunctions(self):
        from ROOT import SingleGauss_V1, SingleGauss_V2
        def name(i, c):
            return 'beam' + i + 'RestVerticesUnfold_' + c.upper() + 'Scan'
        def oth(s):
            if s.isalpha():
                if s == 'x':
                    return 'y'
                else:
                    return 'x'
            else:
                if s == '1':
                    return '2'
                else:
                    return '1'
        def whi(s):
            if s == 'x':
                return '1'
            else:
                return '2'
        return [locals()['SingleGauss_V'+whi(c)](name(i, c), name(i, c), \
                self.xVar(), self.yVar(), self.Parameter['x0'+i+whi(c)], \
                self.Parameter['y0'+i+whi(c)], self.Parameter['rhoN'+i], \
                self.Parameter['xWidthN'+i], self.Parameter['yWidthN'+i], \
                self.Parameter[oth(c)+'WidthN'+oth(i)], \
                self.Parameter['vtxRes']) for i,c in \
                [('1', 'x'), ('1', 'y'), ('2', 'x'), ('2', 'y')]]

    def calcOverlap(self, x, par):
        xx = x[0]
        yy = x[1]
        x01 = par[0]
        y01 = par[1]
        x02 = par[2]
        y02 = par[3]
        xWidthN1 = par[4]
        yWidthN1 = par[5]
        xWidthN2 = par[6]
        yWidthN2 = par[7]
        rhoN1 = par[8]
        rhoN2 = par[9]
        beamN1 = 0.5 / (pi * (1.0 - rhoN1 ** 2) ** 0.5 * abs(xWidthN1) * \
                 abs(yWidthN1)) * exp(-0.5 / (1.0 - rhoN1 ** 2) * (((xx - x01) \
                 / xWidthN1) ** 2 + ((yy -y01) / yWidthN1) ** 2 - 2.0 * rhoN1 \
                 * (xx - x01) * (yy - y01) / (xWidthN1 * yWidthN1)))
        beamN2 = 0.5 / (pi * (1.0 - rhoN1 ** 2) ** 0.5 * abs(xWidthN1) * \
                 abs(yWidthN1)) * exp(-0.5 / (1.0 - rhoN1 ** 2) * (((xx - x01) \
                 / xWidthN1) ** 2 + ((yy -y01) / yWidthN1) ** 2 - 2.0 * rhoN1 \
                 * (xx - x01) * (yy - y01) / (xWidthN1 * yWidthN1)))
        return beamN1 * beamN2

    def assignToOverlap(self, multBeam, random=False):
        multBeam.SetParameter(0, 0.0)
        multBeam.SetParameter(1, 0.0)
        multBeam.SetParameter(2, 0.0)
        multBeam.SetParameter(3, 0.0)
        parNames = ['xWidthN1', 'yWidthN1', 'xWidthN2', 'yWidthN2', 'rhoN1', \
                    'rhoN2']
        parValue = {}
        for name in parNames:
            parValue[name] = self.computeValue(name)
        if random:
            for name in parNames:
                parValue[name] = random.Gaus(parValue[name], \
                                             self.computeError(name))
                if 'rho' in name:
                    if parValue[name] < -1.0:
                        parValue[name] = -1.0
                    elif parValue[name] > 1.0:
                        parValue[name] = 1.0
        for i, name in enumerate(parNames, start=4):
            multBeam.SetParameter(i, parValue[name])
        return multBeam

    def funcOverlap(self):
        multBeam = TF2('multBeam', self.calcOverlap, -30.0, 30.0, -30.0, 30.0, 10)
        multBeam = self.assignToOverlap(multBeam)
        return multBeam

    def computeValue(self, var):
        try:
            return self.Parameter[var].getValV()
        except:
            return False

    def computeError(self, var):
        try:
            return self.Parameter[var].getError()
        except:
            return False


class SingleGaussUncorrelated(SingleGauss):
    """Beam shapes modelled with single Gaussian without correlations"""

    Shortname = 'noCorr'

    def __init__(self):
        SingleGauss.__init__(self, uncorrelated=True)