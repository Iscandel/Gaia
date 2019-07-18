///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "Gaia/widgets/DefaultContainer.h"

namespace gaia
{
//std::string DefaultContainer::myWidgetType = "DefaultContainer";

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
DefaultContainer::DefaultContainer(const std::string& name, 
								   int x, 
								   int y, 
								   int width, 
								   int height)
:BaseWidget(name, x, y, width, height)
{
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
DefaultContainer::DefaultContainer(const std::string& name, const IntRect& dimensions)
:BaseWidget(name, dimensions)
{
}

} //end namespace