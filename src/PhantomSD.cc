#include "PhantomSD.hh"

#include "G4UnitsTable.hh"

namespace med_linac {
	PhantomSD::PhantomSD(
		const G4String& name,
		const G4String& hitsCollectionName)
		: G4VSensitiveDetector(name) {

		collectionName.insert(hitsCollectionName);
	}


	void PhantomSD::Initialize(G4HCofThisEvent* hce) {

		// create hits collection
		fHitsCollection = new PhantomHitsCollection(SensitiveDetectorName, collectionName[0]);
	
		// get hitsCollection id from the SDManager
		G4int hcID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);

		// add hitsCollection to the hc of this event
		hce->AddHitsCollection(hcID, fHitsCollection);

		// set enery for this event back to 0
		fEnergy = 0;

	
	}

	G4bool PhantomSD::ProcessHits(G4Step* aStep, G4TouchableHistory*) {
		fEnergy += aStep->GetTotalEnergyDeposit();

		return true;
	}

	void PhantomSD::EndOfEvent(G4HCofThisEvent*) {
		if (fEnergy > 0.) {
			// create a new hit and add it to our hitsCollection
			PhantomHit* hit = new PhantomHit();
			hit->SetEnergy(fEnergy);

			fHitsCollection->insert(hit);
		}

		// print out all the hits
		for (G4int i = 0; i < fHitsCollection->entries(); i++) {
			(*fHitsCollection)[i]->Print();
		}
	}
}