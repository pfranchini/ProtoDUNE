
run=$1
histo=$2
verbose=$3

sed -e "s/HISTO/$histo/g" FFT_3.c > FFT_3.tmp1
sed -e "s/RUN/$run/g" FFT_3.tmp1 > FFT.c

rm FFT_3.tmp1

if [ "$verbose" == "v" ]; then
 
    root -l FFT.c
    
else
    
    root -b -q -l FFT.c

fi


