import seaborn as sns
import sys
import csv
from statistics import stdev
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

e00 = pd.read_csv("e00.csv")
e001 = pd.read_csv("e001.csv")
e002 = pd.read_csv("e002.csv")
e003 = pd.read_csv("e003.csv")
e004 = pd.read_csv("e004.csv")
e005 = pd.read_csv("e005.csv")
e01 = pd.read_csv("e01.txt")
e015 = pd.read_csv("e015.txt")
e02 = pd.read_csv("e02.txt")
e025 = pd.read_csv("e025.txt")
e03 = pd.read_csv("e03.txt")
all = pd.concat([e00,e001,e002,e003,e004,e005,e01,e015,e02,e025,e03])
#all = pd.concat([e00,e001,e002,e003,e004,e005,e01,e015,e02])
teste = pd.read_csv("teste.csv", sep=",")

#all = all.loc[all["tfix"]>1]
#all = all.sample(500)

all["type"] = np.select(
    [all["numa"]==500, all["numb"]==500],
    ["A", "B"],
    default="Undef.")

#ex = all.loc[all["type"]=="Undef."]
#print(ex)
resumo = all.groupby(["bonus", "type"])["sample"].count().reset_index(name="sum")


#sns.swarmplot(data=all, x="bonus", y="tfix", hue="type")
sns.lineplot(data=resumo, x="bonus", y="sum", hue="type")
plt.show()
