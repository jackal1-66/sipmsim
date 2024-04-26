#include "run.hh"

runaction::runaction()
{
}

runaction::~runaction()
{
}

void runaction::BeginOfRunAction(const G4Run*)
{
    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
    analysisManager->OpenFile("test.root");
    analysisManager->CreateNtuple("Hits", "Hits");
    analysisManager->CreateNtupleIColumn("fEvent");
    analysisManager->CreateNtupleDColumn("fX");
    analysisManager->CreateNtupleDColumn("fY");
    analysisManager->CreateNtupleDColumn("fZ");
    analysisManager->FinishNtuple(0);
}

void runaction::EndOfRunAction(const G4Run*)
{
    G4AnalysisManager *analysisManager = G4AnalysisManager::Instance();
    G4cout << "End of run, Writing root file." << G4endl;
    analysisManager->Write();
    analysisManager->CloseFile("output.root");
}