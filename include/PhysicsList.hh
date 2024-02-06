#ifndef med_linac_PHYSICS_LIST_H
#define med_linac_PHYSICS_LIST_H 1

#include "G4VModularPhysicsList.hh"

// different physics list constructors
#include "G4EmStandardPhysics.hh"
#include "G4EmLivermorePolarizedPhysics.hh"
#include "G4EmDNAPhysics_option2.hh"
#include "G4EmDNAPhysics_option1.hh"


namespace med_linac
{
	class PhysicsList : public G4VModularPhysicsList
	{
	public:
		PhysicsList() : G4VModularPhysicsList() {
			RegisterPhysics(new G4EmStandardPhysics());
		};
		virtual ~PhysicsList() = default;

	};
}

#endif