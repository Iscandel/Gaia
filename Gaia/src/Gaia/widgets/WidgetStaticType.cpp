#include "Gaia/widgets/WidgetStaticType.h"

#include "Gaia/tools/Logger.h"

namespace gaia
{
namespace priv
{
//WidgetNode WidgetNode::myBase("BaseWidget");

WidgetNode::WidgetNode(const std::string& name)
:myName(name)
,myParent(NULL)
{
}

void WidgetNode::addParent(WidgetNode* parent)
{
	myParent = parent;
}

void WidgetNode::addChild(const WidgetNode& node)
{
	myChildren.push_back(node);
	myChildren.back().addParent(this);
}

const WidgetNode* WidgetNode::getParent() const
{
	return myParent;
}

const std::string& WidgetNode::getName() const 
{
	return myName;
}

std::list<WidgetNode>& WidgetNode::getChildren()
{
	return myChildren;
}

WidgetNode* findNode(const std::string& type, WidgetNode& base)
{
	if(base.getName() == type)
		return &base;

	std::list<WidgetNode>& children = base.getChildren();

	std::list<WidgetNode>::iterator it = children.begin();
	while(it != children.end())
	{
		if(it->getName() == type)
			return &(*it);
		else
		{
			WidgetNode* node = findNode(type, *it);
			if(node)
				return node;
		}

		++it;
	}

	return NULL;
}

std::string getParentType(const std::string& type)
{
	const WidgetNode* node = findNode(type);
	if(node)
	{
		const WidgetNode* parentNode = node->getParent();
		if(parentNode)
			return parentNode->getName();
	}
	return "";
}

void addWidgetNode(const std::string& widgetType, const std::string& parentType)
{
	WidgetNode* parentNode = findNode(parentType);
	WidgetNode node(widgetType);

	if(parentNode)
	{
		parentNode->addChild(node);
	}
	else
	{
		ILogger::log(ILogger::ERRORS) << "Cannot register widget hierarchy of " 
			<< widgetType << ". " << parentType << " was not found.\n";
	}
}

WidgetNode& WidgetNode::getRoot()
{
	static WidgetNode myBase("BaseWidget"); 

	return myBase;
}

} //end namespace priv
} //end namespacegaia