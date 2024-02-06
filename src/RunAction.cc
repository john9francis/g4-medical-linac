
#include "RunAction.hh"
#include "G4ThreeVector.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"


namespace med_linac {
	RunAction::RunAction() {

		// init hits collection
		fpddCollection = new PhantomHitsCollection("PddHitsCollection", "PddHitsCollection");

		auto analysisManager = G4AnalysisManager::Instance();

		analysisManager->SetDefaultFileType("root");
		analysisManager->SetVerboseLevel(0);
		analysisManager->SetFileName("Output Graphs");

		// set up our h1s
		// PDD
		analysisManager->CreateH1("PDD", "PDD Graph", 100, 0 * cm, 30 * cm);
		analysisManager->SetH1XAxisTitle(0, "Depth");
		analysisManager->SetH1YAxisTitle(0, "Percent Dose");

		// Beam profile
		analysisManager->CreateH1("BeamProfile", "Lateral Beam Profile", 100, -15 * cm, 15 * cm);

		// Bremsstrahlung spectrum
		analysisManager->CreateH1("BremsSpectrum", "Bremsstrahlung Energy Spectrum", 200, 0, 6 * MeV);


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
		delete fpddCollection;
	}

	void RunAction::AddToPddHitsCollection(PhantomHit* aHit) {
		fpddCollection->insert(aHit);
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
		// fill pdd graph
		fpddCollection->FillPddGraph();
		
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