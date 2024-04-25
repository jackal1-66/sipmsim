#include "construction.hh"

DetectorConstruction::DetectorConstruction()
{
}

DetectorConstruction::~DetectorConstruction()
{
}

G4VPhysicalVolume* DetectorConstruction::Construct()
{
    // Materials
    G4NistManager * nist = G4NistManager::Instance();
    G4Material * w_mat = nist->FindOrBuildMaterial("G4_AIR");

    // World
    G4Box* solidWorld = new G4Box("World", 1.0*m, 1.0*m, 1.0*m);
    G4LogicalVolume* logicWorld = new G4LogicalVolume(solidWorld, w_mat, "LogicWorld");
    G4VPhysicalVolume* physWorld = new G4PVPlacement(0, G4ThreeVector(0.,0.,0.), logicWorld, "physWorld", 0, false, 0, true);

    // Target
    //G4Box* solidTarget = new G4Box("Target", 0.5*m, 0.5*m, 0.5*m);
    //G4LogicalVolume* logicTarget = new G4LogicalVolume(solidTarget, G4NistManager::Instance()->FindOrBuildMaterial("G4_WATER"), "Target");
    //new G4PVPlacement(0, G4ThreeVector(), logicTarget, "Target", logicWorld, false, 0);

    return physWorld;
}