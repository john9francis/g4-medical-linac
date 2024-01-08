#ifndef med_linac_LINAC_HEAD_MESSENGER_HH
#define med_linac_LINAC_HEAD_MESSENGER_HH

#include "G4UImessenger.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWith3VectorAndUnit.hh"

#include "DetectorConstruction.hh"

namespace med_linac {
	class LinacHeadMessenger : public G4UImessenger {
	public:
		LinacHeadMessenger(DetectorConstruction* detectorConstruction);
		//~LinacHeadMessenger();

		void SetNewValue(G4UIcommand* command, G4String newValues);
		//G4String GetCurrentValue(G4UIcommand* command);

	
	private:
		DetectorConstruction* fDetectorConstruction;

		G4UIdirectory* fDirectory;

		G4UIcmdWith3VectorAndUnit* fAngleCmd;
		G4UIcmdWith3VectorAndUnit* fPositionCmd;

		G4UIcmdWithADoubleAndUnit* fShiftZCmd;
	};


}

#endif // !med_linac_LINAC_HEAD_MESSENGER_HH
