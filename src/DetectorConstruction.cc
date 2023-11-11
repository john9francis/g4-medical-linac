
#include "DetectorConstruction.hh"

#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Sphere.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4NistManager.hh"
#include "G4LogicalVolume.hh"

#include "G4SystemOfUnits.hh"
#include "CLHEP/Units/SystemOfUnits.h"

namespace med_linac
{
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
            worldSize / 2,
            worldSize / 2,
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
        G4double linacHeadThicknessXY = 15 * cm;
        G4double linacHeadThicknessZ = 15 * cm;

        G4ThreeVector linacHeadPos = G4ThreeVector(0 * cm , 0 * cm, -1 * m);

        G4double headPhi = 0;
        G4double headTheta = CLHEP::pi / 4;
        G4double headPsi = 0;
        G4RotationMatrix* linacHeadRotation = new G4RotationMatrix(headPhi, headTheta, headPsi);

        G4Box* solidHead = new G4Box("solidHead", linacHeadThicknessXY, linacHeadThicknessXY, linacHeadThicknessZ);
        G4LogicalVolume* logicHead = new G4LogicalVolume(solidHead, vacuum, "logicHead");
        G4VPhysicalVolume* physHead = new G4PVPlacement(
            linacHeadRotation,
            linacHeadPos,
            logicHead,
            "physHead",
            logicWorld,
            false,
            0);

        // set the member variable so we can get this volume in other parts of the program
        fLinacHead = physHead;


        // create a place for the particle gun to shoot from
        G4double particleGunAnchorThickness = 1 * mm;
        G4Box* solidParticleGunAnchor = new G4Box(
            "solidParticleGunAnchor", 
            particleGunAnchorThickness, 
            particleGunAnchorThickness, 
            particleGunAnchorThickness);

        G4ThreeVector particleGunAnchor1Pos = G4ThreeVector(0, 0, -linacHeadThicknessZ + 2 * cm);

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
        G4double targetZ = -linacHeadThicknessZ + 5 * cm;
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
        G4double absorberZ = targetPos.getZ() + (absorberThickness / 2);
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
        G4double colThickness = 10 * cm;

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



        // create our dose detector
        G4double ddThicknessXY = 15 * cm;
        G4double ddThicknessZ = 1 * nm;
        G4double ddZ = colZ + (colThickness / 2) + (ddThicknessZ / 2) + 5 * cm;
        G4ThreeVector ddPos = G4ThreeVector(0, 0, ddZ);

        G4Box* solidDoseDetector = new G4Box("solidDD", ddThicknessXY, ddThicknessXY, ddThicknessZ);
        G4LogicalVolume* logicDoseDetector = new G4LogicalVolume(solidDoseDetector, vacuum, "logicDD");
        new G4PVPlacement(nullptr, ddPos, logicDoseDetector, "physDD", logicHead, false, 0);



        // create our phantom, to represent a person
        G4ThreeVector phantomPos = G4ThreeVector();

        G4Material* water = nist->FindOrBuildMaterial("G4_WATER");

        G4Box* solidPhantom = new G4Box("solidPhantom", 45 * cm, 45 * cm, 45 * cm);
        G4LogicalVolume* logicPhantom = new G4LogicalVolume(solidPhantom, water, "logicPhantom");
        new G4PVPlacement(
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