/*! 
 * \file  GlossaryEntry.cxx
 * \brief
 * \author Helfer Thomas
 * \brief 31 mars 2014
 */

#include<stdexcept>

#include"TFEL/Utilities/StringAlgorithms.hxx"
#include"TFEL/Glossary/GlossaryEntry.hxx"

namespace tfel
{

  namespace glossary
  {
    
    GlossaryEntry::GlossaryEntry(const std::string& k,
				 const std::string& n,
				 const std::string& u,
				 const std::string& t,
				 const std::string& sd,
				 const std::vector<std::string>& d,
				 const std::vector<std::string>& no)
      : key(k),
	names(1u,n),
	unit(u),
	type(t),
	short_description(sd),
	description(d),
	notes(no)
    {
      this->check();
    }

    GlossaryEntry::GlossaryEntry(const std::string& k,
				 const std::string& n,
				 const std::string& u,
				 const std::string& t,
				 const std::string& sd,
				 const std::string& d,
				 const std::string& no)
      : key(k),
	names(1u,n),
	unit(u),
	type(t),
	short_description(sd),
	description(tfel::utilities::tokenize(d,"@^separator^@")),
	notes(tfel::utilities::tokenize(no,"@^separator^@"))
    {
      this->check();
    }

    GlossaryEntry::GlossaryEntry(const std::string& k,
				 const std::vector<std::string>& n,
				 const std::string& u,
				 const std::string& t,
				 const std::string& sd,
				 const std::vector<std::string>& d,
				 const std::vector<std::string>& no)
      : key(k),
	names(n),
	unit(u),
	type(t),
	short_description(sd),
	description(d),
	notes(no)
    {
      this->check();
    }

    GlossaryEntry::GlossaryEntry(const std::string& k,
				 const std::vector<std::string>& n,
				 const std::string& u,
				 const std::string& t,
				 const std::string& sd,
				 const std::string& d,
				 const std::string& no)
      : key(k),
	names(n),
	unit(u),
	type(t),
	short_description(sd),
	description(tfel::utilities::tokenize(d,"@^separator^@")),
	notes(tfel::utilities::tokenize(no,"@^separator^@"))
    {
      this->check();
    }

    GlossaryEntry::GlossaryEntry(const std::string& k,
				 const char * const * const b,
				 const char * const * const e,
				 const std::string& u,
				 const std::string& t,
				 const std::string& sd,
				 const std::vector<std::string>& d,
				 const std::vector<std::string>& no)
      : key(k),
	names(b,e),
	unit(u),
	type(t),
	short_description(sd),
	description(d),
	notes(no)
    {
      this->check();
    }

    GlossaryEntry::GlossaryEntry(const std::string& k,
				 const char * const * const b,
				 const char * const * const e,
				 const std::string& u,
				 const std::string& t,
				 const std::string& sd,
				 const std::string& d,
				 const std::string& no)
      : key(k),
	names(b,e),
	unit(u),
	type(t),
	short_description(sd),
	description(tfel::utilities::tokenize(d,"@^separator^@")),
	notes(tfel::utilities::tokenize(no,"@^separator^@"))
    {
      this->check();
    }

    void
    GlossaryEntry::check(void) const
    {
      using namespace std;
      if(this->names.empty()){
	string msg("GlossaryEntry::check : "
		   "no name specified for key '"+this->getKey()+"'");
	throw(runtime_error(msg));
      }
      if(!(this->type=="scalar")&&(this->type=="vector")&&(this->type=="symmetric tensor")){
	string msg("GlossaryEntry::check : "
		   "unsupported type '"+this->type+"'");
	throw(runtime_error(msg));
      }
    } // end of GlossaryEntry::check

    const std::string&
    GlossaryEntry::getKey(void) const
    {
      return this->key;
    }

    const std::vector<std::string>&
    GlossaryEntry::getNames(void) const
    {
      return this->names;
    }

    const std::string&
    GlossaryEntry::getUnit(void) const
    {
      return this->unit;
    }

    const std::string&
    GlossaryEntry::getType(void) const
    {
      return this->type;
    }

    const std::string&
    GlossaryEntry::getShortDescription(void) const
    {
      return this->short_description;
    }

    const std::vector<std::string>&
    GlossaryEntry::getDescription(void) const
    {
      return this->description;
    }

    const std::vector<std::string>&
    GlossaryEntry::getNotes(void) const
    {
      return this->notes;
    }

    GlossaryEntry::operator const std::string& () const
    {
      return this->key;
    } // end of operator std::string

    bool
    operator < (const GlossaryEntry& e1,
	        const GlossaryEntry& e2)
    {
      return e1.key < e2.key;
    }

    bool
    operator != (const std::string& e1,
		 const GlossaryEntry& e2)
    {
      return e1 != e2.key;
    }

    bool
    operator != (const GlossaryEntry& e1,
		 const std::string& e2)
    {
      return e1.key != e2;
    }

    bool
    operator == (const std::string& e1,
		 const GlossaryEntry& e2)
    {
      return e1 == e2.key;
    }

    bool
    operator == (const GlossaryEntry& e1,
		 const std::string& e2)
    {
      return e1.key == e2;
    }

  } // end of namespace glossary

} // end of namespace tfel