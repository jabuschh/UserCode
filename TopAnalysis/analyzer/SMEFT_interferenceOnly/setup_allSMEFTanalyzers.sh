#!/bin/bash

# cross sections in pb
xsec_SM=0.0
xsecs=(
-12.6274144751 -10.1019315801 -7.57644868508 -5.05096579006 -2.52548289503 2.52548289503 5.05096579006 7.57644868508 10.1019315801 12.6274144751  # cQd8
-47.1327280882 -37.7061824706 -28.2796368529 -18.8530912353 -9.42654561764 9.42654561764 18.8530912353 28.2796368529 37.7061824706 47.1327280882  # cQq81
4.01752552071 3.21402041657 2.41051531243 1.60701020828 0.803505104142 -0.803505104142 -1.60701020828 -2.41051531243 -3.21402041657 -4.01752552071  # cQq83
-18.8057048412 -15.0445638729 -11.2834229047 -7.52228193646 -3.76114096823 3.76114096823 7.52228193646 11.2834229047 15.0445638729 18.8057048412  # cQu8
-30.546311278 -24.4370490224 -18.3277867668 -12.2185245112 -6.1092622556 6.1092622556 12.2185245112 18.3277867668 24.4370490224 30.546311278  # ctG
-11.3409079611 -9.07272636891 -6.80454477668 -4.53636318446 -2.26818159223 2.26818159223 4.53636318446 6.80454477668 9.07272636891 11.3409079611  # ctd8
-39.7636474841 -31.8109179873 -23.8581884905 -15.9054589937 -7.95272949683 7.95272949683 15.9054589937 23.8581884905 31.8109179873 39.7636474841  # ctq8
-21.330778837 -17.0646230696 -12.7984673022 -8.53231153479 -4.26615576739 4.26615576739 8.53231153479 12.7984673022 17.0646230696 21.330778837  # ctu8
)

counter=0

echo "setting up files..."
for WC in {cQd8,cQq81,cQq83,cQu8,ctG,ctd8,ctq8,ctu8} # has to be same order as cross sections above!
do
  echo "Wilson coefficient: " $WC

  cp templates/analyzer_template_ditopmass300to1000.py cfg/
  mv cfg/analyzer_template_ditopmass300to1000.py cfg/analyzer_${WC}_ditopmass300to1000.py
  sed -i "s|WILSONCOEFFICIENT|$WC|g" cfg/analyzer_${WC}_ditopmass300to1000.py
  sed -i "s|XSECSM|$xsec_SM|g"            cfg/analyzer_${WC}_ditopmass300to1000.py
  sed -i "s|XSECMIN5|${xsecs[counter]}|g" cfg/analyzer_${WC}_ditopmass300to1000.py
  ((counter++))
  sed -i "s|XSECMIN4|${xsecs[counter]}|g" cfg/analyzer_${WC}_ditopmass300to1000.py
  ((counter++))
  sed -i "s|XSECMIN3|${xsecs[counter]}|g" cfg/analyzer_${WC}_ditopmass300to1000.py
  ((counter++))
  sed -i "s|XSECMIN2|${xsecs[counter]}|g" cfg/analyzer_${WC}_ditopmass300to1000.py
  ((counter++))
  sed -i "s|XSECMIN1|${xsecs[counter]}|g" cfg/analyzer_${WC}_ditopmass300to1000.py
  ((counter++))
  sed -i "s|XSEC1|${xsecs[counter]}|g"    cfg/analyzer_${WC}_ditopmass300to1000.py
  ((counter++))
  sed -i "s|XSEC2|${xsecs[counter]}|g"    cfg/analyzer_${WC}_ditopmass300to1000.py
  ((counter++))
  sed -i "s|XSEC3|${xsecs[counter]}|g"    cfg/analyzer_${WC}_ditopmass300to1000.py
  ((counter++))
  sed -i "s|XSEC4|${xsecs[counter]}|g"    cfg/analyzer_${WC}_ditopmass300to1000.py
  ((counter++))
  sed -i "s|XSEC5|${xsecs[counter]}|g"    cfg/analyzer_${WC}_ditopmass300to1000.py
  ((counter++))

  cp cfg/analyzer_${WC}_ditopmass300to1000.py ./
  mv analyzer_${WC}_ditopmass300to1000.py analyzer_${WC}_ditopmass1000to2000.py
  sed -i "s|ditopmass300to1000|ditopmass1000to2000|g" analyzer_${WC}_ditopmass1000to2000.py
  sed -i "s|N_events_generated = cms.untracked.double(110000),|N_events_generated = cms.untracked.double(1300000),|g" analyzer_${WC}_ditopmass1000to2000.py
  mv analyzer_${WC}_ditopmass1000to2000.py cfg/

  cp cfg/analyzer_${WC}_ditopmass300to1000.py ./
  mv analyzer_${WC}_ditopmass300to1000.py analyzer_${WC}_ditopmass2000to7000.py
  sed -i "s|ditopmass300to1000|ditopmass2000to7000|g" analyzer_${WC}_ditopmass2000to7000.py
  sed -i "s|N_events_generated = cms.untracked.double(110000),|N_events_generated = cms.untracked.double(13000000),|g" analyzer_${WC}_ditopmass2000to7000.py 
  mv analyzer_${WC}_ditopmass2000to7000.py cfg/

  cp templates/analyzer_template.py cfg/
  mv cfg/analyzer_template.py cfg/analyzer_${WC}.py
  sed -i "s|WILSONCOEFFICIENT|$WC|g" cfg/analyzer_${WC}.py

  cp templates/run_template.sh ./
  mv run_template.sh run_${WC}alone_binned.sh
  sed -i "s|WILSONCOEFFICIENT|$WC|g" run_${WC}alone_binned.sh
  chmod +x run_${WC}alone_binned.sh

  ((counter+10))
done
echo "done..."

echo "compiling..."
cd /nfs/dust/cms/user/jabuschh/PhD/ttbar/genstudy/CMSSW_9_4_6/src/UserCode/TopAnalysis/
scramv1 b -r -j8
