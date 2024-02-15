// Source file to define the very long "Construct" method of DetectorConstruction

#include "DetectorConstruction.hh"


namespace med_linac {
    G4VPhysicalVolume* DetectorConstruction::Construct()
    {
        // construct our detectors here

        // Get nist material manager
        G4NistManager* nist = G4NistManager::Instance();


        // Start with constructing the world:
        G4double worldSize = 1.5 * m;
        G4Material* vacuum = nist->FindOrBuildMaterial("G4_Galactic");

        auto sphereWorld = new G4Sphere(
            "solidWorld",
            0,
            worldSize,
            0,
            2 * CLHEP::pi,
            0,
            CLHEP::pi
        );

        auto boxWorld = new G4Box(
            "solidWorld",
            worldSize,
            worldSize,
            worldSize
        );


        auto logicWorld = new G4LogicalVolume(boxWorld,
            vacuum,
            "logicWorld");


        auto physWorld = new G4PVPlacement(nullptr,
            G4ThreeVector(),
            logicWorld,
            "physWorld",
            nullptr,
            false,
            0);


        // Next, create a 'linac head' object to contain all the radiation generation stuff
        G4double linacHeadThicknessXY = 25 * cm;
        G4double linacHeadThicknessZ = 25 * cm;

        *fLinacHeadPos = G4ThreeVector(0, 0, -1 * m);

        *fLinacHeadPhi = 0;
        *fLinacHeadTheta = 0;
        *fLinacHeadPsi = 0;
        *fLinacHeadRot = G4RotationMatrix(*fLinacHeadPhi, *fLinacHeadTheta, *fLinacHeadPsi);

        G4Box* solidHead = new G4Box("solidHead", linacHeadThicknessXY, linacHeadThicknessXY, linacHeadThicknessZ);
        G4LogicalVolume* logicHead = new G4LogicalVolume(solidHead, vacuum, "logicHead");
        fLinacHead = new G4PVPlacement(
            fLinacHeadRot,
            *fLinacHeadPos,
            logicHead,
            "physHead",
            logicWorld,
            false,
            0);



        // create a place for the particle gun to shoot from
        G4double particleGunAnchorThickness = 1 * mm;
        G4Box* solidParticleGunAnchor = new G4Box(
            "solidParticleGunAnchor",
            particleGunAnchorThickness,
            particleGunAnchorThickness,
            particleGunAnchorThickness);

        G4ThreeVector particleGunAnchor1Pos = G4ThreeVector(0, 0, - 18 * cm);
        *fGunAnchorPos = particleGunAnchor1Pos;

        G4LogicalVolume* logicParticleGunAnchor1 = new G4LogicalVolume(solidParticleGunAnchor, vacuum, "logicParticleGunAnchor1");
        G4VPhysicalVolume* physAnchor1 = new G4PVPlacement(
            nullptr,
            particleGunAnchor1Pos,
            logicParticleGunAnchor1,
            "physParticleGunAnchor1",
            logicHead,
            false,
            0);


        // Set our member variables for the gun anchors:
        fParticleGunAnchor1 = physAnchor1;


        // create our tungsten target
        G4Material* tungsten = nist->FindOrBuildMaterial("G4_W");

        G4double innerTargetRadius = 0.0;
        G4double outerTargetRadius = 1.5 * cm;
        G4double targetThickness = 1 * mm;

        G4Tubs* solidTarget = new G4Tubs("solidTarget",
            innerTargetRadius,
            outerTargetRadius,
            targetThickness / 2.0,
            0.0,
            360.0 * deg);

        G4LogicalVolume* logicTarget = new G4LogicalVolume(solidTarget,
            tungsten,
            "logicTarget");

        // target position and rotation
        G4double targetZ = -15 * cm;
        G4ThreeVector targetPos = G4ThreeVector(0, 0, targetZ); // 0,0,0
        G4RotationMatrix* targetRotation = new G4RotationMatrix();

        // place the target in the world
        new G4PVPlacement(
            targetRotation,
            targetPos,
            logicTarget,
            "physTarget",
            logicHead,
            false,
            0);


        // create a graphite absorber to absorb electrons
        G4Material* graphite = nist->FindOrBuildMaterial("G4_GRAPHITE");

        G4double innerAbsorberRadius = 0.0;
        G4double outerAbsorberRadius = 1.5 * cm;
        G4double absorberThickness = 1.5 * cm;

        G4Tubs* solidAbsorber = new G4Tubs("Absorber",
            innerAbsorberRadius,
            outerAbsorberRadius,
            absorberThickness / 2.0,
            0.0,
            360.0 * deg);

        G4LogicalVolume* logicAbsorber = new G4LogicalVolume(solidAbsorber,
            graphite,
            "Absorber");

        // absorber position and rotation
        G4double absorberZ = -14.2 * cm;
        G4ThreeVector absorberPos = G4ThreeVector(0.0, 0.0, absorberZ);
        G4RotationMatrix* absorberRot = new G4RotationMatrix();

        // place the absorber
        new G4PVPlacement(absorberRot,
            absorberPos,
            logicAbsorber,
            "Absorber",
            logicHead,
            false,
            0);



        // create tungsten collimator
        G4double innerColRadius = 4.0 * cm;
        G4double outerColRadius = 12. * cm;
        G4double colThickness = 20 * cm;

        G4Tubs* solidCol = new G4Tubs("Collimator",
            innerColRadius,
            outerColRadius,
            colThickness / 2.0,
            0.0,
            360.0 * deg);
        G4LogicalVolume* logicCol = new G4LogicalVolume(solidCol,
            tungsten,
            "Collimator");

        // collimator position and rotation
        G4double colZ = -3.45 * cm;

        G4ThreeVector colPos = G4ThreeVector(0, 0, colZ);

        G4RotationMatrix* colRotation = new G4RotationMatrix();

        // place the collimator in the world
        new G4PVPlacement(colRotation,
            colPos,
            logicCol,
            "Collimator",
            logicHead,
            false,
            0);




        // Create a half hollow lead semi-sphere around the backside
        G4Material* lead = nist->FindOrBuildMaterial("G4_Pb");
        G4RotationMatrix* protectorRotation = new G4RotationMatrix();
        protectorRotation->rotateX(90. * deg);

        G4double protectorThickness = 6 * cm;

        G4Sphere* solidProtector = new G4Sphere(
            "solidProtector",
            linacHeadThicknessXY - protectorThickness,
            linacHeadThicknessXY,
            0 * deg,
            180 * deg,
            0 * deg,
            180 * deg
        );

        G4LogicalVolume* logProtector = new G4LogicalVolume(
            solidProtector,
            lead,
            "logProtector"
        );

        new G4PVPlacement(
            protectorRotation,
            G4ThreeVector(),
            logProtector,
            "solidProtector",
            logicHead,
            false,
            0
        );


        // Create flattening filter
        G4double coneInnerRadius = 0.0;
        G4double coneOuterRadius = innerColRadius;
        G4double coneHeight = .8 * cm;

        G4double ffZ = 8 * cm;
        G4ThreeVector ffPos = G4ThreeVector(0, 0, ffZ);

        
        G4Cons* solidFF = new G4Cons("solidFF", 0, 0, 0, coneOuterRadius, coneHeight, 0, 360 * deg);
        G4LogicalVolume* logicFF = new G4LogicalVolume(solidFF, tungsten, "logicFF");
        fFlatteningFilter = new G4PVPlacement(
            nullptr,
            ffPos,
            logicFF,
            "physFF",
            logicHead,
            false,
            0);



        // Create a filter for low energy particles
        G4double filterInnerRadius = 0.0;
        G4double filterOuterRadius = innerColRadius;
        G4double filterWidth = 2 * mm;

        G4double filterZ = 9 * cm;
        G4ThreeVector filterPos = G4ThreeVector(0, 0, filterZ);


        G4Tubs* solidFilter = new G4Tubs("solidFilter", filterInnerRadius, filterOuterRadius, filterWidth, 0, 360 * deg);
        G4LogicalVolume* logicFilter = new G4LogicalVolume(solidFilter, tungsten, "logicFilter");
        new G4PVPlacement(
            nullptr,
            filterPos,
            logicFilter,
            "physFilter",
            logicHead,
            false,
            0);


        

        // Create secondary collimator
        G4double SinnerColRadius = 4.0 * cm;
        G4double SouterColRadius = 12. * cm;
        G4double ScolThickness = 10 * cm;

        G4Tubs* SsolidCol = new G4Tubs("SecondarySolidCollimator",
            SinnerColRadius,
            SouterColRadius,
            ScolThickness / 2.0,
            0.0,
            360.0 * deg);

        G4LogicalVolume* SlogicCol = new G4LogicalVolume(SsolidCol,
            tungsten,
            "SecondaryLogicCollimator");

        // collimator position and rotation
        G4double ScolZ = 19.5 * cm;

        G4ThreeVector ScolPos = G4ThreeVector(0, 0, ScolZ);

        G4RotationMatrix* ScolRotation = new G4RotationMatrix();

        // place the collimator in the world
        new G4PVPlacement(ScolRotation,
            ScolPos,
            SlogicCol,
            "PhysSecondaryCollimator",
            logicHead,
            false,
            0);



        // create our dose detector
        G4double ddThicknessXY = 15 * cm;
        G4double ddThicknessZ = 1 * nm;
        G4double ddZ = 24.9 * cm; // putting it right on the edge of the linac head
        G4ThreeVector ddPos = G4ThreeVector(0, 0, ddZ);

        G4Box* solidDoseDetector = new G4Box("solidDD", ddThicknessXY, ddThicknessXY, ddThicknessZ);
        G4LogicalVolume* logicDoseDetector = new G4LogicalVolume(solidDoseDetector, vacuum, "logicDD");
        new G4PVPlacement(nullptr, ddPos, logicDoseDetector, "physDD", logicHead, false, 0);




        // create our phantom, to represent a person

        G4ThreeVector phantomPos = G4ThreeVector();

        G4Material* water = nist->FindOrBuildMaterial("G4_WATER");

        // we can also test different types of tissue
        G4Material* tissue1 = nist->FindOrBuildMaterial("G4_A-150_TISSUE");
        G4Material* tissue2 = nist->FindOrBuildMaterial("G4_ADIPOSE_TISSUE_TCRP");
        G4Material* tissue3 = nist->FindOrBuildMaterial("G4_TISSUE_SOFT_ICRP");


        G4Box* solidPhantom = new G4Box("solidPhantom", 15 * cm, 15 * cm, 15 * cm);
        G4LogicalVolume* logicPhantom = new G4LogicalVolume(solidPhantom, water, "logicPhantom");
        G4VPhysicalVolume* physPhantom = new G4PVPlacement(
            nullptr,
            phantomPos,
            logicPhantom,
            "physPhantom",
            logicWorld,
            false,
            0);


        // finish by returning the world
        return physWorld;
    }
}