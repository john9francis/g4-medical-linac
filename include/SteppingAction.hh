#ifndef med_linac_STEPPING_ACTION_H
#define med_linac_STEPPING_ACTION_H 1

#include "G4UserSteppingAction.hh"
#include "G4LogicalVolume.hh"


namespace med_linac {

	// Stepping Action: What happens each single monte-carlo
	// step in a particle's trajectory. I basically used this class
	// to check which detector the particle was in, and record 
	// corresponding energies and positions. 
	class SteppingAction : public G4UserSteppingAction {
	public:
		SteppingAction() = default;
		~SteppingAction() = default;

		void UserSteppingAction(const G4Step*) override;

	private:
		// H1 id's
		G4int fPddH1ID = 0;
		G4int fDoseProfileH1ID = 1;
		G4int fBremsstrahlungH1ID = 2;
		G4int fPhotonPddH1ID = 3;

		// H2 ids's
		G4int fXYHeatMapH2ID = 0;
		G4int fYZHeatMapH2ID = 1;
		G4int fXZHeatMapH2ID = 2;
	};

}


#endif // !med_linac_STEPPING_ACTION_H
