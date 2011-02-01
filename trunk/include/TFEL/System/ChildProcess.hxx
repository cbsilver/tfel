/*! 
 * \file  ChildProcess.hxx
 * \brief
 * \author Helfer Thomas
 * \brief 27 avr 2009
 */

#ifndef _LIB_CHILDPROCESS_H_
#define _LIB_CHILDPROCESS_H_ 

#include<cstdlib>
#include<cstring>
#include<memory>

#include<sys/types.h>
#include<unistd.h>


#include"TFEL/Config/TFELConfig.hxx"
#include"TFEL/System/SystemError.hxx"

namespace tfel
{

  namespace system
  {

    /*!
     * base structure for child processes
     */
    struct TFEL_VISIBILITY_EXPORT ChildProcess
    {
      /*!
       * \param in  : input stream
       * \param out : output stream
       */
      ChildProcess(const int,
		   const int);
      /*!
       * \param in  : input stream
       * \param out : output stream
       */
      virtual
      void execute(const int,
		   const int) = 0;
      
      void setPid(const pid_t);
      pid_t getPid(void) const;
      int
      getOutputStream(void) const;
      int
      getInputStream(void) const;
      virtual ~ChildProcess();
    protected:
      pid_t pid;
      int inputStream;
      int outputStream;
    }; // end of struct ChildProcess

    struct TFEL_VISIBILITY_EXPORT ChildProcessCreationFailedException
      : public SystemError
    {
      ChildProcessCreationFailedException();
    }; // end of struct ChildProcessCreationFailedException

    template<typename T>
    T *
    createChildProcess()
    {
      using namespace std;
      int toChild[2];
      int toFather[2];
      pid_t pid;
      if(::pipe(toChild)==-1){
	throw(ChildProcessCreationFailedException());
      }
      if(::pipe(toFather)==-1){
	throw(ChildProcessCreationFailedException());
      }
      auto_ptr<T> childProcess = auto_ptr<T>(new T(toChild[1],toFather[0]));
      pid = ::fork();
      if(pid==-1){
	throw(ChildProcessCreationFailedException());
      }
      if(pid==0){
	// child
	if(::close(toChild[1])==-1){
	  exit(EXIT_FAILURE);
	}
	if(::close(toFather[0])==-1){
	  exit(EXIT_FAILURE);
	}
	childProcess->execute(toChild[0],toFather[1]);
	exit(EXIT_SUCCESS);
      }
      childProcess->setPid(pid);
      if(::close(toChild[0])==-1){
	throw(ChildProcessCreationFailedException());
      }
      if(::close(toFather[1])==-1){
	throw(ChildProcessCreationFailedException());
      }
      return childProcess.release();
    } // end of createChildProcess

  } // end of namespace system
    
} // end of namespace tfel

#endif /* _LIB_CHILDPROCESS_H */
