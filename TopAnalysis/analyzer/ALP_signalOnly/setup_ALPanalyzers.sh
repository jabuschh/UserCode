#!/bin/bash

#cross sections in pb for the values (-5,-4,-3,-2,-1,+1,+2,+3,+4,+5)
xsecs=(13.6 8.704 4.896 2.176 0.544 0.544 2.176 4.896 8.704 13.6)


echo "setting up files..."

for WC in {CaG,CaPhi}
do
  counter=0

  for VALUE in {min5,min4,min3,min2,min1,1,2,3,4,5}
  do
    echo "Wilson coefficient: " $WC "=" $VALUE

    cp templates/analyzer_template.py cfg/
    mv cfg/analyzer_template.py cfg/analyzer_${WC}_${VALUE}.py
    sed -i "s|WILSONCOEFFICIENT|$WC|g" cfg/analyzer_${WC}_${VALUE}.py
    sed -i "s|VALUE|$VALUE|g" cfg/analyzer_${WC}_${VALUE}.py
    sed -i "s|XSEC|${xsecs[counter]}|g" cfg/analyzer_${WC}_${VALUE}.py

    cp templates/run_template.sh ./
    mv run_template.sh run_${WC}.sh
    sed -i "s|WILSONCOEFFICIENT|$WC|g" run_${WC}.sh
    chmod +x run_${WC}.sh

    ((counter++))
  done
done
echo "done..."

echo "compiling..."
cd /nfs/dust/cms/user/jabuschh/PhD/ttbar/EFT_LO/genstudy/CMSSW_9_4_6/src/UserCode/TopAnalysis/
scramv1 b -r -j8
