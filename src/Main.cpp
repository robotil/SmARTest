#include <iostream>
#include <tr1/stdio.h>
#include <string>
#include <boost/filesystem.hpp>

#include "SFDP/SFDPobj.h"
#include "Generators/Gazebo/GazeboScenarioGenerator.h"

#define PATH std::string("")

void printUsage()
{
	std::cout << "usage:" <<std::endl;
	std::cout <<"(0) <mainGen> -help # print this " <<std::endl;
	std::cout <<"(1) <mainGen> -genSFV <sfdp file> <full path to scenario folder> <resource file> " <<std::endl;
	std::cout <<" Will generate a sfv file according to the sfdp and resource files input " <<std::endl;
	std::cout <<" Example: mainGen -genSFV SFDP/convoy.SFDP work_space/scenario_2 resource/resource_convoy.xml" <<std::endl;
	std::cout <<"(2) <mainGen> -MultipleScensGenRun <sfdp file> <destination folder> <resource file> <number of scenarios> " <<std::endl;
	std::cout <<" Will generate the <number of scenarios> scenarios and launch them, one after the other" <<std::endl;
	std::cout <<" Example: mainGen -MultipleScensGenRun SFDP/convoy.SFDP work_space resource/resource_convoy.xml 5" << std::endl;
	std::cout <<"(3) <mainGen> -RunScenario <sfdp file> <full path to scenario folder>" <<std::endl;
	std::cout <<" Will run the scenario defined in the parameter scenario folder" <<std::endl;
	std::cout <<" Example: mainGen -RunScenario SFDP/convoy.SFDP work_space/sampl_2" <<std::endl;
	std::cout <<"(4) <mainGen> -ReplayScenario <sfdp file> <full path to scenario folder>" <<std::endl;
	std::cout <<" Will replay the recorded scenario defined in the parameter scenario folder" <<std::endl;
	std::cout <<" Example: mainGen -ReplayScenario SFDP/convoy.SFDP work_space/sampl_2" <<std::endl;


	exit(1);
}


int main(int argc, char** argv)
{
    if (argc < 4)  {
		std::cout <<"Needs arguments" <<std::endl;
		printUsage();
	}
    
	if(std::string(argv[1]).compare("-help")==0)
		{
		printUsage();
		}

	std::cout << " Main is runing !!! " << std::endl;
    std::string SFDP_file_path = PATH+argv[2];
	std::string scenario_folder_path = PATH + argv[3];
	
    
	if(std::string(argv[1]).compare("-genSFV")==0)
		{
			if (argv[4] == NULL){
				printUsage();
				return 0;
			}

			std::cout << " -genSFV: Generate Scenario " << std::endl;

			std::string resources_file_path = PATH + argv[4];

			SFDPobj * sfdp_root;
			sfdp_root = new SFDPobj(SFDP_file_path,resources_file_path,scenario_folder_path,0);


			if (! sfdp_root->ParseMeFromXMLFile())
			{
				std::cout << "\033[1;31m Failed parse SFDP from file \033[0m " << std::endl;
				return 0;
			}

			boost::filesystem::remove_all(scenario_folder_path);
			boost::filesystem::create_directory(scenario_folder_path);
			SFV * sfv = new SFV(sfdp_root,scenario_folder_path);
			if (! sfv->roll() )
			{
				std::cout << "\033[1;31m rolling of SFV have failed \033[0m" << std::endl;
				return 0;
			}

			sfv->printToXML(scenario_folder_path+"/scen.SFV");

			return 0;
		}


	if(std::string(argv[1]).compare("-MultipleScensGenRun")==0)
		{
            if ((argv[4] == NULL) || (argv[5] == NULL)){
				printUsage();
				return 0;
			}
			std::cout << " -MultipleScensGenRun Generate and Run multiple scenarios !!! " << std::endl;
			std::string resources_file_path = PATH + argv[4];
			int num_of_scens = atoi(argv[5]);


			SFDPobj * sfdp;
			sfdp = new SFDPobj(SFDP_file_path,resources_file_path,scenario_folder_path,0);
			if (! sfdp->ParseMeFromXMLFile())
				{
				std::cout << "\033[1;31m Failed parse SFDP from file \033[0m " << std::endl;
				return 0;
				}

			sfdp->GenMySFVs(num_of_scens);
			sfdp->RunMySFVs(argc,argv);
            sfdp->Summary(num_of_scens);
			return 0;
		}

	if(std::string(argv[1]).compare("-RunScenario")==0)
		{
			std::cout << " -RunScenario is running !!! " << std::endl;

			std::string SFV_root_file = scenario_folder_path+"/scen.SFV";
            std::string grade = scenario_folder_path+"/grades.txt";
            if (boost::filesystem::exists(grade)){
				boost::filesystem::remove(grade);
			}
			std::string player = scenario_folder_path+"/Player.log";
            if (boost::filesystem::exists(player)){
				boost::filesystem::remove(player);
			}
			std::string record = scenario_folder_path+"/record";
            if (boost::filesystem::exists(record)){
				boost::filesystem::remove(record);
			}
			std::string icd = scenario_folder_path+"/icd_logs";
            if (boost::filesystem::exists(icd)){
				boost::filesystem::remove_all(icd);
			}
            SFV * sfv = new SFV(SFV_root_file,scenario_folder_path);
            sfv->execute(argc,argv);
			  
			return 0;
		}

	if(std::string(argv[1]).compare("-ReplayScenario")==0)
		{
			std::cout << " -ReplayScenario is running !!! " << std::endl;

			std::string SFV_root_file = scenario_folder_path+"/scen.SFV";
            SFV * sfv = new SFV(SFV_root_file,scenario_folder_path);
            sfv->replayScenario(argc,argv);
			  
			return 0;
		}

	if(std::string(argv[1]).compare("-Debug")==0)
		{
            if ((argv[4] == NULL) || (argv[5] == NULL)){
				printUsage();
				return 0;
			}
			std::cout << " -MultipleScensGenRun Generate and Run multiple scenarios !!! " << std::endl;
			std::string resources_file_path = PATH + argv[4];
			int num_of_scens = atoi(argv[5]);


			SFDPobj * sfdp;
			sfdp = new SFDPobj(SFDP_file_path,resources_file_path,scenario_folder_path,0);
			if (! sfdp->ParseMeFromXMLFile())
				{
				std::cout << "\033[1;31m Failed parse SFDP from file \033[0m " << std::endl;
				return 0;
				}

			sfdp->Summary(num_of_scens);
			
			return 0;
		}

    printUsage();
	return 1;

}
