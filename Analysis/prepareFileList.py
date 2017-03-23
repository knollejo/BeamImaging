def prepareFileList(directories, outputname):
    from pickle import dump
    from os import listdir, stat, mkdir
    from os.path import exists
    from ROOT import TTree

    files = []
    for directory in directories:
        allfiles = listdir(directory)
        for filename in allfiles:
            if filename.endswith('.root') and \
               stat(directory+'/'+filename).st_size > 0:
                files.append(directory+'/'+filename)
    if not exists('filelist'):
        mkdir('filelist')
    with open('filelist/'+outputname+'.txt', 'w') as f:
        f.write('\n'.join(files))
    print '<<< Found', len(files), 'files'

def main():
    from sys import argv as __ARGV__
    __ARGV__.append('-b')

    from argparse import ArgumentParser
    from json import load as decode

    parser = ArgumentParser(description='Make list of ROOT files')
    parser.add_argument('-b', action='store_true', help='enable batch mode')
    parser.add_argument('json', nargs=1, help='specify JSON file containing '+ \
                        'config information')
    args = parser.parse_args()

    with open(args.json[0]) as f:
        json = decode(f)
    name = str(json['prefix'])
    directories = [json['sourcepath']+'/'+d for d in json['sourcedirectories']]
    prepareFileList(directories, name)

if __name__ == '__main__':
    main()
