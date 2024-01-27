#include "PhantomSD.hh"

#include "G4UnitsTable.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "G4AnalysisManager.hh"
#include "GraphActivator.hh"

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
		auto graphActivator = GraphActivatorSingleton::GetInstance();
		G4int pddH1ID = 0;
		G4int beamProfileH1ID = 1;
		G4int heatMapXYH2ID = 0;
		G4int heatMapYZH2ID = 1;
		G4int heatMapXZH2ID = 2;

		// Loop through our hits collection and add everything to the histogram
		for (G4int i = 0; i < fOneEventHitsCollection->GetSize(); i++) {

			auto hit = (*fOneEventHitsCollection)[i];
			if (hit->GetEnergy() > 0) {

				G4ThreeVector hitPos = hit->GetPos();
				G4double graphX = hitPos.getX();
				G4double graphZ = hitPos.getY();
				G4double graphY = hitPos.getZ();
				G4double energy = hit->GetEnergy();

				// fill whatever graphs we have set to true
				//if (analysisManager->GetH1Activation(pddH1ID)) {
				analysisManager->FillH1(pddH1ID, graphZ, energy);
				//}
				//if (analysisManager->GetH1Activation(beamProfileH1ID)) {
				analysisManager->FillH1(beamProfileH1ID, graphX, energy);
				//}

				analysisManager->FillH2(heatMapXYH2ID, graphX, graphY, energy);
				analysisManager->FillH2(heatMapYZH2ID, graphY, graphZ, energy);
				analysisManager->FillH2(heatMapXZH2ID, graphX, graphZ, energy);
			}
		}

		// draw all hits using the HitsCollection method
		//fOneEventHitsCollection->DrawAllHits();


	}

}