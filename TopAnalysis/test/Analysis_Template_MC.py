# -*- coding: utf-8 -*-
import FWCore.ParameterSet.Config as cms

process = cms.Process("myprocess")
process.TFileService=cms.Service("TFileService",fileName=cms.string("Test.root"))

##-------------------- Define the source  ----------------------------
process.maxEvents = cms.untracked.PSet(
        input = cms.untracked.int32(1)
        )

process.source = cms.Source("EmptySource")


##-------------------- User analyzer  --------------------------------
process.analysis  = cms.EDAnalyzer('Analysis_Template_MC',
                                   filename        = cms.string('file:GenLevelOutput_test.root'),
                                   treename        = cms.string('events'),
                                   dirname         = cms.string('boosted'),
                                   isMCarlo        = cms.untracked.bool(True),
                                   CrossSection    = cms.untracked.double(0.017),
                                   IntLumi         = cms.untracked.double(100),
                                   Triggers        = cms.untracked.vstring(''),
                                   )

process.p = cms.Path(process.analysis)
