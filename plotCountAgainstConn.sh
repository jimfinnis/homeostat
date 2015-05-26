#!/bin/sh

./a.out 2 >f
r plotCountAgainstConn.r
mv f       homeostat_visc09_2units.dat
mv foo.pdf homeostat_visc09_2units.pdf
echo 2 done
./a.out 3 >f
r plotCountAgainstConn.r
mv f       homeostat_visc09_3units.dat
mv foo.pdf homeostat_visc09_3units.pdf
echo 3 done
./a.out 4 >f
r plotCountAgainstConn.r
mv f       homeostat_visc09_4units.dat
mv foo.pdf homeostat_visc09_4units.pdf
echo 4 done
./a.out 5 >f
r plotCountAgainstConn.r
mv f       homeostat_visc09_5units.dat
mv foo.pdf homeostat_visc09_5units.pdf
echo 5 done
./a.out 6 >f
r plotCountAgainstConn.r
mv f       homeostat_visc09_6units.dat
mv foo.pdf homeostat_visc09_6units.pdf
