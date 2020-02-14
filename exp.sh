#!/bin/bash

#Parametros
# $1 job-name $2 seq $3 graphtype $4 numNodes
# $5 numEdges $6 samples $7 ephBonus $8 ephPopHistory
# $9 threads $10 cycles $11 ephTime $12 ni
# $13 sampleId $14 printPartials $15 rBMA
# $16 rBMB $17 bBA $18 bBB $19 folder
# $20 outfile

#SBATCH --job-name=$1
#SBATCH --mem=128000
#SBATCH --cpus-per-task=64
##SBATCH --hint=compute_bound
#SBATCH --exclusive
#SBATCH --mail-user=guilherme.araujo@imd.ufrn.br
#SBATCH --mail-type=ALL
#SBATCH --time=2-0:0

module load softwares/python/3.6-anaconda-5.0.1
module load compilers/gnu/7.3

FILE=main
if [ -f "$FILE" ]; then
	echo "$FILE exists"
else
	g++ main.cpp -o main -O3 -lpthread
	chmod +x main
fi

mkdir $19

for i in $(seq 0 $2); 
do
	python3 main.py --operation=newGraph --graphtype=$3 --numNodes=$4 --numEdges=$5
	./main samples $6 ephBonus $7 ephPopHistory $8 threads $9 cycles $10 ephTime $11 ni $12 sampleId $i printPartials $14 rBMA $15 rBMB $16 bBA $17 bBB $18 >> $19/$20
done

