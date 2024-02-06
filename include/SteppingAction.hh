#ifndef med_linac_STEPPING_ACTION_H
#define med_linac_STEPPING_ACTION_H 1

#include "G4UserSteppingAction.hh"
#include "G4LogicalVolume.hh"
#include "RunAction.hh"


namespace med_linac {


	class SteppingAction : public G4UserSteppingAction {
	public:
		SteppingAction(RunAction* runAction);
		// note: stepping action must take in a pointer to the user run action
		~SteppingAction();

		void UserSteppingAction(const G4Step*) override;

	private:
		G4int fDoseProfileH1ID = 1;
		RunAction* fPointerToUserRunAction;
	};

}


#endif // !med_linac_STEPPING_ACTION_H
