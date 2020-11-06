#!/bin/bash

echo "setting up files..."
for WC in {cQd8,cQq81,cQq83,cQu8,ctd8,ctq8,ctu8,ctG}
do
  echo "Wilson coefficient: " $WC

  cp SMEFT_templates/SMEFT_GenLevelProducer_ditopmass300to1000_template.py ./
  mv SMEFT_GenLevelProducer_ditopmass300to1000_template.py SMEFT_GenLevelProducer_${WC}_ditopmass300to1000.py
  sed -i "s|WILSONCOEFFICIENT|$WC|g" SMEFT_GenLevelProducer_${WC}_ditopmass300to1000.py

  cp SMEFT_templates/SMEFT_GenLevelProducer_ditopmass1000to2000_template.py ./
  mv SMEFT_GenLevelProducer_ditopmass1000to2000_template.py SMEFT_GenLevelProducer_${WC}_ditopmass1000to2000.py
  sed -i "s|WILSONCOEFFICIENT|$WC|g" SMEFT_GenLevelProducer_${WC}_ditopmass1000to2000.py

  cp SMEFT_templates/SMEFT_GenLevelProducer_ditopmass2000to7000_template.py ./
  mv SMEFT_GenLevelProducer_ditopmass2000to7000_template.py SMEFT_GenLevelProducer_${WC}_ditopmass2000to7000.py
  sed -i "s|WILSONCOEFFICIENT|$WC|g" SMEFT_GenLevelProducer_${WC}_ditopmass2000to7000.py

  cp SMEFT_templates/run_local_template.sh ./
  mv run_local_template.sh run_local_${WC}.sh
  sed -i "s|WILSONCOEFFICIENT|$WC|g" run_local_${WC}.sh
done

for WC in ctG
do
  sed -i "s|5p0|0p25|g" SMEFT_GenLevelProducer_${WC}_ditopmass300to1000.py
  sed -i "s|4p0|0p2|g"  SMEFT_GenLevelProducer_${WC}_ditopmass300to1000.py
  sed -i "s|3p0|0p15|g" SMEFT_GenLevelProducer_${WC}_ditopmass300to1000.py
  sed -i "s|2p0|0p1|g"  SMEFT_GenLevelProducer_${WC}_ditopmass300to1000.py
  sed -i "s|1p0|0p05|g" SMEFT_GenLevelProducer_${WC}_ditopmass300to1000.py

  sed -i "s|5p0|0p25|g" SMEFT_GenLevelProducer_${WC}_ditopmass1000to2000.py
  sed -i "s|4p0|0p2|g"  SMEFT_GenLevelProducer_${WC}_ditopmass1000to2000.py
  sed -i "s|3p0|0p15|g" SMEFT_GenLevelProducer_${WC}_ditopmass1000to2000.py
  sed -i "s|2p0|0p1|g"  SMEFT_GenLevelProducer_${WC}_ditopmass1000to2000.py
  sed -i "s|1p0|0p05|g" SMEFT_GenLevelProducer_${WC}_ditopmass1000to2000.py

  sed -i "s|5p0|0p25|g" SMEFT_GenLevelProducer_${WC}_ditopmass2000to7000.py
  sed -i "s|4p0|0p2|g"  SMEFT_GenLevelProducer_${WC}_ditopmass2000to7000.py
  sed -i "s|3p0|0p15|g" SMEFT_GenLevelProducer_${WC}_ditopmass2000to7000.py
  sed -i "s|2p0|0p1|g"  SMEFT_GenLevelProducer_${WC}_ditopmass2000to7000.py
  sed -i "s|1p0|0p05|g" SMEFT_GenLevelProducer_${WC}_ditopmass2000to7000.py
done

echo "done..."
