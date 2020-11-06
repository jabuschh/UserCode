# -*- coding: utf-8 -*-
import FWCore.ParameterSet.Config as cms

outfilename = 'file:/nfs/dust/cms/user/jabuschh/PhD/ttbar/genstudy/CMSSW_9_4_6/src/UserCode/TopAnalysis/output/SMEFT/SMEFT_cQd8_ditopmass1000to2000.root'

process = cms.Process("myprocess")
process.TFileService=cms.Service("TFileService",fileName=cms.string(outfilename))

##-------------------- Define the source  ----------------------------
process.maxEvents = cms.untracked.PSet(
input = cms.untracked.int32(1)
)

process.source = cms.Source("EmptySource")


##-------------------- User analyzer  --------------------------------
process.analysis  = cms.EDAnalyzer('SMEFTanalyzer',
filename           = cms.string('file:/nfs/dust/cms/user/jabuschh/PhD/ttbar/genstudy/CMSSW_9_4_6/src/UserCode/TopAnalysis/gen_output/SMEFT/SMEFT_cQd8_ditopmass1000to2000.root'),
treename           = cms.string('events'),
dirname            = cms.string('boosted'),
filename_out       = cms.string(outfilename),
Triggers           = cms.untracked.vstring(''),
isMCarlo           = cms.untracked.bool(True),
IntLumi            = cms.untracked.double(100),    #not yet used
N_events_generated = cms.untracked.double(1300000),
xsec_baseline      = cms.untracked.double(495.4785),    #from gridpack production log
WCname             = cms.string('cQd8'),
ditopmassbin       = cms.string('ditopmass1000to2000'),
)

process.p = cms.Path(process.analysis)
