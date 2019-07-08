# Run the on mon on a DAQ raw file
# 
# RawDecoder.fcl : set the fragment number
#
# Usage ./om.sh 000run_x
# Produces a directory with a root file, a log file and all the plots 

echo "Build on: " `stat -c %y $MRB_BUILDDIR/dunetpc/lib/libSSPRawDecoder_module.so`

cp RawDecoder.fcl $MRB_BUILDDIR/dunetpc/job/RawDecoder.fcl

run=$1
directory="/home/phswbb/DUNE/software/PD/data"

file="np04_raw_run"$run"_dl1.root"

temp=`ls $directory/$file`

if [[ "$?" -ne "0" ]]; then
    echo -e "\nWrong run number!\n"
    exit
fi

echo "Processing: " `ls $directory/$file`

mkdir -p run_$run
cd run_$run
rm -f *.png
rm -f *.pdf

# Run art 
time art -c ../OnMon.fcl ${directory}/${file}>& output_$run.log
if [[ "$?" -ne "0" ]]; then
    echo -e "\nError running art!\n"
    cat output_$run.log
    exit
fi

less output_$run.log | grep "Event number" | tail -n1
echo "Max "`less output_$run.log | grep "Time \[s\]" | tail -n1`


# Create the plots
root -b -q -l ~/DUNE/software/PD/Plot.c
mv RawDecoder_hist.root RawDecoder_hist_$run.root
convert RawDecoder_*.png np04_raw_run$run.pdf

echo "PDF created " run_$run/np04_raw_run$run.pdf
echo "LOG file    " run_$run/output_$run.log

eog RawDecoder_10.png &