/*!
 * \file   LawFunction.hxx
 * \brief  This file declares the LawFunction class
 * \author Helfer Thomas
 * \date   06 mai 2008
 */

#ifndef _LIB_LAWFUNCTION_H_
#define _LIB_LAWFUNCTION_H_ 

namespace mfront
{

  struct LawFunction
  {
    std::string body;
    std::string cbody;
    unsigned short line;
    bool modified;
  }; // end of struct LawFunction

} // end of namespace mfront

#endif /* _LIB_LAWFUNCTION_H */

