
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

		G4VVisManager* pVVisManager = G4VVisManager::GetConcreteInstance();
		if (pVVisManager)
		{
			// define a circle in a 3D space
			G4Circle circle(hPosition);
			circle.SetScreenSize(1.);
			circle.SetFillStyle(G4Circle::filled);
			circle.SetRadius(G4VMarker::SizeType::world, 20.);

			// Define circle color
			G4Colour colour(255 * (1 - hEnergy), 255 * hEnergy , 0);
			G4VisAttributes attribs(colour);
			circle.SetVisAttributes(attribs);

			// make a 3D data for visualization
			pVVisManager->Draw(circle);
		}

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