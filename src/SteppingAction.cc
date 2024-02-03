
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
			PhantomHit* hit = new PhantomHit();
			hit->SetEnergy(step->GetTotalEnergyDeposit());
			hit->SetPos(step->GetPreStepPoint()->GetPosition());

			fPointerToUserRunAction->AddToPddHitsCollection(hit);

		}
	
	}

}