#include "construction.hh"

DetectorConstruction::DetectorConstruction()
{
    fMessenger = new G4GenericMessenger(this, "/detector/", "Detector control");
    fMessenger->DeclareProperty("mirrorPosZ", mirrorPosZ, "Z position of the mirror in m");
    mirrorPosZ = 0.42;
    def_materials();
}

DetectorConstruction::~DetectorConstruction()
{
}

void DetectorConstruction::def_materials()
{
    // Materials
    G4NistManager *nist = G4NistManager::Instance();

    // Air
    air_mat = nist->FindOrBuildMaterial("G4_AIR");
    G4double gamma_ch_en[2] = {
        1 * eV,
        6.5 * eV,
    };
    // G4double air_rindex[2] = {1.0, 1.0};
    G4MaterialPropertiesTable *air_mt = new G4MaterialPropertiesTable();
    // air_mt->AddProperty("RINDEX", gamma_ch_en, air_rindex, 2);

    // air_mat->SetMaterialPropertiesTable(air_mt);

    // HexaFluoroethane gas (C2F6)
    gas_mat = new G4Material("HexaFluoroethane", 5.734e-3 * g / cm3, 2);
    gas_mat->AddElement(nist->FindOrBuildElement("C"), 2);
    gas_mat->AddElement(nist->FindOrBuildElement("F"), 6);
    G4double gas_rindex[2] = {1.0008, 1.0008};
    G4MaterialPropertiesTable *gas_mt = new G4MaterialPropertiesTable();
    gas_mt->AddProperty("RINDEX", gamma_ch_en, gas_rindex, 2);

    gas_mat->SetMaterialPropertiesTable(gas_mt);

    // Aerogel (SiO2)
    sio2 = new G4Material("SiliconDioxide", 2.201 * g / cm3, 2);
    sio2->AddElement(nist->FindOrBuildElement("Si"), 1);
    sio2->AddElement(nist->FindOrBuildElement("O"), 2);
    h2o = new G4Material("H20", 1.000 * g / cm3, 2);
    h2o->AddElement(nist->FindOrBuildElement("H"), 2);
    h2o->AddElement(nist->FindOrBuildElement("O"), 1);
    G4Element *C = nist->FindOrBuildElement("C");
    aero_mat = new G4Material("Aerogel", 0.2000 * g / cm3, 3);
    aero_mat->AddMaterial(sio2, 62.5 * perCent);
    aero_mat->AddMaterial(h2o, 37.4 * perCent);
    aero_mat->AddElement(C, 0.1 * perCent);
    G4double aero_rindex[2] = {1.02, 1.02};
    G4MaterialPropertiesTable *aero_mt = new G4MaterialPropertiesTable();
    aero_mt->AddProperty("RINDEX", gamma_ch_en, aero_rindex, 2);

    aero_mat->SetMaterialPropertiesTable(aero_mt);

    aluminum = nist->FindOrBuildMaterial("G4_Al");
    // Mirror material
    mirrorSurface = new G4OpticalSurface("MirrorSurface", glisur, polished, dielectric_metal, 1.);

    G4MaterialPropertiesTable *mirrorSurfaceProperty = new G4MaterialPropertiesTable();

    G4double p_mirror[2] = {1 * eV, 6.5 * eV};
    G4double refl_mirror[2] = {1., 1.};
    G4double effi_mirror[2] = {0., 0.};
    G4double r_mirror[2] = {1.7, 1.7};

    mirrorSurfaceProperty->AddProperty("REFLECTIVITY", p_mirror, refl_mirror, 2);
    mirrorSurfaceProperty->AddProperty("EFFICIENCY", p_mirror, effi_mirror, 2);
    mirrorSurfaceProperty->AddProperty("RINDEX", p_mirror, r_mirror, 2);
    mirrorSurface->SetMaterialPropertiesTable(mirrorSurfaceProperty);
}

G4VPhysicalVolume* DetectorConstruction::Construct()
{
    // World
    solidWorld = new G4Box("World", 2 * m, 2 * m, 2 * m);
    logicWorld = new G4LogicalVolume(solidWorld, air_mat, "LogicWorld");
    physWorld = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicWorld, "physWorld", 0, false, 0, true);

    // Gas Radiator
    gasRadiator = new G4Tubs("gasRadiator", 0., 20*cm, 0.6*m, 0., 2*M_PI*rad);
    gaslogicRadiator = new G4LogicalVolume(gasRadiator, gas_mat, "gasLogicRadiator");
    gasphysRadiator = new G4PVPlacement(0, G4ThreeVector(0.,0.,0.), gaslogicRadiator, "gasphysRadiator", logicWorld, false, 0, true);
    
    // Aerogel Radiator
    aerogelRadiator = new G4Box("aerogelRadiator", 0.01 * m, 0.01 * m, 0.02 * m);
    aerologicRadiator = new G4LogicalVolume(aerogelRadiator, aero_mat, "aeroLogicRadiator");
    aerophysRadiator = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.62*m), aerologicRadiator, "aerophysRadiator", logicWorld, false, 0, true);

    // Mirror
    
    mirror = new G4Tubs("mirror", 2.5 * cm, 18 * cm, 0.1 * mm, 0., 2 * M_PI * rad);
    logicMirror = new G4LogicalVolume(mirror, aluminum, "Mirror");
    mirrorPhys = new G4PVPlacement(0, G4ThreeVector(0., 0., mirrorPosZ * m), logicMirror, "mirrorPhys", gaslogicRadiator, false, 0, true);
    mirLogicalSurf = new G4LogicalSkinSurface("mirLogicalSurf", logicMirror, mirrorSurface);
    
    // Spherical Mirror
    /*
    G4Sphere *mirror = new G4Sphere("mirror", 17.999 * cm, 18 * cm, 0, 2*M_PI*rad, M_PI/2, M_PI);
    G4LogicalVolume *logicMirror = new G4LogicalVolume(mirror, aluminum, "Mirror");
    G4VPhysicalVolume *mirrorPhys = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.31 * m), logicMirror, "mirrorPhys", gaslogicRadiator, false, 0, true);
    G4LogicalSkinSurface *mirLogicalSurf = new G4LogicalSkinSurface("mirLogicalSurf", logicMirror, mirrorSurface);
    */

    // SiPM
    sipm = new G4Box("SiPM", 1.5 * mm, 1.5 * mm, 1 * mm);
    logicDetector = new G4LogicalVolume(sipm, air_mat, "logicDetector");
    for(G4int i = 0; i < 24; i++){
        for(G4int j = 0; j < 24; j++){
            if(i>7 && i <16 && j>7 && j<16) continue;
            else
                physDetector = new G4PVPlacement(0, G4ThreeVector(-69 * mm + 6 * mm * i, -69 * mm + 6 * mm * j, 0.59 * m), logicDetector, "physDetector", gaslogicRadiator, false, i + j * 100, true);
        }
    }

    return physWorld;
}

void DetectorConstruction::ConstructSDandField()
{
    Detector *setup = new Detector("Detector");
    logicDetector->SetSensitiveDetector(setup);
}