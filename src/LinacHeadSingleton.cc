#include "LinacHeadSingleton.hh"


namespace med_linac {
	LinacHeadSingleton* LinacHeadSingleton::instance = nullptr;

	LinacHeadSingleton::LinacHeadSingleton() {

		// allocate some memory for these variables
		gunPosition = new G4ThreeVector();
		particleMomentumDirection = new G4ThreeVector();
	}

	LinacHeadSingleton* LinacHeadSingleton::GetInstance() {
		if (!instance) {

			instance = new LinacHeadSingleton();
			G4cout << "Singleton Initialized" << G4endl;
		}

		return instance;
	}

}