#pragma once

#include "CoreMinimal.h"
#include "DTSDefine.h"
//#include "PuertsEx.h"

namespace DTS
{
	struct DTSArguments
	{
		struct FArgument
		{
			FString Name;
			FString Type;
			bool bOptional = true;
			EArgType ArgType;
		private:
			FString GetType();
		public:
			FString GenDTS();
		};

		DTSArguments(FString InName) :Name(InName) {}

		template<typename T> void Add(FString InName, DTS::EArgType ArgType, const bool bOptional = true)
		{
			_Arguments.Add({ InName, puerts::ScriptTypeNameWithNamespace<T>::value().Data(), bOptional, ArgType });
		}
		template<> void Add<DTS::FSlate_Default_Slot>(FString InName, DTS::EArgType ArgType, const bool bOptional)
		{
			_Arguments.Add({ InName, "() => cpp.TSharedRtr<SWidget>", bOptional, ArgType });
		}
		template<> void Add<DTS::FSlate_Named_Slot>(FString InName, DTS::EArgType ArgType, const bool bOptional)
		{
			_Arguments.Add({ InName, "() => cpp.TSharedRtr<SWidget>", bOptional, ArgType });
		}
		template<> void Add<FOnClicked>(FString InName, DTS::EArgType ArgType, const bool bOptional)
		{
			_Arguments.Add({ InName, "() => cpp.FReply", bOptional, ArgType });
		}
		template<> void Add<FSimpleDelegate>(FString InName, DTS::EArgType ArgType, const bool bOptional)
		{
			_Arguments.Add({ InName, "() => void", bOptional, ArgType });
		}
		template<> void Add<FPointerEventHandler>(FString InName, DTS::EArgType ArgType, const bool bOptional)
		{
			_Arguments.Add({ InName, "(Geometry: UE.Geometry, PointerEvent : UE.PointerEvent) => cpp.FReply", bOptional, ArgType });
		}
		template<> void Add<FOnCheckStateChanged>(FString InName, DTS::EArgType ArgType, const bool bOptional)
		{
			_Arguments.Add({ InName, "(UE.ECheckBoxState InNewState) => void", bOptional, ArgType });
		}
		template<> void Add<FOnGetContent>(FString InName, DTS::EArgType ArgType, const bool bOptional)
		{
			_Arguments.Add({ InName, "() => cpp.TSharedRef<SWidget>", bOptional, ArgType });
		}
		template<> void Add<FOnIsOpenChanged>(FString InName, DTS::EArgType ArgType, const bool bOptional)
		{
			_Arguments.Add({ InName, "(boolean bIsOpenChanged) => void", bOptional, ArgType });
		}
		//template<> void Add<FOnComboBoxOpened>(FString InName, DTS::EArgType ArgType, const bool bOptional)
		//{
		//	_Arguments.Add({ InName, "() => void", bOptional, ArgType });
		//}

		FString GenDTS();

	private:
		FString Name;
		TArray<FArgument> _Arguments;
	};
}