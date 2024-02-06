
#include "ActionInit.hh"
#include "PrimaryGeneratorAction.hh"
#include "SteppingAction.hh"
#include "RunAction.hh"

namespace med_linac {

	void ActionInit::Build() const {
		// set our user actions

		SetUserAction(new PrimaryGeneratorAction);

		RunAction* userRunAction = new RunAction();
		SetUserAction(userRunAction);

		SetUserAction(new SteppingAction(userRunAction));

	};

	void ActionInit::BuildForMaster() const {
		// Just for master branch

		SetUserAction(new RunAction());

	}

}