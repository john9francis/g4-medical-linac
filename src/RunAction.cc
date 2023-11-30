
#include "RunAction.hh"
#include "DetectorConstruction.hh"

#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"

#include "G4ThreeVector.hh"
#include "G4UnitsTable.hh"

#include "PhantomHitsCollection.hh"
#include "G4SDManager.hh"
#include "G4RunManager.hh"
#include "G4VisExecutive.hh"

#include <iostream>


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
			300, 0, 300, "mm");

		// Create a H2 heat map
		G4int yzHeatMapID = analysisManager->CreateH2(
			"YZ Heat map",
			"Energy Deposited",
			50, -150, 150, 50, -150, 150);

		G4int xyHeatMapID = analysisManager->CreateH2(
			"XY Heat map",
			"Energy Deposited",
			50, -150, 150, 50, -150, 150);


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

	}

	void RunAction::EndOfRunAction(const G4Run* aRun) {

		// end time
		fTimer.Stop();

		// print out the time it took
		if (IsMaster()) {
			PrintTime();

			G4cout << "Generating PDD Graph..." << G4endl;
		}

		GeneratePDDGraph();

		if (IsMaster()) {
			G4cout << "Finished Generating PDD Graph" << G4endl;
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

	void RunAction::AddToHitsCollection(PhantomHit* hit) {

		fTotalRunEnergy += hit->GetEnergy();
		fRunHitsCollection->insert(hit);
	}

	void RunAction::GeneratePDDGraph() {
		// We want a PDD graph, which is the dose of each hit divided by total dose

		// First, let's get the left hand side position of the phantom and set it to 0
		// Then measure the dose in CM in relation to that.
		auto runManager = G4RunManager::GetRunManager();
		auto detConstruction = static_cast<const DetectorConstruction*>(runManager->GetUserDetectorConstruction());
		G4VPhysicalVolume* physPhantom = detConstruction->GetPhysPhantom();
		G4LogicalVolume* logPhantom = detConstruction->GetPhantom();

		// finessing to find the position of the left side of the phantom
		G4ThreeVector phantomPosition = physPhantom->GetObjectTranslation();
		G4double phantomCubicVolume = logPhantom->GetSolid()->GetCubicVolume();
		G4double phantomSideLength = std::pow(phantomCubicVolume, 1. / 3.);
		G4double startingPos = phantomPosition.getZ() - phantomSideLength / 2;


		for (G4int i = 0; i < fRunHitsCollection->GetSize(); i++) {

			G4double hitEnergy = (*fRunHitsCollection)[i]->GetEnergy();
			//G4double percentDose = hitEnergy / fTotalRunEnergy;
			G4double percentDose = hitEnergy;

			G4double depth = (*fRunHitsCollection)[i]->GetPos().getZ() - startingPos;

			// add to the h1
			auto analysisManager = G4AnalysisManager::Instance();
			analysisManager->FillH1(fPddH1ID, depth, percentDose);

		}

	}

}
