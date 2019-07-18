#include "Gaia/widgetRenderers/ProprietesRenduTextBox.h"

#include "Gaia/widgets/BaseWidget.h"

namespace gaia
{
namespace properties
{
ProprietesRenduTextBox::ProprietesRenduTextBox(const std::string& nom)
:Property(nom)
{
}

std::string ProprietesRenduTextBox::getProperty(const std::string& nom)
{
	return myTextDisplayed;
}

void ProprietesRenduTextBox::setProperty(BaseWidget& Cible, const std::string& valeur)
{
	myTextDisplayed = valeur;
	//IWidgetRenderer* rendu = Cible.getWidgetRenderer();

	//if(rendu)
	//{
	//	RenduTextBox* tbRendu = static_cast<RenduTextBox*>(rendu);

	//	tbRendu->setTexte(valeur);
	//}
}

}
}
