#include "PhantomSD.hh"

#include "G4UnitsTable.hh"

#include "G4AnalysisManager.hh"

namespace med_linac {
	PhantomSD::PhantomSD(
		const G4String& name,
		const G4String& hitsCollectionName)
		: G4VSensitiveDetector(name) {

		collectionName.insert(hitsCollectionName);

	}


	void PhantomSD::Initialize(G4HCofThisEvent* hce) {

		// create hits collection
		fOneEventHitsCollection = new PhantomHitsCollection(SensitiveDetectorName, collectionName[0]);
	
		// get hitsCollection id from the SDManager
		G4int hcID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);

		// add hitsCollection to the hc of this event
		hce->AddHitsCollection(hcID, fOneEventHitsCollection);
	
	}

	G4bool PhantomSD::ProcessHits(G4Step* aStep, G4TouchableHistory*) {

		// If there's a hit, create a hit object saying it's energy and position
		PhantomHit* hit = new PhantomHit();
		hit->SetEnergy(aStep->GetTotalEnergyDeposit());
		hit->SetPos(aStep->GetPreStepPoint()->GetPosition());

		// add it to the hitsCollection
		fOneEventHitsCollection->insert(hit);

		return true;
	}

	void PhantomSD::EndOfEvent(G4HCofThisEvent*) {

		auto analysisManager = G4AnalysisManager::Instance();
		G4int pddH3ID = 0;

		// Loop through our hits collection and add everything to the histogram
		for (G4int i = 0; i < fOneEventHitsCollection->GetSize(); i++) {

			auto hit = (*fOneEventHitsCollection)[i];
			if (hit->GetEnergy() > 0) {

				G4ThreeVector hitPos = hit->GetPos();

				analysisManager->FillH3(pddH3ID, hitPos.getX(), hitPos.getY(), hitPos.getZ(), hit->GetEnergy());
				G4cout << hitPos << G4endl;
			}
		}


	}
}