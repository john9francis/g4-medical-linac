#include "LinacHeadMessenger.hh"

#include "G4UImanager.hh"

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

	}

	void LinacHeadMessenger::SetNewValue(G4UIcommand* command, G4String newValue) {
		G4cout << newValue << G4endl;
		if (command == fAngleCmd) {
			fDetectorConstruction->SetLinacHeadAngle(fAngleCmd->GetNew3VectorValue(newValue));
		}
		if (command == fPositionCmd) {
			fDetectorConstruction->SetLinacHeadPosition(fPositionCmd->GetNew3VectorValue(newValue));
		}

		// update the viewport
		G4UImanager* UI = G4UImanager::GetUIpointer();
		UI->ApplyCommand("/run/beamOn 0");
		UI->ApplyCommand("/vis/viewer/rebuild");
	}
}