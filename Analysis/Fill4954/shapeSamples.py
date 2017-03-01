from sys import argv as __ARGV__
__ARGV__.append('-b')

from ROOT import TF1, TCanvas

def shapeSamples():
    g = [TF1('g'+str(i),'gaus',-10,10) for i in range(10)]
    for i,(w,s,c) in enumerate([(0.8,2.0,2), (0.2,4.0,3), (0.7,2.0,2), (0.2,3.0,3), (0.1,4.0,4), (-0.2,2.0,5), (1.2,3.0,2), (-0.2,2.0,5), (0.9,3.0,2), (0.3,4.0,3)]):
        g[i].SetParameter(0, w)
        g[i].SetParameter(2, s)
        g[i].SetLineColor(c)
    for n,f in (('DG','g0+g1'), ('TG','g2+g3+g4'), ('SupG','g5+g6'), ('SupDG','g7+g8+g9')):
        g.append(TF1(n,f,-10,10))
        g[-1].SetLineColor(1)
    for i,n in ((0,'Double Gaussian'), (2,'Triple Gaussian'), (5,'Super Gaussian'), (7,'Super Double Gaussian')):
        g[i].SetTitle(n)
    can = TCanvas('can', '', 1200, 300)
    can.Divide(4)
    zero = TF1('zero','0.0',-10,10)
    zero.SetLineColor(1)
    zero.SetLineWidth(1)
    zero.SetLineStyle(7)
    for i, j in enumerate([(0,1,10), (2,3,4,11), (5,6,12), (7,8,9,13)]):
        can.cd(i+1)
        g[j[0]].Draw()
        zero.Draw('SAME')
        g[j[0]].GetYaxis().SetRangeUser(-0.25, 1.25)
        for axis in (g[j[0]].GetXaxis(),g[j[0]].GetYaxis()):
            axis.SetNdivisions(505)
            axis.SetLabelSize(0.05)
            axis.SetLabelOffset(0.01)
        for k in j[1:]:
            g[k].Draw('SAME')
    can.SaveAs('shapes1D.pdf')
    can.SaveAs('shapes1D.C')

if __name__ == '__main__':
    shapeSamples()
