#ifndef MED_LINAC_DET_CONST_HH
#define MED_LINAC_DET_CONST_HH

#include "G4VUserDetectorConstruction.hh"

namespace med_linac {

	class DetectorConstruction : public G4VUserDetectorConstruction {
	public:
		DetectorConstruction() = default;
		~DetectorConstruction() = default;

		G4VPhysicalVolume* Construct();
	};
}

#endif // ! MED_LINAC_DET_CONST_HH