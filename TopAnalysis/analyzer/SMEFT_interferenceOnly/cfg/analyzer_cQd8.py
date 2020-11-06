# -*- coding: utf-8 -*-
import FWCore.ParameterSet.Config as cms

outfilename = 'file:/nfs/dust/cms/user/jabuschh/PhD/ttbar/genstudy/CMSSW_9_4_6/src/UserCode/TopAnalysis/output/SMEFT_squared_incl/SMEFT_squared_incl_cQd8.root'

process = cms.Process("myprocess")
process.TFileService=cms.Service("TFileService",fileName=cms.string(outfilename))

##-------------------- Define the source  ----------------------------
process.maxEvents = cms.untracked.PSet(
input = cms.untracked.int32(1)
)

process.source = cms.Source("EmptySource")


##-------------------- User analyzer  --------------------------------
process.analysis  = cms.EDAnalyzer('SMEFTanalyzer',
filename        = cms.string('file:/nfs/dust/cms/user/jabuschh/PhD/ttbar/genstudy/CMSSW_9_4_6/src/UserCode/TopAnalysis/gen_output/SMEFT_squared_incl/SMEFT_squared_incl_cQd8.root'),
treename        = cms.string('events'),
dirname         = cms.string('boosted'),
isMCarlo        = cms.untracked.bool(True),
CrossSection    = cms.untracked.double(447.118586872/10000), #110,000 events generated
IntLumi         = cms.untracked.double(100),    #not yet used
Triggers        = cms.untracked.vstring(''),
WCname          = cms.string('cQd8'),
ditopmassbin    = cms.string(''),   # '' for no ditop mass binning
filename_out    = cms.string(outfilename)
)

process.p = cms.Path(process.analysis)
