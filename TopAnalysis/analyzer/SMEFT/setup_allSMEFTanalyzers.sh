#!/bin/bash

echo "setting up files..."
for WC in {cQd8,cQq81,cQq83,cQu8,ctG,ctd8,ctq8,ctu8} # has to be same order as cross sections above!
do
  echo "Wilson coefficient: " $WC

  cp templates/analyzer_template_ditopmass300to1000.py cfg/
  mv cfg/analyzer_template_ditopmass300to1000.py cfg/analyzer_${WC}_ditopmass300to1000.py
  sed -i "s|WILSONCOEFFICIENT|$WC|g" cfg/analyzer_${WC}_ditopmass300to1000.py

  cp templates/analyzer_template_ditopmass1000to2000.py cfg/
  mv cfg/analyzer_template_ditopmass1000to2000.py cfg/analyzer_${WC}_ditopmass1000to2000.py
  sed -i "s|WILSONCOEFFICIENT|$WC|g" cfg/analyzer_${WC}_ditopmass1000to2000.py

  cp templates/analyzer_template_ditopmass2000to7000.py cfg/
  mv cfg/analyzer_template_ditopmass2000to7000.py cfg/analyzer_${WC}_ditopmass2000to7000.py
  sed -i "s|WILSONCOEFFICIENT|$WC|g" cfg/analyzer_${WC}_ditopmass2000to7000.py


  cp templates/analyzer_template.py cfg/
  mv cfg/analyzer_template.py cfg/analyzer_${WC}.py
  sed -i "s|WILSONCOEFFICIENT|$WC|g" cfg/analyzer_${WC}.py

  cp templates/run_template.sh ./
  mv run_template.sh run_${WC}alone_binned.sh
  sed -i "s|WILSONCOEFFICIENT|$WC|g" run_${WC}alone_binned.sh
  chmod +x run_${WC}alone_binned.sh
done
echo "done..."

echo "compiling..."
cd /nfs/dust/cms/user/jabuschh/PhD/ttbar/genstudy/CMSSW_9_4_6/src/UserCode/TopAnalysis/
scramv1 b -r -j8
