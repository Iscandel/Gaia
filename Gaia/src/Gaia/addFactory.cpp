///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "Gaia/addFactory.h"

namespace gaia
{
	///////////////////////////////////////////////////////////////////////////
	//
	///////////////////////////////////////////////////////////////////////////
	void addDefinedFactories()
	{
		WidgetFactoryManager* Factory = WidgetFactoryManager::getInstance();
	
		Factory->addFactory(PtrWidgetFactory(new TplWidgetFactory<BaseWidget>));
		addFactory<Button>();
		addFactory<Label>();
		addFactory<ImageBox>();
		addFactory<CheckBox>();
		addFactory<DefaultContainer>();
		addFactory<ProgressBar>();
		addFactory<LinkedLabels>();
		addFactory<TextBox>();
		addFactory<NumericTextBox>();		
		addFactory<TextField>();
		addFactory<ScrollBar>();
		addFactory<ListBox>();
		addFactory<ComboBox>();
		addFactory<ComboListBox>();
		addFactory<RadioButton>();
		addFactory<Window>();
		addFactory<TitleBar>();
		addFactory<Slider>();
	}

} //end namespace