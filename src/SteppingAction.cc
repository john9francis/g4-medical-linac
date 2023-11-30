
#include "SteppingAction.hh"
#include "DetectorConstruction.hh"

#include "G4Step.hh"
#include "G4RunManager.hh"

#include "G4AnalysisManager.hh"

#include "G4UnitsTable.hh"

#include "DetectorConstruction.hh"
#include "PhantomHitsCollection.hh"

namespace med_linac {
	SteppingAction::SteppingAction(RunAction* runAction) {

		fRunAction = runAction;

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

		if (currentVolume != fPhantom) return;

		// Create a hit and send it over to the runAction
		G4double particleEnergy = step->GetTotalEnergyDeposit();
		G4ThreeVector particlePos = step->GetPreStepPoint()->GetPosition();

		PhantomHit* hit = new PhantomHit();
		hit->SetEnergy(particleEnergy);
		hit->SetPos(particlePos);

		fRunAction->AddToHitsCollection(hit);


		// add hits to the heat map
		auto analysisManager = G4AnalysisManager::Instance();

		G4int xzH2Id = 0;
		G4int xyH2Id = 1;

		analysisManager->FillH2(xzH2Id, particlePos.getX(), particlePos.getZ(), particleEnergy);
		analysisManager->FillH2(xyH2Id, particlePos.getX(), particlePos.getY(), particleEnergy);
	}
	
}