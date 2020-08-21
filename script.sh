#! bash

##### for 30
root -l -b -q fitres_global.c
mv out.txt out_30.txt
mv *.jpg ./pict/30/.
###############################################
##### for 35
sed 's/( float( n302 )/( float( n352 )/g' fitres_global.c > fitres_global1.c
mv fitres_global1.c fitres_global.c
root -l -b -q fitres_global.c
mv out.txt out_35.txt
mv *.jpg ./pict/35/.
###############################################
##### for 40
sed 's/( float( n352 )/( float( n402 )/g' fitres_global.c > fitres_global1.c
mv fitres_global1.c fitres_global.c
root -l -b -q fitres_global.c
mv out.txt out_40.txt
mv *.jpg ./pict/40/.
###############################################
##### for 45
sed 's/( float( n402 )/( float( n452 )/g' fitres_global.c > fitres_global1.c
mv fitres_global1.c fitres_global.c
root -l -b -q fitres_global.c
mv out.txt out_45.txt
mv *.jpg ./pict/45/.
###############################################
##### for 50
sed 's/( float( n452 )/( float( n502 )/g' fitres_global.c > fitres_global1.c
mv fitres_global1.c fitres_global.c
root -l -b -q fitres_global.c
mv out.txt out_50.txt
mv *.jpg ./pict/50/.
###############################################
##### for 55
sed 's/( float( n502 )/( float( n552 )/g' fitres_global.c > fitres_global1.c
mv fitres_global1.c fitres_global.c
root -l -b -q fitres_global.c
mv out.txt out_55.txt
mv *.jpg ./pict/55/.
###############################################
##### for 60
sed 's/( float( n552 )/( float( n602 )/g' fitres_global.c > fitres_global1.c
mv fitres_global1.c fitres_global.c
root -l -b -q fitres_global.c
mv out.txt out_60.txt
mv *.jpg ./pict/60/.
###############################################
##### for 65
sed 's/( float( n602 )/( float( n652 )/g' fitres_global.c > fitres_global1.c
mv fitres_global1.c fitres_global.c
root -l -b -q fitres_global.c
mv out.txt out_65.txt
mv *.jpg ./pict/65/.
###############################################
##### for 70
sed 's/( float( n652 )/( float( n702 )/g' fitres_global.c > fitres_global1.c
mv fitres_global1.c fitres_global.c
root -l -b -q fitres_global.c
mv out.txt out_70.txt
mv *.jpg ./pict/70/.
###############################################
##### for 75
sed 's/( float( n702 )/( float( n752 )/g' fitres_global.c > fitres_global1.c
mv fitres_global1.c fitres_global.c
root -l -b -q fitres_global.c
mv out.txt out_75.txt
mv *.jpg ./pict/75/.
###############################################
##### for 80
sed 's/( float( n752 )/( float( n802 )/g' fitres_global.c > fitres_global1.c
mv fitres_global1.c fitres_global.c
root -l -b -q fitres_global.c
mv out.txt out_80.txt
mv *.jpg ./pict/80/.
###############################################
sed 's/( float( n802 )/( float( n302 )/g' fitres_global.c > fitres_global1.c
mv fitres_global1.c fitres_global.c
###############################################

