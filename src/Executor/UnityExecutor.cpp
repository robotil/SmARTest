#include <string>
#include <iostream>
#include <signal.h>

#include "Executor/UnityExecutor.h"
#include "utils/Utilities.h"
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
#include "boost/filesystem/operations.hpp"
#include "boost/filesystem/path.hpp"
#include "boost/progress.hpp"

using namespace boost::asio;

UnityExecutor::UnityExecutor(SFV *sfv)
{
	my_Scenario_folder_url = sfv->get_WSfolder(); //Scenario_folder_url;

	//my_pyInterface = ResourceHandler::getInstance(sfv->get_ResourceFile()).getRobotPyInterface();
    //std::cout << "my_pyInterface = " << my_pyInterface << std::endl;

	was_executed_flag = false;
    m_pid = 0;
	char *full_smartest, *scenario_duration_ms;
	full_smartest = getenv("FULL_SMARTEST");
	if (full_smartest == (char *)NULL) {	
		m_is_full_smartest = 1;
	} else m_is_full_smartest=std::stoi(full_smartest);
	scenario_duration_ms = getenv("SMART_SCEN_DURATION_MS");
	if (scenario_duration_ms == (char *)NULL) {	
		m_scenario_duration = 180000;
	} else m_scenario_duration=std::stoi(scenario_duration_ms);
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
    std::string s;

	
	std::cout << "m_is_full_smartest="<< m_is_full_smartest << std::endl;

    if (m_is_full_smartest) {
		s = "ssh -oHostKeyAlgorithms=+ssh-dss 192.168.70.3 -l SRVSS_Pass C:\\\\scripts\\\\startps.bat";
		std::cout << s << std::endl;
		system(s.c_str());
		s = "ssh -oHostKeyAlgorithms=+ssh-dss 192.168.70.2 -l SRVSS_pass C:\\\\scripts\\\\startOCU.bat";
		std::cout << s << std::endl;
		system(s.c_str());
	}
	std::cout << s << std::endl;
	std::cout << " my_Scenario_folder_url = "<< my_Scenario_folder_url << std::endl;
	//Check path expansion if possible
	//s = "echo Robil12 | sudo -S /home/robil/Convoy/Convoy.x86_64 -scenfolder " + my_Scenario_folder_url; // +"/scen.SFV";
    s = "/home/robil/Convoy/Convoy.x86_64 -scenfolder " + my_Scenario_folder_url; // +"/scen.SFV";
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
		PreserveLogs();
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
	std::string s;
	io_service i;
    deadline_timer t(i);
    if (m_is_full_smartest) {
		s = "ssh -oHostKeyAlgorithms=+ssh-dss 192.168.70.3 -l SRVSS_Pass C:\\\\scripts\\\\downps.bat";
		std::cout << s << std::endl;
		system(s.c_str());
		s = "ssh -oHostKeyAlgorithms=+ssh-dss 192.168.70.2 -l SRVSS_pass C:\\\\scripts\\\\stopOCU.bat";
		system(s.c_str());
		std::cout << s << std::endl;
	}
	//Add some sleep
	ret = kill(-m_pid, SIGTERM);
	t.expires_from_now(boost::posix_time::milliseconds(2000));
	t.wait();
	ret = kill(-m_pid, SIGKILL);
	return ret;
}

int UnityExecutor::PreserveLogs()
{
	std::string player_log, icd_log_path;
	player_log = my_Scenario_folder_url+"//Player.log";
	std::cout<<"Copying /home/robil/.config/unity3d/DefaultCompany/Convoy/Player.log to " << player_log <<std::endl;
	boost::filesystem::copy("/home/robil/.config/unity3d/DefaultCompany/Convoy/Player.log", player_log);
	icd_log_path = my_Scenario_folder_url+"/icd_logs";
	Utilities::copyDirectoryRecursively("/home/robil/icd_log",icd_log_path);
	//boost::filesystem::copy_directory("/home/robil/icd_log", icd_log_path);

}
