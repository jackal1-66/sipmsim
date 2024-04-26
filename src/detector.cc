#include "detector.hh"

Detector::Detector(G4String name): G4VSensitiveDetector(name)
{
}

Detector::~Detector() {
}

G4bool Detector::ProcessHits(G4Step* aStep, G4TouchableHistory* ROhist)
{
    G4Track* track = aStep->GetTrack();

    track->SetTrackStatus(fStopAndKill);

    G4StepPoint* preStepPoint = aStep->GetPreStepPoint();
    G4StepPoint *postStepPoint = aStep->GetPostStepPoint();

    G4ThreeVector posPhoton = preStepPoint->GetPosition();
    G4cout << "Photon Position: " << posPhoton << G4endl;
    
    const G4VTouchable* touchable = aStep->GetPreStepPoint()->GetTouchable();
    G4int copyNo = touchable->GetCopyNumber();

    G4cout << "Copy Number: " << copyNo << G4endl;

    G4VPhysicalVolume* physVol = touchable->GetVolume();
    G4ThreeVector pos = physVol->GetTranslation();
    G4cout << "Detector position: " << pos << G4endl;

    G4int evt = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();

    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
    analysisManager->FillNtupleIColumn(0, evt);
    analysisManager->FillNtupleDColumn(1, pos[0]);
    analysisManager->FillNtupleDColumn(2, pos[1]);
    analysisManager->FillNtupleDColumn(3, pos[2]);
    analysisManager->AddNtupleRow(0);
}