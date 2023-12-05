#include "LinacHeadSingleton.hh"

namespace med_linac {
	LinacHeadSingleton* LinacHeadSingleton::instance = nullptr;

	LinacHeadSingleton::LinacHeadSingleton() {
		_gunAnchorPosition = new G4ThreeVector();
		_gunAnchorRotation = new G4RotationMatrix();
		_linacHeadPosition = new G4ThreeVector();
		_linacHeadRotation = new G4RotationMatrix();
	}

	LinacHeadSingleton* LinacHeadSingleton::GetInstance() {
		if (!instance) {
			instance = new LinacHeadSingleton();
		}

		return instance;
	}

	void LinacHeadSingleton::PrintHelloWorld() {
		G4cout << "Hello Linac Head Singleton World!" << G4endl;
	}

	void LinacHeadSingleton::DeleteSingleton() {
		if (instance) {
			delete instance;
		}
	}

	// constructors to convert stack variables to heap ones

	void LinacHeadSingleton::SetGunAnchorPosition(G4ThreeVector stackPos) {
		G4double x = stackPos.getX();
		G4double y = stackPos.getY();
		G4double z = stackPos.getZ();

		_gunAnchorPosition = new G4ThreeVector(x, y, z);
	}

	void LinacHeadSingleton::SetGunAnchorRotation(G4RotationMatrix stackRot) {
		G4double phi = stackRot.getPhi();
		G4double theta = stackRot.getTheta();
		G4double psi = stackRot.getPsi();

		_gunAnchorRotation = new G4RotationMatrix(phi, theta, psi);
	}

	void LinacHeadSingleton::SetLinacHeadPosition(G4ThreeVector stackPos) {
		G4double x = stackPos.getX();
		G4double y = stackPos.getY();
		G4double z = stackPos.getZ();

		_linacHeadPosition = new G4ThreeVector(x, y, z);

	}

	void LinacHeadSingleton::SetLinacHeadRotation(G4RotationMatrix stackRot) {
		G4double phi = stackRot.getPhi();
		G4double theta = stackRot.getTheta();
		G4double psi = stackRot.getPsi();

		_linacHeadRotation = new G4RotationMatrix(phi, theta, psi);
	}
}