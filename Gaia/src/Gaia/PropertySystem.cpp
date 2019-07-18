#include "Gaia/PropertySystem.h"
#include "Gaia/widgets/BaseWidget.h"
#include "Gaia/tools/Logger.h"

namespace gaia
{
//=============================================================================
///////////////////////////////////////////////////////////////////////////////
PropertySystem::PropertySystem(void)
{
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
PropertySystem::~PropertySystem(void)
{
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void PropertySystem::addProperty(const std::string& type, properties::PtrProperty p)
{	
	myProperties[type].insert(std::make_pair(p->getName(), p));
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
bool PropertySystem::deleteProperty(const std::string& type, const std::string& name)
{
	PropertyMultimap::iterator it = myProperties.find(type);
	
	if(it != myProperties.end())
	{
		PropertyMap::iterator it2 = it->second.find(name);
		if(it2 != it->second.end())
		{
			myProperties[type].erase(it2);
			return true;
		}
	}

	return false;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
bool PropertySystem::exists(const std::string& type, const std::string& name)
{
	//Check the type exists
	PropertyMultimap::iterator it = myProperties.find(type);
	if (it != myProperties.end())
	{
		//Look for the name
		PropertyMap::iterator it2 = it->second.find(name);
		if(it2 != it->second.end())
		{
			return true;
		}
	}

	return false;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void PropertySystem::setProperty(const std::string& type, 
								 BaseWidget& parent, 
								 const std::string& name, 
								 const std::string& value)
{
	bool found = false;

	PropertyMultimap::iterator it = myProperties.find(type);
	if (it != myProperties.end())
	{
		PropertyMap::iterator it2 = it->second.find(name);
		if(it2 != it->second.end())
		{
			it2->second->setProperty(parent, value);
			found = true;
		}
	}

	if(!found)
	{
		ILogger::log(ILogger::ERRORS) << "Property " << name << 
					" not found for " << parent.getName() << "`\n";
	}
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
std::string PropertySystem::getProperty(const std::string& type, 
										const std::string& name)
{
	std::string res;

	PropertyMultimap::iterator it = myProperties.find(type);
	if (it != myProperties.end())
	{
		PropertyMap::iterator it2 = it->second.find(name);
		if(it2 != it->second.end())
		{
			res = it2->second->getProperty(name);
		}
	}

	ILogger::log(ILogger::ERRORS) << "Property " << name << " not found for " << type << "\n";

	return res;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
std::vector<properties::PtrProperty> PropertySystem::getProperties(const std::string& type)
{
	std::vector<properties::PtrProperty> res;

	PropertyMultimap::iterator it = myProperties.find(type);
	if (it != myProperties.end())
	{
		PropertyMap::iterator it2 = it->second.begin();
		while(it2 != it->second.end())
		{
			res.push_back(it2->second);
			++it2;
		}
	}

	return res;
}

} //end namespace
