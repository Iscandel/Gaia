#include "Gaia/XMLLoader/XMLGuiLoader.h"
#include "Gaia/GuiManager.h"
#include "Gaia/tools/Logger.h"
#include "Gaia/tools/Tools.h"
#include "tinyxml/tinyxml.h"

#include <iostream>
#include <sstream>

namespace gaia
{
namespace xml
{
/////////////////////////////////////////////////////////////////////////////////
//// Renvoie un rectangle de nouvelles dimensions relativement à la taille de la 
//// fenêtre. Les dimensions de base sont données pour du 640*480
/////////////////////////////////////////////////////////////////////////////////
//IntRect redimensionner(float x, float y, float largeur, float hauteur)
//{
//	int largeurFenetre = gaia::GuiManager::getInstance()->getTailleFenetreX();
//	int hauteurFenetre = gaia::GuiManager::getInstance()->getTailleFenetreY();
//
//	//Les ratios x/y de la fenêtre courante par rapport à des tailles de 640*480
//	float ratioX = largeurFenetre / 640.f;
//	float ratioY = hauteurFenetre / 480.f;
//
//	IntRect res;
//
//	//Si x est entre 0 et 1, ce sont des pourcentages de position dans la fenêtre,
//	//sinon, ce sont des positions dans une fenêtre de taille 640*480
//	//if(x > 0.f && x < 1.f) res.Left = utiles::maths::arrondiProche(x * largeurFenetre);
//	//else				   res.Left = utiles::maths::arrondiProche(x * ratioX);
//	if(x > 0.f && x < 1.f) res.x = utiles::maths::arrondiProche(x * largeurFenetre);
//	else				   res.x = utiles::maths::arrondiProche(x * ratioX);
//
//	//if(y > 0.f && y < 1.f) res.Top = utiles::maths::arrondiProche(y * hauteurFenetre);
//	//else				   res.Top = utiles::maths::arrondiProche(y * ratioY);
//	if(y > 0.f && y < 1.f) res.y = utiles::maths::arrondiProche(y * hauteurFenetre);
//	else				   res.y = utiles::maths::arrondiProche(y * ratioY);
//
//	//if(largeur > 0.f && largeur < 1.f) 
//	//	res.Right = utiles::maths::arrondiProche(res.Left + largeur  * largeurFenetre);
//	//else 
//	//	res.Right = utiles::maths::arrondiProche(res.Left + largeur * ratioX);
//	if(largeur > 0.f && largeur < 1.f) 
//		res.largeur = utiles::maths::arrondiProche(largeur  * largeurFenetre);
//	else 
//		res.largeur = utiles::maths::arrondiProche(largeur * ratioX);
//
//	//if(hauteur > 0.f && hauteur < 1.f) 
//	//	res.Bottom = utiles::maths::arrondiProche(res.Top + hauteur * hauteurFenetre);
//	//else
//	//	res.Bottom = utiles::maths::arrondiProche(res.Top + hauteur * ratioY);
//	if(hauteur > 0.f && hauteur < 1.f) 
//		res.hauteur = utiles::maths::arrondiProche(hauteur * hauteurFenetre);
//	else
//		res.hauteur = utiles::maths::arrondiProche(hauteur * ratioY);
//
//	return res;
//	
//	
//}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
//void resizeAbsolute(PtrWidget widget, 
//					PtrWidget parent, 
//					int x, 
//					int y, 
//					int width, 
//					int height, 
//					bool keepRelative)
//{
//	float ratioX = gaia::GuiManager::getInstance()->getRatioX();
//	float ratioY = gaia::GuiManager::getInstance()->getRatioY();
//
//	if(keepRelative)
//	{
//		int newX = tools::closestInt(x * ratioX);
//		int newWidth = tools::closestInt(width * ratioX);
//		int newY = tools::closestInt(y * ratioY);
//		int newHeight = tools::closestInt(height * ratioY);
//
//		widget->setDimensions(newX, newY, newWidth, newHeight);
//
//		if(parent)
//		{
//			int parentWidth = parent->getWidth();
//			int parentHeight = parent->getHeight();
//
//			double relativeX = newX / (parentWidth + 0.000001);
//			double relativeWidth = newWidth / (parentWidth + 0.000001);
//			double relativeY = newY / (parentHeight + 0.000001);
//			double relativeHeight = newHeight / (parentWidth + 0.000001);
//
//			Rect<double> rect(relativeX, 
//							  relativeY, 
//							  relativeWidth, 
//							  relativeHeight);
//
//			widget->setRelativeDimensions(rect);
//		}
//	}
//	else
//	{
//		widget->setDimensions(x, y, width, height);
//	}
//}
//
////=============================================================================
/////////////////////////////////////////////////////////////////////////////////
//void resizeRelative(PtrWidget widget, double x, double y, double width, double height)
//{
//	Rect<double> rect(x, y, width, height);
//	widget->setRelativeDimensions(rect);
//}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
XMLGuiLoader::XMLGuiLoader(void)
{
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
XMLGuiLoader::~XMLGuiLoader(void)
{
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
bool handleWidget(::TiXmlElement* widgetNode, bool reload, PtrWidget parent)
{
	std::string widgetType = widgetNode->Attribute("type");
	std::string widgetName = widgetNode->Attribute("name");

	PtrWidget child;
	if(parent)
	{
		if(!reload)
		{
			child = parent->createChild(widgetType, widgetName);
			if(!child)
				throw gaia::GuiException("Child " + widgetName + "not created");
		}
		else
		{
			parent->reloadChild(widgetType, widgetName);
		}
	}
	else
	{
		if(!reload)
		{
			child = gaia::GuiManager::getInstance()->createWidget(widgetType, widgetName);
			if(!child)
					throw gaia::GuiException("Child " + widgetName + "not created");
			
			gaia::GuiManager::getInstance()->getRootWidget()->add(child);
		}
		else
		{
			child = gaia::GuiManager::getInstance()->reloadWidget(widgetType, widgetName);
		}
	}

	::TiXmlElement* element = widgetNode->FirstChildElement();
	for(element; element; element = element->NextSiblingElement())
	{
		std::string key = element->ValueStr();

		//If there are children
		if(key == "children")
		{
			::TiXmlElement* childNode = element->FirstChildElement();
			if(!handleWidget(childNode, reload, child))
				return false;
		}
		else if(key == "dimensions")
		{
			if(!handleDimensions(child, parent, element))
				return false;
		}
		else
		{		
			handleProperty(child, key, element);
		}
	}

	return true;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void handleProperty(PtrWidget widget, const std::string& key, TiXmlElement* element)
{
	std::string value(element->GetText());

	//Apply the property
	widget->setProperty(key, value);
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
LayoutInfos constructLayoutInfos2(TiXmlElement* widgetPosAttributes)
{
	LayoutInfos infos;

	for(; widgetPosAttributes; widgetPosAttributes = widgetPosAttributes->NextSiblingElement())
	{
		std::string key = widgetPosAttributes->ValueStr();

		if(key == "fullDimensions")
		{
			std::string type = widgetPosAttributes->Attribute("type");
			LayoutInfos::PositionType enumType = LayoutInfos::FIXED;
			if(type == "fixed")
				enumType = LayoutInfos::FIXED;
			else if(type == "relative")
				enumType = LayoutInfos::RELATIVE;
			else if(type == "uniform")
				enumType = LayoutInfos::UNIFORM;
			else
			{
				ILogger::log(ILogger::ERRORS) << 
					"XML look loader : cannot deduce layout type : " << type << ".\n";
			}
			//std::string* value = widgetPosAttributes->Attribute("screenDependent");
			std::string value = widgetPosAttributes->GetText();
			std::vector<std::string> splitted = tools::split(value, ";");

			if(splitted.size() != 4)
			{
				ILogger::log(ILogger::ERRORS) << 
					"XML look loader : fullDimensions hasn't got 4 argument : " << value << ".\n";
			}

			infos.setPosInfos(enumType, splitted[0] + ";" + splitted[1]);
			infos.setWidthInfos(enumType, splitted[2]);
			infos.setHeightInfos(enumType, splitted[3]);
		}
		else if(key == "position")
		{
			std::string type = widgetPosAttributes->Attribute("type");
			std::string value = widgetPosAttributes->GetText();
			if(type == "fixed")
				infos.setPosInfos(LayoutInfos::FIXED, value);
			else if(type == "relative")
				infos.setPosInfos(LayoutInfos::RELATIVE, value);
			else if(type == "uniform")
				infos.setPosInfos(LayoutInfos::UNIFORM, value);
		}
		else if (key == "width")
		{
			std::string type = widgetPosAttributes->Attribute("type");
			std::string value = widgetPosAttributes->GetText();
			if(type == "fixed")
				infos.setWidthInfos(LayoutInfos::FIXED, value);
			else if(type == "relative")
				infos.setWidthInfos(LayoutInfos::RELATIVE, value);
			else if(type == "uniform")
				infos.setWidthInfos(LayoutInfos::UNIFORM, value);
		}
		else if(key == "height")
		{
			std::string type = widgetPosAttributes->Attribute("type");
			std::string value = widgetPosAttributes->GetText();
			if(type == "fixed")
				infos.setHeightInfos(LayoutInfos::FIXED, value);
			else if(type == "relative")
				infos.setHeightInfos(LayoutInfos::RELATIVE, value);
			else if(type == "uniform")
				infos.setHeightInfos(LayoutInfos::UNIFORM, value);
		}
		else
		{
			ILogger::log(ILogger::INFORMATIVE) << "XML look loading : "
					<< "unknown key " << key << " ignored.\n";
		}
	}

	return infos;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
bool handleDimensions(PtrWidget widget, PtrWidget parent, TiXmlElement* element)
{
	//std::string* attribute = element->Attribute("layout");
	const char* attribute = element->Attribute("layout");
	if(attribute && !tools::stringToBool(attribute))// ok???????????????????????????????????????
	{
		TiXmlElement* widgetPosAttributes = element->FirstChildElement();
		//std::string key = widgetPosAttributes->ValueStr();

		//if(key == "fullDimensions")

		//std::string* value = widgetPosAttributes->Attribute("screenDependent");
		std::string value = widgetPosAttributes->GetText();
		std::vector<std::string> splitted = tools::split(value, ";");

		if(splitted.size() != 4)
		{
			ILogger::log(ILogger::ERRORS) << 
				"XML look loader : fullDimensions hasn't got 4 argument : " << value << ".\n";
			return false;
		}

		widget->setDimensions(tools::stringToNum<int>(splitted[0]), 
							  tools::stringToNum<int>(splitted[1]), 
							  tools::stringToNum<int>(splitted[2]), 
							  tools::stringToNum<int>(splitted[3]));
	}
	else
	{
		TiXmlElement* widgetPosAttributes = element->FirstChildElement();

		LayoutInfos infos = constructLayoutInfos2(widgetPosAttributes);
		PtrLayoutInfos pInfos(new LayoutInfos(infos));

		widget->setLayoutInfos(pInfos);
	}

	return true;
	//std::string typePosition = element->Attribute("type");

	//std::string position(element->GetText());

	////We parse the position
	//std::istringstream stream(position);
	//double x, y, width, height;
	//stream >> x >> y >> width >> height;

	//if(stream.fail())
	//{
	//	ILogger::log(ILogger::ERRORS) << "XML GUI loading : "
	//		<< "Cannot parse widget position\n";
	//	return false;
	//}

	//if(typePosition == "absolute")
	//{
	//	std::string keepRelative = element->Attribute("keepAsRelative");
	//	bool bKeepRelative = tools::stringToBool(keepRelative);

	//	resizeAbsolute(widget, 
	//				   parent, 
	//				   static_cast<int>(x), 
	//				   static_cast<int>(y), 
	//				   static_cast<int>(width), 
	//				   static_cast<int>(height), 
	//				   bKeepRelative);
	//}
	//else
	//{
	//	resizeRelative(widget, x, y, width, height);
	//}

	//return true;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
bool XMLGuiLoader::loadGUI(const std::string& path, bool reload)
{
	TiXmlDocument doc(path.c_str());
	if(!doc.LoadFile())
	{
		ILogger::log(ILogger::ERRORS) << "Error occurred during GUI XML loading. "
			<< "Error : " << doc.ErrorId() << " : " 
			<< doc.ErrorDesc() << "\n";
		return false;
	}

	::TiXmlHandle hdl(&doc);
	TiXmlElement* element = hdl.FirstChildElement().FirstChildElement().Element();

	if(!element)
	{
		ILogger::log(ILogger::ERRORS) << "XML loading : Node to reach doesn't exist.\n";
		return false;
	}

	//loop on all widgets
	while (element)
	{
		if(!handleWidget(element, reload))
			return false;
		element = element->NextSiblingElement();
	}

	return true;
}

} //end namespace xml

} //end namespace