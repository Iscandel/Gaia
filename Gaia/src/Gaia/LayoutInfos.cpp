///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "Gaia/LayoutInfos.h"
#include "Gaia/WidgetManager.h"
#include "Gaia/GuiManager.h"
#include "Gaia/widgets/BaseWidget.h"

namespace gaia
{
LayoutInfos::LayoutInfos(void)
:myPositionIsUpdated(false)
,myWidthIsUpdated(false)
,myHeightIsUpdated(false)
,myCachePos(0.,0.)
,myCacheWidth(0)
,myCacheHeight(0.)
,myIsArea(false)
{
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void LayoutInfos::setPosInfos(LayoutInfos::PositionType type, const std::string& value, bool screenDependent)
{
	myPosition.myPositionType = type;
	myPosition.myRawPos = value;
	myPosition.myIsScreenDependent = screenDependent;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void LayoutInfos::setPosInfos(const Point& value, bool screenDependent)
{
	myPosition.myPositionType = FIXED;
	myPosition.myRawPos = tools::numToString(value.x) + ";" + tools::numToString(value.y);
	myPosition.myIsScreenDependent = screenDependent;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void LayoutInfos::setPosInfos(const std::pair<double, double>& value)
{
	myPosition.myPositionType = RELATIVE;
	myPosition.myRawPos = tools::numToString(value.first) + ";" + tools::numToString(value.second);
	myPosition.myIsScreenDependent = true;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void LayoutInfos::setPosInfos(const std::string& value, bool screenDependent)
{
	myPosition.myPositionType = UNIFORM;
	myPosition.myRawPos = value;
	myPosition.myIsScreenDependent = screenDependent;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void LayoutInfos::setWidthInfos(LayoutInfos::PositionType type, const std::string& value, bool screenDependent)
{
	myWidthType.myPositionType = type;
	myWidthType.myRawPos = value;
	myWidthType.myIsScreenDependent = screenDependent;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void LayoutInfos::setWidthInfos(int value, bool screenDependent)
{
	myWidthType.myPositionType = FIXED;
	myWidthType.myRawPos = tools::numToString(value);
	myWidthType.myIsScreenDependent = screenDependent;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void LayoutInfos::setWidthInfos(double value)
{
	myWidthType.myPositionType = RELATIVE;
	myWidthType.myRawPos = tools::numToString(value);
	myWidthType.myIsScreenDependent = true;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void LayoutInfos::setWidthInfos(const std::string& value, bool screenDependent)
{
	myWidthType.myPositionType = UNIFORM;
	myWidthType.myRawPos = value;
	myWidthType.myIsScreenDependent = screenDependent;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void LayoutInfos::setHeightInfos(LayoutInfos::PositionType type, const std::string& value, bool screenDependent)
{
	myHeightType.myPositionType = type;
	myHeightType.myRawPos = value;
	myHeightType.myIsScreenDependent = screenDependent;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void LayoutInfos::setHeightInfos(int value, bool screenDependent)
{
	myHeightType.myPositionType = FIXED;
	myHeightType.myRawPos = tools::numToString(value);
	myHeightType.myIsScreenDependent = screenDependent;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void LayoutInfos::setHeightInfos(double value)
{
	myHeightType.myPositionType = RELATIVE;
	myHeightType.myRawPos = tools::numToString(value);
	myHeightType.myIsScreenDependent = true;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void LayoutInfos::setHeightInfos(const std::string& value, bool screenDependent)
{
	myHeightType.myPositionType = UNIFORM;
	myHeightType.myRawPos = value;
	myHeightType.myIsScreenDependent = screenDependent;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
IntRect LayoutInfos::getComputedDimensions(BaseWidget* widget)
{
	myPositionIsUpdated = false;
	myWidthIsUpdated = false;
	myHeightIsUpdated = false;

	IntRect res;
	std::pair<double, double> pos = parsePos(widget);
	res.x = static_cast<int>(pos.first);
	res.y = static_cast<int>(pos.second);
	res.width = static_cast<int>(parseWidth(widget));
	res.height = static_cast<int>(parseHeight(widget));

	return res;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
std::pair<double, double> LayoutInfos::parsePos(BaseWidget* widget)
{
	if(myPositionIsUpdated)
		return myCachePos;

	//std::pair<double, double> res;
	double ratioX = GuiManager::getInstance()->getRatioX();
	double ratioY = GuiManager::getInstance()->getRatioY();

	if(myPosition.myPositionType == LayoutInfos::FIXED)
	{

		//res = getAndCheckValues(myPosition.myRawPos);
		myCachePos = getAndCheckValues(myPosition.myRawPos);
		if(myPosition.myIsScreenDependent)
		{
			myCachePos.first *= ratioX;
			myCachePos.second *= ratioY;
		}
	}
	else if(myPosition.myPositionType == LayoutInfos::RELATIVE)
	{
		//res = getAndCheckValues(myPosition.myRawPos);
		//res.first *= widget->getWidth();
		//res.second *= widget->getHeight();

		myCachePos = getAndCheckValues(myPosition.myRawPos);

		if(!myIsArea && widget->getParent())
		{
			myCachePos.first *= widget->getParent()->getWidth();
			myCachePos.second *= widget->getParent()->getHeight();
		}
		else
		{
			myCachePos.first *= widget->getWidth();
			myCachePos.second *= widget->getHeight();
		}
	}
	else
	{
		//res = parsePosLayout(widget, myPosition.myRawPos, myPosition);
		myCachePos = parsePosLayout(widget, myPosition.myRawPos, myPosition);
		if(myPosition.myIsScreenDependent)
		{
			myCachePos.first *= ratioX;
			myCachePos.second *= ratioY;
		}
	}

	myPositionIsUpdated = true;

	return myCachePos;
	//return res;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
double LayoutInfos::parseWidth(BaseWidget* widget)
{
	if(myWidthIsUpdated)
		return myCacheWidth;

	//double res = 0;

	double ratioX = GuiManager::getInstance()->getRatioX();

	if(myWidthType.myPositionType == LayoutInfos::FIXED)
	{
		//res = tools::stringToNum<double>(myWidthType.myRawPos);
		myCacheWidth = tools::stringToNum<double>(myWidthType.myRawPos);
		if(myWidthType.myIsScreenDependent)
		{
			myCacheWidth *= ratioX;
		}
	}
	else if(myWidthType.myPositionType == LayoutInfos::RELATIVE)
	{
		//res = tools::stringToNum<double>(myWidthType.myRawPos);
		//res *= widget->getWidth();
		myCacheWidth = tools::stringToNum<double>(myWidthType.myRawPos);

		if(!myIsArea && widget->getParent())
		{
			myCacheWidth *= widget->getParent()->getWidth();
		}
		else
		{
			myCacheWidth *= widget->getWidth();
		}
	}
	else
	{
		//res = parseLayout(widget, myWidthType.myRawPos, myWidthType);
		myCacheWidth = parseLayout(widget, myWidthType.myRawPos, myWidthType);
		if(myWidthType.myIsScreenDependent)
		{
			myCacheWidth *= ratioX;
		}
	}

	myWidthIsUpdated = true;

	return myCacheWidth;
	//return res;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
double LayoutInfos::parseHeight(BaseWidget* widget)
{
	if(myHeightIsUpdated)
		return myCacheHeight;
	//double res = 0;

	double ratioY = GuiManager::getInstance()->getRatioY();

	if(myHeightType.myPositionType == LayoutInfos::FIXED)
	{
		//res = tools::stringToNum<double>(myHeightType.myRawPos);
		myCacheHeight = tools::stringToNum<double>(myHeightType.myRawPos);
		if(myHeightType.myIsScreenDependent)
		{
			myCacheHeight *= ratioY;
		}
	}
	else if(myHeightType.myPositionType == LayoutInfos::RELATIVE)
	{
		//res = tools::stringToNum<double>(myHeightType.myRawPos);
		//res *= widget->getHeight();
		myCacheHeight = tools::stringToNum<double>(myHeightType.myRawPos);

		if(!myIsArea && widget->getParent())
		{
			myCacheHeight *= widget->getParent()->getHeight();
		}
		else
		{
			myCacheHeight *= widget->getHeight();
		}
	}
	else
	{
		//res = parseLayout(widget, myHeightType.myRawPos, myHeightType);
		myCacheHeight = parseLayout(widget, myHeightType.myRawPos, myHeightType);
		if(myHeightType.myIsScreenDependent)
		{
			myCacheHeight *= ratioY;
		}
	}

	myHeightIsUpdated = true;

	return myCacheHeight;
	//return res;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
std::pair<double, double> LayoutInfos::getAndCheckValues(const std::string& string)
{
	std::pair<double, double> res;
	std::vector<std::string> splittedString = tools::split(string, ";");

	//This also handles the empty string case
	if(splittedString.size() != 2)
	{
		ILogger::log(ILogger::ERRORS) << "Layout infos : \";\" separator probably"
			" missing in " << string << ".\n";
		return res;
	}

	std::istringstream stream(splittedString[0] + " " + splittedString[1]);


	stream >> res.first >> res.second;
	if(stream.fail())
	{
		ILogger::log(ILogger::ERRORS) << "Layout infos : Failed to convert " << string << 
			" into numbers. Unable to parse string.\n";
	}

	return res;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
std::pair<double, double> LayoutInfos::parsePosLayout(BaseWidget* widget, const std::string& string, const Infos& infos)
{
	std::pair<double, double> res;

	std::vector<std::string> splittedString = tools::split(string, ";");

	assert(splittedString.size() == 2);

	res.first = parseLayout(widget, splittedString[0], infos);
	res.second = parseLayout(widget, splittedString[1], infos);

	return res;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
double LayoutInfos::parseLayout(BaseWidget* widget, const std::string& string, const Infos& infos)
{
	//std::vector<std::string> tokens;
	//std::vector<std::string> operators;

	//std::string tmp;
	//for(unsigned int i = 0; i < string.size(); i++)
	//{
	//	if(string[i] == ' ')
	//	{
	//		if(tmp != "")
	//			tokens.push_back(tmp);
	//		tmp = "";
	//	}
	//	else if(string[i] == '+' || string[i] == '-' || string[i] == '*' || string[i] == '/')
	//	{
	//		std::string op; op += string[i];
	//		operators.push_back(op);
	//		if(tmp != "")
	//			tokens.push_back(tmp);
	//		tmp = "";
	//	}
	//	else
	//		tmp += string[i];
	//}

	//if(tmp != "")
	//	tokens.push_back(tmp);

	//double value = convertToken(widget, tokens[0], infos);

	//for(unsigned int i = 0; i < tokens.size() - 1; i++)
	//{
	//	value = computeResult(value, convertToken(widget, tokens[i + 1], infos), operators[i]);
	//}

	RawParser parser(widget, string, infos);
	return parser.eval();

	//return value;
}


//double expression(Token& token, bool get)
//{
//	double left = 0;
//	token = term(left, get);
//	for(;;)
//	{
//	switch(token)
//	{
//	case '+':
//		break;
//	case '-':
//		break;
//	default:
//		break;
//	}
//	}
//}
//
//double term(bool get)
//{
//	double left = 0;
//	Token token = prim(left, get);
//
//	for(;;)
//	{
//	switch(token)
//	{
//	case '*':
//		double val = 0;
//		token = prim(val, true);
//		left *= val;
//		break;
//	case '/':
//		double val = 0;
//		token = prim(d, true);
//		if(val)
//			left /= val;
//		else
//			throw GuiException("Layout infos : division by 0.");
//		
//		break;
//	default:
//		return left;
//	}
//	}
//}

//Token prim(double left, bool get)
//{
//	//double left = 0;
//	Token token;
//	if(get) 
//		token = getToken();
//
//	switch(token)
//	{
//	case '-':
//		return - prim(left, true);
//		break;
//	case '(':
//	{
//		double e = expr(token, true);
//		if (token != ')')
//			ILogger::log(ILogger::ERRORS) << "Layout infos : ) expected.\n";
//		get_token();		// eat ')'
//		left =  e;
//	}
//	default:
//		left = 0;
//		break;
//	}
//
//		if (get) get_token();
//
//	switch (curr_tok) {
//	case NUMBER:		// floating-point constant
//	{	double v = number_value;
//		get_token();
//		return v;
//	}
//	case MINUS:		// unary minus
//		return -prim(true);
//	case LP:
//	{	double e = expr(true);
//		if (curr_tok != RP) return error(") expected");
//		get_token();		// eat ')'
//		return e;
//	}
//	default:
//		return error("primary expected");
//	}
//}
//
//double getToken()
//{
//}

/*
    program:
	END			   // END is end-of-input
	expr_list END

    expr_list:
	expression PRINT	   // PRINT is semicolon
	expression PRINT expr_list

    expression:
	expression + term
	expression - term
	term

    term:
	term / primary
	term * primary
	primary

    primary:
	NUMBER
	NAME
	NAME = expression
	- primary
	( expression )
*/
/*
#include <string>
#include <cctype>
#include<iostream>
#include<map>

//#include<sstream>	// string streams
#include<strstream>	// C-style string streams

using namespace std;

istream* input;	// pointer to input stream

int no_of_errors;	// note: default initialized to 0

double error(const char* s)
{
    no_of_errors++;
    cerr << "error: " << s << '\n';
    return 1;
}

enum Token_value {
	NAME,		NUMBER,		END,
	PLUS='+',	MINUS='-',	MUL='*',	DIV='/',
	PRINT=';',	ASSIGN='=',	LP='(',		RP=')'
};

Token_value curr_tok = PRINT;
double number_value;
string string_value;

Token_value get_token()
{
	char ch;

	do {	// skip whitespace except '\en'
		if(!input->get(ch)) return curr_tok = END;
	} while (ch!='\n' && isspace(ch));

	switch (ch) {
	case ';':
	case '\n':
		return curr_tok=PRINT;
	case '*':
	case '/':
	case '+':
	case '-':
	case '(':
	case ')':
	case '=':
		return curr_tok=Token_value(ch);
	case '0': case '1': case '2': case '3': case '4':
	case '5': case '6': case '7': case '8': case '9':
	case '.':
		input->putback(ch);
		*input >> number_value;
		return curr_tok=NUMBER;
	default:			// NAME, NAME=, or error
		if (isalpha(ch)) {
			string_value = ch;
			while (input->get(ch) && isalnum(ch))
				string_value += ch;	// string_value.push_back(ch);
							// to work around library bug
			input->putback(ch);
			return curr_tok=NAME;
		}
		error("bad token");
		return curr_tok=PRINT;
	}
}

map<string,double> table;

double expr(bool);	// cannot do without


double prim(bool get)		// handle primaries
{
	if (get) get_token();

	switch (curr_tok) {
	case NUMBER:		// floating-point constant
	{	double v = number_value;
		get_token();
		return v;
	}
	case NAME:
	{	double& v = table[string_value];
		if (get_token() == ASSIGN) v = expr(true);
		return v;
	}
	case MINUS:		// unary minus
		return -prim(true);
	case LP:
	{	double e = expr(true);
		if (curr_tok != RP) return error(") expected");
		get_token();		// eat ')'
		return e;
	}
	default:
		return error("primary expected");
	}
}

double term(bool get)		// multiply and divide
{
	double left = prim(get);

	for (;;)
		switch (curr_tok) {
		case MUL:
			left *= prim(true);
			break;
		case DIV:
			if (double d = prim(true)) {
				left /= d;
				break;
			}
			return error("divide by 0");
		default:
			return left;
		}
}

double expr(bool get)		// add and subtract
{
	double left = term(get);

	for (;;)				// ``forever''
		switch (curr_tok) {
		case PLUS:
			left += term(true);
			break;
		case MINUS:
			left -= term(true);
			break;
		default:
			return left;
		}
}



int main(int argc, char* argv[])
{

	switch (argc) {
	case 1:					// read from standard input
		input = &cin;
		break;
	case 2: 				// read argument string
//		input = new istringstream(argv[1]);
		input = new istrstream(argv[1]);
		break;
	default:
		error("too many arguments");
		return 1;
	}

	table["pi"] = 3.1415926535897932385;	// insert predefined names
	table["e"] = 2.7182818284590452354;

	while (*input) {
		get_token();
		if (curr_tok == END) break;
		if (curr_tok == PRINT) continue;
		cout << expr(false) << '\n';
	}

	if (input != &cin) delete input;
	return no_of_errors;
}*/

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
double LayoutInfos::convertToken(BaseWidget* widget, const std::string& token, const Infos&)
{
	double res;

	size_t pos = token.find_last_of("."); // Et si c'est un nombre genre 2.0 ??????????????????????????????????
	std::string lastPart = token;

	if(pos != std::string::npos)
	{
		widget = extractTarget(widget, token.substr(0, pos));
		lastPart = token.substr(pos + 1, std::string::npos);
	}

	if(lastPart == "width")
	{
		if(widget->getLayoutInfos())
			return static_cast<double>(widget->getLayoutInfos()->parseWidth(widget));
		else
			return static_cast<double>(widget->getWidth());
		//res = static_cast<double>(widget->getWidth());
	}
	else if(lastPart == "height")
	{
		if(widget->getLayoutInfos())
			return static_cast<double>(widget->getLayoutInfos()->parseHeight(widget));
		else
			return static_cast<double>(widget->getHeight());
		//res = static_cast<double>(widget->getHeight());
	}
	else if(lastPart == "x")
	{
		if(widget->getLayoutInfos())
			return static_cast<double>(widget->getLayoutInfos()->parsePos(widget).first); //Ok ?
		else
			return static_cast<double>(widget->getX());
	}
	else if(lastPart == "y")
	{
		if(widget->getLayoutInfos())
			return static_cast<double>(widget->getLayoutInfos()->parsePos(widget).second); //Ok ?
		else
			return static_cast<double>(widget->getY());
	}
	else
	{
		if(!tools::sec_stringToNum<double>(lastPart, res))
		{
			ILogger::log(ILogger::ERRORS) << "Layout infos : cannot "
			<< "deduce value from " << token << ". Unable to parse string.\n";

			return 0.;
		}
	}

	return res;

	//if(token == "width")
	//{
	//	if(widget->getLayoutInfos())
	//		return static_cast<double>(widget->getLayoutInfos()->parseWidth(widget));
	//	else
	//		return static_cast<double>(widget->getWidth());
	//	//res = static_cast<double>(widget->getWidth());
	//}
	//else if(token == "height")
	//{
	//	if(widget->getLayoutInfos())
	//		return static_cast<double>(widget->getLayoutInfos()->parseHeight(widget));
	//	else
	//		return static_cast<double>(widget->getHeight());
	//	//res = static_cast<double>(widget->getHeight());
	//}
	//else
	//{
	//	if(token.find(".") != std::string::npos)
	//	{
	//		res = getValueFromFunction(token, widget);
	//	}
	//	else
	//	{
	//		res= tools::stringToNum<double>(token);
	//	}
	//}

	//return res;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
BaseWidget* LayoutInfos::extractTarget(BaseWidget* widget, const std::string& token)
{
	size_t cursor = token.find(".");
	std::string firstPart = token;
	std::string secondPart;
	if(cursor != std::string::npos)
	{
		firstPart = token.substr(0, cursor);
		secondPart = token.substr(cursor + 1, token.size() - (cursor + 1));
	}

	if(firstPart == "parent")
	{
		widget = widget->getParent();
	}
	else
	{
		std::string nameToTest = firstPart;
		//if generic widget
		if(firstPart[0] == '_')
			nameToTest += widget->getName();

		if(widget->isChildPresent(nameToTest))
		{
			widget = (widget->getChild<BaseWidget>(nameToTest)).get();
		}
		else
		{
			ILogger::log(ILogger::ERRORS) << "Layout infos : cannot "
				<< "retrieve widget child from : " << nameToTest << ". Unable to parse string.\n";

			return NULL;
		}
	}

	if(secondPart != "")
	{
		return extractTarget(widget, secondPart);
	}
	else
	{
		return widget;
	}

	//size_t cursor = std::string::npos;
	//std::string string = token;

	//do
	//{
	//	std::string firstPart = token.substr(0, cursor);

	//	if(firstPart == "parent")
	//	{
	//		widget = widget->getParent();
	//	}
	//	else
	//	{
	//		std::string nameToTest = firstPart;
	//		//if generic widget
	//		if(firstPart[0] == '_')
	//			nameToTest += widget->getName();

	//		if(widget->isChildPresent(nameToTest))
	//		{
	//			widget = (widget->getChild<BaseWidget>(nameToTest)).get();
	//		}
	//		else
	//		{
	//			ILogger::log(ILogger::ERRORS) << "Layout infos : cannot "
	//				<< "retrieve widget child from : " << nameToTest << ". Unable to parse string.";

	//			return NULL;
	//		}
	//	}

	//	string = string.substr(cursor + 1, std::string::npos);
	//}while(cursor = string.find(".")) != std::string::npos);
	//
	//return widget;
}

//double LayoutInfos::getValueFromFunction(const std::string& token, BaseWidget* widget)
//{
//	size_t cursor = 0;
//
//	cursor = token.find(".");
//	if(cursor != std::string::npos)
//	{
//		std::string firstPart = token.substr(0, cursor);
//		std::string secondPart = token.substr(cursor + 1, std::string::npos);
//
//		if(firstPart == "parent")
//		{
//			widget = widget->getParent();
//		}
//		else
//		{
//			std::string nameToTest = firstPart;
//			//if generic widget
//			if(firstPart[0] == '_')
//				nameToTest += widget->getName();
//
//			widget = WidgetsManager::getInstance()->getWidget<BaseWidget>(nameToTest).get();
//		
//			//if(widget->isChildPresent(nameToTest))
//			{
//				//widget = (widget->getChild<BaseWidget>(nameToTest)).get();
//			}
//			//else
//			if(widget == NULL)
//			{
//				ILogger::log(ILogger::ERRORS) << "Layout infos : cannot "
//					<< "retrieve widget child from : " << nameToTest << ". Unable to parse string.";
//
//				return 0;
//			}
//		}
//
//		if((cursor = secondPart.find(".")) != std::string::npos)
//		{
//			return getValueFromFunction(secondPart, widget);
//		}
//		else
//		{
//			if(secondPart == "width")
//			{
//				if(widget->getLayoutInfos())
//					return static_cast<double>(widget->getLayoutInfos()->parseWidth(widget));
//				else
//					return static_cast<double>(widget->getWidth());
//			}
//			else if(secondPart == "height")
//			{
//				if(widget->getLayoutInfos())
//					return static_cast<double>(widget->getLayoutInfos()->parseHeight(widget));
//				else
//					return static_cast<double>(widget->getHeight());
//			}
//			else if(secondPart == "x")
//			{
//				return static_cast<double>(widget->getX());
//			}
//			else if(secondPart == "y")
//			{
//				return static_cast<double>(widget->getY());
//			}
//			else
//			{
//				ILogger::log(ILogger::ERRORS) << "Layout infos : cannot "
//					<< "deduce function from " << secondPart << ". Unable to parse string.";
//
//				return 0.;
//			}
//		}
//	}
//	else
//	{
//		ILogger::log(ILogger::ERRORS) << "Layout infos : cannot "
//			<< "deduce function from " << token << ". Unable to parse string.";
//
//		return 0.;
//	}
//}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
double LayoutInfos::computeResult(double v1, double v2, const std::string& op)
{
	if(op == "+")
		return v1 + v2;
	else if(op == "-")
		return v1 - v2;
	else if(op == "*")
		return v1 * v2;
	else if(op == "/")
		return v1 / v2;
	else
	{
		ILogger::log(ILogger::ERRORS) << "Layout infos : unknown operators " <<
								op << ". Unable to parse for resizing.\n";
		return v1;
	}
}


RawParser::RawParser(BaseWidget* widget, const std::string& string, const gaia::LayoutInfos::Infos& infos)
	:myString(string)
	,number_value(0)
	,myCurrentToken(END)
	//std::string string_value;
	,myCurrentTokenIndex(-1)
	,myWidget(widget)
	,myInfos(infos)
{
	std::string tmp;
	for(unsigned int i = 0; i < string.size(); i++)
	{
		if(string[i] == ' ')
		{
			if(tmp != "")
				myTokens.push_back(tmp);
			tmp = "";
		}
		else if(string[i] == '+' || string[i] == '-' || string[i] == '*' || string[i] == '/')
		{
			if(tmp != "")
				myTokens.push_back(tmp);
			tmp = "";

			std::string op; op += string[i];
			myTokens.push_back(op);
		}
		else
			tmp += string[i];
	}

	if(tmp != "")
		myTokens.push_back(tmp);
}

double RawParser::eval()
{
	get_token();
	if (myCurrentToken == END) return 0;
	//if (curr_tok == PRINT) continue;
	return expr(false);
}

double RawParser::convertToken(BaseWidget* widget, const std::string& token, const LayoutInfos::Infos&)
{
	double res;

	size_t pos = token.find_last_of("."); // Et si c'est un nombre genre 2.0 ??????????????????????????????????
	std::string lastPart = token;

	if(pos != std::string::npos)
	{
		widget = extractTarget(widget, token.substr(0, pos));
		lastPart = token.substr(pos + 1, std::string::npos);
	}

	if(lastPart == "width")
	{
		if(widget->getLayoutInfos())
			return static_cast<double>(widget->getLayoutInfos()->parseWidth(widget));
		else
			return static_cast<double>(widget->getWidth());
		//res = static_cast<double>(widget->getWidth());
	}
	else if(lastPart == "height")
	{
		if(widget->getLayoutInfos())
			return static_cast<double>(widget->getLayoutInfos()->parseHeight(widget));
		else
			return static_cast<double>(widget->getHeight());
		//res = static_cast<double>(widget->getHeight());
	}
	else if(lastPart == "x")
	{
		if(widget->getLayoutInfos())
			return static_cast<double>(widget->getLayoutInfos()->parsePos(widget).first); //Ok ?
		else
			return static_cast<double>(widget->getX());
	}
	else if(lastPart == "y")
	{
		if(widget->getLayoutInfos())
			return static_cast<double>(widget->getLayoutInfos()->parsePos(widget).second); //Ok ?
		else
			return static_cast<double>(widget->getY());
	}
	else
	{
		if(!tools::sec_stringToNum<double>(lastPart, res))
		{
			ILogger::log(ILogger::ERRORS) << "Layout infos : cannot "
				<< "deduce value from " << token << ". Unable to parse string.\n";

			return 0.;
		}
	}

	return res;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
BaseWidget* RawParser::extractTarget(BaseWidget* widget, const std::string& token)
{
	size_t cursor = token.find(".");
	std::string firstPart = token;
	std::string secondPart;
	if(cursor != std::string::npos)
	{
		firstPart = token.substr(0, cursor);
		secondPart = token.substr(cursor + 1, token.size() - (cursor + 1));
	}

	if(firstPart == "parent")
	{
		widget = widget->getParent();
	}
	else
	{
		std::string nameToTest = firstPart;
		//if generic widget
		if(firstPart[0] == '_')
			nameToTest += widget->getName();

		if(widget->isChildPresent(nameToTest))
		{
			widget = (widget->getChild<BaseWidget>(nameToTest)).get();
		}
		else
		{
			ILogger::log(ILogger::ERRORS) << "Layout infos : cannot "
				<< "retrieve widget child from : " << nameToTest << ". Unable to parse string.\n";

			return NULL;
		}
	}

	if(secondPart != "")
	{
		return extractTarget(widget, secondPart);
	}
	else
	{
		return widget;
	}
}

RawParser::TokenValue RawParser::get_token()
{
	if(myCurrentTokenIndex < (int)myTokens.size() - 1)
	{
		myCurrentTokenIndex++;
	}

	switch (myTokens[myCurrentTokenIndex][0]) {
		//case ';':
		//case '\n':
		//	return curr_tok=PRINT;
	case '*':
	case '/':
	case '+':
	case '-':
	case '(':
	case ')':
	case '=':
		return myCurrentToken = TokenValue(myTokens[myCurrentTokenIndex][0]);
		//case '0': case '1': case '2': case '3': case '4':
		//case '5': case '6': case '7': case '8': case '9':
		//case '.':
		//	input->putback(ch);
		//	*input >> number_value;
		//	return curr_tok=NUMBER;
	default:			// NAME, NAME=, or error
		number_value = convertToken(myWidget, myTokens[myCurrentTokenIndex], myInfos);
		return myCurrentToken = NUMBER;
		//if (isalpha(ch)) {
		//	string_value = ch;
		//	while (input->get(ch) && isalnum(ch))
		//		string_value += ch;	// string_value.push_back(ch);
		//	// to work around library bug
		//	input->putback(ch);
		//	return curr_tok=NAME;
		//}
		//ILogger::log(ILogger::ERRORS) << "Layout infos : Bad token.\n ";
		//return curr_tok=PRINT;
	}
}

double RawParser::prim(bool get)		// handle primaries
{
	if (get) 
		myCurrentToken = get_token();

	switch (myCurrentToken) {
	case NUMBER:		// floating-point constant
		{	
			double v = number_value;
			get_token();
			return v;
		}
		//case NAME:
		//	{	double& v = table[string_value];
		//	if (get_token() == ASSIGN) v = expr(true);
		//	return v;
		//	}
	case MINUS:		// unary minus
		return -prim(true);
	case LP:
		{	double e = expr(true);
		if (myCurrentToken != RP) 
		{
			ILogger::log(ILogger::ERRORS) << "Layout infos: ) expected.";
			return 0;
		}
		get_token();		// eat ')'
		return e;
		}
	default:
		ILogger::log(ILogger::ERRORS) << "Layout infos: primary expected.\n";
		return 0;
	}
}

double RawParser::term(bool get)		// multiply and divide
{
	double left = prim(get);

	for (;;)
		switch (myCurrentToken) {
		case MUL:
			left *= prim(true);
			break;
		case DIV:
			if (double d = prim(true)) {
				left /= d;
				break;
			}
			ILogger::log(ILogger::ERRORS) << "Layout infos: divide by 0.\n";
			return 0;
		default:
			return left;
	}
}

double RawParser::expr(bool get)		// add and subtract
{
	double left = term(get);

	for (;;)				// ``forever''
		switch (myCurrentToken) {
		case PLUS:
			left += term(true);
			break;
		case MINUS:
			left -= term(true);
			break;
		default:
			return left;
	}
}

} //end namespace
