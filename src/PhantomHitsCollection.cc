
#include "PhantomHitsCollection.hh"
#include "G4VisExecutive.hh"
#include "G4Circle.hh"

namespace med_linac {
	PhantomHit::PhantomHit() {
		
		// Set the energy and position to zero
		hEnergy = 0.;
		hPosition = G4ThreeVector();
	}

	void PhantomHit::Print() {
		G4cout
			<< "Energy: "
			<< G4BestUnit(hEnergy, "Dose")
			<< " "
			<< "Position: "
			<< G4BestUnit(hPosition.getX(), "Length")
			<< G4BestUnit(hPosition.getY(), "Length")
			<< G4BestUnit(hPosition.getZ(), "Length")
			<< G4endl;
	}

	void PhantomHit::Draw() {
		G4cout << "Drawing Hit" << G4endl;

		auto visManager = G4VisManager::GetInstance();
		if (visManager == nullptr) {
			G4cout << "VisManager not found" << G4endl;
		}

		G4Circle energyHit;
		G4VMarker::SizeType markerSize = G4VMarker::world;
		energyHit.SetRadius(markerSize, 2 * cm);
		energyHit.SetPosition(hPosition);
		energyHit.SetFillStyle(G4VMarker::filled);

		visManager->BeginDraw(G4Transform3D());
		visManager->Draw(energyHit);
		visManager->EndDraw();

	}

	// Methods to set the energy and position
	void PhantomHit::SetEnergy(G4double e) { hEnergy = e; }
	void PhantomHit::AddEnergy(G4double e) { hEnergy += e; }
	void PhantomHit::SetPos(G4ThreeVector p) { hPosition = p; }
	G4double PhantomHit::GetEnergy() { return hEnergy; }
	G4ThreeVector PhantomHit::GetPos() { return hPosition; }


	// Very simple HitsCollection, just a list to hold all our hits
	PhantomHitsCollection::PhantomHitsCollection(
		const G4String& name,
		const G4String& collectionName)
		: G4THitsCollection<PhantomHit>(name, collectionName) {}


}