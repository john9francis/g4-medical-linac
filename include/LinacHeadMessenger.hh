#ifndef med_linac_LINAC_HEAD_MESSENGER_HH
#define med_linac_LINAC_HEAD_MESSENGER_HH

#include "G4UImessenger.hh"
#include "G4UIcmdWithoutParameter.hh"

namespace med_linac {
	class LinacHeadMessenger : public G4UImessenger {
	public:
		LinacHeadMessenger();
		~LinacHeadMessenger();

		void SetNewValue(G4UIcommand* command, G4String newValues);
		G4String GetCurrentValue(G4UIcommand* command);

	private:
		G4UIdirectory* fLinacHeadDir;
		G4UIcmdWithoutParameter* fTestCommand;

	};
}

#endif // !med_linac_LINAC_HEAD_MESSENGER_HH
