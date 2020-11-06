# -*- coding: utf-8 -*-
import FWCore.ParameterSet.Config as cms

process = cms.Process("myprocess")
process.TFileService=cms.Service("TFileService",fileName=cms.string('file:/nfs/dust/cms/user/jabuschh/PhD/ttbar/genstudy/CMSSW_9_4_6/src/UserCode/TopAnalysis/output/ALP_interference_colorstudy/ALP_interference_colorfromSM.root'))

##-------------------- Define the source  ----------------------------
process.maxEvents = cms.untracked.PSet(
input = cms.untracked.int32(1)
)

process.source = cms.Source("EmptySource")


##-------------------- User analyzer  --------------------------------
process.analysis  = cms.EDAnalyzer(
'analysis_module',
filename        = cms.string('file:/nfs/dust/cms/user/jabuschh/PhD/ttbar/ntuplizer/output/interference/ALP_ttbar_interference_1_ntuple.root'),
treename        = cms.string('Delphes'),
dirname         = cms.string(''),
isMCarlo        = cms.untracked.bool(True),
CrossSection    = cms.untracked.double(1),
IntLumi         = cms.untracked.double(100),    #not yet used
Triggers        = cms.untracked.vstring('')
)

process.p = cms.Path(process.analysis)
