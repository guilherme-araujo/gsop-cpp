import seaborn as sns
import sys
import csv
from statistics import stdev
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import matplotlib.ticker as mtick
import gc

files = [
    #{'file': 'a5g51p', 'cheater': '0.01'},
    #{'file': 'a5g55p', 'cheater': '0.05'},
    {'file': 'a5g510p', 'cheater': '0.1'}
]

al = []
nz = 0
for f in files:
    with open(f['file']+'.txt') as csv_file_r:
        print(f['file'])
        csv_reader = csv.reader(csv_file_r, delimiter=';')
        e00 = []
        for row in csv_reader:
            if(row[0]!='partial'):
                qta = int(row[0])
                qtb = int(row[1])
                result = 'Undef.'
                if qta == 500:
                    result = 'A'
                elif qta == 0:
                    result = 'B'
                cha = int(row[7])
                chb = int(row[8])
                if chb > 0:
                    nz += 1
                e00.append([qta,qtb,result,f['cheater'],cha,chb])
        al += e00

print(nz)
all = pd.DataFrame(al, columns=['qta', 'qtb', 'type', 'cheater', 'cha', 'chb'])
pd.set_option('display.float_format', lambda x: '%.6f' % x)

print(all.describe())