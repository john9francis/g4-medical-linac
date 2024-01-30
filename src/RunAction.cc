
#include "RunAction.hh"
#include "G4ThreeVector.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"


namespace med_linac {
	RunAction::RunAction() {

		auto analysisManager = G4AnalysisManager::Instance();

		analysisManager->SetDefaultFileType("root");
		analysisManager->SetVerboseLevel(0);
		analysisManager->SetFileName("Output Graphs");

		// set up our h1s
		// PDD
		analysisManager->CreateH1("PDD", "PDD Graph", 100, -15 * cm, 15 * cm);
		analysisManager->SetH1XAxisTitle(0, "Depth");
		analysisManager->SetH1YAxisTitle(0, "Percent Dose");

		// Beam profile
		analysisManager->CreateH1("BeamProfile", "Lateral Beam Profile", 100, -15 * cm, 15 * cm);

		// set up our nTuples
		G4int pddNTupleID = analysisManager->CreateNtuple("PDD_data", "PDD NTuple Data");
		analysisManager->CreateNtupleDColumn(pddNTupleID, "Energy");
		analysisManager->CreateNtupleDColumn(pddNTupleID, "X");
		analysisManager->CreateNtupleDColumn(pddNTupleID, "Y");
		analysisManager->CreateNtupleDColumn(pddNTupleID, "Z");

		// deactivate h1s by default
		analysisManager->SetH1Activation(0, false);
		analysisManager->SetH1Activation(1, false);

		// set up our h2's

		analysisManager->CreateH2("HeatMapXY", "Energy Heat Map XY", 100,-15 * cm, 15 * cm, 100,-15 * cm, 15 * cm);
		analysisManager->CreateH2("HeatMapYZ", "Energy Heat Map YZ", 100,-15 * cm, 15 * cm, 100,-15 * cm, 15 * cm);
		analysisManager->CreateH2("HeatMapXZ", "Energy Heat Map XZ", 100,-15 * cm, 15 * cm, 100,-15 * cm, 15 * cm);

		analysisManager->SetActivation(true);

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