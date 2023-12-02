
#include "LinacHeadMessenger.hh"
#include "G4UImanager.hh"

namespace med_linac {
	LinacHeadMessenger::LinacHeadMessenger() {

		fLinacHeadDir = new G4UIdirectory("/linacHead/");

		fTestCommand = new G4UIcmdWithoutParameter("/linacHead/test", this);
		fLinacHeadAngle = new G4UIcmdWithAnInteger("/linacHead/setAngle", this);
		fLinacHeadY = new G4UIcmdWithADouble("/linacHead/setY", this);
	}

	LinacHeadMessenger::~LinacHeadMessenger() {
		delete fLinacHeadDir;

		delete fTestCommand;
		delete fLinacHeadAngle;
	}

	void LinacHeadMessenger::SetNewValue(G4UIcommand* command, G4String newValues){
		if (command == fTestCommand) {
			G4cout << "Test Command Set" << G4endl;
		}
		else if (command == fLinacHeadY) {
			ChangeLinacHeadY(fLinacHeadY->GetNewDoubleValue(newValues));
		}
		else if (command == fLinacHeadAngle) {
			G4cout << "Setting linac head angle to " << newValues << G4endl;
		}
	}

	G4String LinacHeadMessenger::GetCurrentValue(G4UIcommand* command) {

		return "Hello World";
	}

	void LinacHeadMessenger::SetLinacHeadPointer(G4VPhysicalVolume* physLinacHead) {
		fPhysLinacHead = physLinacHead;
	}

	void LinacHeadMessenger::ChangeLinacHeadY(G4double newY) {

		G4cout << "Setting linac head y to " << newY << G4endl;

		if (fPhysLinacHead == nullptr) {
			G4cout << "Error: Linac head not defined correctly" << G4endl;
			return;
		}
		/*
		// get all the parameters that don't change
		G4ThreeVector currentPos = fPhysLinacHead->GetObjectTranslation();
		G4double x = currentPos.getX();
		G4double z = currentPos.getZ();

		G4cout << "Old linac head position: " << currentPos << G4endl;

		fPhysLinacHead->SetTranslation(G4ThreeVector(x, newY, z));

		G4cout << "New linac head position: " << fPhysLinacHead->GetObjectTranslation() << G4endl;

		// Update the viewport
		G4UImanager* UI = G4UImanager::GetUIpointer();
		UI->ApplyCommand("/vis/viewer/update");

		*/
	}


}