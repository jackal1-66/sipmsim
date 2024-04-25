#ifndef DETECTOR_HH
#define DETECTOR_HH

#include "G4VSensitiveDetector.hh"
#include "G4Step.hh"
#include "G4TouchableHistory.hh"

class Detector : public G4VSensitiveDetector
{
    public:
        Detector(G4String);
        ~Detector();
    private:
        virtual G4bool ProcessHits(G4Step*, G4TouchableHistory*);
};

#endif