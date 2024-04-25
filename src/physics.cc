#include "physics.hh"

physicsList::physicsList(){
    RegisterPhysics(new G4EmStandardPhysics());
    RegisterPhysics(new G4OpticalPhysics());
}

physicsList::~physicsList(){
}