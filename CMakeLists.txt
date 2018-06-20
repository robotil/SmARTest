cmake_minimum_required(VERSION 2.8.3)
project(smartest)

SET(CMAKE_CXX_FLAGS "-std=c++0x")


find_package(Boost REQUIRED COMPONENTS system thread filesystem)

#find_package(TinyXML REQUIRED)

#find_package(OpenCV REQUIRED)
                            
#FIND_PACKAGE(PythonLibs 2.7 REQUIRED)

SET(TinyXML_LIBs  "/usr/lib/x86_64-linux-gnu/libtinyxml.so" CACHE FILEPATH "links to tinyXML")
SET(TinyXML_INCLUDE_DIR "/usr/inlude" CACHE FILEPATH "include files for tinyXML")

SET(BOOST_LIBs "${BOOST_SYSTEM_LIBRARY_RELEASE} ${BOOST_FILESYSTEM_LIBRARY_RELEASE}")                                                                                                                                          
include_directories(include ${TinyXML_INCLUDE_DIR} ${Boost_INCLUDE_DIR}) # ${PYTHON_INCLUDE_DIR} /usr/include/sdformat-4.3/sdf )


############
## UTILS  ##
############

add_library(NumberSampler src/utils/NumberSampler.cpp)


##############
## RESOURCE ##
##############
add_library(ResourceHandler src/Resource/ResourceHandler.cpp)
target_link_libraries(ResourceHandler ${TinyXML_LIBs})




#############
### SFDP ####
#############
add_library(ScenarioFeatureGroup src/SFDP/ScenarioFeatureGroup.cpp)
add_library(ScenarioFeature src/SFDP/ScenarioFeature.cpp)

target_link_libraries(ScenarioFeature ${TinyXML_LIBs}
NumberSampler
)


target_link_libraries(ScenarioFeatureGroup  ${TinyXML_LIBs}
ScenarioFeature
)


add_library(SFDPobj src/SFDP/SFDPobj.cpp)
target_link_libraries(SFDPobj ${BOOST_SYSTEM_LIBRARY_RELEASE}
${BOOST_FILESYSTEM_LIBRARY_RELEASE}
${TinyXML_LIBs}
ScenarioFeatureGroup
ScenarioFeature
SFV
#GazeboExecutor
#GazeboScenarioGenerator
)


#############
#### SFV ####
#############

add_library(sfvSubGroup src/SFV/sfvSubGroup.cpp)
target_link_libraries(sfvSubGroup
)

add_library(SFVwp src/SFV/SFVwp.cpp)
target_link_libraries(SFVwp 
sfvSubGroup
)

add_library(SFVpath src/SFV/SFVpath.cpp)
target_link_libraries(SFVpath 
ScenarioFeature
sfvSubGroup
SFVwp
)

add_library(SFVmass_link src/SFV/SFVmass_link.cpp)
target_link_libraries(SFVmass_link 
sfvSubGroup
)

add_library(SFVfriction_link src/SFV/SFVfriction_link.cpp)
target_link_libraries(SFVfriction_link 
sfvSubGroup
)

add_library(SFVsensor_link src/SFV/SFVsensor_link.cpp)
target_link_libraries(SFVsensor_link 
sfvSubGroup
)


add_library(SFVterraine src/SFV/SFVterraine.cpp)
target_link_libraries(SFVterraine 
sfvSubGroup
)


add_library(SFVObject src/SFV/SFVObject.cpp)
target_link_libraries(SFVObject 
sfvSubGroup
)

add_library(SFVobjScattering src/SFV/SFVobjScattering.cpp)
target_link_libraries(SFVobjScattering 
sfvSubGroup
SFVObject
)

add_library(SFVobstacaleOnPath src/SFV/SFVobstacaleOnPath.cpp)
target_link_libraries(SFVobstacaleOnPath 
sfvSubGroup
ScenarioFeatureGroup
)

add_library(SFVobsOnPathScattering src/SFV/SFVobsOnPathScattering.cpp)
target_link_libraries(SFVobsOnPathScattering 
sfvSubGroup
SFVobstacaleOnPath
)


add_library(SFVplatformPose src/SFV/SFVplatformPose.cpp)
target_link_libraries(SFVplatformPose 
sfvSubGroup
ResourceHandler
)


add_library(SFV src/SFV/SFV.cpp)
target_link_libraries(SFV 
ScenarioFeatureGroup
sfvSubGroup
SFVpath
SFVterraine
SFVobjScattering
SFVplatformPose
SFVmass_link
SFVfriction_link
SFVsensor_link
SFVobsOnPathScattering
#RULE_platform_init_pose_with_no_obj_colisions
#RULE_wp_path_inside_map
#GazeboExecutor
#GazeboScenarioGenerator
UnityExecutor
)

##############
# GENERATORS #
##############

add_library(UnityExecutor src/Executor/UnityExecutor.cpp)
target_link_libraries(UnityExecutor
)

#############
#### MAIN ###
#############

add_executable(mainGen src/Main.cpp)
target_link_libraries(mainGen 
${Boost_FILESYSTEM_LIBRARY_RELEASE}
${Boost_SYSTEM_LIBRARY_RELEASE}
${TinyXML_LIBs}
ScenarioFeatureGroup
ScenarioFeature
SFDPobj
SFV
#GazeboScenarioGenerator
)


