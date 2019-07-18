///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "Gaia/widgets/ISelectable.h"

namespace gaia
{
//=============================================================================
///////////////////////////////////////////////////////////////////////////////
ISelectable::ISelectable(void)
:myIsSelected(false)
{
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
ISelectable::~ISelectable(void)
{
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void ISelectable::setSelected(bool s)
{
	if(s)
	{
		if(!isSelected())
		{
			myIsSelected = true;

			//Let the derived classes show and know they are selected
			onSelected();

			//We unselect the others
			if(myGroup)
			{
				std::vector<ISelectable*>& vec = myGroup->getElements();
				for(unsigned int i = 0; i < vec.size(); i++)
				{
					if(vec[i] != this)
					{
						vec[i]->setSelected(false);
					}
				}
			}
		}
	}
	else
	{
		if(isSelected())
		{
			myIsSelected = false;
		
			//Let the derived classes show and know they are unselected
			onUnselected();
		}
	}
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void ISelectable::joinGroup(PtrSelectableWidgetGroup p)
{
	myGroup = p;
	p->add(this);
}

};
