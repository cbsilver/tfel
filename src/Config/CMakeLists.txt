configure_file(${PROJECT_SOURCE_DIR}/src/Config/GetTFELVersion.c.in
               ${PROJECT_BINARY_DIR}/src/Config/GetTFELVersion.c)

tfel_library(TFELConfig
  GetInstallPath.cxx
  ${PROJECT_BINARY_DIR}/src/Config/GetTFELVersion.c)
target_include_directories(TFELConfig
   PUBLIC 
   $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
   $<INSTALL_INTERFACE:include>
   PRIVATE
   $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/include>)
