
#include "LinacHeadMessenger.hh"

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
			G4cout << "Setting linac head y to " << newValues << G4endl;
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

	}


}