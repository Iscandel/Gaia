#ifndef H__RADIOBUTTON_210620122334__H
#define H__RADIOBUTTON_210620122334__H

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "Gaia/widgets/ISelectable.h"
#include "Gaia/widgets/BaseWidget.h"

namespace gaia
{
///////////////////////////////////////////////////////////////////////////////
/// \brief RadioButton widget.
///////////////////////////////////////////////////////////////////////////////
class GAIA_DLL RadioButton : public BaseWidget, public ISelectable
{
public:
	///////////////////////////////////////////////////////////////////////////
	/// \brief Constructor.
	///
	/// \param name: Widget name. Must be absolutely unique.
	///
	/// \param x: X position relatively to the parent widget (or the window if
	/// it is the top level widget).
	///
	/// \param y: Y position relatively to the parent widget (or the window if
	/// it is the top level widget).
	///
	/// \param width: Width of the widget.
	///
	/// \param height: Height of the widget.
	///////////////////////////////////////////////////////////////////////////
	RadioButton(const std::string& name = "", 
				 int x = 0, 
				 int y = 0 , 
				 int width = 0, 
				 int height = 0);

	///////////////////////////////////////////////////////////////////////////
	/// \brief Constructor.
	///
	/// \param name: Widget name. Must be absolutely unique.
	///
	/// \param dimensions: Rectangle defining the widget size (top left 
	/// position is relative to parent widget, or the screen if the widget is 
	/// the top level widget).
	///////////////////////////////////////////////////////////////////////////
	RadioButton(const std::string& nom, const IntRect& dimensions);

	//@override
	///////////////////////////////////////////////////////////////////////////
	/// \brief Called when the widget is selected.
	///////////////////////////////////////////////////////////////////////////
	virtual void onSelected();

	//@override
	///////////////////////////////////////////////////////////////////////////
	/// \brief Called when the widget is unselected.
	///////////////////////////////////////////////////////////////////////////
	virtual void onUnselected();

	//@override
	///////////////////////////////////////////////////////////////////////////////
	/// \brief Can be overriden by children. Handles in a generic way the response to a 
	/// mouse event.
	///////////////////////////////////////////////////////////////////////////////
	virtual bool handleMouseReleased_impl(MouseEvent& ev);

	///////////////////////////////////////////////////////////////////////////
	/// \brief Subscribes to a "state changed event" for this widget. State
	/// actually changes when the checkbox becomes checked or unchecked.
	///
	/// \param fucntion : Function to call when the event is triggered.
	/// \param instance : Object to which the function belongs. Let it to NULL
	/// or don't specify if you use a free function.
	///////////////////////////////////////////////////////////////////////////
	void subscribeStateChanged(const GenericFunction& f)
	{E_onStateChanged = f;}

	/////////////////////////////////////////////////////////////////////////////
	/// \brief fired when the radio button state has just changed.
	/////////////////////////////////////////////////////////////////////////////
	void onStateChanged();

protected:
	bool myIsStateChanging; ///< Indicates whether the state is currently changing

	GenericFunction E_onStateChanged;
};

///////////////////////////////////////////////////////////////////////////////
/// \brief We register the static LinkedLabels type.
///////////////////////////////////////////////////////////////////////////////
GAIA_REGISTER_TYPE(RadioButton)

}; //end namespace

#endif