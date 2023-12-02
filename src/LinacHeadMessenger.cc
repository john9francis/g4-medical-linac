
#include "LinacHeadMessenger.hh"
#include "G4UImanager.hh"

namespace med_linac {
	LinacHeadMessenger::LinacHeadMessenger() {

		fLinacHeadDir = new G4UIdirectory("/linacHead/");

		fTestCommand = new G4UIcmdWithoutParameter("/linacHead/test", this);
		fLinacHeadAngle = new G4UIcmdWithAnInteger("/linacHead/setAngle", this);
		fLinacHeadY = new G4UIcmdWithADouble("/linacHead/setY", this);
	}

	LinacHeadMessenger::~LinacHeadMessenger() {
		delete fLinacHeadDir;

		delete fTestCommand;
		delete fLinacHeadAngle;
	}

	void LinacHeadMessenger::SetNewValue(G4UIcommand* command, G4String newValues){
		if (command == fTestCommand) {
			G4cout << "Test Command Set" << G4endl;
		}
		else if (command == fLinacHeadY) {
			ChangeLinacHeadY(fLinacHeadY->GetNewDoubleValue(newValues));
		}
		else if (command == fLinacHeadAngle) {
			G4cout << "Setting linac head angle to " << newValues << G4endl;
		}
	}

	G4String LinacHeadMessenger::GetCurrentValue(G4UIcommand* command) {

		return "Hello World";
	}

	void LinacHeadMessenger::SetLinacHeadPointer(G4VPhysicalVolume* physLinacHead) {
		fPhysLinacHead = physLinacHead;
	}

	void LinacHeadMessenger::ChangeLinacHeadY(G4double newY) {

		G4cout << "Setting linac head y to " << newY << G4endl;

		if (fPhysLinacHead == nullptr) {
			G4cout << "Error: Linac head not defined correctly" << G4endl;
			return;
		}

		/*
		For reference:

		G4VPhysicalVolume* physHead = new G4PVPlacement(
			linacHeadRotation,
			linacHeadPos,
			logicHead,
			"physHead",
			logicWorld,
			false,
			0);
		*/
		/*
		// Step 1: get all the necessary parameters
		auto linacHeadRotation = fPhysLinacHead->GetObjectRotationValue();
		auto linacHeadPos = fPhysLinacHead->GetObjectTranslation();
		auto logicHead = fPhysLinacHead->GetLogicalVolume();
		auto name = fPhysLinacHead->GetName();
		auto logicMother = fPhysLinacHead->GetMotherLogical();

		G4cout << "Old linac head position: " << linacHeadPos << G4endl;


		// switch the rotation matrix to the heap
		auto phi = linacHeadRotation.getPhi();
		auto theta = linacHeadRotation.getTheta();
		auto psi = linacHeadRotation.getPsi();
		G4RotationMatrix* heapRot = new G4RotationMatrix(phi, theta, psi);
		
		// Step 2: Delete the old linac head
		delete fPhysLinacHead;

		// Step 3: Create a new linac head in the new position
		G4ThreeVector newPosition = G4ThreeVector(linacHeadPos.getX(), newY, linacHeadPos.getZ());

		fPhysLinacHead = new G4PVPlacement(
			heapRot,
			newPosition,
			logicHead,
			name,
			logicMother,
			false,
			0);

		G4cout << "New linac head position: " << fPhysLinacHead->GetObjectTranslation() << G4endl;

		// Update the viewport
		G4UImanager* UI = G4UImanager::GetUIpointer();
		UI->ApplyCommand("/vis/viewer/rebuild");
		*/

		
		// get all the parameters that don't change
		G4ThreeVector currentPos = fPhysLinacHead->GetObjectTranslation();
		G4double x = currentPos.getX();
		G4double z = currentPos.getZ();

		G4cout << "Old linac head position: " << currentPos << G4endl;

		fPhysLinacHead->SetTranslation(G4ThreeVector(x, newY, z));

		G4cout << "New linac head position: " << fPhysLinacHead->GetObjectTranslation() << G4endl;

		// Update the viewport
		G4UImanager* UI = G4UImanager::GetUIpointer();
		UI->ApplyCommand("/vis/viewer/rebuild");

		
	}


}