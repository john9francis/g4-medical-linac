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

#include "G4SDManager.hh"
#include "PhantomSD.hh"


namespace med_linac
{
	class DetectorConstruction : public G4VUserDetectorConstruction
	{
	public:
		DetectorConstruction();
		~DetectorConstruction() override = default;

		void ConstructSDandField();

		G4VPhysicalVolume* Construct() override;

		// for detectormessenger
		void SetLinacHeadAngle(G4ThreeVector phiThetaPsi);
		void SetLinacHeadPosition(G4ThreeVector xyz);
		void ShiftLinacHeadRotation(G4ThreeVector phiThetaPsi);
		void ShiftLinacHeadPosition(G4ThreeVector xyz);
		void MoveToAim();

		// for primary gen action
		G4ThreeVector GetLinacHeadRot() const { return G4ThreeVector(*fLinacHeadPhi, *fLinacHeadTheta, *fLinacHeadPsi); }
		G4ThreeVector GetLinacHeadPos() const { return *fLinacHeadPos; }
		G4ThreeVector GetGunAnchorPos() const { return *fGunAnchorPos; }

	private:
		G4VPhysicalVolume* fLinacHead = nullptr;
		G4VPhysicalVolume* fParticleGunAnchor1 = nullptr;

		G4ThreeVector* fLinacHeadPos;
		G4RotationMatrix* fLinacHeadRot;

		G4double* fLinacHeadPhi;
		G4double* fLinacHeadTheta;
		G4double* fLinacHeadPsi;

		G4ThreeVector* fGunAnchorPos;

		void MoveLinacHead();
	};
}


#endif