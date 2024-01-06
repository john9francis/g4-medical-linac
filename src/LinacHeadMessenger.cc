#include "LinacHeadMessenger.hh"

#include "G4UImanager.hh"

namespace med_linac {
	LinacHeadMessenger::LinacHeadMessenger(DetectorConstruction* detectorConstruction)
		: G4UImessenger(), fDetectorConstruction(detectorConstruction) {

		fDirectory = new G4UIdirectory("/linacHead/");
		fDirectory->SetGuidance("Commands to move the linac head");

		fAngleCmd = new G4UIcmdWithADoubleAndUnit("/linacHead/setAngle", this);
		fAngleCmd->SetGuidance("Set the angle around the detector in radians or degrees");
		fAngleCmd->SetParameterName("phi", false);
		fAngleCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

	}

	void LinacHeadMessenger::SetNewValue(G4UIcommand* command, G4String newValue) {
		if (command == fAngleCmd) {
			fDetectorConstruction->SetLinacHeadAngle(fAngleCmd->GetNewDoubleValue(newValue));
		}

		// update the viewport
		G4UImanager* UI = G4UImanager::GetUIpointer();
		UI->ApplyCommand("/vis/viewer/rebuild");
	}
}