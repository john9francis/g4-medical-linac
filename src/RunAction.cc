
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

		// Create our PDD 3d histogram
		G4int pddH3ID = analysisManager->CreateH3(
			"3D Energy Deposition Graph",
			"Energy deposited (Gy) vs. position in phantom",
			40, -450, 450,
			40, -450, 450,
			40, -450, 450,
			"mm", "mm", "mm"
		);

	}

	RunAction::~RunAction() {
	}

	void RunAction::BeginOfRunAction(const G4Run* aRun) {
		// start time
		fTimer.Start();

		auto analysisManager = G4AnalysisManager::Instance();
		analysisManager->OpenFile();

	}

	void RunAction::EndOfRunAction(const G4Run* aRun) {

		// end time
		fTimer.Stop();

		// print out the time it took
		if (IsMaster()) {
			PrintTime();
			DrawHits();
		}

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

	void RunAction::DrawHits() {
		G4cout << "Drawing hits" << G4endl;

		// first, find the hc
		G4SDManager* fSDM = G4SDManager::GetSDMpointer();
		G4cout << "Found SDM" << G4endl;
		G4RunManager* fRM = G4RunManager::GetRunManager();
		G4cout << "Found RM" << G4endl;
		G4int collectionID = fSDM->GetCollectionID("phantomHC");
		G4cout << "Found colID" << G4endl;
		const G4Event* currentEvent = fRM->GetCurrentEvent();
		G4cout << "Found currentEvent" << G4endl;
		G4HCofThisEvent* HCofEvent = currentEvent->GetHCofThisEvent();
		G4cout << "Found HCofEvent" << G4endl;
		PhantomHitsCollection* phantomHC = dynamic_cast<PhantomHitsCollection*>(HCofEvent->GetHC(collectionID));
		G4cout << "Found phantomHC" << G4endl;

		// get an instance of visManager and draw all hits
		G4VisManager* visManager = G4VisManager::GetInstance();

		for (G4int i = 0; i < phantomHC->GetSize(); i++) {
			PhantomHit* hit = (*phantomHC)[i];
			PhantomHit stackHit = *hit;

			G4ThreeVector position = stackHit.GetPos();

			G4VisAttributes attribs;
			attribs.SetColor(G4Color(1., 0., 0.)); // red

			visManager->Draw(stackHit);
		}
	
	}
}