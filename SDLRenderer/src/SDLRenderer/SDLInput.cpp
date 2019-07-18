///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "Gaia/SDLRenderer/SDLInput.h"

namespace gaia
{
SDLInput::SDLInput(const SDL_Event& ev)
:myEvent(ev)
{
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void SDLInput::process()
{
	if(myEvent.type == SDL_MOUSEBUTTONDOWN ||
		myEvent.type == SDL_MOUSEBUTTONUP ||
		myEvent.type == SDL_MOUSEMOTION)
	{
		MouseEvent ev;
		switch(myEvent.type)
		{
		case SDL_MOUSEMOTION:
			ev = MouseEvent(NULL, 
				Event::MOUSE_MOVE, 
				myEvent.motion.x, 
				myEvent.motion.y, 
				0.f, 
				MouseButton::NO_BUTTON);
			break;

		case SDL_MOUSEBUTTONDOWN:
			if(myEvent.button.button == SDL_BUTTON_WHEELUP ||
			   myEvent.button.button == SDL_BUTTON_WHEELDOWN)
			{
				float delta = 0.f;
				if(myEvent.button.button == SDL_BUTTON_WHEELUP)
					delta = 1.f;
				else
					delta = -1.f;

				ev = MouseEvent(NULL, 
					Event::MOUSE_WHEEL, 
					-1, 
					-1,
					delta, 
					MouseButton::NO_BUTTON);
			}
			else
			{
				ev = MouseEvent(NULL, 
					Event::MOUSE_PRESSED, 
					myEvent.button.x, 
					myEvent.button.y,
					0.f, 
					getButton(myEvent.button.button));
			}
			break;

		case SDL_MOUSEBUTTONUP:
			ev = MouseEvent(NULL, 
				Event::MOUSE_RELEASED,
				myEvent.button.x, 
				myEvent.button.y,
				0.f, 
				getButton(myEvent.button.button));
			break;

		break;
		}
		myMouseEv.push(ev);
	}
	else if(myEvent.type == ::SDL_KEYDOWN ||
		myEvent.type == ::SDL_KEYUP)
	{
		bool ctrlPressed = (myEvent.key.keysym.mod & KMOD_LCTRL) | 
						   (myEvent.key.keysym.mod & KMOD_RCTRL);
		bool altPressed = (myEvent.key.keysym.mod & KMOD_LALT) | 
						    (myEvent.key.keysym.mod & KMOD_RALT);
		bool shiftPressed = (myEvent.key.keysym.mod & KMOD_LSHIFT) | 
						   (myEvent.key.keysym.mod & KMOD_RSHIFT);
		KeyboardEvent ev(NULL, Event::END, getCode(myEvent.key.keysym.sym), 
			myEvent.key.keysym.unicode, 
			ctrlPressed, altPressed, shiftPressed);

		if(myEvent.type == SDL_KEYDOWN)
			ev.type = Event::KEY_PRESSED;
		else if(myEvent.type == SDL_KEYUP)
			ev.type = Event::KEY_RELEASED;

		myKeyboardEv.push(ev);

		if(myEvent.key.keysym.unicode != 0 && myEvent.type == SDL_KEYDOWN)
		{
			//ev.type = Event::TEXTE_ENTERED;
			KeyboardEvent evText(ev);
			evText.type = Event::TEXT_ENTERED;
			myKeyboardEv.push(evText);
		}
	}
}

MouseButton::Button SDLInput::getButton(Uint8 b)
{
	if(b == SDL_BUTTON_LEFT)
		return MouseButton::LEFT;
	else if(b == SDL_BUTTON_RIGHT)
		return MouseButton::RIGHT;
	else if(b == SDL_BUTTON_MIDDLE)
		return MouseButton::MIDDLE;

	return MouseButton::NO_BUTTON;
}

Keyboard::Code SDLInput::getCode(SDLKey c)
{
	Keyboard::Code res;

	switch(c)
	{
	case SDLK_BACKSPACE:
		res = Keyboard::BACK; break;
	case SDLK_TAB:
		res = Keyboard::TAB; break;
	//case SDLK_CLEAR:
	//	res = Keyboard::TAB; break;
	case SDLK_RETURN:
		res = Keyboard::RETURN; break;
	case SDLK_PAUSE:
		res = Keyboard::PAUSE; break;
	case SDLK_ESCAPE:
		res = Keyboard::ESCAPE; break;
	case SDLK_SPACE:
		res = Keyboard::SPACE; break;
	//case SDLK_EXCLAIM:	
	//	res = Keyboard::eTAB; break;
	//case SDLK_QUOTEDBL:	
	//	res = Keyboard::NUM3; break;
/*	case SDLK_HASH:	
	case SDLK_DOLLAR:		
	case SDLK_AMPERSAND:	
	case SDLK_QUOTE:		
	case SDLK_LEFTPAREN:		
	case SDLK_RIGHTPAREN:	
	case SDLK_ASTERISK:		
	case SDLK_PLUS:	
	case SDLK_COMMA:
	case SDLK_MINUS:		
	case SDLK_PERIOD:		
	case SDLK_SLASH:*/		
	case SDLK_0:
		res = Keyboard::NUM0; break;
	case SDLK_1:
		res = Keyboard::NUM1; break;
	case SDLK_2:
		res = Keyboard::NUM2; break;
	case SDLK_3:	
		res = Keyboard::NUM3; break;
	case SDLK_4:	
		res = Keyboard::NUM4; break;
	case SDLK_5:	
		res = Keyboard::NUM5; break;
	case SDLK_6:
		res = Keyboard::NUM6; break;
	case SDLK_7:	
		res = Keyboard::NUM7; break;
	case SDLK_8:	
		res = Keyboard::NUM8; break;
	case SDLK_9:	
		res = Keyboard::NUM9; break;
/*	case SDLK_COLON:		
	case SDLK_SEMICOLON:		
	case SDLK_LESS:		
	case SDLK_EQUALS:	
	case SDLK_GREATER:
	case SDLK_QUESTION:	
	case SDLK_AT:	*/		
	/* 
	   Skip uppercase letters
	 */
/*	case SDLK_LEFTBRACKET:	
	case SDLK_BACKSLASH:	
	case SDLK_RIGHTBRACKET:	
	case SDLK_CARET:		
	case SDLK_UNDERSCORE:	
	case SDLK_BACKQUOTE:*/		
	case SDLK_a:
		res = Keyboard::A; break;
	case SDLK_b:
		res = Keyboard::B; break;		
	case SDLK_c:
		res = Keyboard::C; break;			
	case SDLK_d:
		res = Keyboard::D; break;		
	case SDLK_e:
		res = Keyboard::E; break;		
	case SDLK_f:
		res = Keyboard::F; break;			
	case SDLK_g:
		res = Keyboard::G; break;		
	case SDLK_h:
		res = Keyboard::H; break;
	case SDLK_i:
		res = Keyboard::I; break;
	case SDLK_j:
		res = Keyboard::J; break;
	case SDLK_k:
		res = Keyboard::K; break;
	case SDLK_l:
		res = Keyboard::L; break;		
	case SDLK_m:
		res = Keyboard::M; break;			
	case SDLK_n:
		res = Keyboard::N; break;			
	case SDLK_o:
		res = Keyboard::O; break;		
	case SDLK_p:
		res = Keyboard::P; break;		
	case SDLK_q:
		res = Keyboard::Q; break;			
	case SDLK_r:
		res = Keyboard::R; break;		
	case SDLK_s:
		res = Keyboard::S; break;
	case SDLK_t:
		res = Keyboard::T; break;
	case SDLK_u:
		res = Keyboard::U; break;
	case SDLK_v:
		res = Keyboard::V; break;
	case SDLK_w:
		res = Keyboard::W; break;
	case SDLK_x:
		res = Keyboard::X; break;
	case SDLK_y:
		res = Keyboard::Y; break;
	case SDLK_z:
		res = Keyboard::Z; break;
	case SDLK_DELETE:		
	/* End of ASCII mapped keysyms */

	/* Numeric keypad */
	case SDLK_KP0:
		res = Keyboard::NUMPAD0; break;
	case SDLK_KP1:res = Keyboard::NUMPAD1; break;
	case SDLK_KP2:res = Keyboard::NUMPAD2; break;
	case SDLK_KP3:res = Keyboard::NUMPAD3; break;
	case SDLK_KP4:res = Keyboard::NUMPAD4; break;
	case SDLK_KP5:res = Keyboard::NUMPAD5; break;
	case SDLK_KP6:res = Keyboard::NUMPAD6; break;
	case SDLK_KP7:res = Keyboard::NUMPAD7; break;
	case SDLK_KP8:res = Keyboard::NUMPAD8; break;
	case SDLK_KP9:res = Keyboard::NUMPAD9; break;
	//case SDLK_KP_PERIOD:		
	case SDLK_KP_DIVIDE:res = Keyboard::DIVIDE; break;		
	case SDLK_KP_MULTIPLY:	res = Keyboard::MULTIPLY; break;
	case SDLK_KP_MINUS:		res = Keyboard::SUBTRACT; break;
	case SDLK_KP_PLUS:	res = Keyboard::ADD; break;
	case SDLK_KP_ENTER:	
		res = Keyboard::RETURN; break;
//	case SDLK_KP_EQUALS:		

	/* Arrows + Home/End pad */
	case SDLK_UP: res = Keyboard::UP; break;	
	case SDLK_DOWN:	res = Keyboard::DOWN; break;	
	case SDLK_RIGHT:	res = Keyboard::RIGHT; break;	
	case SDLK_LEFT:	res = Keyboard::LEFT; break;	
	case SDLK_INSERT:	res = Keyboard::INSERT; break;
	case SDLK_HOME:		res = Keyboard::HOME; break;
	case SDLK_END:	res = Keyboard::END; break;
	case SDLK_PAGEUP:res = Keyboard::PAGEUP; break;		
	case SDLK_PAGEDOWN:	res = Keyboard::PAGEDOWN; break;

	/* Function keys */
	case SDLK_F1:res = Keyboard::F1; break;
	case SDLK_F2:res = Keyboard::F2; break;	
	case SDLK_F3:res = Keyboard::F3; break;
	case SDLK_F4:res = Keyboard::F4; break;
	case SDLK_F5:res = Keyboard::F5; break;
	case SDLK_F6:res = Keyboard::F6; break;
	case SDLK_F7:res = Keyboard::F7; break;
	case SDLK_F8:res = Keyboard::F8; break;
	case SDLK_F9:res = Keyboard::F9; break;
	case SDLK_F10:res = Keyboard::F10; break;
	case SDLK_F11:res = Keyboard::F11; break;
	case SDLK_F12:res = Keyboard::F12; break;
	case SDLK_F13:res = Keyboard::F13; break;
	case SDLK_F14:res = Keyboard::F14; break;
	case SDLK_F15:res = Keyboard::F15; break;

	/* Key state modifier keys */
	//case SDLK_NUMLOCK:		
	//case SDLK_CAPSLOCK:		
	//case SDLK_SCROLLOCK:	
	case SDLK_RSHIFT:res = Keyboard::RSHIFT; break;
	case SDLK_LSHIFT:res = Keyboard::LSHIFT; break;
	case SDLK_RCTRL:res = Keyboard::RCONTROL; break;
	case SDLK_LCTRL:res = Keyboard::LCONTROL; break;
	case SDLK_RALT:res = Keyboard::RALT; break;
	case SDLK_LALT:res = Keyboard::LALT; break;
/*	case SDLK_RMETA:		
	case SDLK_LMETA:	*/	
	//case SDLK_LSUPER:res = Keyboard::LE; break;			/* Left "Windows" key */
	//case SDLK_RSUPER:		,		/* Right "Windows" key */
	//case SDLK_MODE:		/* "Alt Gr" key */
	//case SDLK_COMPOSE:		/* Multi-key compose key */

	/* Miscellaneous function keys */
	//case SDLK_HELP:		
	//case SDLK_PRINT:		
	//case SDLK_SYSREQ:		
	//case SDLK_BREAK:		
	//case SDLK_MENU:		
	//case SDLK_POWER:				/* Power Macintosh power key */
	//case SDLK_EURO:				/* Some european keyboards */
	//case SDLK_UNDO:				/* Atari keyboard has Undo */
	default:
		res = Keyboard::COUNT;
	}

	return res;
}

} //end namespace