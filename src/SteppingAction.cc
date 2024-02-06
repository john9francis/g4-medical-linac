
#include "SteppingAction.hh"
#include "DetectorConstruction.hh"

#include "G4Step.hh"
#include "G4RunManager.hh"

#include "G4AnalysisManager.hh"

#include "G4UnitsTable.hh"

// NEW BRANCH moving phantom logic to stepping action :(
#include "PhantomHitsCollection.hh"

namespace med_linac {
	SteppingAction::SteppingAction(RunAction* runAction) {
		fPointerToUserRunAction = runAction;
	}

	SteppingAction::~SteppingAction() {
		// no need to delete run action, it's not allocated here
	}

	void SteppingAction::UserSteppingAction(const G4Step* step) {

		// if our particle is in the dose detector, find it's x position and energy
		auto currentPhysVolume = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume();

		if (currentPhysVolume->GetName() == "physDD") {

			G4ThreeVector position = step->GetPreStepPoint()->GetPosition();
			G4double x = position.getX();
			G4double energy = step->GetPreStepPoint()->GetTotalEnergy();

			auto analysisManager = G4AnalysisManager::Instance();
			analysisManager->FillH1(fDoseProfileH1ID, x, energy);
		}


		// if our particle is in the phantom, add a hit to the run hits collection
		if (currentPhysVolume->GetName() == "physPhantom") {

			G4ThreeVector pos = step->GetPreStepPoint()->GetPosition();
			G4double energy = step->GetTotalEnergyDeposit();

			PhantomHit* hit = new PhantomHit();
			hit->SetEnergy(energy);
			hit->SetPos(pos);

			// this is for adding to the PDD
			fPointerToUserRunAction->AddToPddHitsCollection(hit);

			// this is adding to the heat map
			auto analysisManager = G4AnalysisManager::Instance();
			analysisManager->FillH2(0, pos.getX(), pos.getY(), energy);
			analysisManager->FillH2(1, pos.getY(), pos.getZ(), energy);
			analysisManager->FillH2(2, pos.getX(), pos.getZ(), energy);


		}
	
	}

}