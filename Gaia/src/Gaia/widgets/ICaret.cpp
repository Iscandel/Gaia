///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "Gaia/widgets/ICaret.h"
#include "Gaia/tools/Logger.h"

namespace gaia
{
ICaret::ICaret()
:myCaret(0)
//,myIsDragging(false)
,myFirstSelection(0)
,myLastSelection(0)
{
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void ICaret::setCaretPosition(unsigned int pos, size_t textLength)
{	
	if(pos <= textLength)
		myCaret = pos;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
unsigned int ICaret::getSelectionStart() const 
{
	return std::min(myFirstSelection, myLastSelection);
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
unsigned int ICaret::getSelectionEnd() const 
{
	return std::max(myFirstSelection, myLastSelection);
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void ICaret::setSelectionStart(unsigned int pos)
{
	if(pos <= getSelectionEnd()) 
	{
		if(myFirstSelection == getSelectionStart())
			myFirstSelection = pos;
		else
			myLastSelection = pos;
	}

	myCaret = myLastSelection; //Ok ?
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void ICaret::setSelectionEnd(unsigned int pos) //Add something not to exceed text length
{
	if(pos >= 0 && pos >= getSelectionStart()) 
	{
		if(myFirstSelection == getSelectionEnd())
			myFirstSelection = pos;
		else
			myLastSelection = pos;
	}

	myCaret = myLastSelection; //Ok ?
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void ICaret::moveSelection(int quantity, size_t textLength)
{
	if((int)myLastSelection + quantity < 0)
	{
		ILogger::log(ILogger::INFORMATIVE) << 
			"Caret cannot be moved for selection : quantity " << 
			quantity << " is greater than last selection value : " 
			<< myLastSelection << "\n";
		return;
	}

	myLastSelection += quantity;
	myLastSelection = myLastSelection > textLength ? (unsigned int)textLength : myLastSelection;
	//myLastSelection = myLastSelection < 0 ? 0 : myLastSelection;
	setCaretPosition(myLastSelection, textLength);
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void ICaret::resetSelection()
{
	myLastSelection = myFirstSelection = getCaretPosition();
}

} //end namespace