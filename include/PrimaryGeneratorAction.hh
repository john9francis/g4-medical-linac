#ifndef med_linac_PRIMARY_GENERATOR_ACTION_H
#define med_linac_PRIMARY_GENERATOR_ACTION_H 1


#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ThreeVector.hh"
#include "globals.hh"
#include "G4SystemOfUnits.hh"
#include "G4ParticleGun.hh"



namespace med_linac {

	// Primary Generator Action: shoots particles
	class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
	{
	public:
		PrimaryGeneratorAction();
		~PrimaryGeneratorAction();

		void GeneratePrimaries(G4Event*) override;
		
	private:
		// our particle gun that actually generates the primaries
		G4ParticleGun* fParticleGun;
	};
}


#endif 
