#include "GraphActivator.hh"

namespace med_linac {
	// initialize our instance variable as null
	GraphActivatorSingleton* GraphActivatorSingleton::instance = nullptr;



	// messenger stuff
	GraphActivatorMessenger::GraphActivatorMessenger() : G4UImessenger() {
		fDirectory = new G4UIdirectory("/graphActivator/");

		setPddCmd = new G4UIcmdWithABool("/graphActivator/activatePDDGraph", this);
		setDoseProfileCmd = new G4UIcmdWithABool("/graphActivator/activateDoseProfileGraph", this);
		setHeatMapCmd = new G4UIcmdWithABool("/graphActivator/activateHeatMap", this);
	}

	void GraphActivatorMessenger::SetNewValue(G4UIcommand* command, G4String newValue) {
		// access singleton
		auto GASingleton = GraphActivatorSingleton::GetInstance();

		if (command == setPddCmd) {
			GASingleton->SetMakePDD(setPddCmd->GetNewBoolValue(newValue));
		}
		if (command == setDoseProfileCmd) {
			GASingleton->SetMakeDoseProfile(setDoseProfileCmd->GetNewBoolValue(newValue));
		}
		if (command == setHeatMapCmd) {
			GASingleton->SetMakeHeatMap(setHeatMapCmd->GetNewBoolValue(newValue));
		}

	}
}