# -*- coding: utf-8 -*-
import FWCore.ParameterSet.Config as cms

# WilsonCoeff = 'SMEFT_cQd8'
# WilsonCoeff = 'SMEFT_cQq81'
# WilsonCoeff = 'SMEFT_cQq83'
# WilsonCoeff = 'SMEFT_cQu8'
# WilsonCoeff = 'SMEFT_ctG'
# WilsonCoeff = 'SMEFT_ctd8'
# WilsonCoeff = 'SMEFT_ctq8'
WilsonCoeff = 'SMEFT_ctu8'

process = cms.Process("myprocess")
process.TFileService=cms.Service("TFileService",fileName=cms.string('file:/nfs/dust/cms/user/jabuschh/PhD/ttbar/EFT_LO/genstudy/CMSSW_9_4_6/src/UserCode/TopAnalysis/output/' + WilsonCoeff + '.root'))

##-------------------- Define the source  ----------------------------
process.maxEvents = cms.untracked.PSet(
input = cms.untracked.int32(1)
)

process.source = cms.Source("EmptySource")


##-------------------- User analyzer  --------------------------------
process.analysis  = cms.EDAnalyzer(
'Analysis_Template_MC',
filename        = cms.string('file:/nfs/dust/cms/user/jabuschh/PhD/ttbar/EFT_LO/genstudy/CMSSW_9_4_6/src/UserCode/TopAnalysis/gen_output/' + WilsonCoeff + '.root'),
treename        = cms.string('events'),
dirname         = cms.string('boosted'),
isMCarlo        = cms.untracked.bool(True),
CrossSection    = cms.untracked.double(100),
IntLumi         = cms.untracked.double(100),
Triggers        = cms.untracked.vstring(''),
)

process.p = cms.Path(process.analysis)
