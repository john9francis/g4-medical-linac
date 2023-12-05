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

		G4ThreeVector* _gunAnchorPosition;
		G4RotationMatrix* _gunAnchorRotation;
		G4ThreeVector* _linacHeadPosition;
		G4RotationMatrix* _linacHeadRotation;

		G4VPhysicalVolume* _physLinacHead;
		G4VPhysicalVolume* _physGunAnchor;
		

	public:
		static LinacHeadSingleton* GetInstance();
		void PrintHelloWorld();
		void DeleteSingleton();

		// getters and setters
		void SetGunAnchorPosition(G4ThreeVector* newPos) { _gunAnchorPosition = newPos; }
		void SetGunAnchorRotation(G4RotationMatrix* newRot) { _gunAnchorRotation = newRot; }
		G4ThreeVector* GetGunAnchorPosition() { return _gunAnchorPosition; }
		G4RotationMatrix* GetGunAnchorRotation() { return _gunAnchorRotation; }

		void SetLinacHeadPosition(G4ThreeVector* newPos) { _linacHeadPosition = newPos; }
		void SetLinacHeadRotation(G4RotationMatrix* newRot) { _linacHeadRotation = newRot; }
		G4ThreeVector* GetLinacHeadPosition() { return _linacHeadPosition; }
		G4RotationMatrix* GetLinacHeadRotation() { return _linacHeadRotation; }

		
		// constructors to change stack variables to heap ones
		void SetLinacHeadPosition(G4ThreeVector stackPos);
		void SetLinacHeadRotation(G4RotationMatrix stackRot);
		void SetGunAnchorPosition(G4ThreeVector stackPos);
		void SetGunAnchorRotation(G4RotationMatrix stackRot);


		// getters and setters for the physical volumes

		void SetPhysLinacHead(G4VPhysicalVolume* physLinacHead) { _physLinacHead = physLinacHead; }
		void SetPhysGunAnchor(G4VPhysicalVolume* physGunAnchor) { _physGunAnchor = physGunAnchor; }

		G4VPhysicalVolume* GetPhysLinacHead() { return _physLinacHead; }
		G4VPhysicalVolume* GetPhysGunAnchor() { return _physGunAnchor; }
		
	};
}

#endif // !med_linac_LINAC_HEAD_SINGLETON_HH
