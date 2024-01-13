#include "LinacHeadMessenger.hh"

#include "G4UImanager.hh"

#include <iostream>
#include <unordered_map>
#include <functional>


namespace med_linac {
	LinacHeadMessenger::LinacHeadMessenger(DetectorConstruction* detectorConstruction)
		: G4UImessenger(), fDetectorConstruction(detectorConstruction) {

		fDirectory = new G4UIdirectory("/linacHead/");
		fDirectory->SetGuidance("Commands to move the linac head");

		// set our commands
		fAngleCmd = new G4UIcmdWith3VectorAndUnit("/linacHead/setAngle", this);
		fAngleCmd->SetGuidance("Set the rotation angle of the linac head in radians or degrees");
		fAngleCmd->SetParameterName("Phi", "Theta", "Psi", false);
		fAngleCmd->SetDefaultUnit("deg");
		fAngleCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

		fPositionCmd = new G4UIcmdWith3VectorAndUnit("/linacHead/setPosition", this);
		fPositionCmd->SetGuidance("Set the position of the linac head");
		fPositionCmd->SetParameterName("x", "y", "z", false);
		fPositionCmd->SetDefaultUnit("cm");
		fPositionCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

		fShiftCmd = new G4UIcmdWithAString("/linacHead/shift", this);
		fShiftCmd->SetGuidance("Shifts your specified coordinate 5 cm.");
		fShiftCmd->SetParameterName("coordinate", false);
		fShiftCmd->AvailableForStates(G4State_PreInit, G4State_Idle);


		

	}

	void LinacHeadMessenger::SetNewValue(G4UIcommand* command, G4String newValue) {
		if (command == fAngleCmd) {
			fDetectorConstruction->SetLinacHeadAngle(fAngleCmd->GetNew3VectorValue(newValue));
		}
		if (command == fPositionCmd) {
			fDetectorConstruction->SetLinacHeadPosition(fPositionCmd->GetNew3VectorValue(newValue));
		}
		if (command == fShiftCmd) {

			// if the direction is a key in our map
			if (positionShiftMap.find(newValue) != positionShiftMap.end()) {

				// then get the value corresponding to that key
				G4ThreeVector shiftAmount = positionShiftMap[newValue];

				// and tell det construction to shift by that value. 
				fDetectorConstruction->ShiftLinacHeadPosition(shiftAmount);

			}

			// then, check the rotation map
			else if (rotationShiftMap.find(newValue) != rotationShiftMap.end()) {

				fDetectorConstruction->ShiftLinacHeadRotation(rotationShiftMap[newValue]);

			}
			else {
				G4cout
					<< "Direction not found. "
					<< '\n'
					<< "Please input one of the following: "
					<< '\n'
					<< "x, y, z, -x, -y, -z, phi, theta, psi, -phi, -theta, -psi"
					<< G4endl;
			}
		}

		// update the viewport
		G4UImanager* UI = G4UImanager::GetUIpointer();
		UI->ApplyCommand("/run/beamOn 0");
		UI->ApplyCommand("/vis/viewer/rebuild");
	}
}