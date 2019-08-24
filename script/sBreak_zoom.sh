#!/bin/bash

cd ../main
make clean
echo "[" > ../results/SB_results_zoom.json

for j in 4 6 8 10 12 14
do     
     sed "s|@l|$j|g" ../include/lattice1.h > ../include/lattice.h
     make symm_break statistics > garbage.dat
          
     sed "s|@KAPPA@|0.18|g" ../INFILE/infile_SB > ../INFILE/infile1
     sed "s|@KAPPA@|0.181|g" ../INFILE/infile_SB > ../INFILE/infile2
     
     ./symm_break ../INFILE/infile1 rebinned_mag1.dat &
     ./symm_break ../INFILE/infile2 rebinned_mag2.dat &
     wait
     wait
 
     echo "{" >> ../results/SB_results_zoom.json
     ./statistics ../INFILE/infile1 rebinned_mag1.dat >> ../results/SB_results_zoom.json
	echo "}," >> ../results/SB_results_zoom.json
     echo "{" >> ../results/SB_results_zoom.json
     ./statistics ../INFILE/infile2 rebinned_mag2.dat >> ../results/SB_results_zoom.json
     echo "}," >> ../results/SB_results_zoom.json

     sed "s|@KAPPA@|0.182|g" ../INFILE/infile_SB > ../INFILE/infile1
     sed "s|@KAPPA@|0.183|g" ../INFILE/infile_SB > ../INFILE/infile2
     ./symm_break ../INFILE/infile1 rebinned_mag1.dat &
     ./symm_break ../INFILE/infile2 rebinned_mag2.dat &
     wait
     wait
     
     echo "{" >> ../results/SB_results_zoom.json
     ./statistics ../INFILE/infile1 rebinned_mag1.dat >> ../results/SB_results_zoom.json
     echo "}," >> ../results/SB_results_zoom.json
     echo "{" >> ../results/SB_results_zoom.json
     ./statistics ../INFILE/infile2 rebinned_mag2.dat >> ../results/SB_results_zoom.json
     echo "}," >> ../results/SB_results_zoom.json

     sed "s|@KAPPA@|0.184|g" ../INFILE/infile_SB > ../INFILE/infile1
     sed "s|@KAPPA@|0.185|g" ../INFILE/infile_SB > ../INFILE/infile2
     ./symm_break ../INFILE/infile1 rebinned_mag1.dat &
     ./symm_break ../INFILE/infile2 rebinned_mag2.dat &
     wait
     wait
     
     echo "{" >> ../results/SB_results_zoom.json
     ./statistics ../INFILE/infile1 rebinned_mag1.dat >> ../results/SB_results_zoom.json
     echo "}," >> ../results/SB_results_zoom.json
     echo "{" >> ../results/SB_results_zoom.json
     ./statistics ../INFILE/infile2 rebinned_mag2.dat >> ../results/SB_results_zoom.json
     echo "}," >> ../results/SB_results_zoom.json
     
     sed "s|@KAPPA@|0.186|g" ../INFILE/infile_SB > ../INFILE/infile1
     sed "s|@KAPPA@|0.1865|g" ../INFILE/infile_SB > ../INFILE/infile2
     ./symm_break ../INFILE/infile1 rebinned_mag1.dat &
     ./symm_break ../INFILE/infile2 rebinned_mag2.dat &
     wait
     wait
     
     echo "{" >> ../results/SB_results_zoom.json
     ./statistics ../INFILE/infile1 rebinned_mag1.dat >> ../results/SB_results_zoom.json
     echo "}," >> ../results/SB_results_zoom.json
     echo "{" >> ../results/SB_results_zoom.json
     ./statistics ../INFILE/infile2 rebinned_mag2.dat >> ../results/SB_results_zoom.json
     echo "}," >> ../results/SB_results_zoom.json

     sed "s|@KAPPA@|0.187|g" ../INFILE/infile_SB > ../INFILE/infile1
     sed "s|@KAPPA@|0.1875|g" ../INFILE/infile_SB > ../INFILE/infile2
     ./symm_break ../INFILE/infile1 rebinned_mag1.dat &
     ./symm_break ../INFILE/infile2 rebinned_mag2.dat &
     wait
     wait
     
     echo "{" >> ../results/SB_results_zoom.json
     ./statistics ../INFILE/infile1 rebinned_mag1.dat >> ../results/SB_results_zoom.json
     echo "}," >> ../results/SB_results_zoom.json
     echo "{" >> ../results/SB_results_zoom.json
     ./statistics ../INFILE/infile2 rebinned_mag2.dat >> ../results/SB_results_zoom.json
     echo "}," >> ../results/SB_results_zoom.json

     sed "s|@KAPPA@|0.188|g" ../INFILE/infile_SB > ../INFILE/infile1
     sed "s|@KAPPA@|0.189|g" ../INFILE/infile_SB > ../INFILE/infile2
     ./symm_break ../INFILE/infile1 rebinned_mag1.dat &
     ./symm_break ../INFILE/infile2 rebinned_mag2.dat &
     wait
     wait
     
     echo "{" >> ../results/SB_results_zoom.json
     ./statistics ../INFILE/infile1 rebinned_mag1.dat >> ../results/SB_results_zoom.json
     echo "}," >> ../results/SB_results_zoom.json
     echo "{" >> ../results/SB_results_zoom.json
     ./statistics ../INFILE/infile2 rebinned_mag2.dat >> ../results/SB_results_zoom.json
     echo "}," >> ../results/SB_results_zoom.json

     sed "s|@KAPPA@|0.190|g" ../INFILE/infile_SB > ../INFILE/infile1
     sed "s|@KAPPA@|0.191|g" ../INFILE/infile_SB > ../INFILE/infile2
     ./symm_break ../INFILE/infile1 rebinned_mag1.dat &
     ./symm_break ../INFILE/infile2 rebinned_mag2.dat &
     wait
     wait
     
     echo "{" >> ../results/SB_results_zoom.json
     ./statistics ../INFILE/infile1 rebinned_mag1.dat >> ../results/SB_results_zoom.json
     echo "}," >> ../results/SB_results_zoom.json
     echo "{" >> ../results/SB_results_zoom.json
     ./statistics ../INFILE/infile2 rebinned_mag2.dat >> ../results/SB_results_zoom.json
     if [[ $j == 14 ]] ; then
          echo "}" >> ../results/SB_results_zoom.json
     else
          echo "}," >> ../results/SB_results_zoom.json
     fi

done

echo ']' >> ../results/SB_results_zoom.json

make clean
rm rebinned_mag1.dat rebinned_mag2.dat garbage.dat
rm ../INFILE/infile1 ../INFILE/infile2

cd ../fit
python3 symm_break.py ../results/SB_results_zoom.json
cd ..
