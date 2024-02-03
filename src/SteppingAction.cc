
#include "SteppingAction.hh"
#include "DetectorConstruction.hh"

#include "G4Step.hh"
#include "G4RunManager.hh"

#include "G4AnalysisManager.hh"

#include "G4UnitsTable.hh"

// NEW BRANCH moving phantom logic to stepping action :(

namespace med_linac {
	SteppingAction::SteppingAction() {
	}

	SteppingAction::~SteppingAction() {
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
	
	}

}