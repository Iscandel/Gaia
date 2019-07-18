///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "Gaia/widgetRenderers/CheckBoxImageRenderer.h"

namespace gaia
{
void CheckBoxImageRenderer::draw_impl(BaseGraphics* Gfx)
{
	drawText(Gfx);
	drawImages(Gfx);
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void CheckBoxImageRenderer::drawImages(BaseGraphics* Gfx)
{
	const std::string checked = "checked";

	int posX = 0;//myWidget->getX();
	int posY = 0;//myWidget->getY();

	if(!myWidget->isTextOnRight())
	{
		posX += myWidget->getWidth() - myWidget->getHeight();
	}

	if(imageExists(myWidget->getStrWidgetState()))
	{
		//NB: CheckBox is square
		Gfx->drawImage(
			myImages[myWidget->getStrWidgetState()], 
			posX, 
			posY,
			myWidget->getHeight(),
			myWidget->getHeight());
	}

	//The following implies the transparency of the check
	if(myWidget->isChecked())
	{
		if(imageExists(checked))
		{
			//NB: CheckBox is a square
			Gfx->drawImage(
				myImages[checked], 
				posX, 
				posY,
				myWidget->getHeight(),
				myWidget->getHeight());
		 }
	}
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void CheckBoxImageRenderer::drawText(BaseGraphics* Gfx)
{
	//We take the height as the reference, because the box should be square

	//No const ref, the text can be modified if it exceeds the width
	std::string text = myWidget->getText();

	if(text == "")
		return;

	int posX = 0;
	int posY = static_cast<int>(/*myWidget->getY() +*/ myWidget->getHeight() / 2.f - myWidget->getFontSize() / 2.f);

	PtrFont font = myWidget->getFont();
	unsigned int fontSize = myWidget->getFontSize();
	
	const int removal = 1;

	if(myWidget->isTextOnRight())
	{
		posX = /*myWidget->getX() +*/ myWidget->getHeight() + removal;
	}
	else
	{
		posX = 0;//myWidget->getX();
	}

	if(font->getTextWidth(text, fontSize) > 
		myWidget->getWidth() - (myWidget->getHeight() + removal))
	{
		text = "";
		for(unsigned int i = 0; i < myWidget->getText().size(); i++)
		{
			text += myWidget->getText()[i];
			if(font->getTextWidth(text + "..", fontSize) > 
				myWidget->getWidth() - (myWidget->getHeight() + removal))
			{
				break;
			}
		}

		text += "..";
	}


	Gfx->drawText(
		font, 
		text, 
		posX, 
		posY, 
		myWidget->getTextColor(), 
		fontSize);
}

} //end namespace