import FWCore.ParameterSet.Config as cms
import os

WilsonCoeff = 'CaG'

process = cms.Process('myprocess')

process.TFileService=cms.Service("TFileService",fileName=cms.string('/nfs/dust/cms/user/jabuschh/PhD/ttbar/genstudy/CMSSW_9_4_6/src/UserCode/TopAnalysis/gen_output/ALP/ALP_CaPhi1_' + WilsonCoeff + '5.root'))

process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(-1))

directory = '/nfs/dust/cms/user/jabuschh/PhD/ttbar/genproduction/CMSSW_7_1_45_patch3/output/ALP/'

file_list = []
for nr in range(10):
  file = 'file:' + directory + 'ALP_CaPhi1_CaG5_' + str(nr) + '.root'
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
process.boosted = cms.EDAnalyzer('gen_runner_ALP',
  genparticles    = cms.untracked.InputTag('genParticles'),
  isMC            = cms.untracked.bool(True),
  genjets         = cms.untracked.InputTag('ak4GenJets'),
  GenptMin        = cms.untracked.double(30),
  GenetaMax       = cms.untracked.double(2.4),
  isPrint         = cms.untracked.bool(True),
  isHigherOrder   = cms.untracked.bool(True)
)

process.p = cms.Path(
    process.boosted
)
