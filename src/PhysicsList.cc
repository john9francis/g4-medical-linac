#include "PhysicsList.hh"

#include "G4EmStandardPhysics.hh"
#include "G4EmLivermorePolarizedPhysics.hh"
#include "G4EmDNAPhysics_option2.hh"

namespace med_linac
{
	PhysicsList::PhysicsList() : G4VModularPhysicsList() {
		// Get the standard EM physics for bremsstrahlung
		RegisterPhysics(new G4EmStandardPhysics());

		// DNA physics for the interactions with G4_Water (see http://geant4-dna.org/)
		//RegisterPhysics(new G4EmDNAPhysics_option2());

	}

	void PhysicsList::ConstructParticle(){
		G4VModularPhysicsList::ConstructParticle();
	}


	void PhysicsList::ConstructProcess() {
		G4VModularPhysicsList::ConstructProcess();
	}
}