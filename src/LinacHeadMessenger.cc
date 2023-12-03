
#include "LinacHeadMessenger.hh"
#include "G4UImanager.hh"

#include "G4UnitsTable.hh"

namespace med_linac {
	LinacHeadMessenger::LinacHeadMessenger() {

		fLinacHeadDir = new G4UIdirectory("/linacHead/");

		fTestCommand = new G4UIcmdWithoutParameter("/linacHead/test", this);
		fLinacHeadAngle = new G4UIcmdWithADouble("/linacHead/setAngle", this);
		fLinacHeadY = new G4UIcmdWithADouble("/linacHead/setY", this);
	}

	LinacHeadMessenger::~LinacHeadMessenger() {
		delete fLinacHeadDir;

		delete fTestCommand;
		delete fLinacHeadAngle;
		delete fLinacHeadY;
	}

	void LinacHeadMessenger::SetNewValue(G4UIcommand* command, G4String newValues){
		if (command == fTestCommand) {
			G4cout << "Test Command Set" << G4endl;
		}
		else if (command == fLinacHeadY) {
			ChangeLinacHeadY(fLinacHeadY->GetNewDoubleValue(newValues));
		}
		else if (command == fLinacHeadAngle) {
			ChangeLinacHeadAngle(fLinacHeadAngle->GetNewDoubleValue(newValues));
		}
	}

	G4String LinacHeadMessenger::GetCurrentValue(G4UIcommand* command) {

		return "Hello World";
	}

	void LinacHeadMessenger::SetLinacHeadPointer(G4VPhysicalVolume* physLinacHead) {
		fPhysLinacHead = physLinacHead;
	}



	void LinacHeadMessenger::ChangeLinacHeadAngle(G4double newTheta) {
		G4cout << "Setting linac head y to " << newTheta << G4endl;

		if (fPhysLinacHead == nullptr) {
			G4cout << "Error: Linac head not defined correctly" << G4endl;
			return;
		}

		// step 1: change newTheta to degrees:


		/*
		For reference:

		Constructor 1: 

		G4VPhysicalVolume* physHead = new G4PVPlacement(
			linacHeadRotation,
			linacHeadPos,
			logicHead,
			"physHead",
			logicWorld,
			false,
			0);

		Constructor 2: 

		G4PVPlacement(const G4Transform3D& Transform3D,
						G4LogicalVolume* pCurrentLogical,
				  const G4String& pName,
						G4LogicalVolume* pMotherLogical,
						G4bool pMany,
						G4int pCopyNo,
						G4bool pSurfChk = false);

		*/
		
		// Step 1: get all the necessary parameters
		auto linacHeadRotation = fPhysLinacHead->GetObjectRotationValue();
		auto linacHeadPos = fPhysLinacHead->GetObjectTranslation();
		auto logicHead = fPhysLinacHead->GetLogicalVolume();
		auto name = fPhysLinacHead->GetName();
		auto logicMother = fPhysLinacHead->GetMotherLogical();

		G4cout << "Old linac head theta: " << linacHeadRotation.getTheta() << G4endl;

		// Get the new rotation matrix
		auto theta = linacHeadRotation.getTheta();
		auto phi = linacHeadRotation.getPhi();
		auto psi = linacHeadRotation.getPsi();
		G4RotationMatrix* newRot = new G4RotationMatrix();
		newRot->rotateX(newTheta);
		newRot->rotateY(phi);
		newRot->rotateZ(psi);

		// set the new x and y to correspond
		G4double radius = linacHeadPos.mag();
		G4double newX = linacHeadPos.getX();
		G4double newY = radius * sin(newTheta);
		G4double newZ = radius * cos(newTheta);
		G4ThreeVector newPos = G4ThreeVector(newX, newY, newZ);

		// Step 2: Delete the old linac head
		delete fPhysLinacHead;

		// Step 3: Create a new linac head with the new rotation
		fPhysLinacHead = new G4PVPlacement(
			newRot,
			newPos,
			logicHead,
			name,
			logicMother,
			false,
			0);



		G4cout << "New linac head theta: " << newTheta << G4endl;

		// Update the viewport
		G4UImanager* UI = G4UImanager::GetUIpointer();
		UI->ApplyCommand("/vis/viewer/rebuild");
		

	}




	void LinacHeadMessenger::ChangeLinacHeadY(G4double newY) {

		G4cout << "Setting linac head y to " << newY << G4endl;

		if (fPhysLinacHead == nullptr) {
			G4cout << "Error: Linac head not defined correctly" << G4endl;
			return;
		}

		
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