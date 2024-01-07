#ifndef med_linac_DETECTOR_CONSTRUCTION_H
#define med_linac_DETECTOR_CONSTRUCTION_H 1

#include "G4VUserDetectorConstruction.hh"

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
	class DetectorConstruction : public G4VUserDetectorConstruction
	{
	public:
		DetectorConstruction() = default;
		~DetectorConstruction() override = default;

		G4VPhysicalVolume* Construct() override;

		G4VPhysicalVolume* GetLinacHead() const { return fLinacHead; }
		G4VPhysicalVolume* GetParticleGunAnchor1() const { return fParticleGunAnchor1; }

		// for detectormessenger
		void SetLinacHeadAngle(G4ThreeVector phiThetaPsi);
		void SetLinacHeadPosition(G4ThreeVector xyz);

	private:
		G4VPhysicalVolume* fLinacHead = nullptr;
		G4VPhysicalVolume* fParticleGunAnchor1 = nullptr;

		void MoveLinacHead(G4ThreeVector xyz, G4RotationMatrix& rotMatrix);
	};
}


#endif