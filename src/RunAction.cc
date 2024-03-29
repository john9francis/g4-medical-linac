
#include "RunAction.hh"
#include "G4ThreeVector.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"


namespace med_linac {
	RunAction::RunAction() {

		//////////////////////////////////////////////////////////////
		//              SETUP OUR OUTPUT GRAPHS                     //
		//////////////////////////////////////////////////////////////

		auto analysisManager = G4AnalysisManager::Instance();

		// Default settings
		analysisManager->SetDefaultFileType("root");
		analysisManager->SetVerboseLevel(0);
		analysisManager->SetFileName("Output_Graphs");

		// set up our h1s
		// 
		// PDD
		analysisManager->CreateH1("PDD", "PDD Graph", 100, 0 * cm, 30 * cm);
		analysisManager->SetH1XAxisTitle(0, "Depth (mm)");
		analysisManager->SetH1YAxisTitle(0, "Dose (MeV)");

		// Beam profile
		analysisManager->CreateH1("BeamProfile", "Lateral Beam Profile", 100, -15 * cm, 15 * cm);
		analysisManager->SetH1XAxisTitle(1, "Off axis distance (mm)");
		analysisManager->SetH1YAxisTitle(1, "Dose (MeV)");

		// Bremsstrahlung spectrum
		analysisManager->CreateH1("photonESpectrum", "Energy Spectrum (Photons)", 200, 0, 6 * MeV);
		analysisManager->SetH1XAxisTitle(2, "Energy (MeV)");
		analysisManager->SetH1YAxisTitle(2, "Number of particles");
		analysisManager->CreateH1("electronESpectrum", "Energy Spectrum (Electrons)", 200, 0, 6 * MeV);
		analysisManager->SetH1XAxisTitle(3, "Energy (MeV)");
		analysisManager->SetH1YAxisTitle(3, "Number of particles");
		analysisManager->CreateH1("positronESpectrum", "Energy Spectrum (Positrons)", 200, 0, 6 * MeV);
		analysisManager->SetH1XAxisTitle(4, "Energy (MeV)");
		analysisManager->SetH1YAxisTitle(4, "Number of particles");
		analysisManager->CreateH1("otherESpectrum", "Energy Spectrum (Other)", 200, 0, 6 * MeV);
		analysisManager->SetH1XAxisTitle(5, "Energy (MeV)");
		analysisManager->SetH1YAxisTitle(5, "Number of particles");

		// Only photon PDD
		analysisManager->CreateH1("photonPDD", "PDD Graph (Only Photons)", 100, 0 * cm, 30 * cm);
		analysisManager->SetH1XAxisTitle(0, "Depth (mm)");
		analysisManager->SetH1YAxisTitle(0, "Dose (MeV)");



		// deactivate h1s by default
		analysisManager->SetH1Activation(0, false);
		analysisManager->SetH1Activation(1, false);

		// set up our h2's
		//
		// Heat maps
		analysisManager->CreateH2("HeatMapXY", "Energy Heat Map XY", 100,-15 * cm, 15 * cm, 100,-15 * cm, 15 * cm);
		analysisManager->CreateH2("HeatMapYZ", "Energy Heat Map YZ", 100,-15 * cm, 15 * cm, 100,-15 * cm, 15 * cm);
		analysisManager->CreateH2("HeatMapXZ", "Energy Heat Map XZ", 100,-15 * cm, 15 * cm, 100,-15 * cm, 15 * cm);

		// set activation so our activation settings work.
		analysisManager->SetActivation(true);

	}

	RunAction::~RunAction() {}


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