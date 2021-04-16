#!/bin/bash
cd ./a5g5 && sbatch ./exp.sh -betaA=0.95 -betaB=0.95 -threads=72 -ephTime=30 -nodes=400 && cd ..