/*!
 * \file   MFrontHeader.cxx
 * \brief  
 * 
 * \author Helfer Thomas
 * \date   09 nov 2006
 */

#include<string>
#include"MFront/MFrontHeader.hxx"

namespace mfront{
  
  std::string
  MFrontHeader::getVersionName(void)
  {
    return PACKAGE_NAME;
  }

  std::string
  MFrontHeader::getVersionNumber(void)
  {
    return VERSION;
  }

  std::string
  MFrontHeader::getBugReportAdress(void)
  {
    return PACKAGE_BUGREPORT;
  }

  std::string
  MFrontHeader::getCompilerName(void)
  {
    return "g++";
  }

  std::string
  MFrontHeader::getBuildCpu(void)
  {
    return "x86_64";
  }

  std::string
  MFrontHeader::getBuildOs(void)
  {
    return "linux-gnu";
  }

  std::string
  MFrontHeader::getHostCpu(void)
  {
    return "x86_64";
  }

  std::string
  MFrontHeader::getHostOs(void)
  {
    return "linux-gnu";
  }

  std::string
  MFrontHeader::getTargetCpu(void)
  {
    return "x86_64";
  }

  std::string
  MFrontHeader::getTargetOs(void)
  {
    return "linux-gnu";
  }

  std::string
  MFrontHeader::getHeader(const std::string& s)
  {
    using namespace std;

    string target_cpu = getTargetCpu();
    string build_cpu  = getBuildCpu();
    string host_cpu   = getHostCpu();
    string target_os = getTargetOs();
    string build_os  = getBuildOs();
    string host_os   = getHostOs();

    string header;

    header  = s;
    header += getVersionName();
    header += "\n";
    header += s;
    header += "Version : " + getVersionNumber();
    header += "\n";
    if((target_cpu != build_cpu)|| (target_cpu != host_cpu) ||
       (target_os  != build_os) || (target_os  != host_os)){
      header += s;
      header += "Compiled with ";
      header +=  getCompilerName();
      header +=  " : ";
      header += "\n";
      header += s;
      header += "- target cpu : ";
      header += target_cpu;
      header += "\n";
      header += s;
      header += "\n";
      header += s;
      header += "- target os  : " ;
      header += target_os ;
      header += "\n";
      header += s;
      header += "\n";
      header += s;
      header += "- build cpu  : ";
      header += build_cpu  ;
      header += "\n";
      header += s;
      header += "\n";
      header += s;
      header += "- build os   : ";
      header +=  build_os;
      header += "\n";
      header += s;
      header += "\n";
      header += s;
      header += "- host cpu   : ";
      header += host_cpu;
      header += "\n";
      header += s;
      header += "\n";
      header += s;
      header += "- host os    : ";
      header += host_os;
      header += "\n";
    } else {
      header += s;
      header += "Compiled with ";
      header += getCompilerName();
      header += " on ";
      header += target_cpu;
      header += " - ";
      header += target_os;
      header += "\n";
    }
    header += s;
    header += "Please submit bug at " ;
    header +=  getBugReportAdress() ;
    header +=  "\n";

    return header;

  }

} // end of namespace mfront

