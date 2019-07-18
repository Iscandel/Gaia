#include "Gaia/FocusWidgetManager.h"

namespace gaia
{
//void FocusWidgetManager::setWidgetCatchInputs(PtrWidget w)
void FocusWidgetManager::addWidgetCatchInputs(PtrWidget w)
{
	//if(myWidgetCaughtInputs.lock() != w)
	//{
	//	//MonWidgetCaptureEntrees->onCapturePerdue();
	//	myWidgetCaughtInputs = w;
	//	//MonWidgetCaptureEntrees->onCaptureGagnee();
	//}

	if(w)
	{
		//Check previous existence
		for(unsigned int i = 0; i < myWidgetCaughtInputs.size(); i++)
		{
			if(myWidgetCaughtInputs[i].lock() == w)
				return;
		}

		myWidgetCaughtInputs.push_back(WeakPtrWidget(w));
	}
}

PtrWidget FocusWidgetManager::getWidgetCaughtInput()
{
	//return myWidgetCaughtInputs.lock();

	//Let's return the first visible modal widget of the stack
	for(size_t i = myWidgetCaughtInputs.size(); i > 0; i--)
	{
		PtrWidget tmp = myWidgetCaughtInputs[i - 1].lock();
		if(tmp)
		{
			if(tmp->isVisible()) //not visible case should not occur with catch input
			{
				return tmp;
			}
		}
	}

	return PtrWidget();
}

void FocusWidgetManager::releaseWidgetCaughtInput(PtrWidget w)
{
	std::deque<WeakPtrWidget>::iterator it = myWidgetCaughtInputs.begin();
	while(it != myWidgetCaughtInputs.end())
	{
		if((*it).lock() == w)
		{
			it = myWidgetCaughtInputs.erase(it);
			return;
		}
		else
		{
			++it;
		}
	}
}

PtrWidget FocusWidgetManager::getWidgetModal()
{
	//Let's return the first visible modal widget of the stack
	for(size_t i = myModalWidgets.size(); i > 0; i--)
	{
		PtrWidget tmp = myModalWidgets[i - 1].lock();
		if(tmp)
		{
			if(tmp->isVisible())
			{
				return tmp;
			}
		}
	}

	return PtrWidget();
	//return MonWidgetModal.empty() ? PtrWidget() : MonWidgetModal.top()->isVisible() ? MonWidgetModal.top() : PtrWidget();
}

void FocusWidgetManager::addModalWidget(PtrWidget w)
{
	if(w)
	{
		//Check previous existence
		for(unsigned int i = 0; i < myModalWidgets.size(); i++)
		{
			if(myModalWidgets[i].lock() == w)
				return;
		}

		myModalWidgets.push_back(WeakPtrWidget(w));
	}
}

void FocusWidgetManager::releaseModalWidget(PtrWidget w)
{
	//assert(MonWidgetModal.top() == w && 
	//	"On ne peut relacher la modalité que du widget de tête");

	//if(!myModalWidgets.empty() && w == myModalWidgets.back())
	//{
	//	myModalWidgets.pop_back();
	//}
	std::deque<WeakPtrWidget>::iterator it = myModalWidgets.begin();
	while(it != myModalWidgets.end())
	{
		if((*it).lock() == w)
		{
			it = myModalWidgets.erase(it);
			return;
		}
		else
		{
			++it;
		}
	}
}

void FocusWidgetManager::update()
{
	std::deque<WeakPtrWidget>::iterator it = myModalWidgets.begin();
	while(it != myModalWidgets.end())
	{
		if((*it).expired())
		{
			it = myModalWidgets.erase(it);
		}
		else
		{
			++it;
		}
	}

	it = myWidgetCaughtInputs.begin();
	while(it != myWidgetCaughtInputs.end())
	{
		if((*it).expired())
		{
			it = myWidgetCaughtInputs.erase(it);
		}
		else
		{
			++it;
		}
	}
}
void FocusWidgetManager::clean()
{
	//myWidgetCaughtInputs.reset();
	myWidgetCaughtInputs.clear();
	myModalWidgets.clear();
}

} //end namespace