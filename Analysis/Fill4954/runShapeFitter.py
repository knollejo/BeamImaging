from sys import argv as __ARGV__
__ARGV__.append('-b')

from argparse import ArgumentParser

def main():
    datafile = '/eos/cms/store/user/jsalfeld/vdmScan_2016ReRecoJan/mergedJan172016.root'
    prefix = 'DataAnalysis'
    suffix = 'stdRes'
    vtxres = 0.00356
    scaling = 0.00458

    parser = ArgumentParser(description='Fit Beam Imaging results')
    parser.add_argument('-b', action='store_true', help='enable batch mode')
    parser.add_argument('-m', '--model', required=True, choices=['SingleGauss', \
                        'SingleGaussUncorrelated', 'DoubleGauss', 'SuperGauss', \
                        'TripleGauss', 'SuperDoubleGauss'], help='specify '+ \
                        'fit model')
    parser.add_argument('-c', '--bcid', required=True, nargs='+', \
                        choices=['41', '281', '872', '1783', '2063'], \
                        help='list one or more bunch crossings')
    parser.add_argument('-r', '--vtxres', choices=['low', 'high'], \
                        default=False, help='specify low or high to reduce '+ \
                        'or increase vertex resolution by 10%')
    args = parser.parse_args()

    from shapeFitter import shapeFitter
    from shapes.SingleGauss import SingleGauss, SingleGaussUncorrelated
    from shapes.DoubleGauss import DoubleGauss, SuperGauss
    from shapes.TripleGauss import TripleGauss, SuperDoubleGauss
    model = locals()[args.model]()
    if args.vtxres:
        factor = {'low': 0.9, 'high': 1.1}[args.vtxres]
        vtxres = vtxres * factor
        suffix = suffix + '_' + args.vtxres
    for bcid in args.bcid:
        shapeFitter(model, bcid, datafile, prefix, suffix, vtxres, scaling)

if __name__ == '__main__':
    main()
