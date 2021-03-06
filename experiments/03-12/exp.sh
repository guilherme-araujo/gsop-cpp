#!/bin/bash

#Parametros
# $1 job-name $2 seq $3 graphtype $4 numNodes
# $5 numEdges $6 samples $7 ephBonus $8 ephPopHistory
# $9 threads $10 cycles $11 ephTime $12 ni
# $13 sampleId $14 printPartials $15 rBMA
# $16 rBMB $17 bBA $18 bBB $19 folder
# $20 outfile

#SBATCH --job-name=b001-001
#SBATCH --mem=128000
#SBATCH --cpus-per-task=64
##SBATCH --hint=compute_bound
#SBATCH --exclusive
#SBATCH --mail-user=guilherme.araujo@imd.ufrn.br
#SBATCH --mail-type=ALL
#SBATCH --time=2-0:0

module load softwares/python/3.6-anaconda-5.0.1
module load compilers/gnu/7.3

FILE=main-03-04-2020
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
	python3 main.py --operation=newGraph --graphtype=ba --numNodes=500 --numEdges=4
	./$FILE samples 5000 ephBonus 0.01 ephBonusB 0.08 ephPopHistory 0 threads 72 cycles 5000 ephTime 30 ni 0 sampleId $i printPartials 1 rBMA 8 rBMB 0.125 bBA 0.99 bBB 0.99 >> exp.txt	
	echo "scale=2; $i/1000" | bc > job-percent.txt
done

echo 1 > job-over.txt