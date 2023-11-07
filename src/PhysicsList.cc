#include "PhysicsList.hh"

#include "G4EmStandardPhysics.hh"


namespace med_linac
{
	PhysicsList::PhysicsList() : G4VModularPhysicsList() {
		// Get the standard EM particles
		RegisterPhysics(new G4EmStandardPhysics());
	}

	void PhysicsList::ConstructParticle() {
		G4VModularPhysicsList::ConstructParticle();
	}


	void PhysicsList::ConstructProcess() {
		G4VModularPhysicsList::ConstructProcess();
	}
}