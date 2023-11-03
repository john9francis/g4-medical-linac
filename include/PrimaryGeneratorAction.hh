#ifndef MED_LINAC_PRIMARY_GEN_ACTION_HH
#define MED_LINAC_PRIMARY_GEN_ACTION_HH

#include "G4VUserPrimaryGeneratorAction.hh"

#include "G4ParticleGun.hh"


namespace med_linac {
	class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction {
	public:
		PrimaryGeneratorAction();
		~PrimaryGeneratorAction();

		void GeneratePrimaries(G4Event*) override;


	private:
		// note: it's geant4 best practice to start member variables with 'f'
		G4ParticleGun* fParticleGun; 
	};

}

#endif // !MED_LINAC_PRIMARY_GEN_ACTION_HH
