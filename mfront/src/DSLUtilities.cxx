/*!
  * \file   mfront/src/DSLUtilities.cxx
  * \brief
  *
  * \author Thomas Helfer
  * \date   23 oct 2008
  * \copyright Copyright (C) 2006-2018 CEA/DEN, EDF R&D. All rights
  * reserved.
  * This project is publicly released under either the GNU GPL Licence
  * or the CECILL-A licence. A copy of thoses licences are delivered
  * with the sources of TFEL. CEA or EDF may also distribute this
  * project under specific licensing conditions.
  */

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "TFEL/Raise.hxx"
#include "TFEL/Config/TFELConfig.hxx"
#include "TFEL/Config/GetTFELVersion.h"
#include "TFEL/Glossary/GlossaryEntry.hxx"
#include "TFEL/Utilities/StringAlgorithms.hxx"
#include "TFEL/System/System.hxx"
#include "MFront/MFrontDebugMode.hxx"
#include "MFront/DSLUtilities.hxx"
#include "MFront/StaticVariableDescription.hxx"
#include "MFront/MaterialPropertyDescription.hxx"
#include "MFront/MaterialPropertyParametersHandler.hxx"
#include "MFront/SymbolsGenerator.hxx"


#ifndef _MSC_VER
    static const char *const constexpr_c = "constexpr";
#else
    static const char *const constexpr_c = "const";
#endif

namespace mfront {

void writeVariablesNamesSymbol(std::ostream &out, const std::string &name,
                               const mfront::MaterialPropertyDescription &mpd) {
  if (!mpd.inputs.empty()) {
    out << "MFRONT_SHAREDOBJ const char *\n"
        << name << "_args[" << mpd.inputs.size() << "] = {";
    for (auto p3 = mpd.inputs.begin(); p3 != mpd.inputs.end();) {
      const auto iname = '\"' + p3->getExternalName() + '\"';
      out << iname;
      if (++p3 != mpd.inputs.end()) {
        out << ",";
      }
    }
    out << "};\n\n";
  }
  out << "MFRONT_SHAREDOBJ unsigned short\n"
      << name << "_nargs = " << mpd.inputs.size() << "u;\n\n";
  } // end of writeVariableNamesSymbol


  void writeBoundsSymbol(std::ostream& out,
                         const std::string& n,
                         const std::string& vn,
                         const std::string& bt,
                         const VariableBoundsDescription& b) {
    if ((b.boundsType == VariableBoundsDescription::LOWER) ||
        (b.boundsType == VariableBoundsDescription::LOWERANDUPPER)) {
      out << "MFRONT_SHAREDOBJ long double " << n << "_" << vn << "_"
          << "Lower" << bt << "Bound = " << b.lowerBound << ";\n\n";
    }
    if ((b.boundsType == VariableBoundsDescription::UPPER) ||
        (b.boundsType == VariableBoundsDescription::LOWERANDUPPER)) {
      out << "MFRONT_SHAREDOBJ long double " << n << "_" << vn << "_"
          << "Upper" << bt << "Bound = " << b.upperBound << ";\n\n";
    }
  }  // end of writeBoundsSymbol

  void  writeVariablesBoundsSymbols(std::ostream &out, const std::string &name,
                              const mfront::MaterialPropertyDescription &mpd) {

    const auto prec = out.precision();
    out.precision(14);
    for (const auto& v: mpd.inputs){
      if (v.arraySize == 1u) {
        if (!v.hasBounds()) {
          continue;
        }
          writeBoundsSymbol(out, name, v.getExternalName(), "",
                          v.getBounds());
        if (!v.hasPhysicalBounds()) {
          continue;
        }
          writeBoundsSymbol(out, name, v.getExternalName(), "Physical",
                          v.getPhysicalBounds());        
      } else {
          for (auto idx = 0; idx != v.arraySize; ++idx) {
            if (!v.hasBounds(idx)) {
              continue;
            }
            writeBoundsSymbol(out, name, 
                v.getExternalName() + "__" + std::to_string(idx) + "__", "",
                v.getBounds(idx));
            if (!v.hasPhysicalBounds(idx)) {
              continue;
            }
            writeBoundsSymbol(out, name, 
                v.getExternalName() + "__" + std::to_string(idx) + "__", "Physical",
                v.getPhysicalBounds(idx));
          }
        }
    }
    out.precision(prec); 
  } // end of writeVariablesBoundsSymbols


  void writeEntryPointSymbol(std::ostream& out, const std::string& n) {
    writeEntryPointSymbol(out, n, n);
  }  // end of writeEntryPointSymbols

  void writeEntryPointSymbol(std::ostream& out,
                             const std::string& n,
                             const std::string& n2) {
    const auto* const build_id = std::getenv("TFEL_BUILD_ID");
    if (build_id != nullptr) {
      out << "MFRONT_SHAREDOBJ const char* \n"
          << n << "_build_id = \"" << build_id << "\";\n\n";
    } else {
      out << "MFRONT_SHAREDOBJ const char* \n" << n << "_build_id = \"\";\n\n";
    }
    out << "MFRONT_SHAREDOBJ const char* \n"
        << n << "_mfront_ept = \"" << n2 << "\";\n\n";
  }  // end of writeEntryPointSymbols

  void writeTFELVersionSymbol(std::ostream& out, const std::string& n) {
    out << "MFRONT_SHAREDOBJ const char* \n"
        << n << "_tfel_version = \"" << ::getTFELVersion() << "\";\n\n";
  }  // end of writeTFELVersionSymbol

  void writeInterfaceSymbol(std::ostream& out,
                            const std::string& n,
                            const std::string& i) {
    out << "MFRONT_SHAREDOBJ const char *\n"
        << n << "_mfront_interface = \"" << i << "\";\n\n";
  }  // end of writeInterfaceSymbol

  void writeMaterialSymbol(std::ostream& out,
                           const std::string& n,
                           const std::string& m) {
    if (!m.empty()) {
      out << "MFRONT_SHAREDOBJ const char* " << n << "_mfront_material = \""
          << m << "\";\n";
    }
  }  // end of writeMaterialSymbol

  void writeMaterialKnowledgeTypeSymbol(std::ostream& out,
                                        const std::string& n,
                                        const MaterialKnowledgeType& t) {
    if (t == MATERIALPROPERTY) {
      out << "MFRONT_SHAREDOBJ unsigned short " << n << "_mfront_mkt = 0u;\n\n";
    } else if (t == BEHAVIOUR) {
      out << "MFRONT_SHAREDOBJ unsigned short " << n << "_mfront_mkt = 1u;\n\n";
    } else if (t == MODEL) {
      out << "MFRONT_SHAREDOBJ unsigned short " << n << "_mfront_mkt = 2u;\n\n";
    } else {
      tfel::raise(
          "writeMaterialKnowledgeTypeSymbol: "
          "internal error, (unsupported material knowledge type)");
    }
  }  // end of writeMaterialKnowledgeTypeSymbol

  void writeMaterialLaws(std::ostream& os,
                         const std::vector<std::string>& materialLaws) {
    for (const auto& l : materialLaws) {
      os << "using mfront::" << l << ";\n"
         << "using mfront::" << l << "_checkBounds;\n";
    }
  }  // end of writeMaterialLaws

  void writeStaticVariables(std::ostream& os,
                            const StaticVariableDescriptionContainer& vc,
                            const std::string& f) {
    if (vc.empty()) {
      return;
    }
    for (const auto& v : vc) {
      if (getDebugMode()) {
        os << "#line " << v.lineNumber << " \"" << f << "\"\n";
      }
      if (v.type == "short") {
        os << "static " << constexpr_c << "  short " << v.name << " = "
           << static_cast<short>(v.value) << ";\n";
      } else if (v.type == "ushort") {
        os << "static " << constexpr_c << "  unsigned short " << v.name << " = "
           << static_cast<unsigned short>(v.value) << ";\n";
      } else if (v.type == "int") {
        os << "static " << constexpr_c << "  int " << v.name << " = "
           << static_cast<int>(v.value) << ";\n";
      } else if (v.type == "uint") {
        os << "static " << constexpr_c << "  unsigned int " << v.name << " = "
           << static_cast<unsigned int>(v.value) << ";\n";
      } else if (v.type == "long") {
        os << "static " << constexpr_c << "  long " << v.name << " = "
           << static_cast<long>(v.value) << ";\n";
      } else if (v.type == "ulong") {
        os << "static " << constexpr_c << "  unsigned long " << v.name << " = "
           << static_cast<unsigned long>(v.value) << ";\n";
      } else if (v.type == "float") {
        os << "static " << constexpr_c << "  float " << v.name << " = "
           << static_cast<float>(v.value) << ";\n";
      } else if ((v.type == "double") || (v.type == "real")) {
        os << "static " << constexpr_c << "  double " << v.name << " = "
           << static_cast<double>(v.value) << ";\n";
      } else if (v.type == "ldouble") {
        os << "static " << constexpr_c << "  long double " << v.name << " = "
           << static_cast<long double>(v.value) << ";\n";
      } else {
        std::ostringstream msg;
        msg << "writeStaticVariables: "
            << "type '" + v.type << "' of variable '" << v.name
            << "' defined at line '" << v.lineNumber << "' "
            << "is not a supported type for a static variable."
            << "Supported types are short, ushort, int, uint, long, ulong,"
            << "float, double and ldouble.";
        tfel::raise(msg.str());
      }
    }
    os << '\n';
  }  // end of writeStaticVariables

  std::string getMaterialLawLibraryNameBase(
      const MaterialPropertyDescription& mpd) {
    const auto material = mpd.material;
    const auto library = mpd.library;
    if (library.empty()) {
      if (material.empty()) {
        return "MaterialLaw";
      }
      return material;
    }
    return library;
  }  // end of getMaterialLawLibraryNameBase

  void writeF77FUNCMacros(std::ostream& f) {
    auto def = [&f] {
      f << "#ifndef F77_FUNC\n"
        << "#define F77_FUNC(X,Y) X##_\n"
        << "#endif\n"
        << "#ifndef F77_FUNC_\n"
        << "#define F77_FUNC_(X,Y) X##_\n"
        << "#endif\n";
    };
    f << "#if (defined GNU_FORTRAN_COMPILER)\n";
    def();
    f << "#elif (defined INTEL_FORTRAN_COMPILER)\n"
      << "#ifdef _WIN32\n"
      << "#ifndef F77_FUNC\n"
      << "#define F77_FUNC(X,Y) Y\n"
      << "#endif\n"
      << "#ifndef F77_FUNC_\n"
      << "#define F77_FUNC_(X,Y) Y\n"
      << "#endif\n"
      << "#else\n";
    def();
    f << "#endif /* _WIN32 */\n"
      << "#else\n";
    def();
    f << "#endif\n\n";
  }  // end of writeF77FuncMacros

  void writeExportDirectives(std::ostream& file) {
    file
        << "#ifdef _WIN32\n"
        << "#ifndef NOMINMAX\n"
        << "#define NOMINMAX\n"
        << "#endif /* NOMINMAX */\n"
        << "#include <windows.h>\n"
        << "#ifdef small\n"
        << "#undef small\n"
        << "#endif /* small */\n"
        << "#ifndef MFRONT_SHAREDOBJ\n"
        << "#ifdef  MFRONT_COMPILING\n"
        << "#define MFRONT_SHAREDOBJ __declspec(dllexport)\n"
        << "#else /* MFRONT_COMPILING */\n"
        << "#define MFRONT_SHAREDOBJ __declspec(dllimport)\n"
        << "#endif /* MFRONT_COMPILING */\n"
        << "#endif /* MFRONT_SHAREDOBJ */\n"
        << "#else\n"
        << "#ifndef MFRONT_SHAREDOBJ\n"
        << "#ifdef __GNUC__\n"
        << "#define MFRONT_SHAREDOBJ __attribute__((visibility(\"default\")))\n"
        << "#else\n"
        << "#define MFRONT_SHAREDOBJ\n"
        << "#endif /* __GNUC__ */\n"
        << "#endif /* MFRONT_SHAREDOBJ */\n"
        << "#endif /* _WIN32 */\n\n";
  }  // end of writeExportDirectives

  std::string makeUpperCase(const std::string& n) {
    std::string s(n);
    std::string::const_iterator p;
    std::string::iterator p2;
    for (p = n.begin(), p2 = s.begin(); p != n.end(); ++p, ++p2) {
      *p2 = static_cast<char>(toupper(*p));
    }
    return s;
  }  // end of makeUpperCase

  std::string makeLowerCase(const std::string& n) {
    std::string s(n);
    std::string::const_iterator p;
    std::string::iterator p2;
    for (p = n.begin(), p2 = s.begin(); p != n.end(); ++p, ++p2) {
      *p2 = static_cast<char>(tolower(*p));
    }
    return s;
  }  // end of makeLowerCase

  void displayGlossaryEntryCompleteDescription(
      std::ostream& os, const tfel::glossary::GlossaryEntry& e) {
    const auto& k = e.getKey();
    const auto& n = e.getNames();
    const auto& sd = e.getShortDescription();
    const auto& d = e.getDescription();
    if ((!sd.empty()) || (!d.empty())) {
      os << '\n'
         << "For your information, the description of the glossary entry '" << k
         << "' is:\n";
      if (!n.empty()) {
        os << k << ":";
        for (const auto& elem : n) {
          os << " '" << elem << "'";
        }
        os << '\n';
      }
      if (!sd.empty()) {
        os << sd << '\n';
      }
      if (!d.empty()) {
        for (const auto& elem : d) {
          os << elem << '\n';
        }
      }
    }
  }  // end of displayGlossaryEntryCompleteDescription
  
  void addSymbol(std::map<std::string, std::string>& symbols,
                 const std::string& s,
                 const std::string& r) {
    if (symbols.find(s) != symbols.end()) {
      if (symbols.at(s) != r) {
        tfel::raise("addSymbol: symbol '" + s +
                    "' has multiple replacement strings ('" + symbols.at(s) +
                    "' and '" + r + "')");
      }
    }
    symbols.insert({s, r});
  }  // end of addSymbol

}  // end of namespace mfront
