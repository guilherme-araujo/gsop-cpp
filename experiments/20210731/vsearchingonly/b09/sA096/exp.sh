#!/bin/bash

#SBATCH --job-name=a5g5
#SBATCH --mem=96000
#SBATCH --cpus-per-task=48
##SBATCH --hint=compute_bound
#SBATCH --mail-user=guilherme.araujo@imd.ufrn.br
#SBATCH --mail-type=ALL
#SBATCH --time=6:0:0

module load softwares/python/3.6-anaconda-5.0.1
module load compilers/gnu/7.3

FILE=gsop

if [ -f "$FILE" ]; then

	echo "$FILE exists"

	touch job-over.txt
	echo "scale=2; 0/1000" | bc > job-percent.txt
	for i in $(seq 1 1000); 
	do
		python3 main.py --operation=newGraph --graphtype=ba --numNodes=500 --numEdges=4
		./$FILE samples 1000 ephBonus 0.09 ephBonusB 0.09 ephStartRatio 0.4 ephBuildingRatio 0.5 ephReusingRatio 0.375 ephPopHistory 0 threads 72 cycles 0 ephTime 30 buildingTime 10 ni 0 sampleId $i printPartials 1 rBMA 1 rBMB 1 bBA 1.0 bBB 1.0 cheaterA 0.13333 cheaterB 0.4  sBA 0.96 sBB 0.96 >> a5g5.txt	
		echo "scale=2; $i/1000" | bc > job-percent.txt
	done

	echo 1 > job-over.txt

else
    echo "$FILE not found."
fi
