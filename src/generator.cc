#include "generator.hh"

primarygen::primarygen(){
    fParticleGun = new G4ParticleGun(1); //one primary vertex per event
}

primarygen::~primarygen(){
    delete fParticleGun;
}

void primarygen::GeneratePrimaries(G4Event* anEvent){
    G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
    G4String particleName = "proton";
    G4ParticleDefinition* particle = particleTable->FindParticle(particleName);
    fParticleGun->SetParticleDefinition(particle);

    G4ThreeVector position = G4ThreeVector(0.,0.,2*m);
    fParticleGun->SetParticlePosition(position);

    G4ThreeVector momentum = G4ThreeVector(0.,0.,-1.);
    fParticleGun->SetParticleMomentumDirection(momentum);

    fParticleGun->SetParticleMomentum(10.*GeV);
    fParticleGun->GeneratePrimaryVertex(anEvent);
}