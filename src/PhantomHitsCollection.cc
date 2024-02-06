
#include "PhantomHitsCollection.hh"
#include "G4VisExecutive.hh"
#include "G4Circle.hh"
#include "G4AnalysisManager.hh"

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

	G4double PhantomHitsCollection::GetMaxEnergy() {

		G4double maxEnergy = 0.0;

		// Loop through our hits collection and find max energy
		for (G4int i = 0; i < this->GetSize(); i++) {

			PhantomHit* hit = (*this)[i];
			G4double hitEnergy = hit->GetEnergy();
			if (hitEnergy > maxEnergy) {
				maxEnergy = hitEnergy;
			}
			
		}

		return maxEnergy;
	}


	void PhantomHitsCollection::FillPddGraph() {
		// for each hit, divide the energy by max energy
		// and add 15 to the position

		auto analysisManager = G4AnalysisManager::Instance();
		G4double maxEnergy = this->GetMaxEnergy();
		G4int pddH1ID = 0;

		// Loop through our hits collection and add to analysis
		for (G4int i = 0; i < this->GetSize(); i++) {
			PhantomHit* hit = (*this)[i];
			
			// first, get the energy
			G4double absoluteEnergy = hit->GetEnergy();

			// now get the position
			G4ThreeVector absolutePos = hit->GetPos();
			// and adjust it
			G4double depth = absolutePos.getZ() + 15 * cm;

			// plot this point
			analysisManager->FillH1(pddH1ID, depth, absoluteEnergy);

			// finally, normalize the h1
			// how??? idkkkk

		}

	}


}