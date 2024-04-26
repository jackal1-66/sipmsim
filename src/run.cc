#include "run.hh"

runaction::runaction()
{
    G4AnalysisManager *analysisManager = G4AnalysisManager::Instance();
    analysisManager->CreateNtuple("Hits", "Hits");
    analysisManager->CreateNtupleIColumn("fEvent");
    analysisManager->CreateNtupleDColumn("fX");
    analysisManager->CreateNtupleDColumn("fY");
    analysisManager->CreateNtupleDColumn("fZ");
    analysisManager->FinishNtuple(0);
}

runaction::~runaction()
{
}

void runaction::BeginOfRunAction(const G4Run* run)
{
    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
    
    G4int runNumber = run->GetRunID();
    std::stringstream ss;
    ss << runNumber;
    
    analysisManager->OpenFile("Results"+ss.str()+".root");
}

void runaction::EndOfRunAction(const G4Run*)
{
    G4AnalysisManager *analysisManager = G4AnalysisManager::Instance();
    G4cout << "End of run, Writing root file." << G4endl;
    analysisManager->Write();
    analysisManager->CloseFile("output.root");
}