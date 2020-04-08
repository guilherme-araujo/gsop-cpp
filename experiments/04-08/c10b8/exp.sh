#!/bin/bash

#SBATCH --job-name=c10b8
#SBATCH --mem=128000
#SBATCH --cpus-per-task=64
##SBATCH --hint=compute_bound
#SBATCH --exclusive
#SBATCH --mail-user=guilherme.araujo@imd.ufrn.br
#SBATCH --mail-type=ALL
#SBATCH --time=2-0:0

module load softwares/python/3.6-anaconda-5.0.1
module load compilers/gnu/7.3

FILE=main-2020-03-19
if [ -f "$FILE" ]; then
	echo "$FILE exists"
else
	g++ main.cpp -o main -O3 -lpthread
	chmod +x main
fi


touch job-over.txt
echo "scale=2; 0/1000" | bc > job-percent.txt
for i in $(seq 1 1000); 
do
	python3 main.py --operation=newGraph --graphtype=complete --numNodes=500 --numEdges=4
	./$FILE samples 5000 ephStartRatio 0.60 ephBuildingRatio 0.667 ephReusingRatio 0.166 ephBonus 0.08 ephBonusB 0.01 ephPopHistory 0 threads 72 cycles 5000 ephTime 30 ni 0 sampleId $i printPartials 1 rBMA 0.125 rBMB 8 bBA 0.95 bBB 0.95 >> exp.txt	
	echo "scale=2; $i/1000" | bc > job-percent.txt
done

echo 1 > job-over.txt
