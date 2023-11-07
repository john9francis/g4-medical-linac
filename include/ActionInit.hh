#ifndef med_linac_ACTION_INIT_H
#define med_linac_ACTION_INIT_H 1

#include "G4VUserActionInitialization.hh"

namespace med_linac {
	class ActionInit : public G4VUserActionInitialization {
	public:
		ActionInit() = default;
		~ActionInit() override = default;

		void Build() const override;
		void BuildForMaster() const override;
	
	};
}

#endif // !med_linac_ACTION_INIT_H
