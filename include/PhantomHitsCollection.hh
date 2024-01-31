// includes Hit and HitsCollection objects



#ifndef med_linac_PHANTOM_HIT_HH
#define med_linac_PHANTOM_HIT_HH

#include "G4VHit.hh"
#include "G4ThreeVector.hh"

#include "G4ios.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

namespace med_linac {
	class PhantomHit : public G4VHit {
	public:
		PhantomHit();
		~PhantomHit() override = default;

		void Print() override;
		void Draw() override;

		void SetEnergy(G4double e);
		void AddEnergy(G4double e);
		void SetPos(G4ThreeVector p);
		G4double GetEnergy();
		G4ThreeVector GetPos();

	private:
		G4double hEnergy;
		G4ThreeVector hPosition;
	};
}

#endif // !med_linac_PHANTOM_HIT_HH

#ifndef med_linac_PHANTOM_HITS_COLLECTION_HH
#define med_linac_PHANTOM_HITS_COLLECTION_HH

#include "G4THitsCollection.hh"

namespace med_linac {
	class PhantomHitsCollection : public G4THitsCollection<PhantomHit> {
	public:
		PhantomHitsCollection(
			const G4String& name, 
			const G4String& collectionName);

		G4double GetMaxEnergy() { return *fMaxEnergy; }
		void SetMaxEnergy(G4double possibleMaxEnergy) {
			if (possibleMaxEnergy > *fMaxEnergy) {
				*fMaxEnergy = possibleMaxEnergy;
			}
		}

	private:
		G4double* fMaxEnergy;

	};

}
#endif // !med_linac_PHANTOM_HITS_COLLECTION
