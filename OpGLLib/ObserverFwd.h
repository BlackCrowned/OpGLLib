/*
 * ObserverFwd.h
 *
 *  Created on: 01.08.2015
 *      Author: mimoe
 */

#include <OpGLLib/LoggingFwd.h>
#include <OpGLLib/ExceptionFwd.h>

namespace OpGLLib {
namespace Observer {

template<class ...ArgsT> class Subject;
template<class ...ArgsT> class Observer;

typedef Observer<std::string const&, LoggingLevel> LoggingObserver;
typedef Subject<std::string const&, LoggingLevel> LoggingSubject;

typedef Observer<ExceptionType> ExceptionHandlerObserver;
typedef Subject<ExceptionType> ExceptionHandlerSubject;


}

}
