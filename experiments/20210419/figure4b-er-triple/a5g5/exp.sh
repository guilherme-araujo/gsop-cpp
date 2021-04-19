#!/bin/bash

#SBATCH --job-name=a5g5
#SBATCH --mem=96000
#SBATCH --cpus-per-task=48
##SBATCH --hint=compute_bound
#SBATCH --mail-user=guilherme.araujo@imd.ufrn.br
#SBATCH --mail-type=ALL
#SBATCH --time=24:0:0

module load softwares/python/3.6-anaconda-5.0.1
module load compilers/gnu/7.3

#argument parsing
for i in "$@"
do
case $i in
    -betaA=*|--extension=*)
    BETA_A="${i#*=}"
    shift # past argument=value
    ;;
    -betaB=*|--searchpath=*)
    BETA_B="${i#*=}"
    shift # past argument=value
    ;;
    -ephTime=*|--lib=*)
    EPHTIME="${i#*=}"
    shift # past argument=value
    ;;
    -threads=*|--lib=*)
    THREADNUM="${i#*=}"
    shift # past argument=value
    ;;
    -nodes=*|--lib=*)
    NODES="${i#*=}"
    shift # past argument=value
    ;;
    *)
          # unknown option
    ;;
esac
done

echo "BETA A  = ${BETA_A}"
echo "BETA B  = ${BETA_B}"
echo "EPHTIME = ${EPHTIME}"
echo "THREADNUM = ${THREADNUM}"
echo "NODES = ${NODES}"

FILE=gsop

if [ -f "$FILE" ]; then

	echo "$FILE exists"

	touch job-over.txt
	echo "scale=2; 0/1000" | bc > job-percent.txt
	for i in $(seq 1 1000);
	do
		python3 main.py --operation=newGraph --graphtype=er --numNodes=$NODES --numEdges=0.048
		./$FILE samples 1000 ephBonus 0.05 ephBonusB 0.05 ephStartRatio 0.6 ephBuildingRatio 0.6666 ephReusingRatio 0.1666 ephPopHistory 0 threads $THREADNUM cycles 5000 ephTime $EPHTIME ni 0 sampleId $i printPartials 1 rBMA 1 rBMB 1 bBA $BETA_A bBB $BETA_B >> a5g5.txt
		echo "scale=2; $i/1000" | bc > job-percent.txt
	done

	echo 1 > job-over.txt

else
    echo "$FILE not found."
fi
