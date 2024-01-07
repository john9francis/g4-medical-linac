#ifndef med_linac_LINAC_HEAD_SINGLETON_HH
#define med_linac_LINAC_HEAD_SINGLETON_HH

#include "globals.hh"
#include "G4ThreeVector.hh"
#include "G4RotationMatrix.hh"
#include "G4PVPlacement.hh"


namespace med_linac {
	class LinacHeadSingleton {

	private:
		static LinacHeadSingleton* instance;
		LinacHeadSingleton();

		G4ThreeVector* gunPosition;
		G4ThreeVector* particleMomentumDirection;
		

	public:
		static LinacHeadSingleton* GetInstance();

		G4ThreeVector GetGunPosition() { return *gunPosition; }
		G4ThreeVector GetParticleMomentumDirection() { return *particleMomentumDirection; }
		void SetGunPosition(G4ThreeVector& pos) { *gunPosition = pos; }
		void SetParticleMomentumDirection(G4ThreeVector& dir) { *particleMomentumDirection = dir; }
		
	};
}

#endif // !med_linac_LINAC_HEAD_SINGLETON_HH
