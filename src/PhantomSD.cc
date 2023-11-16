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
	
	}

	G4bool PhantomSD::ProcessHits(G4Step* aStep, G4TouchableHistory*) {
		G4cout << "Hit" << G4endl;

		return true;
	}

	void PhantomSD::EndOfEvent(G4HCofThisEvent*) {

	}
}