
#include "RunAction.hh"
#include "G4ThreeVector.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"


namespace med_linac {
	RunAction::RunAction() {
		// set up our histograms
		
		auto analysisManager = G4AnalysisManager::Instance();

		analysisManager->SetDefaultFileType("root");
		analysisManager->SetVerboseLevel(0);
		analysisManager->SetFileName("PDD");

		analysisManager->CreateH1("PDD", "PDD Graph", 100, 0, 15 * cm);


	}

	RunAction::~RunAction() {
	}

	void RunAction::BeginOfRunAction(const G4Run* aRun) {
		// start time
		fTimer.Start();

	}

	void RunAction::EndOfRunAction(const G4Run* aRun) {

		// end time
		fTimer.Stop();

		// print out the time it took
		if (IsMaster()) {
			PrintTime();
		}
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