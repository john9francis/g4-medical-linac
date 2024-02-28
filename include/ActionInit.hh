#ifndef med_linac_ACTION_INIT_H
#define med_linac_ACTION_INIT_H 1

#include "G4VUserActionInitialization.hh"

namespace med_linac {

	// Action initialization: where we initialize the user actions
	// like Run Action, Primary Generator Action, Stepping Action
	class ActionInit : public G4VUserActionInitialization {
	public:
		ActionInit() = default;
		~ActionInit() = default;
		
		void Build() const;
		void BuildForMaster() const;
	
	};
}

#endif // !med_linac_ACTION_INIT_H
