#ifndef H__TEXTPROPERTIES_250920110103__H
#define H__TEXTPROPERTIES_250920110103__H

#include "Gaia/Property.h"

namespace gaia
{
namespace properties
{
///////////////////////////////////////////////////////////////////////////////
// \brief Text property of Text widget
///////////////////////////////////////////////////////////////////////////////
class GAIA_DLL LabelSetText : public Property
{
public:
	///////////////////////////////////////////////////////////////////////////
	/// \brief Constructor.
	///
	/// \param name : Property name.
	///////////////////////////////////////////////////////////////////////////
	LabelSetText(const std::string& nom);

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
// \brief Property text color of Text.
///////////////////////////////////////////////////////////////////////////////
class GAIA_DLL LabelSetTextColor : public Property
{
public:
	///////////////////////////////////////////////////////////////////////////
	/// \brief Constructor.
	///
	/// \param name : Property name.
	///////////////////////////////////////////////////////////////////////////
	LabelSetTextColor(const std::string& name);

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
//// \brief "font" property of Text.
/////////////////////////////////////////////////////////////////////////////////
//class GAIA_DLL LabelSetFont : public Property
//{
//public:
//	///////////////////////////////////////////////////////////////////////////
//	/// \brief Constructor.
//	///
//	/// \param name : Property name.
//	///////////////////////////////////////////////////////////////////////////
//	LabelSetFont(const std::string& name);
//
//	//@override
//	///////////////////////////////////////////////////////////////////////////
//	/// \brief Applies the property to the widget. You shou
//	///
//	/// \param target : The widget we want to apply the property.
//	/// \param value : A string describing the action to set. 
//	///////////////////////////////////////////////////////////////////////////
//	virtual void setProperty(BaseWidget& target, const std::string& value); 
//};

///////////////////////////////////////////////////////////////////////////////
// \brief "fontSize" property of Text.
///////////////////////////////////////////////////////////////////////////////
class GAIA_DLL LabelSetFontSize : public Property
{
public:
	///////////////////////////////////////////////////////////////////////////
	/// \brief Constructor.
	///
	/// \param name : Property name.
	///////////////////////////////////////////////////////////////////////////
	LabelSetFontSize(const std::string& name);

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
/// \brief This property adjusts the size of the widget.
/// 
/// If the value is 0, the adjustSize() is called.
/// Otherwise, adjustSize(value) is called.
///////////////////////////////////////////////////////////////////////////////
class GAIA_DLL LabelAdjustSize : public Property
{
public:
	///////////////////////////////////////////////////////////////////////////
	/// \brief Constructor.
	///
	/// \param name : Property name.
	///////////////////////////////////////////////////////////////////////////
	LabelAdjustSize(const std::string& name);

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