# -*- coding: utf-8 -*-
import FWCore.ParameterSet.Config as cms

process = cms.Process("myprocess")
process.TFileService=cms.Service("TFileService",fileName=cms.string('file:/nfs/dust/cms/user/jabuschh/PhD/ttbar/EFT_LO/genstudy/CMSSW_9_4_6/src/UserCode/TopAnalysis/output/ALP/ALP_CaG_min1.root'))

##-------------------- Define the source  ----------------------------
process.maxEvents = cms.untracked.PSet(
input = cms.untracked.int32(1)
)

process.source = cms.Source("EmptySource")


##-------------------- User analyzer  --------------------------------
process.analysis  = cms.EDAnalyzer('ALPanalyzer',
filename        = cms.string('file:/nfs/dust/cms/user/jabuschh/PhD/ttbar/EFT_LO/genstudy/CMSSW_9_4_6/src/UserCode/TopAnalysis/gen_output/ALP/ALP_linear_CaG_min1.root'),
treename        = cms.string('events'),
dirname         = cms.string('boosted'),
isMCarlo        = cms.untracked.bool(True),
CrossSection    = cms.untracked.double(0.544),
IntLumi         = cms.untracked.double(100),    #not yet used
Triggers        = cms.untracked.vstring(''),
WCname          = cms.string('CaG')
)

process.p = cms.Path(process.analysis)
