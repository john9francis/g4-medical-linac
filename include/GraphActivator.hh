//////////////////////////////////////////////////////////////////////////////
// SINGLETON
//////////////////////////////////////////////////////////////////////////////

#ifndef med_linac_GRAPH_ACTIVATOR_SINGLETON_H
#define med_linac_GRAPH_ACTIVATOR_SINGLETON_H 1

#include "globals.hh"

namespace med_linac {
	class GraphActivatorSingleton {
	private:
		GraphActivatorSingleton() {
			makePDD = new G4bool(false);
			makeDoseProfile = new G4bool(false);
			makeHeatMap = new G4bool(false);
		}
		~GraphActivatorSingleton() {
			delete makePDD;
			delete makeDoseProfile;
			delete makeHeatMap;
		};
		static GraphActivatorSingleton* instance;

		// our flags
		G4bool* makePDD;
		G4bool* makeDoseProfile;
		G4bool* makeHeatMap;

	public:
		static GraphActivatorSingleton* GetInstance() {
			if (!instance) {
				instance = new GraphActivatorSingleton();
			}

			return instance;
		}

		static void DeleteInstance() {
			if (instance) {
				delete instance;
				instance = nullptr;

			}
		}

		void TestPrint() {
			G4cout
				<< "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"
				<< "Graph Activator Singleton success" 
				<< "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"
				<< G4endl;
		}

		void SetMakePDD(G4bool value) {
			*makePDD = value;
		}
		void SetMakeDoseProfile(G4bool value) {
			*makeDoseProfile = value;
		}
		void SetMakeHeatMap(G4bool value) {
			*makeHeatMap = value;
		}
		G4bool GetMakePDD() {
			return *makePDD;
		}
		G4bool GetMakeDoseProfile() {
			return *makeDoseProfile;
		}
		G4bool GetMakeHeatMap() {
			return *makeHeatMap;
		}
	};
}

#endif // !med_linac_GRAPH_ACTIVATOR_SINGLETON_H 1


//////////////////////////////////////////////////////////////////////////////
// MESSENGER
//////////////////////////////////////////////////////////////////////////////

#ifndef med_linac_GRAPH_ACTIVATOR_MESSENGER_H
#define med_linac_GRAPH_ACTIVATOR_MESSENGER_H 1

#include "G4UImessenger.hh"
#include "G4UIcmdWithABool.hh"

namespace med_linac {
	class GraphActivatorMessenger : public G4UImessenger {
	public:
		GraphActivatorMessenger();

		void SetNewValue(G4UIcommand* command, G4String newValues);


	private:
		G4UIdirectory* fDirectory;

		G4UIcmdWithABool* setPddCmd;
		G4UIcmdWithABool* setDoseProfileCmd;
		G4UIcmdWithABool* setHeatMapCmd;
	};
}

#endif // !med_linac_GRAPH_ACTIVATOR_MESSENGER_H 1
