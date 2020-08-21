#! bash

rm -rf dataset regression.root *.jpg application*.root

root -l -b -q regression.c

root -l -b -q application.c

root -l application*.root
