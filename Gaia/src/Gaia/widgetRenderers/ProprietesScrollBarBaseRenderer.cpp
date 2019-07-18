//#include "widgetRenderers/ProprietesScrollBarBaseRenderer.h"
//#include "widgets/Button.h"
//#include "widgets/ScrollBar.h"
//#include "tools/Exceptions.h"
//#include "tools/Logger.h"
//#include "tools/Tools.h"
//
//namespace gaia
//{
//namespace properties
//{
//ScrollBarBaseRendererImagesBoutonPlus::ScrollBarBaseRendererImagesBoutonPlus(const std::string& nom)
//:Property(nom)
//{
//}
//
//std::string ScrollBarBaseRendererImagesBoutonPlus::getProperty(const std::string& nom)
//{
//	throw GuiException("ScrollBarBaseRendererImagesBoutonPlus::getProperty implémentée");
//}
//
//void ScrollBarBaseRendererImagesBoutonPlus::setProperty(BaseWidget& Cible, const std::string& valeur)
//{
//	//gaia::PtrButton bouton = ((ScrollBar&)Cible).getDecreaseButton();
//
//	//std::vector<std::string> s = utiles::chaine::split(valeur, "|");
//	//GuiImagesManager* Manager = GuiImagesManager::getInstance();
//	//if(s.size() == 3)
//	//{
//	//		bouton->setImages(
//	//		s[0] == "_" ? Image() : Image(Manager->getRessource(s[0])->getImage()), 
//	//		s[1] == "_" ? Image() : Image(Manager->getRessource(s[1])->getImage()), 
//	//		s[2] == "_" ? Image() : Image(Manager->getRessource(s[2])->getImage()));
//	//}
//	//else if(s.size() == 1)
//	//{
//	//	bouton->setImages(
//	//		Image(Manager->getRessource(s[0])->getImage()));
//	//}
//	//else
//	//{
//	//	ILogger::log(ILogger::ERREURS) << POSITIONLOG << 
//	//		"Nombre d'images incorrect : " << Cible.getName() << "\n";
//	//}
//}
//
//ScrollBarBaseRendererImagesBoutonMoins::ScrollBarBaseRendererImagesBoutonMoins(const std::string& nom)
//:Property(nom)
//{
//}
//
//std::string ScrollBarBaseRendererImagesBoutonMoins::getProperty(const std::string& nom)
//{
//	throw GuiException("ScrollBarBaseRendererImagesBoutonMoins::getProperty implémentée");
//}
//
//void ScrollBarBaseRendererImagesBoutonMoins::setProperty(BaseWidget& Cible, const std::string& valeur)
//{
//	//gaia::PtrButton bouton = ((ScrollBar&)Cible).getIncreaseButton();
//
//	//std::vector<std::string> s = utiles::chaine::split(valeur, "|");
//	//GuiImagesManager* Manager = GuiImagesManager::getInstance();
//	//if(s.size() == 3)
//	//{
//	//	bouton->setImages(
//	//		s[0] == "_" ? Image() : Image(Manager->getRessource(s[0])->getImage()), 
//	//		s[1] == "_" ? Image() : Image(Manager->getRessource(s[1])->getImage()), 
//	//		s[2] == "_" ? Image() : Image(Manager->getRessource(s[2])->getImage()));
//	//}
//	//else if(s.size() == 1)
//	//{
//	//	bouton->setImages(
//	//		Image(Manager->getRessource(s[0])->getImage()));
//	//}
//	//else
//	//{
//	//	ILogger::log(ILogger::ERREURS) << POSITIONLOG << 
//	//		"Nombre d'images incorrect : " << Cible.getName() << "\n";
//	//}
//}
//
//ScrollBarBaseRendererImagesCurseur::ScrollBarBaseRendererImagesCurseur(const std::string& nom)
//:Property(nom)
//{
//}
//
//std::string ScrollBarBaseRendererImagesCurseur::getProperty(const std::string& nom)
//{
//	throw GuiException("ScrollBarBaseRendererImagesCurseur::getProperty implémentée");
//}
//
//void ScrollBarBaseRendererImagesCurseur::setProperty(BaseWidget& Cible, const std::string& valeur)
//{
//	//gaia::PtrButton bouton = ((ScrollBar&)Cible).getThumb();
//
//	//std::vector<std::string> s = utiles::chaine::split(valeur, "|");
//	//GuiImagesManager* Manager = GuiImagesManager::getInstance();
//	//if(s.size() == 3)
//	//{
//	//	bouton->setImages(
//	//		s[0] == "_" ? Image() : Image(Manager->getRessource(s[0])->getImage()), 
//	//		s[1] == "_" ? Image() : Image(Manager->getRessource(s[1])->getImage()), 
//	//		s[2] == "_" ? Image() : Image(Manager->getRessource(s[2])->getImage()));
//	//}
//	//else if(s.size() == 1)
//	//{
//	//	bouton->setImages(
//	//		Image(Manager->getRessource(s[0])->getImage()));
//	//}
//	//else
//	//{
//	//	ILogger::log(ILogger::ERREURS) << POSITIONLOG << 
//	//		"Nombre d'images incorrect : " << Cible.getName() << "\n";
//	//}
//}
//
//} // end namespace properties
//
//} //end namespace
