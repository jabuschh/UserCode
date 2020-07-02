./setup_SMEFTanalyzers.sh

echo "compiling..."

cd ../
scramv1 b -r -j8
cd analyzer/

echo "compiling finished..."
echo

cmsRun analyzer_cQd8.py
cmsRun analyzer_cQq81.py
cmsRun analyzer_cQq83.py
cmsRun analyzer_cQu8.py
cmsRun analyzer_ctG.py
cmsRun analyzer_ctd8.py
cmsRun analyzer_ctq8.py
cmsRun analyzer_ctu8.py
