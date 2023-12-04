#include "LinacHeadSingleton.hh"

namespace med_linac {
	LinacHeadSingleton* LinacHeadSingleton::instance = nullptr;

	LinacHeadSingleton::LinacHeadSingleton() {

	}

	LinacHeadSingleton* LinacHeadSingleton::GetInstance() {
		if (!instance) {
			instance = new LinacHeadSingleton();
		}

		return instance;
	}

	void LinacHeadSingleton::PrintHelloWorld() {
		
	}
}