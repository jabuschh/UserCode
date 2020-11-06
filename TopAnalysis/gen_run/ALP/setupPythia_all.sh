#!/bin/bash

echo "setting up files..."
for VALUE in {min5,min4,min3,min2,min1,1,2,3,4,5}
do
  echo "CaG: " $VALUE

  cp templates/runPythia_ALP_CaPhi1_CaGVALUE.py ./
  mv runPythia_ALP_CaPhi1_CaGVALUE.py runPythia_ALP_CaPhi1_CaG${VALUE}.py
  sed -i "s|VALUE|$VALUE|g" runPythia_ALP_CaPhi1_CaG${VALUE}.py
done
echo ""
for VALUE in {min5,min4,min3,min2,min1,2,3,4,5}
do
  echo "CaPhi: " $VALUE

  cp templates/runPythia_ALP_CaPhiVALUE_CaG1.py ./
  mv runPythia_ALP_CaPhiVALUE_CaG1.py runPythia_ALP_CaPhi${VALUE}_CaG1.py
  sed -i "s|VALUE|$VALUE|g" runPythia_ALP_CaPhi${VALUE}_CaG1.py
done

echo "done..."
