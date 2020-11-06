#!/bin/bash

echo "setting up files..."
for VALUE in {min5,min4,min3,min2,min1,1,2,3,4,5}
do
  echo "CaPhi: " $VALUE

  cp templates/runPythia_ALP_CaPhi_VALUE.py ./
  mv runPythia_ALP_CaPhi_VALUE.py runPythia_ALP_CaPhi_${VALUE}.py
  sed -i "s|VALUE|$VALUE|g" runPythia_ALP_CaPhi_${VALUE}.py
done
echo "done..."
