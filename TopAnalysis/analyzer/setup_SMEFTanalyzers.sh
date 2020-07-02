#!/bin/bash

echo "setting up files..."
for WC in {cQd8,cQq81,cQq83,cQu8,ctG,ctd8,ctq8,ctu8}
do
  echo "Wilson coefficient: " $WC

  cp templates/analyzer_template.py ./
  mv analyzer_template.py analyzer_${WC}.py
  sed -i "s|WILSONCOEFFICIENT|$WC|g" analyzer_${WC}.py

  cp templates/run_template.sh ./
  mv run_template.sh run_${WC}_alone.sh
  sed -i "s|WILSONCOEFFICIENT|$WC|g" run_${WC}_alone.sh
  chmod +x run_${WC}_alone.sh
done
echo "done..."
