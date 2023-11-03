#include "ActionInitialization.hh"

#include "PrimaryGeneratorAction.hh"

namespace med_linac {
	void ActionInitialization::Build() const {
		// Set our user actions
		SetUserAction(new PrimaryGeneratorAction);
	}

	void ActionInitialization::BuildForMaster() const {
		// This is for the main thread, RunAction will go here eventually
	}
}