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
            SFV * sfv = new SFV(SFV_root_file,scenario_folder_path);
            sfv->execute(argc,argv);
			  
			return 0;
		}

    printUsage();
	return 1;

/*

	if(std::string(argv[1]).compare("-DomainEploretion")==0)
		{

			std::cout << " -OtomaticScensGenRun is runing !!! " << std::endl;

			std::string SFDP_file_path = PATH+argv[2];
			std::string scenario_folder_path = PATH + argv[3];
			std::string work_space_folder_url = PATH + argv[4];
			int division_limit = atoi(argv[5]);
			int samples_number = atoi(argv[6]);

			SFDPobj * sfdp;
			sfdp = new SFDPobj(SFDP_file_path,work_space_folder_url,scenario_folder_path,0);
			if (! sfdp->ParseMeFromXMLFile())
				{
				std::cout << "\033[1;31m Failed parse SFDP from file \033[0m " << std::endl;
				return 0;
				}

			sfdp->ExploreMe(argc,argv,division_limit,samples_number);

			return 0;
		}


	if(std::string(argv[1]).compare("-ScenarioReplications")==0)
		{

		std::string SFV_root_file = PATH + argv[2];
		std::string WS_folder_path = PATH + argv[3];
		int SampNum = std::stoi(argv[4]);

		TiXmlElement * sampsXML = new TiXmlElement("samples");

		for (int sfv_i=1; sfv_i<=SampNum ; sfv_i++)
		{
			std::string scenario_folder_path = WS_folder_path +"/sfv_run_" + std::to_string(sfv_i);

			boost::filesystem::remove_all(scenario_folder_path);
			boost::filesystem::create_directory(scenario_folder_path);

			SFV * sfv = new SFV(SFV_root_file,scenario_folder_path);
			sfv->printToXML(scenario_folder_path+"/scen.SFV");
			sfv->execute(argc,argv);

			std::string sfv_name = "sfv_" + std::to_string(sfv_i);
			TiXmlElement * xml_sfv = new TiXmlElement( sfv_name );
			TiXmlElement * xml_grades = sfv->get_GradesAsXMLElement(0);
			xml_sfv->LinkEndChild(xml_grades);
			sampsXML->LinkEndChild(xml_sfv);
		}

		    std::string Grades_file_url = WS_folder_path + "/grades.xml";
			TiXmlDocument doc(Grades_file_url);
			TiXmlDeclaration * decl = new TiXmlDeclaration( "1.0", "", "" );
			doc.LinkEndChild(decl);
			doc.LinkEndChild(sampsXML);
			doc.SaveFile(Grades_file_url.c_str());
			std::cout << " printing Grades to file : " << Grades_file_url << std::endl;

			return 0;
		}

*/

	return 0;

}
