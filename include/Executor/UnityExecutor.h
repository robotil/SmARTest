#ifndef UNITYXECUTOR_H_
#define UNITYXECUTOR_H_

#include <string>
#include "Executor/scenarioLauncher.h"
#include "SFV/SFV.h"


class UnityExecutor {
	private :

		std::string my_Scenario_folder_url;

		std::string my_pyInterface;

		bool was_executed_flag;

		ScenarioLauncher *my_launcher;

	public :
		UnityExecutor(SFV *sfv);
		~UnityExecutor();

		int RunScenario(int argc, char** argv);

		inline bool get_wasExecutedFlag()
			{	return was_executed_flag; }
};



#endif /* UNITYXECUTOR_H_ */
