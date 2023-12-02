#ifndef med_linac_LINAC_HEAD_MESSENGER_HH
#define med_linac_LINAC_HEAD_MESSENGER_HH

#include "G4UImessenger.hh"
#include "G4UIcmdWithoutParameter.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWithADouble.hh"

#include "G4PVPlacement.hh"

namespace med_linac {
	class LinacHeadMessenger : public G4UImessenger {
	public:
		LinacHeadMessenger();
		~LinacHeadMessenger();

		void SetNewValue(G4UIcommand* command, G4String newValues);
		G4String GetCurrentValue(G4UIcommand* command);

		void SetLinacHeadPointer(G4VPhysicalVolume* physLinacHead);

	private:
		G4UIdirectory* fLinacHeadDir;
		G4UIcmdWithoutParameter* fTestCommand;
		G4UIcmdWithAnInteger* fLinacHeadAngle;
		G4UIcmdWithADouble* fLinacHeadY;

		G4VPhysicalVolume* fPhysLinacHead = nullptr;

		void ChangeLinacHeadY(G4double newY);
		

	};
}

#endif // !med_linac_LINAC_HEAD_MESSENGER_HH
