#include <string>
#include <iostream>

#include <signal.h>

#include "Executor/UnityExecutor.h"
//#include "Executor/scenarioLauncher.h"
#include "SFV/SFV.h"
#include "Resource/ResourceHandler.h"

//#include "ros/ros.h"

#include <tinyxml.h>
#include "utils/TinyXmlDef.h"

#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

using namespace boost::asio;

UnityExecutor::UnityExecutor(SFV *sfv)
{
	my_Scenario_folder_url = sfv->get_WSfolder(); //Scenario_folder_url;

	//my_pyInterface = ResourceHandler::getInstance(sfv->get_ResourceFile()).getRobotPyInterface();
    //std::cout << "my_pyInterface = " << my_pyInterface << std::endl;

	was_executed_flag = false;
    m_pid = 0;
	m_scenario_duration = 60000;

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
	io_service i;
    deadline_timer t(i);
	std::cout << " my_Scenario_folder_url = "<< my_Scenario_folder_url << std::endl;
    std::string s = "/home/robil/ConvoyUnity/builds/Convoy.x86_64 -scenfolder " + my_Scenario_folder_url; // +"/scen.SFV";
    //std::string s = "/bin/sh -c \"/home/robil/ConvoyUnity/builds/Convoy.x86_64 -scenfolder " + my_Scenario_folder_url + "\"";//+ " &";  +"/scen.SFV";
	std::string param = "-scenfolder " + my_Scenario_folder_url;
	std::cout << s << std::endl;
	int pid = fork();
	if (pid == 0){
		setpgid(0,0);
		system(s.c_str());
		//execl(s.c_str(), "", "", (char *) 0);
		//execl("/home/robil/ConvoyUnity/builds/Convoy.x86_64","Convoy.x86_64","-scenfolder","/home/robil/ws/src/SmARTest/"+my_Scenario_folder_url,NULL);
		std::cout <<s.c_str() << std::endl;
		exit(127);

	} else {
		m_pid = pid;
        was_executed_flag = true;
		std::cout << "m_pid="<< m_pid << std::endl;
		t.expires_from_now(boost::posix_time::milliseconds(m_scenario_duration));
		t.wait();
		TerminateScenario();
	}
	//system(s.c_str());


	// my_launcher->setScenarioEnv(my_Scenario_folder_url);
	// std::cout << "\033[1;35m Scenario Env_Variables are loaded !!! \033[0m" << std::endl;

    

   // my_launcher->stop_launcher();

	return 1;
}

int UnityExecutor::TerminateScenario()
{
	int ret;
	ret = kill(-m_pid, SIGTERM);
	sleep(2);
	ret = kill(-m_pid, SIGKILL);
	return ret;
}
