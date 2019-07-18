///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "Gaia/widgets/NumericTextBox.h"

#include <sstream>

namespace gaia
{
//const std::string NumericTextBox::myWidgetType = "NumericTextBox";

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
NumericTextBox::NumericTextBox(const std::string& name, 
								   int x, 
								   int y, 
								   int width, 
								   int height)
:TextBox(name, x, y, width, height)
,myTypeNumber(DECIMAL)
{
	copyProperties<NumericTextBox>();
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
NumericTextBox::NumericTextBox(const std::string& name, const IntRect& dimensions)
:TextBox(name, dimensions)
,myTypeNumber(DECIMAL)
{
	copyProperties<NumericTextBox>();
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
bool NumericTextBox::handleTextEntered_impl(KeyboardEvent& ev)
{
	if(isNumeric(ev.getCharacter()) || ev.getCharacter() == '\b')
			return(TextBox::handleTextEntered_impl(ev));

	ev.use(); 
	return true;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
bool NumericTextBox::isNumeric(int character)
{
	if(myTypeNumber == DECIMAL && character == '.')
		return true;

	return(character == '0' || character == '1' || character == '2' ||
		   character == '3' || character == '4' || character == '5' ||
		   character == '6' || character == '7' || character == '8' ||
		   character == '9');
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
bool NumericTextBox::getValue(double& value)
{
	std::istringstream string(myText);
	string >> value;
	return !string.fail();
}

} //end namespaces
	
