#ifndef med_linac_DETECTOR_CONSTRUCTION_H
#define med_linac_DETECTOR_CONSTRUCTION_H 1

#include "G4VUserDetectorConstruction.hh"
#include "G4PVPlacement.hh"


namespace med_linac
{
	class DetectorConstruction : public G4VUserDetectorConstruction
	{
	public:
		DetectorConstruction() = default;
		~DetectorConstruction() override = default;

		G4VPhysicalVolume* Construct() override;

		G4VPhysicalVolume* GetParticleGunAnchor1() const { return fParticleGunAnchor1; }
		G4VPhysicalVolume* GetParticleGunAnchor2() const { return fParticleGunAnchor2; }

	private:
		G4VPhysicalVolume* fParticleGunAnchor1 = nullptr;
		G4VPhysicalVolume* fParticleGunAnchor2 = nullptr;

	};
}


#endif