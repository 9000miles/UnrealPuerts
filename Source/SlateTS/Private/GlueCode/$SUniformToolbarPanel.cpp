#pragma once

#include "CoreMinimal.h"
#include "JsObject.h"
#include "Binding.hpp"
#include "DTSDefine.h"
#include "TypeInfo.hpp"
#include "UEDataBinding.hpp"
#include "Helper/WidgetHelper.hpp"
#include "DTSHelper.h"
#include "DTSDefine.h"
#include "PuertsEx.h"

UsingCppType(SUniformToolbarPanel);
UsingTSharedPtr(SUniformToolbarPanel);

namespace $SUniformToolbarPanel
{
	static void $Arguments(const v8::FunctionCallbackInfo<v8::Value>& Info, uint8 ArgumentsIndex, v8::Local<v8::Context> Context, v8::Isolate* Isolate, SUniformToolbarPanel::FArguments& Arguments)
	{
		if (!Info[ArgumentsIndex]->IsObject()) return;

		v8::Local<v8::Object> JsObject = Info[ArgumentsIndex].As<v8::Object>();
		$SLATE_SLOT_ARGUMENT(FSlot, Slots, );
		$SLATE_ARGUMENT(const ISlateStyle*, StyleSet, );
		$SLATE_ARGUMENT(FName, StyleName, );
		$SLATE_ARGUMENT(EOrientation, Orientation, );
		$SLATE_ATTRIBUTE(FMargin, SlotPadding, );
		$SLATE_ATTRIBUTE(FVector2D, MinDesiredSlotSize, );
		$SLATE_ATTRIBUTE(float, MaxUniformSize, );
		$SLATE_ATTRIBUTE(float, MinUniformSize, );
		//$SLATE_EVENT(FOnGetContent, OnDropdownOpened, );
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

		SUniformToolbarPanel::FArguments Arguments;
		$Arguments(Info, ArgumentsIndex, Context, Isolate, Arguments);

		FString Filename;
		if (Info[FilenameIndex]->IsString()) Filename = UTF8_TO_TCHAR(*(v8::String::Utf8Value(Isolate, Info[FilenameIndex])));

		TSharedPtr<SUniformToolbarPanel> Widget = MakeTDecl<SUniformToolbarPanel>("SUniformToolbarPanel", TCHAR_TO_ANSI(*Filename), 0, RequiredArgs::MakeRequiredArgs()) <<= Arguments;
		if (InfoLength == 2)
		{
			auto V8Result = puerts::converter::Converter<TSharedPtr<SUniformToolbarPanel>>::toScript(Context, Widget);
			Info.GetReturnValue().Set(V8Result); return;
		}

		if (InfoLength == 3)
		{
			auto RefObject = puerts::DataTransfer::UnRef(Isolate, Info[ExposeIndex]);
			if (Info[ExposeIndex]->IsObject() && RefObject->IsObject() &&
				puerts::DataTransfer::IsInstanceOf(Isolate, puerts::StaticTypeId<TSharedPtr<SUniformToolbarPanel>>::get(), RefObject->ToObject(Context).ToLocalChecked()))
			{
				TSharedPtr<SUniformToolbarPanel>* Arg1 = puerts::DataTransfer::GetPointerFast<TSharedPtr<SUniformToolbarPanel>>(puerts::DataTransfer::UnRef(Isolate, Info[ExposeIndex])->ToObject(Context).ToLocalChecked());
				*Arg1 = Widget; return;
			}
		}
	}
	static void $MakeShared(const v8::FunctionCallbackInfo<v8::Value>& Info)
	{
		v8::Isolate* Isolate = Info.GetIsolate();
		v8::Local<v8::Context> Context = Isolate->GetCurrentContext();

		TSharedPtr<SUniformToolbarPanel> Widget = MakeShared<SUniformToolbarPanel>();
		auto V8Result = puerts::converter::Converter<TSharedPtr<SUniformToolbarPanel>>::toScript(Context, Widget);
		Info.GetReturnValue().Set(V8Result);
	}
	static void $SAssignNew(const v8::FunctionCallbackInfo<v8::Value>& Info) { $SNew(Info); }
}

struct AutoRegister_SUniformToolbarPanel
{
	DTS::DTSArguments RegisterArguments()
	{
		DTS::DTSArguments Args = DTS::DTSArguments("SUniformToolbarPanel");
		Args.Add<FSlot>("Slots", DTS::EArgType::SLATE_SLOT_ARGUMENT);
		Args.Add<const ISlateStyle*>("StyleSet", DTS::EArgType::SLATE_ARGUMENT);
		Args.Add<FName>("StyleName", DTS::EArgType::SLATE_ARGUMENT);
		Args.Add<EOrientation>("Orientation", DTS::EArgType::SLATE_ARGUMENT);
		Args.Add<FMargin>("SlotPadding", DTS::EArgType::SLATE_ATTRIBUTE);
		Args.Add<FVector2D>("MinDesiredSlotSize", DTS::EArgType::SLATE_ATTRIBUTE);
		Args.Add<float>("MaxUniformSize", DTS::EArgType::SLATE_ATTRIBUTE);
		Args.Add<float>("MinUniformSize", DTS::EArgType::SLATE_ATTRIBUTE);
		Args.Add<FOnGetContent>("OnDropdownOpened", DTS::EArgType::SLATE_EVENT);
		return Args;
	}

	void GenDTS()
	{
		DTS::Class ClassDTS = DTS::Class().Name("SUniformToolbarPanel").Super("SPanel")
			.Arguments(RegisterArguments())
			.Functions(DTS::Array<DTS::Function>()
				+ DTS::Function()
				[
					DTS::Function::Slot().Name("SNew").Static(true)
						.Parameters(DTS::Array<DTS::Property>()
							+ DTS::Property().Name("Arguments").Type("SUniformToolbarPanel.Arguments")
							+ DTS::Property().Name("Filename").Type(TS_string)
						)
						.Return(DTS::Property().Type(puerts::ScriptTypeName<TSharedPtr<SUniformToolbarPanel>>::value().Data()))
				]
				+ DTS::Function()
				[
					DTS::Function::Slot().Name("SAssignNew").Static(true)
						.Parameters(DTS::Array<DTS::Property>()
							+ DTS::Property().Name("WidgetRef").Type(puerts::ScriptTypeName<TSharedPtr<SUniformToolbarPanel>>::value().Data()).Out(true)
							+ DTS::Property().Name("Arguments").Type("SUniformToolbarPanel.Arguments")
							+ DTS::Property().Name("Filename").Type(TS_string)
						)
				]
				+ DTS::Function()
				[
					DTS::Function::Slot().Name("MakeShared").Static(true)
						.Return(DTS::Property().Type(puerts::ScriptTypeName<TSharedPtr<SUniformToolbarPanel>>::value().Data()))
				]
			);

		DTS::FClassDTS::Add(ClassDTS);
	}

	AutoRegister_SUniformToolbarPanel()
	{
		GenDTS();
		RegisterTSharedPtr(SUniformToolbarPanel);

		puerts::JSClassDefinition Def = JSClassEmptyDefinition;

		static puerts::JSFunctionInfo Methods[] =
		{
			{0, 0}
		};
		static puerts::JSFunctionInfo Functions[] =
		{
			{"SNew", $SUniformToolbarPanel::$SNew},
			{"SAssignNew", $SUniformToolbarPanel::$SAssignNew},
			{"MakeShared", $SUniformToolbarPanel::$MakeShared},
			{0, 0}
		};

		Def.ScriptName = "SUniformToolbarPanel";
		Def.TypeId = puerts::StaticTypeId<SUniformToolbarPanel>::get();
		Def.SuperTypeId = puerts::StaticTypeId<SPanel>::get();
		Def.Methods = Methods;
		Def.Functions = Functions;

		puerts::RegisterJSClass(Def);
	}
};

AutoRegister_SUniformToolbarPanel _AutoRegister_SUniformToolbarPanel;