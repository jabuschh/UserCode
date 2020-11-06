source /cvmfs/cms.cern.ch/cmsset_default.sh
eval `scramv1 runtime -sh`

export NR=${1}
print $NR

cd /nfs/dust/cms/user/jabuschh/PhD/ttbar/EFT_LO/genstudy/CMSSW_9_4_6/src/UserCode/TopAnalysis/gen_run/SMEFT/
cmsRun SMEFT_GenLevelProducer_ditopmass300to1000_template.py
cmsRun SMEFT_GenLevelProducer_ditopmass1000to2000_template.py
cmsRun SMEFT_GenLevelProducer_ditopmass2000to7000_template.py
