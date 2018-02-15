# SmARTest
This repository contains the code of SmARTest (Simulated Autonomous Robotic Testing) a tool for automatic testing and safety verification of autonomous vehicles.




# Compile:
mkdir build

cd build

cmake ..

make


# Command line to generate scenario:
cd ~smartest;

build/devel/lib/smartest/mainGen -genSFV SFDP/convoy.SFDP work_space/scenario_2 resource/resource_convoy.xml


# Command line to generate ad run Multiple scenarios:
build/devel/lib/smartest/mainGen -MultipleScensGenRun SFDP/convoy.SFDP work_space resource/resource_convoy.xml 5
