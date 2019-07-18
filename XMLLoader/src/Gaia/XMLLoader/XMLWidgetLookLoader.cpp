///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "Gaia/XMLLoader/XMLWidgetLookLoader.h"
#include "../../../../Dependencies/Headers/tinyxml/tinyxml.h"

namespace gaia
{
namespace xml
{
//=============================================================================
///////////////////////////////////////////////////////////////////////////////
XMLWidgetLookLoader::XMLWidgetLookLoader(void)
{
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
XMLWidgetLookLoader::~XMLWidgetLookLoader(void)
{
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
bool XMLWidgetLookLoader::load(const std::string& imageSetPath, const std::string& lookPath)
{
	bool res = true;
	res = loadImageSet(imageSetPath);
	res = res & loadLooks(lookPath);

	return res;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
bool XMLWidgetLookLoader::handleSheet(TiXmlElement* sheetNode)
{
	ImageSheet* sheet = NULL;

	std::string sheetName = sheetNode->Attribute("name");
	TiXmlElement* sheetElement = sheetNode->FirstChildElement();
	for(; sheetElement; sheetElement = sheetElement->NextSiblingElement())
	{
		std::string key = sheetElement->ValueStr();

		if(key == "texture")
		{
			std::string pathSheet = sheetElement->GetText();
			sheet = new ImageSheet(pathSheet, sheetName);
		}
		else if(key == "image")
		{
			std::string name = sheetElement->Attribute("name");
			double x, y, l, h; //int ?
			if(sheetElement->QueryDoubleAttribute("x", &x) == TIXML_SUCCESS &&
				sheetElement->QueryDoubleAttribute("y", &y) == TIXML_SUCCESS &&
				sheetElement->QueryDoubleAttribute("l", &l) == TIXML_SUCCESS &&
				sheetElement->QueryDoubleAttribute("h", &h) == TIXML_SUCCESS) 
			{
				if(!sheet)
				{
					ILogger::log(ILogger::ERRORS) << "XML look loading : "
					<< "Texture hasn't been defined yet.\n";
					return false;
				}

				sheet->addImage(name, IntRect(x, y, l, h));
			}
			else
			{
				throw GuiException("XML look loading : cannot convert the position in " + sheetName);
			}
		}
		else
		{
			ILogger::log(ILogger::ERRORS) << "XML look loading : "
					<< "unknown key " << key << " ignored.\n";
		}
	}

	//We add the sheet to finish
	ImageSheetsManager::getInstance()->registerImageSheet(sheet);
	
	return true;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
bool XMLWidgetLookLoader::loadImageSet(const std::string& imageSetName)
{
	TiXmlDocument doc(imageSetName.c_str());
	if(!doc.LoadFile())
	{
		ILogger::log(ILogger::ERRORS) << "Error occurred during GUI XML loading. "
			<< "Error : " << doc.ErrorId() << " : " 
			<< doc.ErrorDesc() << "\n";
		return false;
	}

	TiXmlHandle hdl(&doc);
	TiXmlElement* element = hdl.FirstChildElement().FirstChildElement().Element();

	if(!element)
	{
		ILogger::log(ILogger::ERRORS) << "XML loading : Node to reach doesn't exist.\n";
		return false;
	}

	//while (element)
	{
		std::string collectionName = element->Attribute("name");
	
		TiXmlElement* elemSet = element->FirstChildElement();

		for(elemSet; elemSet; elemSet = elemSet->NextSiblingElement())
		{
			handleSheet(elemSet);
		}

		//next set
		//element = element->NextSiblingElement();
	}
	return true;
}

////=============================================================================
/////////////////////////////////////////////////////////////////////////////////
//bool XMLWidgetLookLoader::chargerImageSets(const std::string& nomImageSets)
//{
//	TiXmlDocument doc(nomImageSets.c_str());
//	if(!doc.LoadFile())
//	{
//		ILogger::log(ILogger::ERRORS) << "Error occurred during GUI XML loading. "
//			<< "Error : " << doc.ErrorId() << " : " 
//			<< doc.ErrorDesc() << "\n";
//		return false;
//	}
//
//	TiXmlHandle hdl(&doc);
//	TiXmlElement* element = hdl.FirstChildElement().FirstChildElement().Element();
//
//	if(!element)
//	{
//		ILogger::log(ILogger::ERRORS) << "XML loading : Node to reach doesn't exist.\n";
//		return false;
//	}
//
//	//loop on all widgets
//	while (element)
//	{
//		std::string collectionName = element->Attribute("name");
//	
//		TiXmlElement* elemSet = element->FirstChildElement();
//
//		int numEnfant = 0;
//		for( elemSet; elemSet; elemSet = elemSet->NextSiblingElement())
//		{
//			handleSheet(elemSet);
//
//
//			ImageSheet* feuille = NULL;
//
//			std::string nomFeuille = elemSet->Attribute("nom");
//			TiXmlElement* elemFeuille = elemSet->FirstChildElement();
//			for( elemFeuille; elemFeuille; elemFeuille = elemFeuille->NextSiblingElement())
//			{
//				std::string cle = elemFeuille->ValueStr();
//
//				if(cle == "texture")
//				{
//					std::string cheminFeuille = elemFeuille->GetText();
//					feuille = new ImageSheet(cheminFeuille, nomFeuille);
//				}
//				else if(cle == "image")
//				{
//					std::string nom = elemFeuille->Attribute("nom");
//					double x, y, l, h;
//					if(elemFeuille->QueryDoubleAttribute("x", &x) == TIXML_SUCCESS &&
//						elemFeuille->QueryDoubleAttribute("y", &y) == TIXML_SUCCESS &&
//						elemFeuille->QueryDoubleAttribute("l", &l) == TIXML_SUCCESS &&
//						elemFeuille->QueryDoubleAttribute("h", &h) == TIXML_SUCCESS) 
//					{
//						if(!feuille)
//							throw GuiException("Problème XMLApparenceGuiLoader à corriger");
//
//						feuille->ajouterImage(nom, IntRect(x, y, l, h));
//					}
//					else
//					{
//						throw GuiException("Problème de conversion en nombre "
//							"dans XMLWidgetLookLoader pour la feuille " + nomFeuille);
//					}
//				}
//			}
//
//				//On ajoute le thème pour terminer
//			ImageSheetsManager::getInstance()->enregistrerImageSheet(feuille);
//		}
//
//		//On passe au widget suivant
//		element = element->NextSiblingElement();
//	}
//	return true;
//}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void XMLWidgetLookLoader::handleRenderer(WidgetLook& theme, TiXmlElement* widgetAttributes, bool isChild)
{
	std::string rendererName = widgetAttributes->GetText();

	if(!isChild)
	{
		theme.setWidgetRenderer(rendererName);
	}
	else
	{
		theme.addChildWidgetRenderer(rendererName);
	}
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void XMLWidgetLookLoader::handleImageLook(WidgetLook& theme, 
										  TiXmlElement* widgetAttributes, 
										  const std::string& name, 
										  bool isChild)
{
	std::string stateName = widgetAttributes->Attribute("state");
	std::string imageSheetName = widgetAttributes->Attribute("imageSheet");
	std::string imageName = widgetAttributes->Attribute("name");

	if(!isChild)
	{
		theme.addImage(stateName, imageSheetName, imageName);
	}
	else
	{
		theme.addChildImage(name, stateName, imageSheetName, imageName);
	}
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
bool XMLWidgetLookLoader::handleAreaLook(WidgetLook& theme, 
										 TiXmlElement* widgetAttributes, 
										 const std::string& childName, 
										 bool isChild)
{
	//double x, y, l, h;
	//std::string areaName = widgetAttributes->Attribute("name");
	//if(widgetAttributes->QueryDoubleAttribute("x", &x) != TIXML_SUCCESS ||
	//	widgetAttributes->QueryDoubleAttribute("y", &y) != TIXML_SUCCESS ||
	//	widgetAttributes->QueryDoubleAttribute("l", &l) != TIXML_SUCCESS ||
	//	widgetAttributes->QueryDoubleAttribute("h", &h) != TIXML_SUCCESS) 
	//{
	//	ILogger::log(ILogger::ERRORS) << "XML look loading : "
	//				<< "Texture hasn't been defined yet.\n";
	//	return false;
	//}

	TiXmlElement* widgetPosAttributes = widgetAttributes->FirstChildElement();
	std::string areaName = widgetAttributes->Attribute("name");

	LayoutInfos infos = constructLayoutInfos(widgetPosAttributes);
	if(!isChild)
	{
		theme.addLayoutArea(areaName, infos);
		//theme.addArea(areaName, gaia::Rect<double>(x, y, l, h));
	}
	else
	{
		theme.addChildLayoutArea(childName, areaName, infos);
		//theme.addChildArea(childName, areaName, gaia::Rect<double>(x, y, l, h));
	}

	return true;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
bool XMLWidgetLookLoader::handleChildLook(WidgetLook& theme, TiXmlElement* widgetAttributes, bool isChild)
{
	bool res = true;

	if(!isChild) //prevent recursion for now
	{
		std::string childName = widgetAttributes->Attribute("genericName");
		std::string childType = widgetAttributes->Attribute("type");
		theme.addChild(childName, childType);

		TiXmlElement* childAttributes = widgetAttributes->FirstChildElement();

		for(; childAttributes; childAttributes = childAttributes->NextSiblingElement())
		{
			std::string key = childAttributes->ValueStr();

			res = res & handleCommon(theme, childAttributes, key, childName, true);

		}
	}

	return res;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
LayoutInfos XMLWidgetLookLoader::constructLayoutInfos(
							 TiXmlElement* widgetPosAttributes)
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
	}

	return infos;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void XMLWidgetLookLoader::handleChildDimensions(WidgetLook& theme, 
											  TiXmlElement* widgetAttributes,
											  const std::string& childName, 
											  bool isChild)
{
	TiXmlElement* widgetPosAttributes = widgetAttributes->FirstChildElement();

	LayoutInfos infos = constructLayoutInfos(widgetPosAttributes);

	
	//for(; widgetPosAttributes; widgetPosAttributes = widgetPosAttributes->NextSiblingElement())
	//{
	//	std::string key = widgetPosAttributes->ValueStr();

	//	if(key == "fullDimensions")
	//	{
	//		std::string type = widgetPosAttributes->Attribute("type");
	//		LayoutInfos::PositionType enumType = LayoutInfos::FIXED;
	//		if(type == "fixed")
	//			enumType = LayoutInfos::FIXED;
	//		else if(type == "relative")
	//			enumType = LayoutInfos::RELATIVE;
	//		else if(type == "uniform")
	//			enumType = LayoutInfos::UNIFORM;
	//		else
	//		{
	//			ILogger::log(ILogger::ERRORS) << 
	//				"XML look loader : cannot deduce layout type : " << type << ".\n";
	//		}
	//		//std::string* value = widgetPosAttributes->Attribute("screenDependent");
	//		std::string value = widgetPosAttributes->GetText();
	//		std::string splitted = tools::split(value, ";");

	//		if(splitted.size() != 4)
	//		{
	//			ILogger::log(ILogger::ERRORS) << 
	//				"XML look loader : fullDimensions hasn't got 4 argument : " << value << ".\n";
	//		}

	//		infos.setPosInfos(enumType, splitted[0] + ";" + splitted[1]);
	//		infos.setWidthInfos(enumType, splitted[2]);
	//		infos.setHeightInfos(enumType, splitted[3]);
	//	}
	//	else if(key == "position")
	//	{
	//		std::string type = widgetPosAttributes->Attribute("type");
	//		std::string value = widgetPosAttributes->GetText();
	//		if(type == "fixed")
	//			infos.setPosInfos(LayoutInfos::FIXED, value);
	//		else if(type == "relative")
	//			infos.setPosInfos(LayoutInfos::RELATIVE, value);
	//		else if(type == "uniform")
	//			infos.setPosInfos(LayoutInfos::UNIFORM, value);
	//	}
	//	else if (key == "width")
	//	{
	//		std::string type = widgetPosAttributes->Attribute("type");
	//		std::string value = widgetPosAttributes->GetText();
	//		if(type == "fixed")
	//			infos.setWidthInfos(LayoutInfos::FIXED, value);
	//		else if(type == "relative")
	//			infos.setWidthInfos(LayoutInfos::RELATIVE, value);
	//		else if(type == "uniform")
	//			infos.setWidthInfos(LayoutInfos::UNIFORM, value);
	//	}
	//	else if(key == "height")
	//	{
	//		std::string type = widgetPosAttributes->Attribute("type");
	//		std::string value = widgetPosAttributes->GetText();
	//		if(type == "fixed")
	//			infos.setHeightInfos(LayoutInfos::FIXED, value);
	//		else if(type == "relative")
	//			infos.setHeightInfos(LayoutInfos::RELATIVE, value);
	//		else if(type == "uniform")
	//			infos.setHeightInfos(LayoutInfos::UNIFORM, value);
	//	}
	//}

	theme.addChildLayout(childName, infos);

	//std::string pos = widgetAttributes->GetText();
	//std::istringstream stream(pos);
	//double x, y, l, h;
	//stream >> x >> y >> l >> h;
	//theme.addChildPosition(childName, Rect<double>(x, y, l, h));
}

void XMLWidgetLookLoader::handleChildPosition(WidgetLook& theme, 
											  TiXmlElement* widgetAttributes,
											  const std::string& childName, 
											  bool isChild)
{
	//std::string pos = widgetAttributes->GetText();
	//std::istringstream stream(pos);
	//double x, y;
	//stream >> x >> y;
	//theme.addChildPosition(childName, );
}

void XMLWidgetLookLoader::handleChildWidth(WidgetLook& theme, 
										   TiXmlElement* widgetAttributes,
										   const std::string& childName, 
										   bool isChild)
{
}

void XMLWidgetLookLoader::handleChildHeight(WidgetLook& theme, 
											TiXmlElement* widgetAttributes,
											const std::string& childName, 
											bool isChild)
{
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
bool XMLWidgetLookLoader::handleCommon(WidgetLook &theme, 
									   TiXmlElement* widgetAttributes, 
									   const std::string& key,
									   const std::string& widgetName, 
									   bool isChild)
{
	if(key == "widgetRenderer")
	{
		handleRenderer(theme, widgetAttributes, isChild);
	}
	else if(key == "image")
	{			
		handleImageLook(theme, widgetAttributes, widgetName, isChild);
	}
	else if(key == "area")
	{
		return handleAreaLook(theme, widgetAttributes, widgetName, isChild);
	}
	else if(key == "child")
	{
		return handleChildLook(theme, widgetAttributes, isChild);
	}
	else if(key == "dimensions")
	{
		handleChildDimensions(theme, widgetAttributes, widgetName, isChild);
	}
	//else if(key == "position")
	//{
	//	handleChildPosition(theme, widgetAttributes, widgetName, isChild);
	//}
	//else if(key == "width")
	//{
	//	handleChildWidth(theme, widgetAttributes, widgetName, isChild);
	//}
	//else if(key == "height")
	//{
	//	handleChildHeight(theme, widgetAttributes, widgetName, isChild);
	//}
	else
	{
		ILogger::log(ILogger::INFORMATIVE) << "XML look loading : "
					<< "unknown key " << key << " ignored.\n";
	}

	return true;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
bool XMLWidgetLookLoader::handleWidgetLook(TiXmlElement* widgetNode)
{
	bool res = true;

	WidgetLook theme;

	std::string widgetName = widgetNode->Attribute("name");

	TiXmlElement* widgetAttributes = widgetNode->FirstChildElement();

	int numEnfant = 0;
	for(; widgetAttributes; widgetAttributes = widgetAttributes->NextSiblingElement())
	{
		std::string key = widgetAttributes->ValueStr();

		res = res & handleCommon(theme, widgetAttributes, key, widgetName, false);
	}

	//On ajoute le thème pour terminer
	WidgetLookManager::getInstance()->addLook(widgetName, theme);

	return res;
	////On passe au widget suivant
	//element = element->NextSiblingElement();
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
bool XMLWidgetLookLoader::loadLooks(const std::string& lookPath)
{
	TiXmlDocument doc(lookPath.c_str());
	if(!doc.LoadFile())
	{
		ILogger::log(ILogger::ERRORS) << "Error occurred during GUI XML loading. "
			<< "Error : " << doc.ErrorId() << " : " 
			<< doc.ErrorDesc() << "\n";
		return false;
	}

	TiXmlHandle hdl(&doc);
	TiXmlElement* widgetNode = hdl.FirstChildElement().FirstChildElement().ToElement();

	if(!widgetNode)
	{
		ILogger::log(ILogger::ERRORS) << "XML loading : Node to reach doesn't exist.\n";
		return false;
	}

	TiXmlElement* root = widgetNode->Parent()->ToElement();

	Point resolution;
	const TiXmlAttribute* att = root->FirstAttribute();
	while(att)
	{
		if(att->NameTStr() == "resolutionX")
			resolution.x = tools::stringToNum<int>(att->ValueStr());
		else if(att->NameTStr() == "resolutionY")
			resolution.y = tools::stringToNum<int>(att->ValueStr());
		else
		{
			ILogger::log(ILogger::INFORMATIVE) << "XML Look loader : attribute "
			<< att->NameTStr() << " unknown. Ignored.\n";
		}

		att = att->Next();
	}

	WidgetLookManager::getInstance()->setPreferredResolution(resolution.x, resolution.y);

	//loop on all widgets
	while (widgetNode)
	{
		if(!handleWidgetLook(widgetNode))
			return false;

		//On passe au widget suivant
		widgetNode = widgetNode->NextSiblingElement();
	}

	return true;
}

} //end namespace xml

} //end namespace