#include "DetectorConstruction.hh"
#include "PhysicsList.hh"
#include "ActionInitialization.hh"

#include "G4RunManagerFactory.hh"
#include "G4UImanager.hh"
#include "G4UIExecutive.hh"
#include "G4VisManager.hh"
#include "G4VisExecutive.hh"

using namespace med_linac;

int main(int argc, char** argv)
{
	// initialize ui executive
	G4UIExecutive* ui = new G4UIExecutive(argc, argv);

	// construct the default run manager
	auto runManager = G4RunManagerFactory::CreateRunManager();

	// set mandatory initialization classes
	runManager->SetUserInitialization(new DetectorConstruction);
	runManager->SetUserInitialization(new PhysicsList);
	runManager->SetUserInitialization(new ActionInitialization);

	// get the vismanager
	G4VisManager* visManager = new G4VisExecutive;
	visManager->Initialize();

	// get the pointer to the UI manager and set verbosities
	G4UImanager* UImanager = G4UImanager::GetUIpointer();


	// start the "init-vis" macro
	UImanager->ApplyCommand("control/execute init_vis.mac");


	// use ui
	ui->SessionStart();
	delete ui;


	// job termination
	delete visManager;
	delete runManager;
	return 0;
}
