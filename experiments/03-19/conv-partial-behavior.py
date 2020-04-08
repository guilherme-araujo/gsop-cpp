#!/usr/bin/python

import sys
import csv

graphFile = sys.argv[1]

rowlist = []

with open(graphFile) as csv_file:

    csv_reader = csv.reader(csv_file, delimiter=';')

    for row in csv_reader:
        if(row[0] == 'bhistory' and (int(row[2]) == 0 or (int(row[2]) % 100 == 99)  ) ):
            sid = int(row[1])
            cyc = int(row[2])
            searchA = int(row[3])
            searchB = int(row[4])
            prodA = int(row[5])
            prodB = int(row[6])
            useA = int(row[7])
            useB = int(row[8])
            sharedA = int(row[9])
            sharedB = int(row[10])

            allA = searchA + prodA + useA + sharedA
            allB = searchB + prodB + useB + sharedB

            if(allA!=0):
                searchAr = searchA / allA
                prodAr = prodA / allA
                useAr = useA / allA
                sharedAr = sharedA / allA
            else:
                searchAr = 0.0
                prodAr = 0.0
                useAr = 0.0
                sharedAr = 0.0
            
            if(allB!=0):
                searchBr = searchB / allB
                prodBr = prodB / allB
                useBr = useB / allB
                sharedBr = sharedB / allB
            else:
                searchBr = 0.0
                prodBr = 0.0
                useBr = 0.0
                sharedBr = 0.0

            rowlist.append([searchAr, cyc, 'sAr'])
            rowlist.append([prodAr, cyc, 'pAr'])
            rowlist.append([useAr, cyc, 'uAr'])
            rowlist.append([sharedAr, cyc, 'shAr'])

            rowlist.append([searchBr, cyc, 'sBr'])
            rowlist.append([prodBr, cyc, 'pBr'])
            rowlist.append([useBr, cyc, 'uBr'])
            rowlist.append([sharedBr, cyc, 'shBr'])
    else:
        if(row[2] == '-1'):
            previousCyc = int(row[2])
            sharedBr = rowlist[-1][0]
            useBr = rowlist[-2][0]
            prodBr = rowlist[-3][0]
            searchBr = rowlist[-4][0]

            sharedAr = rowlist[-5][0]
            useAr = rowlist[-6][0]
            prodAr = rowlist[-7][0]
            searchAr = rowlist[-8][0]
            for cyc in range(previousCyc+100, 5000, 100):
                rowlist.append([searchAr, cyc, 'sAr'])
                rowlist.append([prodAr, cyc, 'pAr'])
                rowlist.append([useAr, cyc, 'uAr'])
                rowlist.append([sharedAr, cyc, 'shAr'])

                rowlist.append([searchBr, cyc, 'sBr'])
                rowlist.append([prodBr, cyc, 'pBr'])
                rowlist.append([useBr, cyc, 'uBr'])
                rowlist.append([sharedBr, cyc, 'shBr'])


with open("conv_"+graphFile, "a+") as csv_file:
    writer = csv.writer(csv_file)
    for roww in rowlist:
        writer.writerow(roww)
