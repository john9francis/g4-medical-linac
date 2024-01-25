
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

		analysisManager->CreateH1("PDD", "PDD Graph", 100, -15 * cm, 15 * cm);
		analysisManager->SetH1XAxisTitle(0, "Depth");
		analysisManager->SetH1YAxisTitle(0, "Percent Dose");

		// deactivate by default
		analysisManager->SetH1Activation(0, false);

		analysisManager->CreateH1("BeamProfile", "Lateral Beam Profile", 100, -15 * cm, 15 * cm);

		// deactivate by default
		analysisManager->SetH1Activation(1, false);

		analysisManager->CreateH2("HeatMapXY", "Energy Heat Map XY", 100,-15 * cm, 15 * cm, 100,-15 * cm, 15 * cm);
		analysisManager->CreateH2("HeatMapYZ", "Energy Heat Map YZ", 100,-15 * cm, 15 * cm, 100,-15 * cm, 15 * cm);
		analysisManager->CreateH2("HeatMapXZ", "Energy Heat Map XZ", 100,-15 * cm, 15 * cm, 100,-15 * cm, 15 * cm);


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