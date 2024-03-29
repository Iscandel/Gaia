#ifndef H__EXCEPTIONS_090620112320__H
#define H__EXCEPTIONS_090620112320__H

#include <exception>
#include <string>
#include <sstream>

#include "Gaia/Config.h"

#ifdef _MSC_VER
	#pragma warning(disable: 4275) // disable warning 4275
#endif


namespace gaia
{
///////////////////////////////////////////////////////////////////////////////
// Base class for exceptions
///////////////////////////////////////////////////////////////////////////////
class GAIA_DLL GuiException : public std::exception 
{
public:
	///////////////////////////////////////////////////////////////////////////
	/// Constructor
	///
	/// \param reason: message explaining the reason of this exception
	///////////////////////////////////////////////////////////////////////////
	GuiException(const std::string& reason = "");

	///////////////////////////////////////////////////////////////////////////
	/// Destructor
	///////////////////////////////////////////////////////////////////////////
	virtual ~GuiException(void) throw();

	///////////////////////////////////////////////////////////////////////////
	/// Returns the d�tailed error.
	///
	/// \return A string explaining why the exception happened.
	///////////////////////////////////////////////////////////////////////////
	virtual const char* what() const throw();

protected:
	std::string myMessage; ///< Some text containing explanations about the error
};

///////////////////////////////////////////////////////////////////////////////
/// Exceptions for non valid arguments provided to functions
///////////////////////////////////////////////////////////////////////////////
class GAIA_DLL IllegalArgument : public GuiException
{
public:
	///////////////////////////////////////////////////////////////////////////////
	/// Constructor
	///
	/// \param reason: message explaining the reason of this exception
	///////////////////////////////////////////////////////////////////////////////
	IllegalArgument(const std::string& reason);
};
};

#ifdef _MSC_VER
	#pragma warning(default: 4275) // enable warning 4275back
#endif

#endif

