from ROOT import TFile

files = {0: ('1783_DG', 'DataAnalysisBunch1783DG_with_StronRescale.root'), \
         1: ('1783_TG', 'DataAnalysisBunch1783TG_with_StronRescale.root'), \
         2: ('2063_DG', 'DataAnalysisBunch2063DG_with_StronRescale.root'), \
         3: ('2063_TG', 'DataAnalysisBunch2063TG_with_StronRescale.root'), \
         4: ('281_DG', 'DataAnalysisBunch281DG_with_StronRescale.root'), \
         5: ('281_TG', 'DataAnalysisBunch281TG_with_StronRescale.root'), \
         6: ('41_DG', 'DataAnalysisBunch41DG_with_StronRescale.root'), \
         7: ('41_TG', 'DataAnalysisBunch41TG_with_StronRescale.root'), \
         8: ('872_DG', 'DataAnalysisBunch872DG_with_StronRescale.root'), \
         9: ('872_TG', 'DataAnalysisBunch872TG_with_StronRescale.root')}
def scale(x, y):
    return 0.00458 * 1e4 * x, 0.00458 * 1e4 * y
parameters = {0: {'key': 'weight1N', 'name': 'w1N'}, \
              1: {'key': 'weight1', 'name': 'w1N'}, \
              2: {'key': 'xwidth1N', 'name': 'SigX1N', 'func': scale}, \
              3: {'key': 'ywidth1N', 'name': 'SigY1N', 'func': scale}, \
              4: {'key': 'rho1N', 'name': 'Rho1N'}, \
              5: {'key': 'weight1M', 'name': 'w1M'}, \
              6: {'key': 'xwidth1M', 'name': 'SigX1M', 'func': scale}, \
              7: {'key': 'ywidth1M', 'name': 'SigY1M', 'func': scale}, \
              8: {'key': 'rho1M', 'name': 'Rho1M'}, \
              9: {'key': 'weight1W', 'name': 'w1W'}, \
              10: {'key': 'weight1', 'name': 'w1W', 'func': lambda x, y: (1-x, y)}, \
              11: {'key': 'xwidth1W', 'name': 'SigX1W', 'func': scale}, \
              12: {'key': 'ywidth1W', 'name': 'SigY1W', 'func': scale}, \
              13: {'key': 'rho1W', 'name': 'Rho1W'}, \
              14: {'key': 'weight2N', 'name': 'w2N'}, \
              15: {'key': 'weight2', 'name': 'w2N'}, \
              16: {'key': 'xwidth2N', 'name': 'SigX2N', 'func': scale}, \
              17: {'key': 'ywidth2N', 'name': 'SigY2N', 'func': scale}, \
              18: {'key': 'rho2N', 'name': 'Rho2N'}, \
              19: {'key': 'weight2M', 'name': 'w2M'}, \
              20: {'key': 'xwidth2M', 'name': 'SigX2M', 'func': scale}, \
              21: {'key': 'ywidth2M', 'name': 'SigY2M', 'func': scale}, \
              22: {'key': 'rho2M', 'name': 'Rho2M'}, \
              23: {'key': 'weight2W', 'name': 'w2W'}, \
              24: {'key': 'weight2', 'name': 'w2W', 'func': lambda x, y: (1-x, y)}, \
              25: {'key': 'xwidth2W', 'name': 'SigX2W', 'func': scale}, \
              26: {'key': 'ywidth2W', 'name': 'SigY2W', 'func': scale}, \
              27: {'key': 'rho2W', 'name': 'Rho2W'}}

def gatherParameters(filelist, paralist):
    results = {}
    names = {}
    for j in paralist:
        if not paralist[j]['name'] in names.values():
            names[len(names)] = paralist[j]['name']
    for i in filelist:
        dataset = filelist[i][0]
        filename = filelist[i][1]
        results[dataset] = {}
        f = TFile.Open(filename)
        for j in paralist:
            par = paralist[j]
            histV = f.Get(par['key']+'_h')
            histE = f.Get(par['key']+'_error_h')
            if histV and histE:
                histV = histV.GetMean()
                histE = histE.GetMean()
                if 'func' in par:
                    histV, histE = par['func'](histV, histE)
                results[dataset][par['name']] = (histV, histE)
            elif not par['name'] in results[dataset]:
                results[dataset][par['name']] = ('', '')
    print
    print
    print '',
    for i in filelist:
        print ';', filelist[i][0], ';', '',
    print
    for j in names:
        print names[j],
        for i in filelist:
            dataset = filelist[i][0]
            res = results[dataset][names[j]]
            print ';', res[0], ';', res[1],
        print
    print
    print

if __name__ == '__main__':
    gatherParameters(files, parameters)
