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

	}
}