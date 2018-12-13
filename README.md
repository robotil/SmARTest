# SmARTest
This repository contains the code of SmARTest (Simulated Autonomous Robotic Testing) a tool for automatic testing and safety verification of autonomous vehicles.

# Compile:
mkdir build
cd build
cmake ..   (for debug version cmake -DCMAKE_BUILD_TYPE=Debug .. )
make

# Command line to generate one scenario:
cd ~smartest;
build/mainGen -genSFV SFDP/convoy.SFDP <location of the scenario> resource/resource_convoy.xml
For example:
build/mainGen -genSFV SFDP/convoy.SFDP work_space/scenario_2 resource/resource_convoy.xml

# Command line to generate and run multiple scenarios:
cd ~smartest;
build/mainGen -MultipleScensGenRun SFDP/convoy.SFDP <location scenarios> resource/resource_convoy.xml <number of scenarios>

build/mainGen -MultipleScensGenRun SFDP/convoy.SFDP work_space resource/resource_convoy.xml 5
## note ## 
that work_space is a path relative to the SmARTest directory but if the directory doesn't exist, it will be created.
A tree of non-existing directories can also be used as input parameter; the tree will be created.
The results are integrated in the file testSummary.csv located in the directory input in the command
For example: 
build/mainGen -MultipleScensGenRun SFDP/convoy.SFDP test/13-11-2018-16:48 resource/resource_convoy.xml 5
The results will be integrated in test/13-11-2018-16:48/testSummary.csv

# Command line to play a specific scenario:
cd ~smartest;
build/mainGen -RunScenario SFDP/convoy.SFDP <location of the scenario> resource/resource_convoy.xml
For example:
build/mainGen -RunScenario SFDP/convoy.SFDP work_space/sampl_2 resource/resource_convoy.xml

# Command line to replay a recorded scenario
cd ~smartest;
build/mainGen -ReplayScenario SFDP/convoy.SFDP <location of the scenario> resource/resource_convoy.xml
For example:
build/mainGen -ReplayScenario SFDP/convoy.SFDP work_space/sampl_2 resource/resource_convoy.xml



# Notes:
1. All the paths are relative to the SmARTest directory
2. If you are in mode of checking without connection to the platform, then setenv FULL_SMARTEST to 0:
export FULL_SMARTEST=0
In this case, Smartest will not turn on/off the car and the OCU. 
3. The default duration of a scenario is 3 minutes or 180000 milliseconds. It can be changed with the environment variable SMART_SCEN_DURATION_MS:
export SMART_SCEN_DURATION_MS=60000
4. For your convenience, there is a script: scripts/this.env that you can source before you run smartest and that will help configure smartest environment
