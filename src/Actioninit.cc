
#include "ActionInit.hh"
#include "PrimaryGeneratorAction.hh"
#include "SteppingAction.hh"
#include "RunAction.hh"

namespace med_linac {

	void ActionInit::Build() const {
		// Multithreaded
		
		// set the Geant4 actions
		SetUserAction(new PrimaryGeneratorAction);

		SetUserAction(new RunAction());

		SetUserAction(new SteppingAction());

	};

	void ActionInit::BuildForMaster() const {
		// Sequential

		SetUserAction(new RunAction());

	}

}