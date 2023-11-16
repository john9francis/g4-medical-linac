#ifndef med_linac_PHANTOM_SD_HH
#define med_linac_PHANTOM_SD_HH


#include "G4SDManager.hh"

#include "PhantomHitsCollection.hh"

namespace med_linac {
	class PhantomSD : public G4VSensitiveDetector {
	public:
		PhantomSD(
			const G4String& name,
			const G4String& hitsCollectionName);
		~PhantomSD() override = default;

		void Initialize(G4HCofThisEvent*) override;
		G4bool ProcessHits(G4Step*, G4TouchableHistory*) override;
		void EndOfEvent(G4HCofThisEvent*) override;

	private:
		PhantomHitsCollection* fHitsCollection = nullptr;
	};
}


#endif // !med_linac_PHANTOM_SD_HH