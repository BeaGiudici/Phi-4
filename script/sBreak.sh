#!/bin/bash

cd ../main
make clean
echo "[" > ../results/SB_results.json

for j in 4 6 8 10 12 14
do     
     sed "s|@l|$j|g" ../include/lattice1.h > ../include/lattice.h
     make symm_break statistics > garbage.dat
          
     sed "s|@KAPPA@|0.15|g" ../INFILE/infile_SB > ../INFILE/infile1
     sed "s|@KAPPA@|0.16|g" ../INFILE/infile_SB > ../INFILE/infile2
     
     ./symm_break ../INFILE/infile1 rebinned_mag1.dat &
     ./symm_break ../INFILE/infile2 rebinned_mag2.dat &
     wait
     wait
 
     echo "{" >> ../results/SB_results.json
     ./statistics ../INFILE/infile1 rebinned_mag1.dat >> ../results/SB_results.json
	echo "}," >> ../results/SB_results.json
     echo "{" >> ../results/SB_results.json
     ./statistics ../INFILE/infile2 rebinned_mag2.dat >> ../results/SB_results.json
     echo "}," >> ../results/SB_results.json

     sed "s|@KAPPA@|0.17|g" ../INFILE/infile_SB > ../INFILE/infile1
     sed "s|@KAPPA@|0.18|g" ../INFILE/infile_SB > ../INFILE/infile2
     ./symm_break ../INFILE/infile1 rebinned_mag1.dat &
     ./symm_break ../INFILE/infile2 rebinned_mag2.dat &
     wait
     wait
     
     echo "{" >> ../results/SB_results.json
     ./statistics ../INFILE/infile1 rebinned_mag1.dat >> ../results/SB_results.json
     echo "}," >> ../results/SB_results.json
     echo "{" >> ../results/SB_results.json
     ./statistics ../INFILE/infile2 rebinned_mag2.dat >> ../results/SB_results.json
     echo "}," >> ../results/SB_results.json

     sed "s|@KAPPA@|0.19|g" ../INFILE/infile_SB > ../INFILE/infile1
     sed "s|@KAPPA@|0.20|g" ../INFILE/infile_SB > ../INFILE/infile2
     ./symm_break ../INFILE/infile1 rebinned_mag1.dat &
     ./symm_break ../INFILE/infile2 rebinned_mag2.dat &
     wait
     wait
     
     echo "{" >> ../results/SB_results.json
     ./statistics ../INFILE/infile1 rebinned_mag1.dat >> ../results/SB_results.json
     echo "}," >> ../results/SB_results.json
     echo "{" >> ../results/SB_results.json
     ./statistics ../INFILE/infile2 rebinned_mag2.dat >> ../results/SB_results.json
     echo "}," >> ../results/SB_results.json
     
     sed "s|@KAPPA@|0.21|g" ../INFILE/infile_SB > ../INFILE/infile1
     sed "s|@KAPPA@|0.22|g" ../INFILE/infile_SB > ../INFILE/infile2
     ./symm_break ../INFILE/infile1 rebinned_mag1.dat &
     ./symm_break ../INFILE/infile2 rebinned_mag2.dat &
     wait
     wait
     
     echo "{" >> ../results/SB_results.json
     ./statistics ../INFILE/infile1 rebinned_mag1.dat >> ../results/SB_results.json
     echo "}," >> ../results/SB_results.json
     echo "{" >> ../results/SB_results.json
     ./statistics ../INFILE/infile2 rebinned_mag2.dat >> ../results/SB_results.json
     if [[ $j == 14 ]] ; then
          echo "}" >> ../results/SB_results.json
     else
          echo "}," >> ../results/SB_results.json
     fi
done

echo ']' >> ../results/SB_results.json

make clean
rm rebinned_mag1.dat rebinned_mag2.dat garbage.dat
rm ../INFILE/infile1 ../INFILE/infile2

cd ../fit
python3 symm_break.py
cd ..
