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

		// define particle properties
		const G4String& particleName = "e-";


		// Find the particle (e-) in the G4Particle table
		G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
		G4ParticleDefinition* particle
			= particleTable->FindParticle(particleName);

		// Set the particle type to the particle gun
		fParticleGun->SetParticleDefinition(particle);

		// (test) hardcode the energy and we'll change it in mac files
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


		// get the position of the linac head and gun anchors
		auto* linacHead = detConstruction->GetLinacHead();
		auto* gunAnchor1 = detConstruction->GetParticleGunAnchor1();

		auto* linacHeadRotation = linacHead->GetObjectRotation();
		auto phi = linacHeadRotation->getPhi();
		auto theta = linacHeadRotation->getTheta();
		auto psi = linacHeadRotation->getPsi();

		G4ThreeVector linacHeadPos = linacHead->GetObjectTranslation();
		G4ThreeVector gunAnchor1Pos = gunAnchor1->GetObjectTranslation().rotate(phi, theta, psi);

		// now we get the position of the gun anchor relative to the world
		G4ThreeVector absoluteGunPos = gunAnchor1Pos + linacHeadPos;


		// set the particle gun's position to the anchor
		fParticleGun->SetParticlePosition(absoluteGunPos);


		// Now we set the particle's momentum direction based on the gun's rotation
		auto baseVector = G4ThreeVector(0,0,1);
		G4ThreeVector momentumDirection = baseVector.rotate(phi, theta, psi);

		fParticleGun->SetParticleMomentumDirection(momentumDirection);

		// satisfy "generate primaries" here.
		fParticleGun->GeneratePrimaryVertex(event);
	}
}