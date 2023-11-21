#ifndef med_linac_RUN_ACTION_HH
#define med_linac_RUN_ACTION_HH

#include "G4UserRunAction.hh"

#include "PhantomHitsCollection.hh"

#include "G4AnalysisManager.hh"

// timing the run
#include "G4Timer.hh"



namespace med_linac {

	class HitsCollection;

	class RunAction : public G4UserRunAction {
	public:
		RunAction();
		~RunAction();

		void BeginOfRunAction(const G4Run* aRun) override;
		void EndOfRunAction(const G4Run* aRun) override;

		void AddToHitsCollection(PhantomHit*);
		void AddHitsToAnalysis();

	private:

		G4Timer fTimer;
		PhantomHitsCollection* fRunHitsCollection;
		G4double fTotalRunEnergy;
		G4int fPddH1ID;

		void PrintTime();

	};


}

#endif // !med_linac_RUN_ACTION_HH
