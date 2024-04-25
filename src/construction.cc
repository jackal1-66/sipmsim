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

    //Air
    G4Material* air_mat = nist->FindOrBuildMaterial("G4_AIR");

    //HexaFluoroethane gas (C2F6)
    G4Material* gas_mat = new G4Material("HexaFluoroethane", 5.734e-3*g/cm3, 2);
    gas_mat->AddElement(nist->FindOrBuildElement("C"), 2);
    gas_mat->AddElement(nist->FindOrBuildElement("F"), 6);
    G4double gamma_ch_en[2] = {
        1.239841939 * eV / 0.9, 1.239841939 * eV / 0.2,
    };
    G4double gas_rindex[2] = {1.0008, 1.0008};
    G4MaterialPropertiesTable* gas_mt = new G4MaterialPropertiesTable();
    gas_mt->AddProperty("RINDEX", gamma_ch_en, gas_rindex, 2);

    gas_mat->SetMaterialPropertiesTable(gas_mt);

    //Aerogel (SiO2)
    G4Material* sio2 = new G4Material("SiliconDioxide", 2.201*g/cm3, 2);
    sio2->AddElement(nist->FindOrBuildElement("Si"), 1);
    sio2->AddElement(nist->FindOrBuildElement("O"), 2);
    G4Material *h2o = new G4Material("H20", 1.000 * g / cm3, 2);
    h2o->AddElement(nist->FindOrBuildElement("H"), 2);
    h2o->AddElement(nist->FindOrBuildElement("O"), 1);
    G4Element * C = nist->FindOrBuildElement("C");    
    G4Material* aero_mat = new G4Material("Aerogel", 0.2000*g/cm3, 3);
    aero_mat->AddMaterial(sio2, 62.5*perCent);
    aero_mat->AddMaterial(h2o, 37.4*perCent);
    aero_mat->AddElement(C, 0.1*perCent);
    G4double aero_rindex[2] = {1.02, 1.02};
    G4MaterialPropertiesTable* aero_mt = new G4MaterialPropertiesTable();
    aero_mt->AddProperty("RINDEX", gamma_ch_en, aero_rindex, 2);

    aero_mat->SetMaterialPropertiesTable(aero_mt);

    // World
    G4Box *solidWorld = new G4Box("World", 2 * m, 2 * m, 2 * m);
    G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWorld, air_mat, "LogicWorld");
    G4VPhysicalVolume *physWorld = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicWorld, "physWorld", 0, false, 0, true);

    // Gas Radiator
    G4Tubs* gasRadiator = new G4Tubs("gasRadiator", 0., 20*cm, 0.6*m, 0., 2*M_PI*rad);
    G4LogicalVolume *gaslogicRadiator = new G4LogicalVolume(gasRadiator, gas_mat, "gasLogicRadiator");
    G4VPhysicalVolume* gasphysRadiator = new G4PVPlacement(0, G4ThreeVector(0.,0.,0.), gaslogicRadiator, "gasphysRadiator", logicWorld, false, 0, true);

    // Aerogel Radiator
    G4Box *aerogelRadiator = new G4Box("aerogelRadiator", 0.01 * m, 0.01 * m, 0.02 * m);
    G4LogicalVolume *aerologicRadiator = new G4LogicalVolume(aerogelRadiator, aero_mat, "aeroLogicRadiator");
    G4VPhysicalVolume *aerophysRadiator = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.62*m), aerologicRadiator, "aerophysRadiator", logicWorld, false, 0, true);

    return physWorld;
}