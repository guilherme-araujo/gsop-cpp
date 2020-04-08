import seaborn as sns
import sys
import csv
from statistics import stdev
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

e00 = pd.read_csv("conv_bhistory-005.csv")

#all = e00

lp = sns.lineplot(data=e00, x="cyc", y="share", hue="type")
plt.savefig("behavior-005.png", dpi=200)
