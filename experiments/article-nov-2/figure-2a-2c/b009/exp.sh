#!/bin/bash

#SBATCH --job-name=b009
#SBATCH --mem=128000
#SBATCH --cpus-per-task=64
##SBATCH --hint=compute_bound
#SBATCH --exclusive
#SBATCH --mail-user=guilherme.araujo@imd.ufrn.br
#SBATCH --mail-type=ALL
#SBATCH --time=0-12:0

module load softwares/python/3.6-anaconda-5.0.1
module load compilers/gnu/8.3

FILE=gsop

if [ -f "$FILE" ]; then

echo "$FILE exists"


touch job-over.txt
echo "scale=2; 0/100" | bc > job-percent.txt
for i in $(seq 1 100); 
do
	python3 main.py --operation=newGraph --graphtype=er --numNodes=500 --numEdges=0.02
	./$FILE samples 5000 ephBonus 0.09 ephBonusB 0.0 ephStartRatio 0.50 ephBuildingRatio 0.0 ephReusingRatio 0.0 ephPopHistory 0 threads 72 cycles 0 ephTime 30 ni 0 sampleId $i printPartials 1 rBMA 1 rBMB -1 bBA -1 bBB -1 bEph 0 ephBirthGenChance 0.5 >> b009.txt	
	echo "scale=2; $i/100" | bc > job-percent.txt
done

echo 1 > job-over.txt


else
    	echo "$FILE not found."
fi
