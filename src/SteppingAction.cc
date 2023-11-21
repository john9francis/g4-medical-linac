
#include "SteppingAction.hh"
#include "DetectorConstruction.hh"

#include "G4Step.hh"
#include "G4RunManager.hh"

#include "G4AnalysisManager.hh"

#include "G4UnitsTable.hh"

#include "DetectorConstruction.hh"

namespace med_linac {
	SteppingAction::SteppingAction() {
		// Get our phantom from the detectorconstruction
		auto runManager = G4RunManager::GetRunManager();
		auto detConstruction = static_cast<const DetectorConstruction*>(runManager->GetUserDetectorConstruction());

		fPhantom = detConstruction->GetPhantom();

	}

	SteppingAction::~SteppingAction() {
	}

	void SteppingAction::UserSteppingAction(const G4Step* step) {
		
		// get the step's current volume
		G4LogicalVolume* currentVolume = step->GetPreStepPoint()->GetPhysicalVolume()->GetLogicalVolume();
		if (currentVolume == fPhantom) {
			G4cout << "In phantom" << G4endl;
		}
	}
	
}