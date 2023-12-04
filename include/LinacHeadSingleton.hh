#ifndef med_linac_LINAC_HEAD_SINGLETON_HH
#define med_linac_LINAC_HEAD_SINGLETON_HH

#include "globals.hh"
#include "G4ThreeVector.hh"
#include "G4RotationMatrix.hh"


namespace med_linac {
	class LinacHeadSingleton {

	private:
		static LinacHeadSingleton* instance;
		LinacHeadSingleton();

		G4ThreeVector _gunAnchorPosition;
		G4RotationMatrix _gunAnchorRotation;
		

	public:
		static LinacHeadSingleton* GetInstance();
		void PrintHelloWorld();
		void DeleteSingleton();

		// getters and setters
		void SetGunAnchorPosition(G4ThreeVector newPos) { _gunAnchorPosition = newPos; }
		void SetGunAnchorRotation(G4RotationMatrix newRot) { _gunAnchorRotation = newRot; }
		G4ThreeVector GetGunAnchorPosition() { return _gunAnchorPosition; }
		G4RotationMatrix GetGunAnchorRotation() { return _gunAnchorRotation; }
	};
}

#endif // !med_linac_LINAC_HEAD_SINGLETON_HH
