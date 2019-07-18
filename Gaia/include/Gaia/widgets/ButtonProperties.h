#ifndef H__IMAGEBUTTON_240920110014__H
#define H__IMAGEBUTTON_240920110014__H

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "Gaia/Property.h"

namespace gaia
{
namespace properties
{
///////////////////////////////////////////////////////////////////////////////
/// \brief "image" property of widget. 
///
/// You have to specify the name of the associated sheet, and the name of the 
/// image, for the 3 images.
///
/// \code
/// "imageSheet1/image1|imageSheet2/image2|imageSheet3/image3"
/// \endcode
///////////////////////////////////////////////////////////////////////////////
class GAIA_DLL ButtonSetImages : public Property
{
public:
	///////////////////////////////////////////////////////////////////////////
	/// \brief Constructor.
	///
	/// \param name : Property name.
	///////////////////////////////////////////////////////////////////////////
	ButtonSetImages(const std::string& nom);

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
/// \brief "text" property of widget. 
///
/// Apply the specified text.
///////////////////////////////////////////////////////////////////////////////
class GAIA_DLL ButtonSetText : public Property
{
public:
	///////////////////////////////////////////////////////////////////////////
	/// \brief Constructor.
	///
	/// \param name : Property name.
	///////////////////////////////////////////////////////////////////////////
	ButtonSetText(const std::string& nom);

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
/// \brief "textAlignement" property of widget. 
///
/// Apply the specified text.
///////////////////////////////////////////////////////////////////////////////
class GAIA_DLL ButtonSetTextAlignement : public Property
{
public:
	///////////////////////////////////////////////////////////////////////////
	/// \brief Constructor.
	///
	/// \param name : Property name.
	///////////////////////////////////////////////////////////////////////////
	ButtonSetTextAlignement(const std::string& nom);

	//@override
	///////////////////////////////////////////////////////////////////////////
	/// \brief Applies the property to the widget. You shou
	///
	/// \param target : The widget we want to apply the property.
	/// \param value : A string describing the action to set. 
	///////////////////////////////////////////////////////////////////////////
	virtual void setProperty(BaseWidget& target, const std::string& value); 
};

}
}

#endif