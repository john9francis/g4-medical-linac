#include "PrimaryGeneratorAction.hh"

#include "G4Event.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"

#include "Randomize.hh"

#include "G4UnitsTable.hh"

#include "G4RunManager.hh"
#include "DetectorConstruction.hh"


namespace med_linac
{
	PrimaryGeneratorAction::PrimaryGeneratorAction() {
		// set up particle gun
		G4int nParticles = 1;
		fParticleGun = new G4ParticleGun(nParticles);

		// define default particle
		const G4String& particleName = "e-";


		// Find the particle in the G4Particle table
		G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
		G4ParticleDefinition* particle
			= particleTable->FindParticle(particleName);

		// Set the particle type to the particle gun
		fParticleGun->SetParticleDefinition(particle);

		// set default energy, can be changed with the "gun" ui messenger
		G4double energy = 6 * MeV;
		fParticleGun->SetParticleEnergy(energy);

	}

	PrimaryGeneratorAction::~PrimaryGeneratorAction() {
		delete fParticleGun;
	}

	void PrimaryGeneratorAction::GeneratePrimaries(G4Event* event)
	{
		// First, find the particle gun anchors

		// access runManager singleton
		auto* runManager = G4RunManager::GetRunManager();

		// find our detectorConstruction in the runmanager
		const auto* detConstruction = static_cast<const DetectorConstruction*>(
			runManager->GetUserDetectorConstruction());


		// get position and rotation of linac head and gun anchor
		G4ThreeVector linacHeadPos = detConstruction->GetLinacHeadPos();
		G4ThreeVector linacHeadRot = detConstruction->GetLinacHeadRot();

		G4double phi = linacHeadRot.getX();
		G4double theta = linacHeadRot.getY();
		G4double psi = linacHeadRot.getZ();
		G4ThreeVector gunAnchorPos = detConstruction->GetGunAnchorPos().rotate(phi, theta, psi);


		// now we get the position of the gun anchor relative to the world
		G4ThreeVector absoluteGunPos = gunAnchorPos + linacHeadPos;


		// set the particle gun's position to where the anchor is
		fParticleGun->SetParticlePosition(absoluteGunPos);


		// Now we set the particle's momentum direction based on the gun's rotation
		auto baseVector = G4ThreeVector(0, 0, 1);
		G4ThreeVector momentumDirection = baseVector.rotate(phi, theta, psi);

		// set the direction to where the gun anchor is pointing to
		fParticleGun->SetParticleMomentumDirection(momentumDirection);

		// satisfy "generate primaries" here.
		fParticleGun->GeneratePrimaryVertex(event);
	}
}