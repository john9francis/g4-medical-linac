// Source file to define the very long "Construct" method of DetectorConstruction

#include "DetectorConstruction.hh"

#include "G4Cons.hh"

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

        G4ThreeVector particleGunAnchor1Pos = G4ThreeVector(0, 0, -linacHeadThicknessZ + 7 * cm);
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

        G4Tubs* solidTarget = new G4Tubs("Target",
            innerTargetRadius,
            outerTargetRadius,
            targetThickness / 2.0,
            0.0,
            360.0 * deg);

        G4LogicalVolume* logicTarget = new G4LogicalVolume(solidTarget,
            tungsten,
            "Target");

        // target position and rotation
        G4double targetZ = particleGunAnchor1Pos.getZ() + 3 * cm;
        G4ThreeVector targetPos = G4ThreeVector(0, 0, targetZ); // 0,0,0
        G4RotationMatrix* targetRotation = new G4RotationMatrix();

        // place the target in the world
        new G4PVPlacement(
            targetRotation,
            targetPos,
            logicTarget,
            "Target",
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
        G4double absorberZ = targetPos.getZ() + targetThickness / 2 + (absorberThickness / 2);
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


        //////////////////////////////////////////////////////////////////////////
        // In this section I will test some filters
        // Inspiration comes from this article: 
        // https://www.ncbi.nlm.nih.gov/pmc/articles/PMC5496272/
        //////////////////////////////////////////////////////////////////////////

        // Add a CU filter
        G4Material* copper = nist->FindOrBuildMaterial("G4_Cu");

        G4double innerCuFilterRadius = 0.0;
        G4double outerCuFilterRadius = 1.5 * cm;
        G4double CuFilterThickness = 2 * mm;

        G4Tubs* solidCuFilter = new G4Tubs("solidCuFilter",
            innerCuFilterRadius,
            outerCuFilterRadius,
            CuFilterThickness / 2.0,
            0.0,
            360.0 * deg);

        G4LogicalVolume* logicCuFilter = new G4LogicalVolume(solidCuFilter,
            copper,
            "logicCuFilter");

        // filter position and rotation
        G4double CuFilterZ = absorberZ + absorberThickness / 2 + (CuFilterThickness / 2);
        G4ThreeVector CuFilterPos = G4ThreeVector(0.0, 0.0, CuFilterZ);

        // place the absorber
        new G4PVPlacement(new G4RotationMatrix(),
            CuFilterPos,
            logicCuFilter,
            "physCuFilter",
            logicHead,
            false,
            0);


        // add an AL filter
        



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
        G4double colZ =
            absorberZ
            + (absorberThickness / 2)
            + (colThickness / 2);

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
        G4double coneHeight = 1 * cm;
        G4double startPhi = 0.0;
        G4double endPhi = 360.0 * deg;

        G4double ffZ = colZ + (colThickness / 2) + (coneHeight / 2) + 1 * cm;
        G4ThreeVector ffPos = G4ThreeVector(0, 0, ffZ);

        
        G4Cons* solidFF = new G4Cons("solidFF", 0, 0, 0, coneOuterRadius, coneHeight, startPhi, endPhi);
        G4LogicalVolume* logicFF = new G4LogicalVolume(solidFF, tungsten, "logicFF");
        new G4PVPlacement(
            nullptr,
            ffPos,
            logicFF,
            "physFF",
            logicHead,
            false,
            0);

        




        // create our dose detector
        G4double ddThicknessXY = 15 * cm;
        G4double ddThicknessZ = 1 * nm;
        G4double ddZ = ffZ + (coneHeight / 2) + (ddThicknessZ / 2) + 5 * cm;
        G4ThreeVector ddPos = G4ThreeVector(0, 0, ddZ);

        G4Box* solidDoseDetector = new G4Box("solidDD", ddThicknessXY, ddThicknessXY, ddThicknessZ);
        G4LogicalVolume* logicDoseDetector = new G4LogicalVolume(solidDoseDetector, vacuum, "logicDD");
        new G4PVPlacement(nullptr, ddPos, logicDoseDetector, "physDD", logicHead, false, 0);



        // create our phantom, to represent a person

        G4ThreeVector phantomPos = G4ThreeVector();

        G4Material* water = nist->FindOrBuildMaterial("G4_WATER");

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