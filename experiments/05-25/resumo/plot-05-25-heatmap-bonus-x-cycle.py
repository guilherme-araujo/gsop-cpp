import seaborn as sns
import sys
import csv
from statistics import stdev
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import gc

#pd.set_option('display.max_rows', None)

files = [
    {'file': 'b2g2', 'bonus': '0.02'},
    {'file': 'b2g3', 'bonus': '0.03'},
    {'file': 'b2g4', 'bonus': '0.04'},
    {'file': 'b2g5', 'bonus': '0.05'},
    {'file': 'b2g6', 'bonus': '0.06'},
    {'file': 'b2g7', 'bonus': '0.07'},
    {'file': 'b2g8', 'bonus': '0.08'},  
]

files2 = [
    {'file': 'b2g2', 'bonus': '0.02'},
    {'file': 'b3g2', 'bonus': '0.03'},
    {'file': 'b4g2', 'bonus': '0.04'},
    {'file': 'b5g2', 'bonus': '0.05'},
    {'file': 'b6g2', 'bonus': '0.06'},
    {'file': 'b7g2', 'bonus': '0.07'},
    {'file': 'b8g2', 'bonus': '0.08'},  
]

al = []

'''
for f in files:
    with open(f['file']+'.txt') as csv_file_r:
        print(f['file']+' 1')
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
                e00.append([qta,qtb,result,f['bonus'],'γ A: 0.02-0.08'])
                
        al += e00'''

for f in files:
    with open(f['file']+'.txt') as csv_file_r:
        print(f['file']+' 1')
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
                e00.append([qta,qtb,result,f['bonus'],'γ A: 0.02-0.08',5000])
            else:
                qta = int(row[2])
                qtb = int(row[3])
                result = 'Undef.'
                cycle = int(row[1])
                e00.append([qta,qtb,result,f['bonus'],'γ A: 0.02-0.08',cycle])

                
        al += e00

'''for f in files2:
    with open(f['file']+'.txt') as csv_file_r:
        print(f['file']+' 1')
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
                e00.append([qta,qtb,result,f['bonus'],'α A: 0.02-0.08'])
                
        al += e00'''

#all = pd.DataFrame(al, columns=['qta', 'qtb', 'type', 'bonus', 'exp'])
all = pd.DataFrame(al, columns=['qta', 'qtb', 'type', 'bonus', 'exp', 'cycle'])

resumo = all.groupby(["bonus", "type", "exp"])["qta"].count().unstack(fill_value=0).stack().reset_index(name="sum")
allpivot = pd.pivot_table(all,values='qta',index='cycle',columns='bonus')
print(allpivot)


#fig_dims = (6, 4)
#fig, ax = plt.subplots(figsize=fig_dims)

print(resumo)
sns.heatmap(allpivot)
#sns.jointplot('qta','qtb',data=all,kind='kde')
#sns.violinplot(x="bonus",y="sum",data=resumo,hue="type")
plt.show()
'''
fig = sns.lineplot(data=resumo, x="bonus", y="sum", hue="type", style="exp")
plt.legend(bbox_to_anchor=(1.05, 1.0), loc='upper left')

ax.set(xlabel="γ/α A", ylabel="Fixation count" )
plt.setp(ax.get_xticklabels(), rotation=90, horizontalalignment='center')
plt.tight_layout()

plt.show()'''
#plt.savefig("lineplot.svg")
#plt.savefig("lineplot.png", dpi=200)
