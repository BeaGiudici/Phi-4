#!/bin/bash

cd ..
echo "[" > results/accRej.json
echo "[" > results/no_accRej.json
cd main
make clean

for j in 4 8 12 14 
do
	sed "s|@l|$j|g" ../include/lattice1.h > ../include/lattice.h
	make hybrid_MC no_acc_rej > garbage.dat

<<<<<<< HEAD
	for ((i=10; i<=50; i+=5)); do
=======
	for ((i=15; i<=50; i+=5)); do
>>>>>>> 16d13066fcae8d7c4cd1975c4b6fa202534775d4
		echo "L = $j	nStep = $i"
		echo "{" >> ../results/accRej.json
		echo "{" >> ../results/no_accRej.json
		sed "s|@STEP@|$i|g" ../INFILE/infile_AR > ../INFILE/infile
		./hybrid_MC ../INFILE/infile >> ../results/accRej.json &
		./no_acc_rej ../INFILE/infile >> ../results/no_accRej.json &
		wait
		wait
		if [[ $i == 50 && $j == 14 ]] ; then
			echo "}" >> ../results/accRej.json
			echo "}" >> ../results/no_accRej.json
		else
			echo "}," >> ../results/accRej.json
			echo "}," >> ../results/no_accRej.json
		fi
	done
done

echo "]" >> ../results/accRej.json
echo "]" >> ../results/no_accRej.json

rm garbage.dat
rm ../INFILE/infile
make clean

cd ../fit
python3 acc_rej.py > fit_results/final_AR_test.dat
cd ..
