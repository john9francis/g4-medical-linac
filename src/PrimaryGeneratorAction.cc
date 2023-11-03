#include "PrimaryGeneratorAction.hh"

#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"

#include "G4SIunits.hh"

namespace med_linac {
	PrimaryGeneratorAction::PrimaryGeneratorAction() {
		// Create particle gun
		fParticleGun = new G4ParticleGun;


		// set the particle properties
		G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
		G4ParticleDefinition* particle = particleTable->FindParticle("e-");

		// set particle, energy, position, and momentum direction:
		fParticleGun->SetParticleDefinition(particle);
		fParticleGun->SetParticleEnergy(6 * MeV);
		fParticleGun->SetParticlePosition(G4ThreeVector(0, 0, -.49 * m));
		fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0, 0, 1));



	}

	PrimaryGeneratorAction::~PrimaryGeneratorAction() {
		delete fParticleGun;
	}

	void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent) {
		fParticleGun->GeneratePrimaryVertex(anEvent);
	}
}