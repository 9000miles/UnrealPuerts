#pragma once
#include "JsObject.h"
#include "v8.h"
#include "V8Utils.h"
#include "Converter.hpp"
#define SET_SLATE_STYLE_ARGUMENT(Name, Type)\
	template<typename TArgumentType>\
	void Set_##Name(TArgumentType& Arguments, v8::Isolate* Isolate, v8::Local<v8::Object>& JsObject, const char* VariableName, const char* WidgetClass = "")\
	{\
		v8::Local<v8::Context> Context = Isolate->GetCurrentContext();\
		const bool bHas = JsObject->Has(Context, puerts::FV8Utils::ToV8String(Isolate, VariableName)).FromMaybe(false);\
		if (!bHas) return;\
		if (puerts::converter::Converter<Type>::accept(Context, JsObject))\
		{\
			Type* Ret = puerts::converter::Converter<Type*>::toCpp(Context, JsObject);\
			Arguments._##Name = Ret;\
		}\
	}
/** ======================= SLATE_STYLE_ARGUMENT ======================= **/
namespace WidgetArgument4
{

	SET_SLATE_STYLE_ARGUMENT(TextStyle, FTextBlockStyle);
	SET_SLATE_STYLE_ARGUMENT(Style, FCheckBoxStyle);
	SET_SLATE_STYLE_ARGUMENT(ComboButtonStyle, FComboButtonStyle);
	//SET_SLATE_STYLE_ARGUMENT(ButtonStyle, FButtonStyle);

}