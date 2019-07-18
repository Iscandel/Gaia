///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "Gaia/widgets/TextBox.h"
#include "Gaia/widgetRenderers/TextBoxBaseRenderer.h"

namespace gaia
{
//const std::string TextBox::myWidgetType = "TextBox";

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
TextBox::TextBox(const std::string& nom, int x, int y, int largeur, int hauteur)
:BaseTextWidget(nom, x, y, largeur, hauteur)
//,tailleMaxMessage(300)
//,myCaret(0)
//,myText("")
//,myIsDragging(false)
//,myFirstSelection(0)
//,myLastSelection(0)
{
	copyProperties<TextBox>();
	//setTextColor(Color(0,0,0));
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
TextBox::TextBox(const std::string& nom, const IntRect& dimensions)
:BaseTextWidget(nom, dimensions)
//,tailleMaxMessage(300)
//,myCaret(0)
//,myText("")
//,myIsDragging(false)
//,myFirstSelection(0)
//,myLastSelection(0)
{
	copyProperties<TextBox>();
	//setRetraitGauche(2);
	//setTextColor(Color(0,0,0));
}

//void TextBox::onTextChanged()
//{
//	if(E_onTextChanged != NULL)	
//	{
//		Evenement ev(this);
//		E_onTextChanged(ev);
//	}
//}

//void TextBox::setWidgetRenderer(IWidgetRenderer* mr)
//{
//	if(myRenderer)
//		removeObservers();
//
//	BaseWidget::setWidgetRenderer(mr);
//}
//void TextBox::setGraphics(BaseGraphics* Gfx) //Inutile ?
//{
//	BaseWidget::setGraphics(Gfx);
//	setFont(Gfx->getGlobalFont());
//}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void TextBox::assignToModel(Observer* renderer)
{
	if(myRenderer)
	{
		Observer* obsRenderer = dynamic_cast<Observer*>(myRenderer); 
		if(obsRenderer)
			removeObserver(obsRenderer);
	}
	addObserver(renderer);
	notifyObservers(); 
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void TextBox::insertText(const std::string& texte, unsigned int pos)
{
	if(!isReadOnly())
	{
		setCaretPosition(pos);
		resetSelection();

		myText.insert(pos, texte);
		myCaret += static_cast<unsigned int>(texte.size()); //Check if we can simpliy
			
		onTextChanged();

		invalidate();
	}
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void TextBox::deleteTextRange(unsigned int startingPos, unsigned int endingPos)
{
	if(endingPos < startingPos)
	{
		throw IllegalArgument("delete text : Ending position must be greater "
							  "than starting position.");
	}

	deleteText(startingPos, (endingPos - startingPos));
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void TextBox::deleteText(unsigned int startingPos, unsigned int amount)
{
	if(!isReadOnly())
	{
		setCaretPosition(startingPos);

		myText.erase(startingPos, amount);
			
		resetSelection();
		adjustCaret();

		//Notify observers
		onTextChanged();

		invalidate();
	}
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void TextBox::replaceTextRange(const std::string& text, unsigned int startingPos, unsigned int endingPos)
{
	if(endingPos < startingPos)
	{
		throw IllegalArgument("replace Text : Ending position must be greater "
							  "than starting position.");
	}

	replaceText(text, startingPos, endingPos - startingPos);
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void TextBox::replaceText(const std::string& text, unsigned int startPosition, unsigned int amount) //2 ev onTextChanged triggered..
{
	deleteText(startPosition, amount);
	insertText(text, startPosition);
}

//void TextBox::handleDeleting()
//{
//	if (myText.size() > 0)
//	{
//		if(myCaret > 0)
//		{
//			int debutSelection = getSelectionStart();
//			int finSelection = getSelectionEnd();
//
//			if(debutSelection != finSelection)
//			{
//				deleteTextRange(debutSelection,finSelection);
//			}
//			else
//			{
//				//Reset pour s'assurer que debutSelection est à la pos du curseur
//				//resetSelection();
//				deleteText(getCaretPosition() - 1, 1);
//			}
//		}
//	}
//}

/////////////////////////////////////////////////////////////////////////////////
////A faire redéfinir par les widgets enfants.
////Traite de façon générique la réponse à un évènement de souris pressée
/////////////////////////////////////////////////////////////////////////////////
//bool TextBox::handleMousePressed_impl(MouseEvent& ev)
//{
//	if(ev.getButton() == MouseButton::LEFT)
//	{
//		myIsDragging = true;
//		catchMouseInputs();
//
//		if(myRenderer)
//		{
//			int posWidgetX = static_cast<TextBoxBaseRenderer*>(myRenderer)->computeCaretPosition(
//													Point(ev.getX(), ev.getY()));
//
//			if(posWidgetX >= 0)
//			{
//				myCaret = posWidgetX;
//				myFirstSelection = myCaret;
//				myLastSelection = myFirstSelection;
//			}
//		}
//	}
//
//	ev.use();
//	return ev.isHandled();
//}

/////////////////////////////////////////////////////////////////////////////////
////A faire redéfinir par les widgets enfants.
////Traite de façon générique la réponse à un évènement de souris en déplacement
/////////////////////////////////////////////////////////////////////////////////
//bool TextBox::handleMouseHover_impl(MouseEvent& ev)
//{
//	myMousePos.x = ev.getX(); myMousePos.y = ev.getY();
//
//	if(myIsDragging)
//	{
//		if(myRenderer)
//		{
//			int posWidgetX = static_cast<TextBoxBaseRenderer*>(myRenderer)->computeCaretPosition(
//												Point(ev.getX(), ev.getY()));
//			if(posWidgetX >= 0)
//			{
//				moveSelection(posWidgetX - myLastSelection, getText().size());
//			}
//		}
//	}
//
//	ev.use();
//	return ev.isHandled();
//}

/////////////////////////////////////////////////////////////////////////////////
////A faire redéfinir par les widgets enfants.
////Traite de façon générique la réponse à un évènement de souris relachee
/////////////////////////////////////////////////////////////////////////////////
//bool TextBox::handleMouseReleased_impl(MouseEvent& ev)
//{
//	if(ev.getButton() == MouseButton::LEFT)
//	{
//		myIsDragging = false;
//		releaseMouseInputs();
//
//		int posWidgetX = static_cast<TextBoxBaseRenderer*>(myRenderer)->
//					computeCaretPosition(Point(ev.getX(), ev.getY()));
//
//		if(posWidgetX >= 0)
//		{
//			myLastSelection = posWidgetX;
//			myCaret = posWidgetX;
//		}
//	}
//
//	ev.use();
//	return ev.isHandled();
//}

/////////////////////////////////////////////////////////////////////////////////
////A faire redéfinir par les widgets enfants.
////Traite de façon générique la réponse à un évènement de touche pressée
/////////////////////////////////////////////////////////////////////////////////
//bool TextBox::handleKeyPressed_impl(KeyboardEvent& ev)
//{
//	if(ev.getKey() == Keyboard::LEFT)//sf::Key::Left)
//	{
//		//Selection
//		if(ev.isShiftPressed)
//		{
//			moveSelection(-1, getText().size());
//		}
//		else
//		{
//			setCaretPosition(getCaretPosition() - 1, myText.size());
//			resetSelection();
//		}
//
//		notifyObservers();
//	}
//
//	else if(ev.getKey() == Keyboard::RIGHT)//sf::Key::Right)
//	{
//		//Selection
//		if(ev.isShiftPressed)
//		{
//			moveSelection(1, getText().size());
//		}
//		else
//		{
//			setCaretPosition(getCaretPosition() + 1, myText.size());
//			resetSelection();
//		}
//
//		notifyObservers();
//	}
//
//	else if(ev.getKey() == Keyboard::DELETE_TOUCHE)//sf::Key::Delete)
//	{
//		handleDeleting();
//		//deleteText(getCaretPosition(), 1);
//		////On met à jour notre chaine en supprimant le dernier caractère
//		//myText.erase(myText.begin() + getCaretPosition());
//
//		//notifyObservers();
//	}
//
//	ev.use();
//	return ev.isHandled();
//}

/////////////////////////////////////////////////////////////////////////////////
////A faire redéfinir par les widgets enfants.
////Traite de façon générique la réponse à un évènement de texte entré
/////////////////////////////////////////////////////////////////////////////////
//bool TextBox::handleTextEntered_impl(KeyboardEvent& ev)
//{
//	//Si on supprime un caractère écrit
//	if (ev.getCharacter() == '\b')
//	{
//		if (myText.size() > 0)
//		{
//			if(myCaret > 0)
//			{
//				////On regarde si la chaine dépassait de la textbox en longueur
//				//if(monPremierCaractereVisible > 0)
//				//{
//				//	monPremierCaractereVisible--;
//				//}
//				
//				int debutSelection = getSelectionStart();
//				int selectionEnd = getSelectionEnd();
//				
//				if(debutSelection != selectionEnd)
//				{
//					//int nombreCaracteres = selectionEnd - debutSelection;
//					//myText.erase(debutSelection, nombreCaracteres);
//					//
//					//setCaretPosition(debutSelection, myText.size());
//
//					//resetSelection();
//					deleteTextRange(debutSelection,selectionEnd);
//				}
//				else
//				{
//					//On met à jour notre chaine en supprimant le dernier caractère
//					//chaineMessage = chaineMessage.substr(0,(chaineMessage.size()-1));
//					//myText.erase(myText.begin() + getCaretPosition() - 1);
//					//myCaret--;
//					deleteText(getCaretPosition() - 1, 1);
//				}
//			}
//		}
//
//		//notifyObservers();
//	}
//
//	//Ajout de texte au texte en train d'être tapé
//	//else if(ev.Text.Unicode != 13)
//	else if(ev.getCharacter() >= 32)
//	{
//		std::string s;
//		s += (char) ev.getCharacter();
//		insertText(s, getCaretPosition());
//
//		////if(chaineMessage.size() < tailleMaxMessage)
//		//{
//		//	myText.insert(myText.begin() + myCaret, ev.getCharacter());
//		//	myCaret++;
//		//}
//		//
//		//notifyObservers();
//	}
//
//	ev.use();
//	return ev.isHandled();
//}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void TextBox::setText(const std::string& texte)
{
	myText = texte;
	myCaret = 0;
	resetSelection();

	notifyObservers();
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void TextBox::update(unsigned int time)
{
	myTimeAccumulator += time;
	const unsigned int interval = 330;

	// if the text is moving by "dragging"
	if(myIsDragging) 
	{
		if(myTimeAccumulator > interval)
		{
			if(myMousePos.x > getWidth()) //NB : Relative mouse pos
			{
				setCaretPosition(getCaretPosition() + 1);
				myTimeAccumulator = 0;
				notifyObservers();
			}
			else if(myMousePos.x < 0)
			{
				moveSelection(-1);
				//setCaretPosition(getCaretPosition() - 1);
				myTimeAccumulator = 0;
				notifyObservers();
			}
		}
	}

	BaseWidget::update(time);
}

/////////////////////////////////////////////////////////////////////////////////
//// Donne ou retire le focus à une textBox
/////////////////////////////////////////////////////////////////////////////////
//void TextBox::requestFocus(bool b)
//{
//	BaseWidget::requestFocus(b);
//
//	if(!hasFocus())
//	{
//		resetSelection();
//	}
//}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void TextBox::onLostFocus()
{
	BaseWidget::onLostFocus();

	resetSelection();
}

//void TextBox::setCaretPosition(unsigned int pos)
//{
//	if(pos >= 0 && pos <= myText.size())
//		myCaret = pos;
//}

//void TextBox::resetSelection()
//{
//	myLastSelection = myFirstSelection = getCaretPosition();
//}

//void TextBox::moveSelection(int quantite, unsigned int tailleTexte)
//{
//	int tailleTexte = static_cast<int>(getText().size());
//	myLastSelection += quantite;
//	myLastSelection = myLastSelection >  tailleTexte ? tailleTexte : myLastSelection;
//	myLastSelection = myLastSelection < 0 ? 0 : myLastSelection;
//	setCaretPosition(myLastSelection);
//}

};


//namespace gaia
//{
//const std::string TextBox::myWidgetType = "TextBox";
//
/////////////////////////////////////////////////////////////////////////////////
//// Constructeur 1
//// Params : nom		-> Le nom du widget
////			x		-> La position x
////			y		-> La position y
////			largeur -> La largeur du widget
////			hauteur -> La hauteur du widget
/////////////////////////////////////////////////////////////////////////////////
//TextBox::TextBox(const std::string& nom, int x, int y, int largeur, int hauteur)
//:BaseWidget(nom, x, y, largeur, hauteur)
////,tailleMaxMessage(300)
//,monPremierCaractereVisible(0)
//,maPosBarreVerticale(0)
//,maChaineMessage("")
//,myBackgroundColor(sf::Color::White)
//,monDessinerCurseur(false)
//,myIsDragging(false)
//,myFirstSelection(0)
//,myLastSelection(0)
//{
//	setRetraitGauche(2);
//	//setTextColor(Color(0,0,0));
//	
//}
//
/////////////////////////////////////////////////////////////////////////////////
//// Constructeur 2
//// Params : nom		   -> Le nom du widget
////			dimensions -> Rectangle définissant les dimensions du widget
/////////////////////////////////////////////////////////////////////////////////
//TextBox::TextBox(const std::string& nom, const IntRect& dimensions)
//:BaseWidget(nom, dimensions)
////,tailleMaxMessage(300)
//,monPremierCaractereVisible(0)
//,maPosBarreVerticale(0)
//,maChaineMessage("")
//,myBackgroundColor(sf::Color::White)
//,monDessinerCurseur(false)
//,myIsDragging(false)
//,myFirstSelection(0)
//,myLastSelection(0)
//{
//	setRetraitGauche(2);
//	//setTextColor(Color(0,0,0));
//}
//
/////////////////////////////////////////////////////////////////////////////////
//// Destructeur
/////////////////////////////////////////////////////////////////////////////////
//TextBox::~TextBox(void)
//{
//}
//
//
//void TextBox::setGraphics(BaseGraphics* Gfx)
//{
//	BaseWidget::setGraphics(Gfx);
//	setFont(Gfx->getGlobalFont());
//}
//
//void TextBox::assignToModel(TextBoxRendu* rendu)
//{
//	addObserver(rendu);
//}
//
/////////////////////////////////////////////////////////////////////////////////
////A faire redéfinir par les widgets enfants.
////Traite de façon générique la réponse à un évènement de souris pressée
/////////////////////////////////////////////////////////////////////////////////
//bool TextBox::handleMousePressed_impl(MouseEvent& ev)
//{
//	myIsDragging = true;
//	catchMouseInputs();
//
//	if(myRenderer)
//	{
//		int posWidgetX = ((TextBoxRendu*)myRenderer)->computeCaretPosition(
//												Point(ev.getX(), ev.getY()));
//
//		if(posWidgetX >= 0)
//		{
//			maPosBarreVerticale = posWidgetX;
//			myFirstSelection = maPosBarreVerticale;
//			myLastSelection = myFirstSelection;
//		}
//	}
//
//	ev.use();
//	return ev.isHandled();
//}
//
/////////////////////////////////////////////////////////////////////////////////
////A faire redéfinir par les widgets enfants.
////Traite de façon générique la réponse à un évènement de souris en déplacement
/////////////////////////////////////////////////////////////////////////////////
//bool TextBox::handleMouseHover_impl(MouseEvent& ev)
//{
//	myMousePos.x = ev.getX(); myMousePos.y = ev.getY();
//
//	if(myIsDragging)
//	{
//		if(myRenderer)
//		{
//			int posWidgetX = ((TextBoxRendu*)myRenderer)->computeCaretPosition(
//												Point(ev.getX(), ev.getY()));
//
//			if(posWidgetX >= 0)
//			{
//				moveSelection(posWidgetX - myLastSelection);
//				//maFinSelection = posWidgetX;
//				//maPosBarreVerticale = posWidgetX;
//			}
//
//			//if(posWidgetX >= 0)
//			//{
//			//	if(posWidgetX > monDebutSelection)
//			//	{
//			//		maPosBarreVerticale = posWidgetX;
//			//		maFinSelection = posWidgetX;
//			//	}
//			//	else if(posWidgetX < monDebutSelection)
//			//	{
//			//		//maFinSelection = monDebutSelection;
//			//		monDebutSelection = posWidgetX;
//			//		maPosBarreVerticale = posWidgetX;
//			//	}
//			//}
//		}
//	}
//
//	ev.use();
//	return ev.isHandled();
//}
//
/////////////////////////////////////////////////////////////////////////////////
////A faire redéfinir par les widgets enfants.
////Traite de façon générique la réponse à un évènement de souris relachee
/////////////////////////////////////////////////////////////////////////////////
//bool TextBox::handleMouseReleased_impl(MouseEvent& ev)
//{
//	myIsDragging = false;
//	releaseMouseInputs();
//
//	int posWidgetX = ((TextBoxRendu*)myRenderer)->computeCaretPosition(Point(ev.getX(), ev.getY()));
//
//	if(posWidgetX >= 0)
//	{
//		myLastSelection = posWidgetX;
//		maPosBarreVerticale = posWidgetX;
//
//		//if(posWidgetX >= monDebutSelection)
//		//{
//		//	maPosBarreVerticale = posWidgetX;
//		//	maFinSelection = posWidgetX;
//		//}
//		//else
//		//{
//		//	//maFinSelection = monDebutSelection;
//		//	monDebutSelection = posWidgetX;
//		//	maPosBarreVerticale = posWidgetX;
//		//}
//	}
//
//	//Détermination de l'emplacement de la barre de sélection verticale
//
//	//int posClicWidgetX = ev.getX() - monRetraitGauche;// - x;
//
//	//std::string chaineAffiche = MaChaineAffichage.GetString();
//
//	//for(unsigned int i = 0; i < chaineAffiche.size(); i++)
//	//{
//	//	if(MaChaineAffichage.GetCharacterPos(i).x >= posClicWidgetX)
//	//	{
//	//		maPosBarreVerticale = i + monPremierCaractereVisible;
//	//		break;
//	//	}
//	//	else
//	//	{
//	//		if(i < chaineAffiche.size() - 1)//if(i == i < chaineAffiche.size() - 1)
//	//		{
//	//			maPosBarreVerticale = static_cast<int>(chaineAffiche.size());
//	//		}
//	//	}
//	//}
//
//	ev.use();
//	return ev.isHandled();
//}
//
/////////////////////////////////////////////////////////////////////////////////
////A faire redéfinir par les widgets enfants.
////Traite de façon générique la réponse à un évènement de touche pressée
/////////////////////////////////////////////////////////////////////////////////
//bool TextBox::handleKeyPressed_impl(KeyboardEvent& ev)
//{
//	if(ev.getKey() == Keyboard::LEFT)//sf::Key::Left)
//	{
//		//Selection
//		if(ev.isShiftPressed)
//		{
//			//int debutSelection = getSelectionStart();
//			//int finSelection = getSelectionEnd();
//
//			//monSelectionDernier++;
//			moveSelection(-1);
//
//			//setSelectionEnd(getSelectionEnd() + 1);
//		}
//		else
//		{
//			setCaretPosition(getCaretPosition() - 1);
//			resetSelection();
//		}
//
//		//maPosBarreVerticale = maPosBarreVerticale == 0 ? 0 : --maPosBarreVerticale;
//		//if(premierCaractereVisible > 0)
//		//	premierCaractereVisible--;
//		MonHorloge.Reset();
//		mettreAJourTexte();
//
//		notifyObservers();
//	}
//
//	else if(ev.getKey() == Keyboard::RIGHT)//sf::Key::Right)
//	{
//		//Selection
//		if(ev.isShiftPressed)
//		{
//			//int debutSelection = getSelectionStart();
//			//int finSelection = getSelectionEnd();
//
//			//monSelectionDernier++;
//			moveSelection(1);
//
//			//setSelectionEnd(getSelectionEnd() + 1);
//		}
//		else
//		{
//			setCaretPosition(getCaretPosition() + 1);
//			resetSelection();
//		}
//
//		//maPosBarreVerticale < (int)maChaineMessage.size() ? 
//		//	++maPosBarreVerticale : maChaineMessage.size();
//		MonHorloge.Reset();
//		mettreAJourTexte();
//
//		notifyObservers();
//	}
//
//	else if(ev.getKey() == Keyboard::DELETE_TOUCHE)//sf::Key::Delete)
//	{
//		//On met à jour notre chaine en supprimant le dernier caractère
//		maChaineMessage.erase(maChaineMessage.begin() + getCaretPosition());
//		
//		//if(posBarreVerticale > 0)
//		//	{
//		//		//On regarde si la chaine dépassait de la textbox en longueur
//		//		if(premierCaractereVisible > 0)
//		//		{
//		//			premierCaractereVisible--;
//		//		}
//		//		//On met à jour notre chaine en supprimant le dernier caractère
//		//		//chaineMessage = chaineMessage.substr(0,(chaineMessage.size()-1));
//		//		chaineMessage.erase(chaineMessage.begin() + posBarreVerticale);
//		//	}
//
//		notifyObservers();
//	}
//
//	ev.use();
//	return ev.isHandled();
//}
//
/////////////////////////////////////////////////////////////////////////////////
////A faire redéfinir par les widgets enfants.
////Traite de façon générique la réponse à un évènement de texte entré
/////////////////////////////////////////////////////////////////////////////////
//bool TextBox::handleTextEntered_impl(KeyboardEvent& ev)
//{
//	//Si on supprime un caractère écrit
//	if (ev.getCharacter() == '\b')
//	{
//		if (maChaineMessage.size() > 0)
//		{
//			if(maPosBarreVerticale > 0)
//			{
//				//maPosBarreVerticale--;
//				//On regarde si la chaine dépassait de la textbox en longueur
//				if(monPremierCaractereVisible > 0)
//				{
//					monPremierCaractereVisible--;
//				}
//				
//				int debutSelection = getSelectionStart();
//				int finSelection = getSelectionEnd();
//				
//				if(debutSelection != finSelection)
//				{
//					int nombreCaracteres = finSelection - debutSelection;
//					maChaineMessage.erase(debutSelection, nombreCaracteres);
//					if(debutSelection != getCaretPosition())
//					{
//						maPosBarreVerticale -= nombreCaracteres;
//					}
//
//					resetSelection();
//				}
//				else
//				{
//					//On met à jour notre chaine en supprimant le dernier caractère
//					//chaineMessage = chaineMessage.substr(0,(chaineMessage.size()-1));
//					maChaineMessage.erase(maChaineMessage.begin() + getCaretPosition() - 1);
//					maPosBarreVerticale--;
//				}
//			}
//		}
//
//		notifyObservers();
//	}
//
//	//Ajout de texte au texte en train d'être tapé
//	//else if(ev.Text.Unicode != 13)
//	else if(ev.getCharacter() >= 32)
//	{
//		//if(chaineMessage.size() < tailleMaxMessage)
//		{
//			//chaineMessage += ev.Text.Unicode;
//			maChaineMessage.insert(maChaineMessage.begin() + maPosBarreVerticale, (char)ev.getCharacter());
//			maPosBarreVerticale++;
//		}
//		
//		notifyObservers();
//	}
//
//	mettreAJourTexte();
//
//	ev.use();
//	return ev.isHandled();
//}
//
///////////////////////////////////////////////////////////////////////////////////
////// Traite l'évènement
///////////////////////////////////////////////////////////////////////////////////
////bool TextBox::traiterEvenement(const sf::Event& ev, const Point& posSouris)
////{
////	Point posRepere = convertToMyCoordinates(posSouris);
////
////	//Détermination de l'emplacement de la barre de sélection verticale
////	if(ev.Type == sf::Event::MouseButtonReleased)
////	{
////		int posClicWidgetX = posRepere.x - monRetraitGauche;// - x;
////		//unsigned int position = monPremierCaractereVisible;
////		//sf::String tmp(maChaineMessage.substr(
////		//					monPremierCaractereVisible,
////		//					maChaineMessage.size() - monPremierCaractereVisible), 
////		//			   MaChaineAffichage.GetFont(), 
////		//			   MaChaineAffichage.GetSize());
////		//std::string chaineAffiche = maChaineMessage.substr(
////		//		monPremierCaractereVisible,
////		//		maChaineMessage.size() - monPremierCaractereVisible);
////		std::string chaineAffiche = MaChaineAffichage.GetText();
////
////		for(unsigned int i = 0; i < chaineAffiche.size(); i++)
////		{
////			if(MaChaineAffichage.GetCharacterPos(i).x >= posClicWidgetX)
////			{
////				maPosBarreVerticale = i + monPremierCaractereVisible;
////				break;
////			}
////			else
////			{
////				if(i < chaineAffiche.size() - 1)//if(i == i < chaineAffiche.size() - 1)
////				{
////					maPosBarreVerticale = static_cast<int>(chaineAffiche.size());
////				}
////			}
////		}
////		//while(tmp.GetRect().GetWidth() < (float)posClicWidgetX && position < maChaineMessage.size())
////		//{
////		//	tmp.SetText(maChaineMessage.substr(monPremierCaractereVisible, position - monPremierCaractereVisible + 1));
////		//	position++;
////		//}
////		//maPosBarreVerticale = (int)position;
////	}
////
////	else if (ev.Type == sf::Event::KeyPressed)
////	{
////		if(ev.Key.Code == sf::Key::Left)
////		{
////			maPosBarreVerticale = maPosBarreVerticale == 0 ? 0 : --maPosBarreVerticale;
////			//if(premierCaractereVisible > 0)
////			//	premierCaractereVisible--;
////			MonHorloge.Reset();
////			mettreAJourTexte();
////		}
////
////		else if(ev.Key.Code == sf::Key::Right)
////		{
////			maPosBarreVerticale < (int)maChaineMessage.size() ? 
////									++maPosBarreVerticale : maChaineMessage.size();
////			MonHorloge.Reset();
////			mettreAJourTexte();
////		}
////		
////		else if(ev.Key.Code == sf::Key::Delete)
////		{
////			//if(posBarreVerticale > 0)
////			//	{
////			//		//On regarde si la chaine dépassait de la textbox en longueur
////			//		if(premierCaractereVisible > 0)
////			//		{
////			//			premierCaractereVisible--;
////			//		}
////			//		//On met à jour notre chaine en supprimant le dernier caractère
////			//		//chaineMessage = chaineMessage.substr(0,(chaineMessage.size()-1));
////			//		chaineMessage.erase(chaineMessage.begin() + posBarreVerticale);
////			//	}
////		}
////	}
////
////	if(ev.Type == sf::Event::TextEntered)
////	{
////		//Si on supprime un caractère écrit
////		if (ev.Text.Unicode == '\b')
////		{
////			if (maChaineMessage.size() > 0)
////			{
////				if(maPosBarreVerticale > 0)
////				{
////					maPosBarreVerticale--;
////					//On regarde si la chaine dépassait de la textbox en longueur
////					if(monPremierCaractereVisible > 0)
////					{
////						monPremierCaractereVisible--;
////					}
////					//On met à jour notre chaine en supprimant le dernier caractère
////					//chaineMessage = chaineMessage.substr(0,(chaineMessage.size()-1));
////					maChaineMessage.erase(maChaineMessage.begin() + maPosBarreVerticale);
////				}
////			}
////		}
////		
////		//Ajout de texte au texte en train d'être tapé
////		//else if(ev.Text.Unicode != 13)
////		else if(ev.Text.Unicode >= 32)
////		{
////			//if(chaineMessage.size() < tailleMaxMessage)
////			{
////				//chaineMessage += ev.Text.Unicode;
////				maChaineMessage.insert(maChaineMessage.begin() + maPosBarreVerticale, (char)ev.Text.Unicode);
////				maPosBarreVerticale++;
////			}
////		}
////
////		mettreAJourTexte();
////	}
////
////	BaseWidget::traiterEvenement(ev, posSouris);
////
////	return true;
////}
//
/////////////////////////////////////////////////////////////////////////////////
//// Calcule la partie visible du texte dans la textbox
/////////////////////////////////////////////////////////////////////////////////
//void TextBox::mettreAJourTexte()
//{
//	//On met à jour la chaine qui affichera le texte à l'écran
//	std::string chaineAffichee = maChaineMessage.substr(monPremierCaractereVisible,
//											maChaineMessage.size() - monPremierCaractereVisible);
//		MaChaineAffichage.SetString(chaineAffichee);
//		//sf::Vector2f dernierCaractere = 
//		//	MaChaineAffichage.GetCharacterPos(chaineAffichee.size()- 1);
//		//std::cout << static_cast<int>(dernierCaractere.x) + monRetraitGauche << " " << getWidth() << std::endl;
//		//if(static_cast<int>(dernierCaractere.x) + monRetraitGauche > getWidth())
//		//{
//		//	monPremierCaractereVisible++;
//		//}
//
//		//On fait les tests afin que la chaine ne sorte pas de sa boiboite
//		while(MaChaineAffichage.GetRect().Width > (getWidth() - monRetraitGauche) )
//		{
//			monPremierCaractereVisible++;
//			MaChaineAffichage.SetString(
//				maChaineMessage.substr(monPremierCaractereVisible,
//									 maChaineMessage.size()-monPremierCaractereVisible)
//			);
//		}
//
//		//if(myRenderer)
//		//{
//		//	if(myRenderer->possedePropriete("_texte"))
//		//	{
//		//		myRenderer->setProperty(MaChaineAffichage.GetText());
//		//	}
//		//}
//}
//
/////////////////////////////////////////////////////////////////////////////////
//// Définit le texte de la textebox
/////////////////////////////////////////////////////////////////////////////////
//void TextBox::setText(const std::string& texte)
//{
//	maChaineMessage = texte;
//	monPremierCaractereVisible = 0;
//	maPosBarreVerticale =0;
//	mettreAJourTexte();
//
//	notifyObservers();
//}
//
/////////////////////////////////////////////////////////////////////////////////
//// Ne fait rien...
/////////////////////////////////////////////////////////////////////////////////
//void TextBox::update(unsigned int temps)
//{
//	myTimeAccumulator += temps;
//	const unsigned int intervalle = 330;
//
//	if(myIsDragging)
//	{
//		if(myTimeAccumulator = 0 > intervalle)
//		{
//			if(myMousePos.x > getWidth())
//			{
//				setCaretPosition(getCaretPosition() + 1);
//				myTimeAccumulator = 0;
//				notifyObservers();
//			}
//			else if(myMousePos.x < 0)
//			{
//				setCaretPosition(getCaretPosition() - 1);
//				myTimeAccumulator = 0;
//				notifyObservers();
//			}
//		}
//	}
//	//monDessinerCurseur = (myHasFocus && ((int)(MonHorloge.GetElapsedTime() * 2) % 2 == 0) );
//}
//

/////////////////////////////////////////////////////////////////////////////////
//// Donne ou retire le focus à une textBox
/////////////////////////////////////////////////////////////////////////////////
//void TextBox::requestFocus(bool b)
//{
//	//myHasFocus = b;
//
//	BaseWidget::requestFocus(b);
//
//	if(!hasFocus())
//	{
//		resetSelection();
//	}
//
//	MonHorloge.Reset();
//}
//
//void TextBox::setCaretPosition(unsigned int pos)
//{
//	if(pos >= 0 && pos <= maChaineMessage.size())
//		maPosBarreVerticale = pos;
//
//	//if(getSelectionStart() != getSelectionEnd())
//	//{
//	//	resetSelection();
//	//}
//
//	//if(getSelectionStart() == getSelectionEnd()) //non
//	//{
//		//setSelectionStart(getCaretPosition());
//		//setSelectionEnd(getCaretPosition());
//	//}
//
//}
//
//void TextBox::resetSelection()
//{
//	myLastSelection = myFirstSelection = getCaretPosition();
//
//	//setSelectionStart(getCaretPosition());
//	//setSelectionEnd(getCaretPosition());
//}
//
//void TextBox::moveSelection(int quantite)
//{
//	int tailleTexte = static_cast<int>(getText().size());
//	myLastSelection += quantite;
//	myLastSelection = myLastSelection >  tailleTexte ? tailleTexte : myLastSelection;
//	myLastSelection = myLastSelection < 0 ? 0 : myLastSelection;
//	setCaretPosition(myLastSelection);
//}
//
//};
