###=================================================
###  initialize ilcsoft
###=================================================

source /cvmfs/ilc.desy.de/sw/x86_64_gcc49_sl6/v02-00-02/init_ilcsoft.sh

###==================================================
###  Launch
###==================================================

cd /afs/desy.de/user/k/korpach/tmva/tmva_condor

rm -rf dataset regression.root *.jpg application*.root

root -l -b -q regression.c

root -l -b -q application.c

######################################################

