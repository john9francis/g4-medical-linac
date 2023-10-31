#include "PhysicsList.hh"

#include "G4EmStandardPhysics.hh"

namespace med_linac {

	PhysicsList::PhysicsList() {
		RegisterPhysics(new G4EmStandardPhysics);
	}

	PhysicsList::~PhysicsList() {
		// it should delete everything automatically
	}

	void PhysicsList::ConstructParticle() {
		G4VModularPhysicsList::ConstructParticle();
	}

	void PhysicsList::ConstructProcess() {
		G4VModularPhysicsList::ConstructProcess();
	}
}