#ifndef H__FOCUSWIDGETMANAGER_010920110254__H
#define H__FOCUSWIDGETMANAGER_010920110254__H

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include <deque>

#include "Gaia/Config.h"
#include "Gaia/widgets/BaseWidget.h"

namespace gaia
{
///////////////////////////////////////////////////////////////////////////////
/// \brief Focus manager.
///////////////////////////////////////////////////////////////////////////////
class GAIA_DLL FocusWidgetManager
{
public:
	//void setWidgetCatchInputs(PtrWidget w);
	void addWidgetCatchInputs(PtrWidget w);

	PtrWidget getWidgetCaughtInput();

	void releaseWidgetCaughtInput(PtrWidget w);

	PtrWidget getWidgetModal();

	void addModalWidget(PtrWidget w);

	void releaseModalWidget(PtrWidget w);

	void update();

	void clean();

protected:
	typedef std::weak_ptr<BaseWidget> WeakPtrWidget;

	//WeakPtrWidget myWidgetCaughtInputs;
	std::deque<WeakPtrWidget> myWidgetCaughtInputs;

	std::deque<WeakPtrWidget> myModalWidgets;

};

}//end namespace

#endif