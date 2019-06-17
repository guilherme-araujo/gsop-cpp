#!/bin/bash
#./main-centosV7 samples 5000 ephBonus 0  ephPopHistory 0 threads 40 cycles 5000 ephTime 30 ni 1 > eph00.txt
#./main-centosV7 samples 5000 ephBonus 0.05 ephPopHistory 0 threads 40 cycles 5000 ephTime 30 ni 1 > eph005.txt
#./main-centosV7 samples 5000 ephBonus 0.1 ephPopHistory 0 threads 40 cycles 5000 ephTime 30 ni 1 > eph01.txt

for i in $(seq 0 999); 
do
	python3 main.py --operation=newGraph --graphtype=ba --numNodes=500 --numEdges=4
	./main samples 30 ephBonus 0.15 ephPopHistory 0 threads 3 cycles 1000 ephTime 30 ni 0 sampleId $i
#	./main-centosV7 samples 5000 ephBonus 0.15 ephPopHistory 0 threads 40 cycles 5000 ephTime 30 ni 1
done
#./main-centosV7 samples 5000 ephBonus 0.2 ephPopHistory 0 threads 40 cycles 5000 ephTime 30 ni 1 > eph02.txt
#./main-centosV7 samples 5000 ephBonus 0.25 ephPopHistory 0 threads 40 cycles 5000 ephTime 30 ni 1 > eph025.txt
#./main-centosV7 samples 5000 ephBonus 0.3 ephPopHistory 0 threads 40 cycles 5000 ephTime 30 ni 1 > eph03.txt
