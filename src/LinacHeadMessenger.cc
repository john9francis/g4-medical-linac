
#include "LinacHeadMessenger.hh"

namespace med_linac {
	LinacHeadMessenger::LinacHeadMessenger() {
		fLinacHeadDir = new G4UIdirectory("/hello/");
		fTestCommand = new G4UIcmdWithoutParameter("/hello/test", this);
	}

	LinacHeadMessenger::~LinacHeadMessenger() {
		delete fLinacHeadDir;
		delete fTestCommand;
	}

	void LinacHeadMessenger::SetNewValue(G4UIcommand* command, G4String newValues){
		if (command == fTestCommand) {
			G4cout << "Test Command Set" << G4endl;
		}
	}

	G4String LinacHeadMessenger::GetCurrentValue(G4UIcommand* command) {
		if (command == fTestCommand) {
			G4cout << "Test command Got" << G4endl;
		}

		return "Hello World";
	}


}