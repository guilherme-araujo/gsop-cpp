#!/bin/bash
cd ./a9g1 && sbatch ./exp.sh -betaA=0.95 -betaB=0.95 -threads=72 -ephTime=30 -nodes=200 && cd ..