#include "PhysicsList.hh"

#include "G4EmStandardPhysics.hh"
#include "G4EmLivermorePolarizedPhysics.hh"

namespace med_linac
{
	PhysicsList::PhysicsList() : G4VModularPhysicsList() {
		// Get the standard EM physics for bremsstrahlung
		RegisterPhysics(new G4EmStandardPhysics());

		// Get the livermore polarized physics for dose measurement
		RegisterPhysics(new G4EmLivermorePolarizedPhysics());

	}

	void PhysicsList::ConstructParticle(){
		G4VModularPhysicsList::ConstructParticle();
	}


	void PhysicsList::ConstructProcess() {
		G4VModularPhysicsList::ConstructProcess();
	}
}