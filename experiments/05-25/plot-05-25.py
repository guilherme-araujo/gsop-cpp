import seaborn as sns
import sys
import csv
from statistics import stdev
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

pd.set_option('display.max_rows', None)

files = [
    {'file': 'b2g2', 'bonus': '0.02'},
    {'file': 'b2g3', 'bonus': '0.03'},
    {'file': 'b2g4', 'bonus': '0.04'},
    {'file': 'b2g5', 'bonus': '0.05'},
    {'file': 'b2g6', 'bonus': '0.06'},
    {'file': 'b2g7', 'bonus': '0.07'},
    {'file': 'b2g8', 'bonus': '0.08'},
    
]

all = pd.DataFrame([], columns=['qta', 'qtb', 'type'])
for f in files:
    #with open(f['file']+'/'+f['file']+'.txt') as csv_file_r:
    with open(f['file']+'.txt') as csv_file_r:
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
        e00["bonus"]=f['bonus']
        all = pd.concat([all, e00])


#all = pd.concat([e00,e001,e002,e003,e004,e005,e006,e007,e008,e009,e010,e011,e012,e013,e014,e015])


#all[""] = np.select(
#    [all["numa"]==500, all["numb"]==500],
#    ["A", "B"],
#    default="Undef.")

#ex = all.loc[all["type"]=="Undef."]
#print(ex)
resumo = all.groupby(["bonus", "type"])["qta"].count().unstack(fill_value=0).stack().reset_index(name="sum")

resumo2 = resumo
for x in resumo["bonus"].unique():
    u_x = all.loc[(all["type"]=="Undef.") & (all["bonus"]==x)]    
    u_x_a = u_x["qta"].sum()
    u_x_b = u_x["qtb"].sum()
    col_a = {"bonus":x, "type":"Undef. A", "sum":u_x_a/500}
    col_b = {"bonus":x, "type":"Undef. B", "sum":u_x_b/500}
    resumo = resumo.append(col_a, ignore_index=True)
    resumo = resumo.append(col_b, ignore_index=True)
print(resumo)
fig_dims = (6, 4)
fig, ax = plt.subplots(figsize=fig_dims)


plt.fill_between(resumo[~resumo.bonus.duplicated()].bonus, 0, 
                 resumo.loc[resumo["type"]=="Undef. A", "sum"], facecolor="lawngreen", alpha=0.5, label="A %")
plt.fill_between(resumo[~resumo.bonus.duplicated()].bonus, resumo.loc[resumo["type"]=="Undef. A", "sum"], 
                 resumo.loc[resumo["type"]=="Undef.", "sum"], facecolor="forestgreen", alpha=0.5, label="B %")
fig = sns.lineplot(data=resumo2, x="bonus", y="sum", hue="type")
plt.legend(bbox_to_anchor=(1.05, 1.0), loc='upper left')
plt.tight_layout()
ax.set(xlabel="γ A", ylabel="Fixation count" )
plt.setp(ax.get_xticklabels(), rotation=90, horizontalalignment='center')

#plt.show()
plt.savefig("lineplot.svg")
plt.savefig("lineplot.png", dpi=200)
