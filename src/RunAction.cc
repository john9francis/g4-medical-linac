
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
		G4int pddH1ID = analysisManager->CreateH1(
			"PDD Graph",
			"PDD (Gy)",
			40, -450, 450, "Gy");

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

}
