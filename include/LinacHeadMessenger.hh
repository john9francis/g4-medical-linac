#ifndef med_linac_LINAC_HEAD_MESSENGER_HH
#define med_linac_LINAC_HEAD_MESSENGER_HH

#include "G4UImessenger.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWith3VectorAndUnit.hh"
#include "G4UIcmdWithAString.hh"

#include "G4SystemOfUnits.hh"

#include "DetectorConstruction.hh"

#include <iostream>
#include <map>


namespace med_linac {
	class LinacHeadMessenger : public G4UImessenger {
	public:
		LinacHeadMessenger(DetectorConstruction* detectorConstruction);
		//~LinacHeadMessenger();

		void SetNewValue(G4UIcommand* command, G4String newValues);
		//G4String GetCurrentValue(G4UIcommand* command);

	
	private:
		DetectorConstruction* fDetectorConstruction;

		G4UIdirectory* fDirectory;

		G4UIcmdWith3VectorAndUnit* fAngleCmd;
		G4UIcmdWith3VectorAndUnit* fPositionCmd;

		G4UIcmdWithADoubleAndUnit* fShiftZCmd;

		G4UIcmdWithAString* fShiftCmd;

		G4double shiftAmount = 5 * cm;
		std::map<G4String, G4ThreeVector> positionShiftMap = {
			{"x",  G4ThreeVector(shiftAmount, 0, 0)},
			{"y",  G4ThreeVector(0, shiftAmount, 0)},
			{"z",  G4ThreeVector(0, 0, shiftAmount)},
			{"-x", G4ThreeVector(-shiftAmount, 0, 0)},
			{"-y", G4ThreeVector(0, -shiftAmount, 0)},
			{"-z", G4ThreeVector(0, 0, -shiftAmount)}
		};
		std::map<G4String, G4ThreeVector> rotationShiftMap = {
			{"phi",    G4ThreeVector(shiftAmount, 0, 0)},
			{"theta",  G4ThreeVector(0, shiftAmount, 0)},
			{"psi",    G4ThreeVector(0, 0, shiftAmount)},
			{"-phi",   G4ThreeVector(-shiftAmount, 0, 0)},
			{"-theta", G4ThreeVector(0, -shiftAmount, 0)},
			{"-psi",   G4ThreeVector(0, 0, -shiftAmount)}
		};
	};


}

#endif // !med_linac_LINAC_HEAD_MESSENGER_HH
