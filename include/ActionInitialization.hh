#ifndef MED_LINAC_ACTION_INIT_HH
#define MED_LINAC_ACTION_INIT_HH

#include "G4VUserActionInitialization.hh"

namespace med_linac {
	class ActionInitialization : public G4VUserActionInitialization {

	public:
		ActionInitialization() = default;
		~ActionInitialization() = default;

		void Build() const override;
		void BuildForMaster() const override;
	};

}

#endif // !MED_LINAC_ACTION_INIT_HH
