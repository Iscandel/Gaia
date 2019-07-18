#include "Gaia/addWidgetRendererFactory.h"
#include "Gaia/widgetRenderers/WidgetRendererList.h"

namespace gaia
{
#define ADD_WIDGET_RENDERER_FACTORY(type) \
	addWidgetRendererFactory<type>(#type);

	void addDefinedWidgetRendererFactories()
	{
		addWidgetRendererFactory<ButtonImageRenderer>("ButtonImageRenderer");
		addWidgetRendererFactory<TextBoxSimpleRenderer>("TextBoxSimpleRenderer");
		addWidgetRendererFactory<LabelRenderer>("LabelRenderer");
		addWidgetRendererFactory<ScrollBarBaseRenderer>("ScrollBarBaseRenderer");

		ADD_WIDGET_RENDERER_FACTORY(ImageBoxRenderer)
		ADD_WIDGET_RENDERER_FACTORY(TextBoxImageRenderer)
		ADD_WIDGET_RENDERER_FACTORY(TextFieldSimpleRenderer)
		ADD_WIDGET_RENDERER_FACTORY(CheckBoxImageRenderer)
		ADD_WIDGET_RENDERER_FACTORY(ListBoxSimpleRenderer)
		ADD_WIDGET_RENDERER_FACTORY(WindowSimpleRenderer)
		ADD_WIDGET_RENDERER_FACTORY(TitleBarSimpleRenderer)
		ADD_WIDGET_RENDERER_FACTORY(TitleBarImageRenderer)
		ADD_WIDGET_RENDERER_FACTORY(WindowImageRenderer)
		ADD_WIDGET_RENDERER_FACTORY(ComboBoxRenderer)
		ADD_WIDGET_RENDERER_FACTORY(RadioButtonImageRenderer)
		ADD_WIDGET_RENDERER_FACTORY(SliderBaseRenderer)
	}

#undef ADD_WIDGET_RENDERER_FACTORY
} //end namespace