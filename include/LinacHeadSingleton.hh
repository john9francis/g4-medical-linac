#ifndef med_linac_LINAC_HEAD_SINGLETON_HH
#define med_linac_LINAC_HEAD_SINGLETON_HH

namespace med_linac {
	class LinacHeadSingleton {

	private:
		static LinacHeadSingleton* instance;
		LinacHeadSingleton();

	public:
		static LinacHeadSingleton* GetInstance();
		void PrintHelloWorld();
	};
}

#endif // !med_linac_LINAC_HEAD_SINGLETON_HH
