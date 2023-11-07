#ifndef med_linac_PHYSICS_LIST_H
#define med_linac_PHYSICS_LIST_H 1

#include "G4VModularPhysicsList.hh"


namespace med_linac
{
	class PhysicsList : public G4VModularPhysicsList
	{
	public:
		PhysicsList();
		virtual ~PhysicsList() override = default;

		// Mandatory methods to override;
		virtual void ConstructParticle() override;
		virtual void ConstructProcess() override;

	};
}

#endif