
#include "SteppingAction.hh"

#include "G4Step.hh"
#include "G4AnalysisManager.hh"
#include "G4SystemOfUnits.hh"

namespace med_linac {


	void SteppingAction::UserSteppingAction(const G4Step* step) {

		// Get our current volume.
		// The particle's current volume will dictate which graph we add data to.
		//
		auto currentPhysVolume = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume();


		// if it's in the dose detector, fill the dose profile h1
		if (currentPhysVolume->GetName() == "physDD") {

			G4ThreeVector position = step->GetPreStepPoint()->GetPosition();
			G4double x = position.getX();
			G4double energy = step->GetPreStepPoint()->GetTotalEnergy();

			auto analysisManager = G4AnalysisManager::Instance();
			analysisManager->FillH1(fDoseProfileH1ID, x, energy);
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


		// create the bremsstrahlung spectrum from secondaries produced in the target
		if (currentPhysVolume->GetName() == "physTarget") {

			// save the energy of all secondaries
			const std::vector<const G4Track*>* secondaries = step->GetSecondaryInCurrentStep();

			// out of all secondaries, save the gammas. 
			for (G4int i = 0; i < secondaries->size(); i++) {
				const G4Track* track = (*secondaries)[i];

				G4String particleName = track->GetParticleDefinition()->GetParticleName();

				if (particleName == "gamma") {
					G4double energy = track->GetKineticEnergy();

					auto analysisManager = G4AnalysisManager::Instance();
					analysisManager->FillH1(fBremsstrahlungH1ID, energy);
				}
			}

		}
	
	}

}