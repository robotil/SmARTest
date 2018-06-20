#include <string>
#include <iostream>

#include "Executor/UnityExecutor.h"
//#include "Executor/scenarioLauncher.h"
#include "SFV/SFV.h"
#include "Resource/ResourceHandler.h"

//#include "ros/ros.h"

#include <tinyxml.h>
#include "utils/TinyXmlDef.h"

UnityExecutor::UnityExecutor(SFV *sfv)
{
	my_Scenario_folder_url = sfv->get_WSfolder(); //Scenario_folder_url;

	//my_pyInterface = ResourceHandler::getInstance(sfv->get_ResourceFile()).getRobotPyInterface();
    //std::cout << "my_pyInterface = " << my_pyInterface << std::endl;

	was_executed_flag = false;

	//my_launcher = new ScenarioLauncher(my_pyInterface);
	//my_launcher->start_launcher();
}

UnityExecutor::~UnityExecutor()
{
	//my_launcher->stop_launcher();
	//my_launcher->~ScenarioLauncher();
}


int UnityExecutor::RunScenario(int argc, char** argv)
{
    std::cout << " my_Scenario_folder_url = "<< my_Scenario_folder_url << std::endl;
    
    std::string s = "/home/robil/ConvoyUnity/builds/Convoy.x86_64 -scenfolder " + my_Scenario_folder_url; // +"/scen.SFV";
	std::cout << s << std::endl;
	system(s.c_str());


	// my_launcher->setScenarioEnv(my_Scenario_folder_url);
	// std::cout << "\033[1;35m Scenario Env_Variables are loaded !!! \033[0m" << std::endl;

    was_executed_flag = true;

   // my_launcher->stop_launcher();

	return 1;
}


