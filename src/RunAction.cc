
#include "RunAction.hh"
#include "G4ThreeVector.hh"
#include "G4UnitsTable.hh"

#include "PhantomHitsCollection.hh"
#include "G4SDManager.hh"
#include "G4RunManager.hh"
#include "G4VisExecutive.hh"


namespace med_linac {
	RunAction::RunAction() {
		// Create our PDD output file:
		auto analysisManager = G4AnalysisManager::Instance();
		G4String pddFileName = "PDD_Graph.root";
		analysisManager->SetFileName(pddFileName);

		// Create our PDD 1d histogram
		fPddH1ID = analysisManager->CreateH1(
			"PDD Graph",
			"PDD (Gy)",
			40, -450, 450, "Gy");


		// initialize our variables:
		fRunHitsCollection = new PhantomHitsCollection("Phantom", "PhantomHitsCollection");
		fTotalRunEnergy = 0.;

	}

	RunAction::~RunAction() {
		delete fRunHitsCollection;
	}

	void RunAction::BeginOfRunAction(const G4Run* aRun) {
		// start time
		fTimer.Start();

		auto analysisManager = G4AnalysisManager::Instance();
		analysisManager->OpenFile();

		// reset our variables
		for (G4int i = 0; i < fRunHitsCollection->GetSize(); i++) {
			delete (*fRunHitsCollection)[i];
		}
		fTotalRunEnergy = 0.;
		G4cout << "Hits reset" << G4endl;

	}

	void RunAction::EndOfRunAction(const G4Run* aRun) {

		// end time
		fTimer.Stop();

		// print out the time it took
		if (IsMaster()) {
			PrintTime();
		}

		GeneratePDDGraph();


		// write to our analysis file
		auto analysisManager = G4AnalysisManager::Instance();
		analysisManager->Write();
		analysisManager->CloseFile();
	}

	void RunAction::PrintTime() {
		auto time = fTimer.GetRealElapsed();

		G4cout
			<< "Elapsed time: "
			<< time
			<< " Seconds."
			<< G4endl;

	}

	void RunAction::AddToHitsCollection(PhantomHit* hit) {

		fTotalRunEnergy += hit->GetEnergy();
		fRunHitsCollection->insert(hit);
	}

	void RunAction::GeneratePDDGraph() {
		// We want a PDD graph, which is the dose of each hit divided by total dose
		
		if (IsMaster()) {
			G4cout << "Generating PDD graph..." << G4endl;
		}

		for (G4int i = 0; i < fRunHitsCollection->GetSize(); i++) {

			G4double hitEnergy = (*fRunHitsCollection)[i]->GetEnergy();
			G4double percentDose = hitEnergy / fTotalRunEnergy;

			G4double depth = (*fRunHitsCollection)[i]->GetPos().getZ();

			// add to the h1
			auto analysisManager = G4AnalysisManager::Instance();
			analysisManager->FillH1(fPddH1ID, depth, percentDose);

		}

		if (IsMaster()) {
			G4cout << "Finished Generating PDD Graph." << G4endl;
		}
	}

}
