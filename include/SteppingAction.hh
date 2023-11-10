#ifndef med_linac_STEPPING_ACTION_H
#define med_linac_STEPPING_ACTION_H 1

#include "G4UserSteppingAction.hh"
#include "G4LogicalVolume.hh"


namespace med_linac {


	class SteppingAction : public G4UserSteppingAction {
	public:
		SteppingAction();
		~SteppingAction();

		void UserSteppingAction(const G4Step*) override;
	};

}


#endif // !med_linac_STEPPING_ACTION_H
