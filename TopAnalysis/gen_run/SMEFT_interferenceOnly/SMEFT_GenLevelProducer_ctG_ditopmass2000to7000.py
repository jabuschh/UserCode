import FWCore.ParameterSet.Config as cms
import os

WilsonCoeff = 'ctG'

process = cms.Process('myprocess')

process.TFileService=cms.Service("TFileService",fileName=cms.string('/nfs/dust/cms/user/jabuschh/PhD/ttbar/EFT_LO/genstudy/CMSSW_9_4_6/src/UserCode/TopAnalysis/gen_output/SMEFT/SMEFT_' + WilsonCoeff + '_ditopmass2000to7000.root'))

process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(-1))

directory = '/nfs/dust/cms/user/jabuschh/PhD/ttbar/EFT_LO/genproduction/CMSSW_7_1_45_patch3/output/SMEFT/'

file_list = []
for nr in range(1300):
  file = 'file:' + directory + 'SMEFT_DIM6_ditopmass2000to7000_' + str(nr) + '.root'
  file_list.append(file)

process.source = cms.Source("PoolSource",
fileNames = cms.untracked.vstring(file_list),
duplicateCheckMode = cms.untracked.string('noDuplicateCheck')
)

#############   Format MessageLogger #################
process.load('FWCore.MessageService.MessageLogger_cfi')
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

from RecoJets.Configuration.RecoGenJets_cff import ak4GenJets, ak8GenJets

genParticleCollection = 'genParticles'

from RecoJets.JetProducers.ak4GenJets_cfi import ak4GenJets
from RecoJets.JetProducers.GenJetParameters_cfi import *

##-------------------- User analyzer  --------------------------------
process.boosted = cms.EDAnalyzer('BoostedTTbarFlatTreeProducerGenLevel',
  genparticles    = cms.untracked.InputTag('genParticles'),
  isMC            = cms.untracked.bool(True),
  genjets         = cms.untracked.InputTag('ak4GenJets'),
  GenptMin        = cms.untracked.double(30),
  GenetaMax       = cms.untracked.double(2.4),
  isPrint         = cms.untracked.bool(True),
  isHigherOrder   = cms.untracked.bool(True),
  EFT_weights     = cms.untracked.vstring(
    "rwgt_" + WilsonCoeff + "_min0p25",
    "rwgt_" + WilsonCoeff + "_min0p2",
    "rwgt_" + WilsonCoeff + "_min0p15",
    "rwgt_" + WilsonCoeff + "_min0p1",
    "rwgt_" + WilsonCoeff + "_min0p05",
    "rwgt_SM",
    "rwgt_" + WilsonCoeff + "_0p05",
    "rwgt_" + WilsonCoeff + "_0p1",
    "rwgt_" + WilsonCoeff + "_0p15",
    "rwgt_" + WilsonCoeff + "_0p2",
    "rwgt_" + WilsonCoeff + "_0p25"
    )
)

process.p = cms.Path(
    process.boosted
)
