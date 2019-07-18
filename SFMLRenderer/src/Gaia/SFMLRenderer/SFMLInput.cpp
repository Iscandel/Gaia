///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "Gaia/SFMLRenderer/SFMLInput.h"

namespace gaia
{
SFMLInput::SFMLInput(const sf::Event& ev)
:myEvent(ev)
{
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void SFMLInput::process()
{
	if(myEvent.type == sf::Event::MouseButtonPressed ||
		myEvent.type == sf::Event::MouseButtonReleased ||
		myEvent.type == sf::Event::MouseWheelMoved ||
		myEvent.type == sf::Event::MouseMoved)
	{
		MouseEvent ev;
		switch(myEvent.type)
		{
		case sf::Event::MouseMoved:
			ev = MouseEvent(NULL, 
				Event::MOUSE_MOVE, 
				myEvent.mouseMove.x, 
				myEvent.mouseMove.y, 
				0.f, 
				MouseButton::NO_BUTTON);
			break;

		case sf::Event::MouseButtonPressed:
			ev = MouseEvent(NULL, 
				Event::MOUSE_PRESSED, 
				myEvent.mouseButton.x, 
				myEvent.mouseButton.y, 0.f, 
				getButton(myEvent.mouseButton.button));
			break;

		case sf::Event::MouseButtonReleased:
			ev = MouseEvent(NULL, 
				Event::MOUSE_RELEASED,
				myEvent.mouseButton.x, 
				myEvent.mouseButton.y, 
				0.f, 
				getButton(myEvent.mouseButton.button));
			break;

		case sf::Event::MouseWheelMoved:
			ev = MouseEvent(NULL, 
				Event::MOUSE_WHEEL, 
				-1, 
				-1, 
				static_cast<float>(myEvent.mouseWheel.delta), 
				MouseButton::NO_BUTTON);
		break;
		}
		myMouseEv.push(ev);
	}
	else if(myEvent.type == sf::Event::KeyPressed ||
		myEvent.type == sf::Event::KeyReleased ||
		myEvent.type == sf::Event::TextEntered)
	{
		KeyboardEvent ev(NULL, Event::END, getCode(myEvent.key.code), 
		myEvent.type == sf::Event::TextEntered ? myEvent.text.unicode : 0, 
		myEvent.key.shift, myEvent.key.alt, myEvent.key.control);

		if(myEvent.type == sf::Event::KeyPressed)
			ev.type = Event::KEY_PRESSED;
		else if(myEvent.type == sf::Event::KeyReleased)
			ev.type = Event::KEY_RELEASED;
		else if(myEvent.type == sf::Event::TextEntered)
			ev.type = Event::TEXT_ENTERED;

		myKeyboardEv.push(ev);
	}
}

MouseButton::Button SFMLInput::getButton(sf::Mouse::Button b)
{
	if(b == sf::Mouse::Left)
		return MouseButton::LEFT;
	else if(b == sf::Mouse::Right)
		return MouseButton::RIGHT;
	else if(b == sf::Mouse::Middle)
		return MouseButton::MIDDLE;
	//else if(b == sf::Mouse::XButton1)
	//	return MouseButton::XBOUTON1;
	//else if(b == sf::Mouse::XButton2)
	//	return MouseButton::XBOUTON2;

	return MouseButton::NO_BUTTON;
}

Keyboard::Code SFMLInput::getCode(sf::Keyboard::Key c)
{
	Keyboard::Code res;

	switch(c)
	{
	case sf::Keyboard::A: 
		res = Keyboard::A; break;
	case sf::Keyboard::B: 
		res = Keyboard::B; break;
	case sf::Keyboard::C: 
		res = Keyboard::C; break;
	case sf::Keyboard::D: 
		res = Keyboard::D; break;
	case sf::Keyboard::E: 
		res = Keyboard::E; break;
	case sf::Keyboard::F: 
		res = Keyboard::F; break;
	case sf::Keyboard::G: 
		res = Keyboard::G; break;
	case sf::Keyboard::H: 
		res = Keyboard::H; break;
	case sf::Keyboard::I: 
		res = Keyboard::I; break;
	case sf::Keyboard::J: 
		res = Keyboard::J; break;
	case sf::Keyboard::K: 
		res = Keyboard::K; break;
	case sf::Keyboard::L: 
		res = Keyboard::L; break;
	case sf::Keyboard::M: 
		res = Keyboard::M; break;
	case sf::Keyboard::N: 
		res = Keyboard::N; break;
	case sf::Keyboard::O: 
		res = Keyboard::O; break;
	case sf::Keyboard::P: 
		res = Keyboard::P; break;
	case sf::Keyboard::Q: 
		res = Keyboard::Q; break;
	case sf::Keyboard::R: 
		res = Keyboard::R; break;
	case sf::Keyboard::S: 
		res = Keyboard::S; break;
	case sf::Keyboard::T: 
		res = Keyboard::T; break;
	case sf::Keyboard::U: 
		res = Keyboard::U; break;
	case sf::Keyboard::V: 
		res = Keyboard::V; break;
	case sf::Keyboard::W: 
		res = Keyboard::W; break;
	case sf::Keyboard::X: 
		res = Keyboard::X; break;
	case sf::Keyboard::Y: 
		res = Keyboard::Y; break;
	case sf::Keyboard::Z: 
		res = Keyboard::Z; break;
	case sf::Keyboard::Num0: 
		res = Keyboard::NUM0; break;
	case sf::Keyboard::Num1: 
		res = Keyboard::NUM1; break;
	case sf::Keyboard::Num2: 
		res = Keyboard::NUM2; break;
	case sf::Keyboard::Num3: 
		res = Keyboard::NUM3; break;
	case sf::Keyboard::Num4: 
		res = Keyboard::NUM4; break;
	case sf::Keyboard::Num5: 
		res = Keyboard::NUM5; break;
	case sf::Keyboard::Num6: 
		res = Keyboard::NUM6; break;
	case sf::Keyboard::Num7: 
		res = Keyboard::NUM7; break;
	case sf::Keyboard::Num8: 
		res = Keyboard::NUM8; break;
	case sf::Keyboard::Num9: 
		res = Keyboard::NUM9; break;
	case sf::Keyboard::Escape: 
		res = Keyboard::ESCAPE; break;
	case sf::Keyboard::LControl: 
		res = Keyboard::LCONTROL; break;
	case sf::Keyboard::LShift: 
		res = Keyboard::LSHIFT; break;
	case sf::Keyboard::LAlt: 
		res = Keyboard::LALT; break;
	case sf::Keyboard::LSystem: 
		res = Keyboard::LSSYSTEM; break;
	case sf::Keyboard::RControl: 
		res = Keyboard::RCONTROL; break;
	case sf::Keyboard::RShift: 
		res = Keyboard::RSHIFT; break;
	case sf::Keyboard::RAlt: 
		res = Keyboard::RALT; break;
	case sf::Keyboard::RSystem: 
		res = Keyboard::RSYSTEM; break;
	case sf::Keyboard::Menu :
		res = Keyboard::MENU; break;
	case sf::Keyboard::LBracket: 
		res = Keyboard::LBRACKET; break;
	case sf::Keyboard::RBracket: 
		res = Keyboard::RBRACKET; break;
	case sf::Keyboard::SemiColon: 
		res = Keyboard::SEMICOLON; break;
	case sf::Keyboard::Comma: 
		res = Keyboard::COMMA; break;; break;
	case sf::Keyboard::Period: 
		res = Keyboard::PERIOD; break;
	case sf::Keyboard::Quote: 
		res = Keyboard::QUOTE; break;
	case sf::Keyboard::Slash: 
		res = Keyboard::SLASH; break;
	case sf::Keyboard::BackSlash: 
		res = Keyboard::BACKSLAH; break;
	case sf::Keyboard::Tilde: 
		res = Keyboard::TILDE; break;
	case sf::Keyboard::Equal: 
		res = Keyboard::EQUAL; break;
	case sf::Keyboard::Dash: 
		res = Keyboard::DASH; break;
	case sf::Keyboard::Space: 
		res = Keyboard::SPACE; break;
	case sf::Keyboard::Return: 
		res = Keyboard::RETURN; break;
	case sf::Keyboard::BackSpace:
		res = Keyboard::BACK; break;
	case sf::Keyboard::Tab: 
		res = Keyboard::TAB; break;
	case sf::Keyboard::PageUp: 
		res = Keyboard::PAGEUP; break;
	case sf::Keyboard::PageDown: 
		res = Keyboard::PAGEDOWN; break;
	case sf::Keyboard::End:
		res = Keyboard::END; break;
	case sf::Keyboard::Home: 
		res = Keyboard::HOME; break;
	case sf::Keyboard::Insert: 
		res = Keyboard::INSERT; break;
	case sf::Keyboard::Delete: 
		res = Keyboard::DEL; break;
	case sf::Keyboard::Add: 
		res = Keyboard::ADD; break;
	case sf::Keyboard::Subtract: 
		res = Keyboard::SUBTRACT; break;
	case sf::Keyboard::Multiply: 
		res = Keyboard::MULTIPLY; break;
	case sf::Keyboard::Divide: 
		res = Keyboard::DIVIDE; break;
	case sf::Keyboard::Left: 
		res = Keyboard::LEFT; break;
	case sf::Keyboard::Right: 
		res = Keyboard::RIGHT; break;
	case sf::Keyboard::Up: 
		res = Keyboard::UP; break;
	case sf::Keyboard::Down: 
		res = Keyboard::DOWN; break;
	case sf::Keyboard::Numpad0: 
		res = Keyboard::NUMPAD0; break;
	case sf::Keyboard::Numpad1: 
		res = Keyboard::NUMPAD1; break;
	case sf::Keyboard::Numpad2: 
		res = Keyboard::NUMPAD2; break;
	case sf::Keyboard::Numpad3: 
		res = Keyboard::NUMPAD3; break;
	case sf::Keyboard::Numpad4: 
		res = Keyboard::NUMPAD4; break;
	case sf::Keyboard::Numpad5: 
		res = Keyboard::NUMPAD5; break;
	case sf::Keyboard::Numpad6: 
		res = Keyboard::NUMPAD6; break;
	case sf::Keyboard::Numpad7: 
		res = Keyboard::NUMPAD7; break;
	case sf::Keyboard::Numpad8: 
		res = Keyboard::NUMPAD8; break;
	case sf::Keyboard::Numpad9: 
		res = Keyboard::NUMPAD9; break;
	case sf::Keyboard::F1: 
		res = Keyboard::F1; break;
	case sf::Keyboard::F2: 
		res = Keyboard::F2; break;
	case sf::Keyboard::F3: 
		res = Keyboard::F3; break;
	case sf::Keyboard::F4: 
		res = Keyboard::F4; break;
	case sf::Keyboard::F5: 
		res = Keyboard::F5; break;
	case sf::Keyboard::F6: 
		res = Keyboard::F6; break;
	case sf::Keyboard::F7: 
		res = Keyboard::F7; break;
	case sf::Keyboard::F8: 
		res = Keyboard::F8; break;
	case sf::Keyboard::F9: 
		res = Keyboard::F9; break;
	case sf::Keyboard::F10: 
		res = Keyboard::F10; break;
	case sf::Keyboard::F11: 
		res = Keyboard::F11; break;
	case sf::Keyboard::F12: 
		res = Keyboard::F12; break;
	case sf::Keyboard::F13: 
		res = Keyboard::F13; break;
	case sf::Keyboard::F14: 
		res = Keyboard::F14; break;
	case sf::Keyboard::F15: 
		res = Keyboard::F15; break;
	case sf::Keyboard::Pause: 
		res = Keyboard::PAUSE; break;
	default:
		res = Keyboard::COUNT;
	}

	return res;
}

} //end namespace