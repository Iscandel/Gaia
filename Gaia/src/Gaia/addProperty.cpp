///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "Gaia/addProperty.h"
#include "Gaia/widgets/BaseWidgetProperties.h"
#include "Gaia/widgets/ComboBoxProperties.h"
#include "Gaia/widgets/ImageBoxProperties.h"
#include "Gaia/widgets/ITextProperties.h"
#include "Gaia/widgets/ButtonProperties.h"
#include "Gaia/widgets/TextProperties.h"
#include "Gaia/widgets/LabelProperties.h"
#include "Gaia/widgets/WidgetList.h"


namespace gaia
{
void addDefinedProperties()
{
	//BaseWidget
	addProperty<BaseWidget, properties::BaseVisible>("visible");
	addProperty<BaseWidget, properties::BaseModal>("modal");
	addProperty<BaseWidget, properties::BaseOpaque>("opaque");
	addProperty<BaseWidget, properties::BaseFocusable>("focusable");
	addProperty<BaseWidget, properties::BaseEnableDoubleClick>("doubleClick");
	addProperty<BaseWidget, properties::BaseEnable>("enabled");

	//ImageBox
	addProperty<ImageBox, properties::ImageBoxSetImage>("image");

	//Button
	addProperty<Button, properties::ButtonSetImages>("images");
	addProperty<Button, properties::ButtonSetText>("text");
	addProperty<Button, properties::ButtonSetTextAlignement>("textAlignment");

	//ImageProgressBar

	//IText
	//addProperty<IText, properties::ITextSetText>("text");
	//addProperty<IText, properties::ITextSetTextColor>("textColor");
	//addProperty<BaseTextWidget, properties::TextSetFont>("font");
	//addProperty<IText, properties::ITextSetFontSize>("fontSize");

	//ScrollBar

	//Text widgets
	addProperty<BaseTextWidget, properties::TextSetText>("text");
	addProperty<BaseTextWidget, properties::TextSetTextColor>("textColor");
	addProperty<BaseTextWidget, properties::TextSetFont>("font");
	addProperty<BaseTextWidget, properties::TextSetFontSize>("fontSize");	

	//Label
	addProperty<Label, properties::LabelSetText>("text");
	//addProperty<Label, properties::TexteSetFont>("font");
	addProperty<Label, properties::LabelSetFontSize>("fontSize");
	addProperty<Label ,properties::LabelSetTextColor>("textColor");
	addProperty<Label, properties::LabelAdjustSize>("adjustSize");

	////Textfield

	//ComboBox
	addProperty<ComboBox, properties::ComboBoxSetText>("text");
	addProperty<ComboBox, properties::ComboBoxSetFontSize>("fontSize");
	addProperty<ComboBox ,properties::ComboBoxSetTextColor>("textColor");
}

} //end namespace