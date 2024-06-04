﻿#pragma once

#include "CoreMinimal.h"
#include "JsObject.h"
#include "Binding.hpp"
#include "DTSDefine.h"
#include "TypeInfo.hpp"
#include "DTSHelper.h"
#include "PuertsEx.h"
#include "Helper/WidgetHelper.hpp"

#include "Widgets/Text/STextBlock.h"
#include "../Helper/WidgetAttribute.hpp"

UsingCppType(STextBlock);
UsingTSharedPtr(STextBlock);
UsingTSharedRef(STextBlock);

namespace $STextBlock
{
	static void $Arguments(const v8::FunctionCallbackInfo<v8::Value>& Info, uint8 ArgumentsIndex, v8::Local<v8::Context> Context, v8::Isolate* Isolate, STextBlock::FArguments& Arguments)
	{
		//@TODO 实现从Info读取数据，并赋值到Arguments
		if (!Info[ArgumentsIndex]->IsObject()) return;

		v8::Local<v8::Object> JsObject = Info[ArgumentsIndex].As<v8::Object>();
		$SLATE_ATTRIBUTE(Text);
		$SLATE_STYLE_ARGUMENT(TextStyle);
		$SLATE_ATTRIBUTE(Font);
		$SLATE_ATTRIBUTE(StrikeBrush);
		$SLATE_ATTRIBUTE_WITH_TYPE(ColorAndOpacity, FSlateColor);
		$SLATE_ATTRIBUTE(ShadowOffset);
		$SLATE_ATTRIBUTE(ShadowColorAndOpacity);
		$SLATE_ATTRIBUTE(HighlightColor);
		$SLATE_ATTRIBUTE(HighlightShape);
		$SLATE_ATTRIBUTE(HighlightText);
		$SLATE_ATTRIBUTE(WrapTextAt);
		$SLATE_ATTRIBUTE(AutoWrapText);
		$SLATE_ATTRIBUTE(WrappingPolicy);
		$SLATE_ATTRIBUTE(TransformPolicy);
		$SLATE_ATTRIBUTE(Margin);
		$SLATE_ATTRIBUTE(LineHeightPercentage);
		$SLATE_ATTRIBUTE(Justification);
		$SLATE_ATTRIBUTE_WITH_TYPE(MinDesiredWidth, float);
		$SLATE_ARGUMENT(TextShapingMethod);
		$SLATE_ARGUMENT(TextFlowDirection);
		//SET_VARIABLESLATE_ARGUMENT___A(LineBreakPolicy);
		$SLATE_ARGUMENT(OverflowPolicy);
		$SLATE_ARGUMENT(SimpleTextMode);
		$SLATE_EVENT(OnDoubleClicked);
	}

	static void $SNew(const v8::FunctionCallbackInfo<v8::Value>& Info)
	{
		v8::Isolate* Isolate = Info.GetIsolate();
		v8::Local<v8::Context> Context = Isolate->GetCurrentContext();
		const uint8 InfoLength = Info.Length();
		if (InfoLength <= 1) { puerts::DataTransfer::ThrowException(Isolate, "Invalid argument!"); return; }

		uint8 ExposeIndex = InfoLength == 3 ? 0 : -1;
		uint8 ArgumentsIndex = InfoLength == 3 ? 1 : 0;
		uint8 FilenameIndex = InfoLength == 3 ? 2 : 1;

		STextBlock::FArguments Arguments;
		$Arguments(Info, ArgumentsIndex, Context, Isolate, Arguments);

		FString Filename;
		if (Info[FilenameIndex]->IsString()) Filename = UTF8_TO_TCHAR(*(v8::String::Utf8Value(Isolate, Info[FilenameIndex])));

		TSharedPtr<STextBlock> Widget = MakeTDecl<STextBlock>("STextBlock", TCHAR_TO_ANSI(*Filename), 0, RequiredArgs::MakeRequiredArgs()) <<= Arguments;
		if (InfoLength == 2)
		{
			auto V8Result = puerts::converter::Converter<TSharedPtr<STextBlock>>::toScript(Context, Widget);
			Info.GetReturnValue().Set(V8Result); return;
		}

		if (InfoLength == 3)
		{
			auto RefObject = puerts::DataTransfer::UnRef(Isolate, Info[ExposeIndex]);
			if (Info[ExposeIndex]->IsObject() && RefObject->IsObject() &&
				puerts::DataTransfer::IsInstanceOf(Isolate, puerts::StaticTypeId<TSharedPtr<STextBlock>>::get(), RefObject->ToObject(Context).ToLocalChecked()))
			{
				TSharedPtr<STextBlock>* Arg1 = puerts::DataTransfer::GetPointerFast<TSharedPtr<STextBlock>>(puerts::DataTransfer::UnRef(Isolate, Info[ExposeIndex])->ToObject(Context).ToLocalChecked());
				*Arg1 = Widget; return;
			}
		}
	}
	static void $MakeShared(const v8::FunctionCallbackInfo<v8::Value>& Info)
	{
		v8::Isolate* Isolate = Info.GetIsolate();
		v8::Local<v8::Context> Context = Isolate->GetCurrentContext();

		TSharedPtr<STextBlock> Widget = MakeShared<STextBlock>();
		auto V8Result = puerts::converter::Converter<TSharedPtr<STextBlock>>::toScript(Context, Widget);
		Info.GetReturnValue().Set(V8Result);
	}
	static void $SAssignNew(const v8::FunctionCallbackInfo<v8::Value>& Info) { $SNew(Info); }

	static void GetText(const v8::FunctionCallbackInfo<v8::Value>& Info)
	{
		v8::Isolate* Isolate = Info.GetIsolate();
		v8::Local<v8::Context> Context = Isolate->GetCurrentContext();
		if (Info.Length() == 0)
		{
			auto Self = puerts::converter::Converter<STextBlock*>::toCpp(Context, Info.Holder());
			if (!Self) { puerts::DataTransfer::ThrowException(Isolate, "[STextBlock::GetText] Attempt to access a NULL self pointer"); return; }

			auto MethodResult = Self->GetText();
			auto V8Result = puerts::converter::Converter<FText>::toScript(Context, MethodResult);
			Info.GetReturnValue().Set(V8Result); return;
		}
		puerts::DataTransfer::ThrowException(Isolate, "Invalid argument!");
	}
	static void SetText(const v8::FunctionCallbackInfo<v8::Value>& Info)
	{
		v8::Isolate* Isolate = Info.GetIsolate();
		v8::Local<v8::Context> Context = Isolate->GetCurrentContext();
		if (Info.Length() == 1)
		{
			auto Self = puerts::converter::Converter<STextBlock*>::toCpp(Context, Info.Holder());
			if (!Self) { puerts::DataTransfer::ThrowException(Isolate, "[STextBlock::GetText] Attempt to access a NULL self pointer"); return; }

			v8::Local<v8::Value> JsObject = Info[0].As<v8::Value>();
			auto Ret = WidgetAttribute::MakeAttribute<FText>(Context, JsObject, "");
			Self->SetText(Ret); return;
		}
		puerts::DataTransfer::ThrowException(Isolate, "Invalid argument!");
	}
}

struct AutoRegister_STextBlock
{
	DTS::DTSArguments RegisterArguments()
	{
		DTS::DTSArguments Args = DTS::DTSArguments("STextBlock");
		Args.Add<FText>("Text", DTS::EArgType::SLATE_ATTRIBUTE);
		Args.Add<FTextBlockStyle>("TextStyle", DTS::EArgType::SLATE_STYLE_ARGUMENT);
		Args.Add<FSlateFontInfo>("Font", DTS::EArgType::SLATE_ATTRIBUTE);
		Args.Add<FSlateBrush>("StrikeBrush", DTS::EArgType::SLATE_ATTRIBUTE);
		Args.Add<FLinearColor>("ColorAndOpacity", DTS::EArgType::SLATE_ATTRIBUTE);
		Args.Add<FVector2D>("ShadowOffset", DTS::EArgType::SLATE_ATTRIBUTE);
		Args.Add<FLinearColor>("ShadowColorAndOpacity", DTS::EArgType::SLATE_ATTRIBUTE);
		Args.Add<FLinearColor>("HighlightColor", DTS::EArgType::SLATE_ATTRIBUTE);
		Args.Add<FSlateBrush>("HighlightShape", DTS::EArgType::SLATE_ATTRIBUTE);
		Args.Add<FText>("HighlightText", DTS::EArgType::SLATE_ATTRIBUTE);
		Args.Add<float>("WrapTextAt", DTS::EArgType::SLATE_ATTRIBUTE);
		Args.Add<bool>("AutoWrapText", DTS::EArgType::SLATE_ATTRIBUTE);
		Args.Add<ETextWrappingPolicy>("WrappingPolicy", DTS::EArgType::SLATE_ATTRIBUTE);
		Args.Add<ETextTransformPolicy>("TransformPolicy", DTS::EArgType::SLATE_ATTRIBUTE);
		Args.Add<FMargin>("Margin", DTS::EArgType::SLATE_ATTRIBUTE);
		Args.Add<float>("LineHeightPercentage", DTS::EArgType::SLATE_ATTRIBUTE);
		Args.Add<ETextJustify::Type>("Justification", DTS::EArgType::SLATE_ATTRIBUTE);
		Args.Add<float>("MinDesiredWidth", DTS::EArgType::SLATE_ATTRIBUTE);
		Args.Add<ETextShapingMethod>("TextShapingMethod", DTS::EArgType::SLATE_ARGUMENT);
		Args.Add<ETextFlowDirection>("TextFlowDirection", DTS::EArgType::SLATE_ARGUMENT);
		Args.Add<ETextOverflowPolicy>("OverflowPolicy", DTS::EArgType::SLATE_ARGUMENT);
		Args.Add<bool>("SimpleTextMode", DTS::EArgType::SLATE_ARGUMENT);
		Args.Add<FPointerEventHandler>("OnDoubleClicked", DTS::EArgType::SLATE_EVENT);
		//REGISTER_WIDGET_ARGUMENT_TYPE__LineBreakPolicy(ESlateArgumentType::SLATE_ARGUMENT);
		return Args;
	}

	void GenDTS()
	{
		DTS::Class ClassDTS = DTS::Class().Name("STextBlock").Super("SLeafWidget")
			.Arguments(RegisterArguments())
			.Functions(DTS::Array<DTS::Function>()
				+ DTS::Function()
				[
					DTS::Function::Slot().Name("SNew").Static(true)
						.Parameters(DTS::Array<DTS::Property>()
							+ DTS::Property().Name("Arguments").Type("STextBlock.Arguments")
							+ DTS::Property().Name("Filename").Type(TS_string)
						)
						.Return(DTS::Property().Type(puerts::ScriptTypeName<TSharedPtr<STextBlock>>::value().Data()))
				]
				+ DTS::Function()
				[
					DTS::Function::Slot().Name("SAssignNew").Static(true)
						.Parameters(DTS::Array<DTS::Property>()
							+ DTS::Property().Name("WidgetRef").Type(puerts::ScriptTypeName<TSharedPtr<STextBlock>>::value().Data()).Out(true)
							+ DTS::Property().Name("Arguments").Type("STextBlock.Arguments")
							+ DTS::Property().Name("Filename").Type(TS_string)
						)
				]
				+ DTS::Function()
				[
					DTS::Function::Slot().Name("MakeShared").Static(true)
						.Return(DTS::Property().Type(puerts::ScriptTypeName<TSharedPtr<STextBlock>>::value().Data()))
				]
				+ DTS::Function()
				[
					DTS::Function::Slot().Name("GetText")
						.Return(DTS::Property().Type(TS_string))
				]
				+ DTS::Function()
				[
					DTS::Function::Slot().Name("SetText")
						.Parameters(DTS::Array<DTS::Property>()
							+ DTS::Property().Name("Text").Type(puerts::ScriptTypeName<TAttribute<FText>>::value().Data())
						)
				]
			);

		DTS::FClassDTS::Add(ClassDTS);
	}

	AutoRegister_STextBlock()
	{
		GenDTS();
		RegisterTSharedPtr(STextBlock);


		puerts::JSClassDefinition Def = JSClassEmptyDefinition;

		static puerts::JSFunctionInfo Methods[] =
		{
			{"GetText", $STextBlock::GetText},
			{"SetText", $STextBlock::SetText},
			{0, 0}
		};
		static puerts::JSFunctionInfo Functions[] =
		{
			{"SNew", $STextBlock::$SNew},
			{"SAssignNew", $STextBlock::$SAssignNew},
			{"MakeShared", $STextBlock::$MakeShared},
			{0, 0}
		};

		Def.ScriptName = "STextBlock";
		Def.TypeId = puerts::StaticTypeId<STextBlock>::get();
		Def.SuperTypeId = puerts::StaticTypeId<SLeafWidget>::get();
		Def.Methods = Methods;
		Def.Functions = Functions;

		puerts::RegisterJSClass(Def);
	}
};

AutoRegister_STextBlock _AutoRegister_STextBlock;