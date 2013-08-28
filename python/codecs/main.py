#! coding=utf-8

import chardet
import csv
import codecs
def main(filename = 'city_data_res2.csv'):

    f = csv.reader(open(filename))
    pos = 0
    for line in f :
        if pos == 0 : pos +=1 ;continue 
        if "GB"  in chardet.detect(line[1])['encoding']:
            newStr = line[1].decode('gbk').encode('utf-8')
            print newStr
    f.close()

def main2(filename = 'city_data_res2.csv'):
    f = codecs.open(filename, 'r', encoding='utf-8')
    for each in f:
        print f
if __name__ == "__main__":

    main2()
