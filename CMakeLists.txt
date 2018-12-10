CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

set(customSourcesDir /home/kalloch/OpenFOAM/kalloch-3.0.1/additional_stuff/PVCustomClasses)

#--------------------------------------------------
# Find and Use ParaView
#--------------------------------------------------
FIND_PACKAGE(ParaView REQUIRED)
INCLUDE(${PARAVIEW_USE_FILE})
 ADD_PARAVIEW_PLUGIN(SaveOFField "1.0" 
   SERVER_MANAGER_XML vtkSaveOFFieldFilter_SM.xml
   SERVER_MANAGER_SOURCES vtkSaveOFFieldFilter.cxx
   SOURCES
   	${customSourcesDir}/FieldTemplate.cxx
   REQUIRED_ON_SERVER)

# let cmake decide which c++-version is needed to satisfy all the features used in the source-code
target_compile_features(SaveOFField PRIVATE cxx_range_for)
