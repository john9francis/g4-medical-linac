#ifndef MED_LINAC_PHYSICS_LIST_HH
#define MED_LINAC_PHYSICS_LIST_HH

#include "G4VModularPhysicsList.hh"

namespace med_linac {

	class PhysicsList : public G4VModularPhysicsList {
	public:
		PhysicsList();
		virtual ~PhysicsList() override = default;

		void ConstructParticle() override;
		void ConstructProcess() override;
	};
}

#endif // !MED_LINAC_PHYSICS_LIST_HH
