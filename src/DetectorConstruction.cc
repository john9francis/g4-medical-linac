#include "DetectorConstruction.hh"

#include "G4Box.hh"
#include "G4Tubs.hh"

#include "G4SIunits.hh"
#include "G4LogicalVolume.hh"
#include "G4NistManager.hh"
#include "G4PVPlacement.hh"

namespace med_linac {

	G4VPhysicalVolume* DetectorConstruction::Construct() {

		// create the world, detectors, and return the world's physical volume

		// get our materials
		auto* nist = G4NistManager::Instance();
		G4Material* vacuum = nist->FindOrBuildMaterial("G4_Galactic");

		// pattern: solid object, logical volume, and pvplacement

		G4double worldXY = 20 * cm;
		G4double worldZ = .5 * m;
		G4Box* solidWorld = new G4Box("solidWorld", worldXY, worldXY, worldZ);

		G4LogicalVolume* logicWorld = new G4LogicalVolume(
			solidWorld,
			vacuum,
			"logicWorld");

		G4VPhysicalVolume* physWorld = new G4PVPlacement(
			nullptr,
			G4ThreeVector(),
			logicWorld,
			"physWorld",
			nullptr, // note: this field is for the 'mother' volume, world IS the mother
			false,
			0);


		// Create the rest of the detectors

		G4Material* tungsten = nist->FindOrBuildMaterial("G4_W");

		G4Tubs* solidTarget = new G4Tubs(
			"solidTarget",
			0.,
			1.5 * cm,
			.5 * mm,
			0.,
			360. * deg
		);

		G4LogicalVolume* logicTarget = new G4LogicalVolume(
			solidTarget,
			tungsten,
			"logicTarget"
		);

		new G4PVPlacement(
			new G4RotationMatrix(),
			G4ThreeVector(0, 0, -.45 * m),
			logicTarget,
			"solidTarget",
			logicWorld,
			false,
			0
		);



		return physWorld;
	}


}