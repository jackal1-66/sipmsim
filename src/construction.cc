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

    //HexaFluoroethane gas (C2F6)
    G4Element * elC = new G4Element("Carbon",
                                    "C",
                                    6,
                                    12.011*g/mole);
    G4Element * elF = new G4Element("Fluorine",
                                    "F",
                                    9,
                                    18.998*g/mole);
    G4Material * gas_mat = new G4Material("HexaFluoroethane", 5.734e-3*g/cm3, 2);
    gas_mat->AddElement(elC, 2);
    gas_mat->AddElement(elF, 6);

    // World
    G4Tubs* solidWorld = new G4Tubs("World", 0., 20*cm, 1.20*m, 0., 2*M_PI*rad);
    G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWorld, gas_mat, "LogicWorld");
    G4VPhysicalVolume* physWorld = new G4PVPlacement(0, G4ThreeVector(0.,0.,0.), logicWorld, "physWorld", 0, false, 0, true);

    // Target
    //G4Box* solidTarget = new G4Box("Target", 0.5*m, 0.5*m, 0.5*m);
    //G4LogicalVolume* logicTarget = new G4LogicalVolume(solidTarget, G4NistManager::Instance()->FindOrBuildMaterial("G4_WATER"), "Target");
    //new G4PVPlacement(0, G4ThreeVector(), logicTarget, "Target", logicWorld, false, 0);

    return physWorld;
}