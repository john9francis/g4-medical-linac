#include "LinacHeadMessenger.hh"

#include "G4UImanager.hh"

#include <iostream>
#include <unordered_map>
#include <functional>


namespace med_linac {
	LinacHeadMessenger::LinacHeadMessenger(DetectorConstruction* detectorConstruction)
		: G4UImessenger(), fDetectorConstruction(detectorConstruction) {

		// create the directory for our ui commands
		fDirectory = new G4UIdirectory("/linacHead/");
		fDirectory->SetGuidance("Commands to move the linac head");

		// set our commands
		fAddFlatteningFilterCmd = new G4UIcmdWithoutParameter("/linacHead/addFF", this);
		fAddFlatteningFilterCmd->SetGuidance("Adds a flattening filter to make the beam uniform");
		fAddFlatteningFilterCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

		fRemoveFlatteningFilterCmd = new G4UIcmdWithoutParameter("/linacHead/removeFF", this);
		fRemoveFlatteningFilterCmd->SetGuidance("Removes flattening filter if it exists");
		fRemoveFlatteningFilterCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

		fPurePhotonBeamCmd = new G4UIcmdWithABool("/linacHead/purePhotonBeam", this);
		fPurePhotonBeamCmd->SetParameterName("Pure Photon?", false);
		fPurePhotonBeamCmd->SetGuidance("Deletes electrons from the beam. !!!WARNING!!! the resulting beam is not physically accurate!");
		fPurePhotonBeamCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

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

		fMoveToAimCmd = new G4UIcmdWithoutParameter("/linacHead/moveToAim", this);
		fMoveToAimCmd->SetGuidance("Moves the linac head so the beam will hit the target");
		fMoveToAimCmd->AvailableForStates(G4State_PreInit, G4State_Idle);



	}

	void LinacHeadMessenger::SetNewValue(G4UIcommand* command, G4String newValue) {
		// takes in command and does the corresponding action

		if (command == fAddFlatteningFilterCmd) {
			fDetectorConstruction->AddFlatteningFilter();
		}
		if (command == fRemoveFlatteningFilterCmd) {
			fDetectorConstruction->RemoveFlatteningFilter();
		}
		if (command == fPurePhotonBeamCmd) {
			fDetectorConstruction->SetPurePhotonBeamFlag(fPurePhotonBeamCmd->GetNewBoolValue(newValue));
		}
		if (command == fAngleCmd) {
			fDetectorConstruction->SetLinacHeadAngle(fAngleCmd->GetNew3VectorValue(newValue));
		}
		if (command == fPositionCmd) {
			fDetectorConstruction->SetLinacHeadPosition(fPositionCmd->GetNew3VectorValue(newValue));
		}
		if (command == fMoveToAimCmd) {
			fDetectorConstruction->MoveToAim();
		}
		if (command == fShiftCmd) {

			// checking if the value is in the position map
			if (positionShiftMap.find(newValue) != positionShiftMap.end()) {

				// then get the value corresponding to that key
				G4ThreeVector shiftAmount = positionShiftMap[newValue];

				// and tell det construction to shift by that value. 
				fDetectorConstruction->ShiftLinacHeadPosition(shiftAmount);

			}

			// if it's not in the position map, it may be in the rotation map
			else if (rotationShiftMap.find(newValue) != rotationShiftMap.end()) {

				fDetectorConstruction->ShiftLinacHeadRotation(rotationShiftMap[newValue]);

			}
			// if the user put in an invalid command
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

		// We run 0 particles just to clear out the visualization
		// if we didn't have this, it would redraw all the trajectories
		// before shifting.
		UI->ApplyCommand("/run/beamOn 0");
		UI->ApplyCommand("/vis/viewer/rebuild");
	}
}