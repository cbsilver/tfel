/*!
 * \file   MFrontFortranLawInterface.cxx
 * \brief  
 * 
 * \author Helfer Thomas
 * \date   01 déc 2008
 */

#include<sstream>
#include<stdexcept>

#include"ParserUtilities.hxx"
#include"MFrontHeader.hxx"
#include"MFrontFortranLawInterface.hxx"

namespace mfront
{

  std::string
  MFrontFortranLawInterface::getName(void)
  {
    return "fortran";
  }

  MFrontFortranLawInterface::MFrontFortranLawInterface()
    : MFrontCLawInterfaceBase()
  {}

  std::map<std::string,std::vector<std::string> >
  MFrontFortranLawInterface::getGlobalDependencies(const std::string& library,
						   const std::string& material,
						   const std::string&)
  {
    using namespace std;
    map<string,vector<string> > libs;
    libs["libFortran"+getMaterialLawLibraryNameBase(library,material)].push_back("-lm");
    return libs;
  } // end of MFrontFortranLawInterface::getGeneratedSources

  std::map<std::string,std::vector<std::string> >
  MFrontFortranLawInterface::getGlobalIncludes(const std::string&,
					       const std::string&,
					       const std::string&)
  {
    using namespace std;
    return map<string,vector<string> >();
  } // end of MFrontFortranLawInterface::getGeneratedSources

  std::map<std::string,std::vector<std::string> >
  MFrontFortranLawInterface::getGeneratedSources(const std::string& library,
						 const std::string& material,
						 const std::string& className)
  {
    using namespace std;
    map<string,vector<string> > src;
    string name = this->getSrcFileName(material,className);
    src["libFortran"+getMaterialLawLibraryNameBase(library,material)].push_back(name+".cxx");
    return src;
  } // end of MFrontFortranLawInterface::getGeneratedSources

  std::vector<std::string>
  MFrontFortranLawInterface::getGeneratedIncludes(const std::string&,
						  const std::string&,
						  const std::string&)
  {
    using namespace std;
    return vector<string>();
  } // end of MFrontFortranLawInterface::getGeneratedIncludes

  std::map<std::string,std::vector<std::string> >
  MFrontFortranLawInterface::getLibrariesDependencies(const std::string& library,
						      const std::string& material,
						      const std::string&)
  {
    using namespace std;
    map<string,vector<string> > libs;
    libs["libFortran"+getMaterialLawLibraryNameBase(library,material)].push_back("-lm");
    return libs;
  } // end of MFrontFortranLawInterface::getLibrariesDependencies()

  std::map<std::string,
	   std::pair<std::vector<std::string>,
		     std::vector<std::string> > >
    MFrontFortranLawInterface::getSpecificTargets(const std::string&,
						  const std::string&,
						  const std::string&,
						  const std::vector<std::string>&)
  {
    using namespace std;
    return map<string,pair<vector<string>,vector<string> > >();
  } // end of MFrontFortranLawInterface::getSpecificTargets

  std::string
  MFrontFortranLawInterface::getHeaderFileName(const std::string&,
					       const std::string&)
  {
    return "";
  } // end of MFrontFortranLawInterface::getHeaderFileName

  std::string
  MFrontFortranLawInterface::getSrcFileName(const std::string& material,
					    const std::string& className)
  {
    if(material.empty()){
      return className+"-fortran";
    }
    return material+"_"+className+"-fortran";
  } // end of MFrontFortranLawInterface::getSrcFileName

  void
  MFrontFortranLawInterface::writeInterfaceSpecificVariables(const VarContainer& inputs)
  {
    VarContainer::const_iterator p;
    for(p=inputs.begin();p!=inputs.end();++p){
      this->srcFile << "const mfront_fortran_real8 " << p->name << " =  *(_mfront_var_" << p->name << ");\n";
    }
  } // end of MFrontFortranLawInterface::writeInterfaceSpecificVariables

  void
  MFrontFortranLawInterface::writeParameterList(std::ostream& file,
					      const VarContainer& inputs){
    VarContainer::const_iterator p;
    if(!inputs.empty()){
      for(p=inputs.begin();p!=inputs.end();){
	file << "const mfront_fortran_real8 * const _mfront_var_" << p->name;
	if((++p)!=inputs.end()){
	  file << ",\n";
	}
      }
    } else {
      file << "void";
    }
  } // end of MFrontFortranLawInterface::writeParameterList
  
  void
  MFrontFortranLawInterface::writeHeaderPreprocessorDirectives(const std::string&,
							       const std::string&)
  {} // end of MFrontFortranLawInterface::writePreprocessorDirectives

  void
  MFrontFortranLawInterface::writeSrcPreprocessorDirectives(const std::string& material,
							    const std::string& className)
  {
    if(!material.empty()){
    this->srcFile << "#define " 
		  << MFrontCLawInterfaceBase::makeUpperCase(material+"_"+className)
		  << "_F77 \\\n"
		  << "        F77_FUNC("
		  << MFrontCLawInterfaceBase::makeLowerCase(material+"_"+className) << ","
		  << MFrontCLawInterfaceBase::makeUpperCase(material+"_"+className) << ")\n\n";
    this->srcFile << "#define " 
		  << MFrontCLawInterfaceBase::makeUpperCase(material+"_"+className)
		  << "_CHECKBOUNDS_F77 \\\n"
		  << "        F77_FUNC("
		  << MFrontCLawInterfaceBase::makeLowerCase(material+"_"+className) 
		  << "_checkbounds,\\\n        "
		  << MFrontCLawInterfaceBase::makeUpperCase(material+"_"+className) 
		  << "_CHECKBOUNDS)\n\n";
    } else {
    this->srcFile << "#define " 
		  << MFrontCLawInterfaceBase::makeUpperCase(className)
		  << "_F77 \\\n"
		  << "        F77_FUNC("
		  << MFrontCLawInterfaceBase::makeLowerCase(className) << ","
		  << MFrontCLawInterfaceBase::makeUpperCase(className) << ")\n\n";
    this->srcFile << "#define " 
		  << MFrontCLawInterfaceBase::makeUpperCase(className)
		  << "_CHECKBOUNDS_F77 \\\n"
		  << "        F77_FUNC("
		  << MFrontCLawInterfaceBase::makeLowerCase(className) 
		  << "_checkbounds,\\\n        "
		  << MFrontCLawInterfaceBase::makeUpperCase(className) 
		  << "_CHECKBOUNDS)\n\n";
    }
    this->srcFile << "typedef double mfront_fortran_real8;\n";
    this->srcFile << "typedef int    mfront_fortran_integer4;\n";
  } // end of MFrontFortranLawInterface::writeSrcPreprocessorDirectives

  void
  MFrontFortranLawInterface::writeBeginHeaderNamespace(void)
  {} // end of MFrontFortranLawInterface::writeBeginHeaderNamespace
  
  void
  MFrontFortranLawInterface::writeEndHeaderNamespace(void)
  {} // end of MFrontFortranLawInterface::writeEndHeaderNamespace(void)

  void
  MFrontFortranLawInterface::writeBeginSrcNamespace(void)
  {
    this->srcFile << "#ifdef __cplusplus\n";
    this->srcFile << "extern \"C\"{\n";
    this->srcFile << "#endif /* __cplusplus */\n\n";
  } // end of MFrontFortranLawInterface::writeBeginSrcNamespace
  
  void
  MFrontFortranLawInterface::writeEndSrcNamespace(void)
  {
    this->srcFile << "#ifdef __cplusplus\n";
    this->srcFile << "} // end of extern \"C\"\n";
    this->srcFile << "#endif /* __cplusplus */\n\n";
  } // end of MFrontFortranLawInterface::writeEndSrcNamespace(void)

  std::string
  MFrontFortranLawInterface::getFunctionDeclaration(const std::string& material,
						    const std::string& className)
  {
    if(material.empty()){
      return "mfront_fortran_real8\n"+ MFrontCLawInterfaceBase::makeUpperCase(className) + "_F77";
    }
    return "mfront_fortran_real8\n"+ MFrontCLawInterfaceBase::makeUpperCase(material+"_"+className) + "_F77";
  } // end of MFrontFortranLawInterface::getFunctionDeclaration
  
  std::string
  MFrontFortranLawInterface::getCheckBoundsFunctionDeclaration(const std::string& material,
							       const std::string& className)
  {
    if(material.empty()){
      return "mfront_fortran_integer4\n" + MFrontCLawInterfaceBase::makeUpperCase(className) + "_CHECKBOUNDS_F77";
    }
    return "mfront_fortran_integer4\n" + MFrontCLawInterfaceBase::makeUpperCase(material+"_"+className) + "_CHECKBOUNDS_F77";
  } // end of MFrontFortranLawInterface::getCheckBoundsFunctionDeclaration
  
  MFrontFortranLawInterface::~MFrontFortranLawInterface()
  {} // end of MFrontFortranLawInterface::~MFrontFortranLawInterface

} // end of namespace mfront
