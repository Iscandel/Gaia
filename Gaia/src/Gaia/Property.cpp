///////////////////////////////////////////////////////////////////////////////
/// Headers
///////////////////////////////////////////////////////////////////////////////
#include "Gaia/Property.h"
#include "Gaia/tools/Exceptions.h"

namespace gaia
{
namespace properties
{
//=============================================================================
///////////////////////////////////////////////////////////////////////////////
Property::Property(const std::string& name)
:myName(name)
{
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
std::string Property::getProperty(const std::string& name)
{
	throw GuiException("Property " + name + " is not implemented");
}

} //end namespace properties

} //end namespace