#ifndef GENERATOR_H
#define GENERATOR_H

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4SystemOfUnits.hh"
#include "G4ParticleTable.hh"

class primarygen : public G4VUserPrimaryGeneratorAction
{
    public:
        primarygen();
        ~primarygen();

        virtual void GeneratePrimaries(G4Event*);
    
    private:
        G4ParticleGun* fParticleGun;
};

#endif