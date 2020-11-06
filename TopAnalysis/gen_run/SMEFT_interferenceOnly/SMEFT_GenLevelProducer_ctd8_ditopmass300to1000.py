import FWCore.ParameterSet.Config as cms
import os

WilsonCoeff = 'ctd8'

process = cms.Process('myprocess')

process.TFileService=cms.Service("TFileService",fileName=cms.string('/nfs/dust/cms/user/jabuschh/PhD/ttbar/EFT_LO/genstudy/CMSSW_9_4_6/src/UserCode/TopAnalysis/gen_output/SMEFT/SMEFT_' + WilsonCoeff + '_ditopmass300to1000.root'))

process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(-1))

directory = '/nfs/dust/cms/user/jabuschh/PhD/ttbar/EFT_LO/genproduction/CMSSW_7_1_45_patch3/output/SMEFT/'

file_list = []
for nr in range(11):
  file = 'file:' + directory + 'SMEFT_DIM6_ditopmass300to1000_' + str(nr) + '.root'
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
    "rwgt_" + WilsonCoeff + "_min5p0",
    "rwgt_" + WilsonCoeff + "_min4p0",
    "rwgt_" + WilsonCoeff + "_min3p0",
    "rwgt_" + WilsonCoeff + "_min2p0",
    "rwgt_" + WilsonCoeff + "_min1p0",
    "rwgt_SM",
    "rwgt_" + WilsonCoeff + "_1p0",
    "rwgt_" + WilsonCoeff + "_2p0",
    "rwgt_" + WilsonCoeff + "_3p0",
    "rwgt_" + WilsonCoeff + "_4p0",
    "rwgt_" + WilsonCoeff + "_5p0"
    )
)

process.p = cms.Path(
    process.boosted
)
