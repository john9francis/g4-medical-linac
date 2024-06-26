
#include "SteppingAction.hh"

#include "G4Step.hh"
#include "G4AnalysisManager.hh"
#include "G4SystemOfUnits.hh"

#include "DetectorConstruction.hh"
#include "G4RunManager.hh"

namespace med_linac {


	void SteppingAction::UserSteppingAction(const G4Step* step) {

		// Get our current volume.
		// The particle's current volume will dictate which graph we add data to.
		//
		auto currentPhysVolume = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume();


		// if it's in the dose detector, fill the dose profile h1
		if (currentPhysVolume->GetName() == "physDD") {

			G4Track* track = (G4Track*)(step->GetTrack());
			G4String particleName = track->GetDefinition()->GetParticleName();

			// if the user wants a pure photon beam, kill all particles
			auto runManger = G4RunManager::GetRunManager();
			const DetectorConstruction* detConst = static_cast<const DetectorConstruction*>(runManger->GetUserDetectorConstruction());
			G4bool purePhotonBeam = detConst->GetPurePhotonBeamFlag();

			if (purePhotonBeam == true) {
				// Kill other particles from beam

				if (track->GetParticleDefinition()->GetParticleName() != "gamma") {
					track->SetTrackStatus(fStopAndKill);
				}
			}


			G4ThreeVector position = step->GetPreStepPoint()->GetPosition();
			G4double x = position.getX();
			G4double energy = step->GetPreStepPoint()->GetKineticEnergy();

			auto analysisManager = G4AnalysisManager::Instance();
			analysisManager->FillH1(fDoseProfileH1ID, x, energy);

			// also fill the bremsstrahlung spectrum H1
			if (particleName == "gamma"){
				analysisManager->FillH1(2, energy);
			}
			else if (particleName == "e-") {
				analysisManager->FillH1(3, energy);
			}
			else if (particleName == "e+") {
				analysisManager->FillH1(4, energy);
			}
			else {
				analysisManager->FillH1(5, energy);
			}

		}



		// if our particle is in the phantom, add to the PDD and HeatMap graphs
		if (currentPhysVolume->GetName() == "physPhantom") {

			G4ThreeVector pos = step->GetPreStepPoint()->GetPosition();
			G4double energy = step->GetTotalEnergyDeposit();

			auto analysisManager = G4AnalysisManager::Instance();

			// add to the PDD graph
			// the + 15 * cm converts position to depth.
			analysisManager->FillH1(fPddH1ID, pos.getZ() + 15 * cm, energy);

			// add to the heat map
			analysisManager->FillH2(fXYHeatMapH2ID, pos.getX(), pos.getY(), energy);
			analysisManager->FillH2(fYZHeatMapH2ID, pos.getY(), pos.getZ(), energy);
			analysisManager->FillH2(fXZHeatMapH2ID, pos.getX(), pos.getZ(), energy);

		}

		

	}

}