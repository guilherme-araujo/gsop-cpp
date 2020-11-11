import seaborn as sns
import sys
import csv
from statistics import stdev
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import matplotlib.ticker as mtick
import gc

#pd.set_option('display.max_rows', None)

files = [
    {'file': 'b2g2', 'bonus': np.log(1.0)}, #'ωA/ωB = 1.0'
    {'file': 'a3g2', 'bonus': np.log(2.0)}, #'ωA/ωB = 2.0'
    {'file': 'a4g2', 'bonus': np.log(3.0)}, #'ωA/ωB = 3.0'
    {'file': 'a5g2', 'bonus': np.log(4.0)}, #'ωA/ωB = 4.0'
    {'file': 'a6g2', 'bonus': np.log(5.0)}, #'ωA/ωB = 5.0'
    {'file': 'a7g2', 'bonus': np.log(6.0)}, #'ωA/ωB = 6.0'
    {'file': 'a8g2', 'bonus': np.log(7.0)}, #'ωA/ωB = 7.0'
]

files2 = [
    {'file': 'b3g2', 'bonus': np.log(0.5)}, #'ωA/ωB = 0.5'
    {'file': 'b4g2', 'bonus': np.log(0.333)}, #'ωA/ωB = 0.333'
    {'file': 'b5g2', 'bonus': np.log(0.25)}, #'ωA/ωB = 0.25'
    {'file': 'b6g2', 'bonus': np.log(0.2)}, #'ωA/ωB = 0.2'
    {'file': 'b7g2', 'bonus': np.log(0.167)}, #'ωA/ωB = 0.167'
    {'file': 'b8g2', 'bonus': np.log(0.143)}, #'ωA/ωB = 0.143'
]

al = []

for f in files:
    with open(f['file']+'/'+f['file']+'.txt') as csv_file_r:
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
                e00.append([qta,qtb,result,f['bonus'],'γ A: 0.02-0.08'])
                
        al += e00

for f in files2:
    with open(f['file']+'/'+f['file']+'.txt') as csv_file_r:
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
                e00.append([qta,qtb,result,f['bonus'],'γ A: 0.02-0.08'])
                
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

all = pd.DataFrame(al, columns=['qta', 'qtb', 'type', 'bonus', 'exp'])
#all = pd.DataFrame(al, columns=['qta', 'qtb', 'type', 'bonus', 'exp', 'cycle'])
print(all)
resumo = all.groupby(["bonus", "type", "exp"])["qta"].count().unstack(fill_value=0).stack().reset_index(name="sum")
#allpivot = pd.pivot_table(all,values='qta',index='cycle',columns='bonus')
#print(allpivot)


fig_dims = (6, 4)
fig, ax = plt.subplots(figsize=fig_dims)

print(resumo)
#sns.heatmap(allpivot)
#sns.jointplot('qta','qtb',data=all,kind='kde')
#sns.violinplot(x="bonus",y="sum",data=resumo,hue="type")
#plt.show()

fig = sns.lineplot(data=resumo, x="bonus", y="sum", hue="type")
plt.legend(bbox_to_anchor=(1.05, 1.0), loc='upper left')

#ax.set(xlabel="log(ωA/ωB)", ylabel="Fixation %", xscale='log' )
ax.set(xlabel="ln(ωA/ωB)", ylabel="Fixation %" )
ax.yaxis.set_major_formatter(mtick.PercentFormatter(xmax=5000000))
ax.xaxis.set_major_formatter(mtick.ScalarFormatter())
ax.set_xticks(resumo['bonus'].unique())
plt.setp(ax.get_xticklabels(), rotation=90, horizontalalignment='center')
plt.tight_layout()

#plt.show()
plt.savefig("lineplot-wawb2.svg")
plt.savefig("lineplot-wawb2.png", dpi=200)
