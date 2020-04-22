#!/bin/bash

#SBATCH --job-name=sanity
#SBATCH --mem=128000
#SBATCH --cpus-per-task=64
##SBATCH --hint=compute_bound
#SBATCH --exclusive
#SBATCH --mail-user=guilherme.araujo@imd.ufrn.br
#SBATCH --mail-type=ALL
#SBATCH --time=0-16:0

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
echo "scale=2; 0/10" | bc > job-percent.txt
for i in $(seq 1 10); 
do
	python3 main.py --operation=newGraph --graphtype=ba --numNodes=500 --numEdges=4
	./$FILE samples 5000 ephStartRatio 0.60 ephBuildingRatio 0.667 ephReusingRatio 0.166 ephBonus 0.01 ephBonusB 0.08 ephPopHistory 0 threads 72 cycles 5000 ephTime 30 ni 0 sampleId $i printPartials 1 rBMA 8 rBMB 0.125 bBA 0.95 bBB 0.95 >> exp-ba.txt	
	echo "scale=2; $i/10" | bc > job-percent.txt
done

echo 1 > job-over.txt

touch job-over2.txt
echo "scale=2; 0/10" | bc > job-percent2.txt
for i in $(seq 1 10); 
do
	python3 main.py --operation=newGraph --graphtype=simple --numNodes=500 --numEdges=4
	./$FILE samples 5000 ephStartRatio 0.60 ephBuildingRatio 0.667 ephReusingRatio 0.166 ephBonus 0.01 ephBonusB 0.08 ephPopHistory 0 threads 72 cycles 5000 ephTime 30 ni 0 sampleId $i printPartials 1 rBMA 8 rBMB 0.125 bBA 0.95 bBB 0.95 >> exp-simple.txt	
	echo "scale=2; $i/10" | bc > job-percent2.txt
done

echo 1 > job-over2.txt

touch job-over3.txt
echo "scale=2; 0/10" | bc > job-percent3.txt
for i in $(seq 1 10); 
do
	python3 main.py --operation=newGraph --graphtype=complete --numNodes=500 
	./$FILE samples 5000 ephStartRatio 0.60 ephBuildingRatio 0.667 ephReusingRatio 0.166 ephBonus 0.01 ephBonusB 0.08 ephPopHistory 0 threads 72 cycles 5000 ephTime 30 ni 0 sampleId $i printPartials 1 rBMA 8 rBMB 0.125 bBA 0.95 bBB 0.95 >> exp-complete.txt	
	echo "scale=2; $i/10" | bc > job-percent3.txt
done

echo 1 > job-over3.txt