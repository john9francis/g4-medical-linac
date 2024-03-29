#ifndef med_linac_LINAC_HEAD_MESSENGER_HH
#define med_linac_LINAC_HEAD_MESSENGER_HH

#include "G4UImessenger.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWith3VectorAndUnit.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithoutParameter.hh"
#include "G4UIcmdWithABool.hh"

#include "G4SystemOfUnits.hh"

#include "DetectorConstruction.hh"

#include <iostream>
#include <map>


namespace med_linac {

	// Linac Head Messenger: exposes some commands to the user to control
	// the linac head. The user can move it, rotate it, add or remove the FF.
	class LinacHeadMessenger : public G4UImessenger {
	public:
		LinacHeadMessenger(DetectorConstruction* detectorConstruction);
		~LinacHeadMessenger() = default;

		// From the base UImessenger class
		void SetNewValue(G4UIcommand* command, G4String newValues) override;


	private:
		// variable to hold a pointer to the detector construction
		DetectorConstruction* fDetectorConstruction;

		// ui directory
		G4UIdirectory* fDirectory;

		// All our commands
		//
		G4UIcmdWithoutParameter* fAddFlatteningFilterCmd;
		G4UIcmdWithoutParameter* fRemoveFlatteningFilterCmd;
		
		G4UIcmdWithABool* fPurePhotonBeamCmd;

		G4UIcmdWith3VectorAndUnit* fAngleCmd;
		G4UIcmdWith3VectorAndUnit* fPositionCmd;

		G4UIcmdWithAString* fShiftCmd;

		G4UIcmdWithoutParameter* fMoveToAimCmd;


		// variables for the shift command
		//
		G4double shiftPositionAmount = 5 * cm;
		G4double shiftRotationAmount = 10 * deg;
		std::map<G4String, G4ThreeVector> positionShiftMap = {
			{"x",  G4ThreeVector(shiftPositionAmount, 0, 0)},
			{"y",  G4ThreeVector(0, shiftPositionAmount, 0)},
			{"z",  G4ThreeVector(0, 0, shiftPositionAmount)},
			{"-x", G4ThreeVector(-shiftPositionAmount, 0, 0)},
			{"-y", G4ThreeVector(0, -shiftPositionAmount, 0)},
			{"-z", G4ThreeVector(0, 0, -shiftPositionAmount)}
		};
		std::map<G4String, G4ThreeVector> rotationShiftMap = {
			{"phi",    G4ThreeVector(shiftRotationAmount, 0, 0)},
			{"theta",  G4ThreeVector(0, shiftRotationAmount, 0)},
			{"psi",    G4ThreeVector(0, 0, shiftRotationAmount)},
			{"-phi",   G4ThreeVector(-shiftRotationAmount, 0, 0)},
			{"-theta", G4ThreeVector(0, -shiftRotationAmount, 0)},
			{"-psi",   G4ThreeVector(0, 0, -shiftRotationAmount)}
		};
	};


}

#endif // !med_linac_LINAC_HEAD_MESSENGER_HH
