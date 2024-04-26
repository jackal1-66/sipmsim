#ifndef CONSTRUCTION_HH
#define CONSTRUCTION_HH

#include "G4SystemOfUnits.hh"
#include "G4NistManager.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4Box.hh"
#include "G4VPhysicalVolume.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4Tubs.hh"
#include "G4MaterialPropertiesTable.hh"
#include "G4OpticalSurface.hh"
#include "G4LogicalSkinSurface.hh"
#include "detector.hh"
#include "G4Sphere.hh"
#include "G4GenericMessenger.hh"

class DetectorConstruction : public G4VUserDetectorConstruction{
    
    public:
        DetectorConstruction();
        ~DetectorConstruction();  

        virtual G4VPhysicalVolume* Construct();
    private:
        G4LogicalVolume* logicDetector;    
        virtual void ConstructSDandField();
        G4GenericMessenger* fMessenger;
        G4double mirrorPosZ;
        G4Box *solidWorld, *aerogelRadiator, *sipm;
        G4Tubs *gasRadiator, *mirror;
        G4LogicalVolume *logicWorld, *gaslogicRadiator, *aerologicRadiator, *logicMirror;
        G4VPhysicalVolume *physWorld, *gasphysRadiator, *aerophysRadiator, *physDetector, *mirrorPhys;
        void def_materials();
        G4Material *air_mat, *gas_mat, *aero_mat, *aluminum, *sio2, *h2o;
        G4LogicalSkinSurface *mirLogicalSurf;
        G4OpticalSurface *mirrorSurface;
};

#endif