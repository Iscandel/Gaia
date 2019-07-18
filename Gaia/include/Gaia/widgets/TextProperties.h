#ifndef H__TEXTBOXPROPERTIES_250920110208__H
#define H__TEXTBOXPROPERTIES_250920110208__H

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "Gaia/Property.h"

namespace gaia
{
namespace properties
{
///////////////////////////////////////////////////////////////////////////////
// \brief "text" property of Text widgets.
///////////////////////////////////////////////////////////////////////////////
class GAIA_DLL TextSetText : public Property
{
public:
	///////////////////////////////////////////////////////////////////////////
	/// \brief Constructor.
	///
	/// \param name : Property name.
	///////////////////////////////////////////////////////////////////////////
	TextSetText(const std::string& name);

	//@override
	///////////////////////////////////////////////////////////////////////////
	/// \brief Applies the property to the widget. You shou
	///
	/// \param target : The widget we want to apply the property.
	/// \param value : A string describing the action to set. 
	///////////////////////////////////////////////////////////////////////////
	virtual void setProperty(BaseWidget& target, const std::string& value); 
};

///////////////////////////////////////////////////////////////////////////////
// \brief "textColor" property of Text widgets.
///////////////////////////////////////////////////////////////////////////////
class GAIA_DLL TextSetTextColor : public Property
{
public:
	///////////////////////////////////////////////////////////////////////////
	/// \brief Constructor.
	///
	/// \param name : Property name.
	///////////////////////////////////////////////////////////////////////////
	TextSetTextColor(const std::string& name);

	//@override
	///////////////////////////////////////////////////////////////////////////
	/// \brief Applies the property to the widget. You shou
	///
	/// \param target : The widget we want to apply the property.
	/// \param value : A string describing the action to set. 
	///////////////////////////////////////////////////////////////////////////
	virtual void setProperty(BaseWidget& target, const std::string& value); 
};

/////////////////////////////////////////////////////////////////////////////////
//// \brief "font" property of Text widgets.
/////////////////////////////////////////////////////////////////////////////////
class GAIA_DLL TextSetFont : public Property
{
public:
	///////////////////////////////////////////////////////////////////////////
	/// \brief Constructor.
	///
	/// \param name : Property name.
	///////////////////////////////////////////////////////////////////////////
	TextSetFont(const std::string& name);

	//@override
	///////////////////////////////////////////////////////////////////////////
	/// \brief Applies the property to the widget. You shou
	///
	/// \param target : The widget we want to apply the property.
	/// \param value : A string describing the action to set. 
	///////////////////////////////////////////////////////////////////////////
	virtual void setProperty(BaseWidget& target, const std::string& value); 
};

///////////////////////////////////////////////////////////////////////////////
// \brief "fontSize" property of Text widgets.
///////////////////////////////////////////////////////////////////////////////
class GAIA_DLL TextSetFontSize : public Property
{
public:
	///////////////////////////////////////////////////////////////////////////
	/// \brief Constructor.
	///
	/// \param name : Property name.
	///////////////////////////////////////////////////////////////////////////
	TextSetFontSize(const std::string& name);

	//@override
	///////////////////////////////////////////////////////////////////////////
	/// \brief Applies the property to the widget. You shou
	///
	/// \param target : The widget we want to apply the property.
	/// \param value : A string describing the action to set. 
	///////////////////////////////////////////////////////////////////////////
	virtual void setProperty(BaseWidget& target, const std::string& value); 
};

} //end namespace properties

} //end namespace

#endif