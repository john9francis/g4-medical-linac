#ifndef med_linac_DETECTOR_CONSTRUCTION_H
#define med_linac_DETECTOR_CONSTRUCTION_H 1

#include "G4VUserDetectorConstruction.hh"
#include "G4PVPlacement.hh"

#include "G4UImessenger.hh"

namespace med_linac
{
	class DetectorConstruction : public G4VUserDetectorConstruction
	{
	public:
		DetectorConstruction();
		~DetectorConstruction();

		G4VPhysicalVolume* Construct() override;
		void ConstructSDandField() override;

		G4VPhysicalVolume* GetLinacHead() const { return fLinacHead; }
		G4VPhysicalVolume* GetParticleGunAnchor1() const { return fParticleGunAnchor1; }
		G4VPhysicalVolume* GetPhysPhantom() const { return fPhysPhantom; }
		G4LogicalVolume* GetPhantom() const { return fLogicPhantom; }

	private:
		G4VPhysicalVolume* fLinacHead = nullptr;
		G4VPhysicalVolume* fParticleGunAnchor1 = nullptr;

		G4LogicalVolume* fLogicPhantom = nullptr;
		G4VPhysicalVolume* fPhysPhantom = nullptr;

		G4UImessenger* fLinacHeadMessenger;

	};
}


#endif