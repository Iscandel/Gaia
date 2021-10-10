#ifndef H__TYPEDEFLIST_240920111726__H
#define H__TYPEDEFLIST_240920111726__H

#include <memory>

namespace gaia
{
class BaseListBoxItem;
class BaseWidget;
class Button;
class CheckBox;
class ComboBox;
class ComboListBox;
class DefaultContainer;
class Label;
class LinkedLabels;
class ListBox;
class ImageBox;
class NumericTextBox;
class ProgressBar;
class RadioButton;
class ScrollBar;
class Slider;
class TextBox;
class TextField;
class TextListBoxItem;
class Window;
class TitleBar;

typedef std::shared_ptr<BaseListBoxItem> PtrBaseListBoxItem;
typedef std::shared_ptr<BaseWidget> PtrWidget;
typedef std::shared_ptr<Button> PtrButton;
typedef std::shared_ptr<CheckBox> PtrCheckBox;
typedef std::shared_ptr<ComboBox> PtrComboBox;
typedef std::shared_ptr<ComboListBox> PtrComboListBox;
typedef std::shared_ptr<DefaultContainer> PtrDefaultContainer;
typedef std::shared_ptr<ImageBox> PtrImageBox;
typedef std::shared_ptr<Label> PtrLabel;
typedef std::shared_ptr<ListBox> PtrListBox;
typedef std::shared_ptr<LinkedLabels> PtrLinkedLabels;
typedef std::shared_ptr<NumericTextBox> PtrNumericTextBox;
typedef std::shared_ptr<ProgressBar> PtrProgressBar;
typedef std::shared_ptr<RadioButton> PtrRadioButton;
typedef std::shared_ptr<ScrollBar> PtrScrollBar;
typedef std::shared_ptr<Slider> PtrSlider;
typedef std::shared_ptr<TextBox> PtrTextBox;
typedef std::shared_ptr<TextField> PtrTextField;
typedef std::shared_ptr<TextListBoxItem> PtrTextListBoxItem;
typedef std::shared_ptr<Window> PtrWindow;
typedef std::shared_ptr<TitleBar> PtrTitleBar;

}
#endif