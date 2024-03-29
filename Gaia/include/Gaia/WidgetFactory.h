#ifndef H__WIDGETFACTORY_100920111649__H
#define H__WIDGETFACTORY_100920111649__H

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include <string>

#include "Gaia/widgets/WidgetList.h"

namespace gaia
{
class BaseWidget;

///////////////////////////////////////////////////////////////////////////////
/// \brief Base class of widget factory.
///////////////////////////////////////////////////////////////////////////////
class GAIA_DLL WidgetFactory
{
public:
	///////////////////////////////////////////////////////////////////////////
	/// \brief Constructor.
	///  
	/// \param type : Type name of the widget to be handled by this factory.
	///////////////////////////////////////////////////////////////////////////
	WidgetFactory(const std::string& type);

	///////////////////////////////////////////////////////////////////////////
	// \brief Virtual destructor.
	///////////////////////////////////////////////////////////////////////////
	virtual ~WidgetFactory(void);

	///////////////////////////////////////////////////////////////////////////
	/// \brief Returns the widget type name created by this factory.
	///
	/// \return Widget type.
	///////////////////////////////////////////////////////////////////////////
	const std::string& getWidgetType() const {return myType;}

	///////////////////////////////////////////////////////////////////////////
	// \brief Creates a widget with the given name.
	///////////////////////////////////////////////////////////////////////////
	virtual PtrWidget create(const std::string& name) = 0;

protected:
	std::string myType;
};

typedef std::shared_ptr<WidgetFactory> PtrWidgetFactory; ///< Typedef for smart pointers to widget factory.

///////////////////////////////////////////////////////////////////////////////
/// \brief Constructs a widget of the given type.
///
/// Usage:
///
/// \code
/// PtrWidgetFactory p(new TplWidgetFactory<SomeWidget>);
/// WidgetFactoryManager::getInstance()->addFactory(p);
/// \endcode
///
/// \see addFactory
///////////////////////////////////////////////////////////////////////////////
template<class T>
class TplWidgetFactory : public WidgetFactory
{
public:
	///////////////////////////////////////////////////////////////////////////
	/// \brief Constructor.
	///////////////////////////////////////////////////////////////////////////
	TplWidgetFactory() 
		:WidgetFactory(WidgetStaticType<T>::get())//::myWidgetType ) 
	{
	}

	///////////////////////////////////////////////////////////////////////////
	/// \brief Creates a new widget with the given name.
	///
	/// \param name : Unique name to give to this widget.
	///
	/// \return A smart pointer to the newly created widget.
	///////////////////////////////////////////////////////////////////////////
	PtrWidget create(const std::string& name)
	{
		//T* widget = new T(name);
		//ThemeWidget* look = ThemeWidgetsManager::getInstance()->getLook(name);

		//if(look)
		//	look->initWidget<T>(widget); //?
		//return PtrWidget(widget);

		return PtrWidget(new T(name));
	}
protected:
	std::string myType; ///< Widget type
};

} //end namespace


#endif