import sys
import csv
from statistics import stdev
import numpy as np
import pandas as pd

all = pd.DataFrame([], columns=['qta', 'qtb', 'type'])
csv_file_r = open('b012.txt.bkp')
csv_reader = csv.reader(csv_file_r, delimiter=';')
qtas = []
qtbs = []
results = []
for row in csv_reader:
    if(row[0]!='partial'):            
        qta = int(row[0])
        qtb = int(row[1])
        result = 'Undef.'
        if qta == 500:
            result = 'A'
        elif qta == 0:
            result = 'B'
        qtas.append(qta)
        qtbs.append(qtb)
        results.append(result)
e00 = pd.DataFrame(list(zip(qtas,qtbs,results)), columns=['qta', 'qtb', 'type'])
all = pd.concat([all, e00])

print(len(all.loc[all['qta']==500]))
print(len(all.loc[all['qtb']==500]))