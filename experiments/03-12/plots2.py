import seaborn as sns
import sys
import csv
from statistics import stdev
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

file = sys.argv[1]

e00 = pd.read_csv(file+".csv")

alla = e00.loc[(e00["type"]=='A')]
allb = e00.loc[(e00["type"]=='B')]

lp = sns.boxplot(data=e00, x="cyc", y="nodes", hue="type")
lp.set(xlabel="Simulation Cycle", ylabel="Node count")
if file=="e001":
  lp.set_title("A 0.01 x 0.08 B")
elif file=="e002":
  lp.set_title("A 0.02 x 0.07 B")
elif file=="e003":
  lp.set_title("A 0.03 x 0.06 B")
elif file=="e005-r":
  lp.set_title("A 0.04 x 0.05 B")
elif file=="e005":
  lp.set_title("A 0.05 x 0.05 B")
elif file=="e005-l":
  lp.set_title("A 0.05 x 0.04 B")
elif file=="e006":
  lp.set_title("A 0.06 x 0.03 B")
elif file=="e007":
  lp.set_title("A 0.07 x 0.02 B")
elif file=="e008":
  lp.set_title("A 0.08 x 0.01 B")
 

box = lp.get_position()
lp.set_position([box.x0, box.y0, box.width * 0.85, box.height])
lp.legend(loc='center right', bbox_to_anchor=(1.25, 0.5), ncol=1)
plt.savefig("boxplot-"+file+".png", dpi=200)

alla5k = alla.loc[alla["cyc"]==5000,"nodes"]
allb5k = allb.loc[allb["cyc"]==5000,"nodes"]

perc_file = open("perc-"+file+".txt", "a+")
txt = str(alla5k.describe().apply(lambda x: format(x, 'f'))) + "\n" + str(allb5k.describe().apply(lambda x: format(x, 'f'))) + "\n"
perc_file.write(txt)
perc_file.close()

winc_file = open("fixc-"+file+".txt", "a+")
total = len(alla5k)
awin = len(alla5k.loc[alla5k==500,])
bwin = len(allb5k.loc[allb5k==500,])
undef = total - awin - bwin
awperc = awin / total
bwperc = bwin / total
unperc = undef / total

winc = str(awin)+" "+str(bwin)+" "+str(undef)+"\n"+str(awperc)+" "+str(bwperc)+" "+str(unperc)+"\n"
winc_file.write(winc)
winc_file.close()

