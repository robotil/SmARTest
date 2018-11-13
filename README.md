# SmARTest
This repository contains the code of SmARTest (Simulated Autonomous Robotic Testing) a tool for automatic testing and safety verification of autonomous vehicles.

# Compile:
mkdir build
cd build
cmake ..   (for debug version cmake -DCMAKE_BUILD_TYPE=Debug .. )
make

# Command line to generate scenario:
cd ~smartest;
build/mainGen -genSFV SFDP/convoy.SFDP work_space/scenario_2 resource/resource_convoy.xml

# Command line to generate and run Multiple scenarios:
cd ~smartest;
build/mainGen -MultipleScensGenRun SFDP/convoy.SFDP work_space resource/resource_convoy.xml 5

# Command line to play a specific scenario:
cd ~smartest;
build/mainGen -RunScenario SFDP/convoy.SFDP work_space/sampl_2 resource/resource_convoy.xml

# Notes:
1. If you are in mode of checking without connection to the platform, then setenv FULL_SMARTEST to 0:
export FULL_SMARTEST=0
In this case, Smartest will not turn on/off the car and the OCU. 
2. The default duration of a scenario is 3 minutes or 180000 milliseconds. It can be changed with the environment variable SMART_SCEN_DURATION_MS:
export SMART_SCEN_DURATION_MS=60000
3. For your convenience, there is a script: scripts/this.env that you can source before you run smartest and that will help configure smartest environment
