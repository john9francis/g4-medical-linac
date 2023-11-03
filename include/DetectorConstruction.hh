#ifndef MED_LINAC_DET_CONST_HH
#define MED_LINAC_DET_CONST_HH

#include "G4VUserDetectorConstruction.hh"
#include "G4Material.hh"
#include "G4LogicalVolume.hh"

namespace med_linac {

	class DetectorConstruction : public G4VUserDetectorConstruction {
	public:
		DetectorConstruction() = default;
		~DetectorConstruction() = default;

		G4VPhysicalVolume* Construct();

	};
}

#endif // ! MED_LINAC_DET_CONST_HH