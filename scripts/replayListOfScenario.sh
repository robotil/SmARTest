#!/bin/bash

cd /home/robil/SmARTest
for i in 1 2 3 4 5
	do
	build/mainGen -ReplayScenario SFDP/convoy.SFDP work_space/sampl_$i resource/resource_convoy.xml
	sleep 1
	done
