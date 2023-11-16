
#include "RunAction.hh"
#include "G4ThreeVector.hh"
#include "G4UnitsTable.hh"


namespace med_linac {
	RunAction::RunAction() {
		// Create our PDD output file:
		auto analysisManager = G4AnalysisManager::Instance();
		G4String pddFileName = "PDD_Graph.root";
		analysisManager->OpenFile(pddFileName);

		// Create our PDD 3d histogram
		G4int pddH3ID = analysisManager->CreateH3(
			"3D Energy Deposition Graph",
			"Energy deposited (Gy) vs. position in phantom (Cm)",
			100, 0, 45,
			100, 0, 45,
			100, 0, 45
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