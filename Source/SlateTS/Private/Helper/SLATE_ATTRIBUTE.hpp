#pragma once
#include "JsObject.h"
#include "v8.h"
#include "V8Utils.h"
#include "Converter.hpp"
/**
 * WidgetClass 用于判断同名属性，但是不同类型的处理，比如：Style
 */
#define SET_SLATE_ATTRIBUTE(Name, Type)\
	template<typename TArgumentType>\
	void Set_##Name(TArgumentType& Arguments, v8::Isolate* Isolate, v8::Local<v8::Object>& JsObject, const char* VariableName, const char* WidgetClass = "")\
	{\
		v8::Local<v8::Context> Context = Isolate->GetCurrentContext();\
		const bool bHas = JsObject->Has(Context, puerts::FV8Utils::ToV8String(Isolate, VariableName)).FromMaybe(false);\
		if (!bHas) return;\
		v8::Local<v8::Value> JsValue = JsObject->Get(Context, puerts::FV8Utils::ToV8String(Isolate, VariableName)).ToLocalChecked();\
		Arguments._##Name = WidgetAttribute::MakeAttribute<Type>(Context, JsValue, WidgetClass);\
	}

 /** ======================= SET_SLATE_ATTRIBUTE ======================= **/
namespace WidgetArgument4
{
	SET_SLATE_ATTRIBUTE(Text, FText);
	SET_SLATE_ATTRIBUTE(Font, FSlateFontInfo);
	SET_SLATE_ATTRIBUTE(StrikeBrush, const FSlateBrush*);
	SET_SLATE_ATTRIBUTE(ColorAndOpacity, FSlateColor);
	SET_SLATE_ATTRIBUTE(ShadowOffset, FVector2D);
	SET_SLATE_ATTRIBUTE(ShadowColorAndOpacity, FLinearColor);
	SET_SLATE_ATTRIBUTE(HighlightColor, FLinearColor);
	SET_SLATE_ATTRIBUTE(HighlightShape, const FSlateBrush*);
	SET_SLATE_ATTRIBUTE(HighlightText, FText);
	SET_SLATE_ATTRIBUTE(WrapTextAt, float);
	SET_SLATE_ATTRIBUTE(AutoWrapText, bool);
	SET_SLATE_ATTRIBUTE(WrappingPolicy, ETextWrappingPolicy);
	SET_SLATE_ATTRIBUTE(TransformPolicy, ETextTransformPolicy);
	SET_SLATE_ATTRIBUTE(Margin, FMargin);
	SET_SLATE_ATTRIBUTE(Padding, FMargin);
	SET_SLATE_ATTRIBUTE(LineHeightPercentage, float);
	SET_SLATE_ATTRIBUTE(Justification, ETextJustify::Type);
	SET_SLATE_ATTRIBUTE(MinDesiredWidth, float);
	SET_SLATE_ATTRIBUTE(DesiredSizeScale, FVector2D);
	SET_SLATE_ATTRIBUTE(ContentScale, FVector2D);
	SET_SLATE_ATTRIBUTE(ButtonColorAndOpacity, FSlateColor);
	SET_SLATE_ATTRIBUTE(ForegroundColor, FSlateColor);
	SET_SLATE_ATTRIBUTE(BorderBackgroundColor, FSlateColor);
	SET_SLATE_ATTRIBUTE(IsChecked, ECheckBoxState);
	SET_SLATE_ATTRIBUTE(ShowEffectWhenDisabled, bool);
	SET_SLATE_ATTRIBUTE(MenuPlacement, EMenuPlacement);
}
