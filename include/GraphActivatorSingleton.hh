#ifndef med_linac_GRAPH_ACTIVATOR_SINGLETON_H
#define med_linac_GRAPH_ACTIVATOR_SINGLETON_H 1

#include "globals.hh"

namespace med_linac {
	class GraphActivatorSingleton {
	private:
		GraphActivatorSingleton() {}
		static GraphActivatorSingleton* instance;

	public:
		static GraphActivatorSingleton* GetInstance() {
			if (!instance) {
				instance = new GraphActivatorSingleton();
			}

			return instance;
		}

		void TestPrint() {
			G4cout << "Graph Activator Singleton success" << G4endl;
		}
	};
}

#endif