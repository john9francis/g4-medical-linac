#include "GraphActivator.hh"
#include "G4AnalysisManager.hh"

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
		auto analysisManager = G4AnalysisManager::Instance();

		if (command == setPddCmd) {
			//GASingleton->SetMakePDD(setPddCmd->GetNewBoolValue(newValue));
			analysisManager->SetH1Activation(0, setPddCmd->GetNewBoolValue(newValue));
		}
		if (command == setDoseProfileCmd) {
			//GASingleton->SetMakeDoseProfile(setDoseProfileCmd->GetNewBoolValue(newValue));
			analysisManager->SetH1Activation(1, setPddCmd->GetNewBoolValue(newValue));
		}
		if (command == setHeatMapCmd) {
			//GASingleton->SetMakeHeatMap(setHeatMapCmd->GetNewBoolValue(newValue));
			// do nothing (for now)
		}

	}
}