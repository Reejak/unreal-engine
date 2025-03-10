﻿// Copyright (c) 2025 Thirdweb. All Rights Reserved.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "TWUOFunctionLibrary.generated.h"

enum class EThirdwebInAppWalletSource : uint8;
struct FThirdwebEngineTransactionStatusResult;
struct FThirdwebCountryCode;
struct FInAppWalletHandle;
struct FSmartWalletHandle;
enum class EFunctionResult : uint8;
enum class EThirdwebOAuthProvider : uint8;

/**
 * Thirdweb Function Library
 */
UCLASS(meta=(BlueprintThreadSafe, DisplayName="Thirdweb", ScriptName="TWUOFunctionLibrary"))
class THIRDWEBUNCOOKEDONLY_API UTWUOFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, DisplayName="To String (In App Wallet Source)", meta=(CompactNodeTitle="=>", BlueprintAutocast), Category="Utilities|String|In App Wallet")
	static FString Conv_ThirdwebInAppWalletSourceToString(EThirdwebInAppWalletSource Source);

	UFUNCTION(BlueprintPure, DisplayName="To Text (In App Wallet Source)", meta=(CompactNodeTitle="=>", BlueprintAutocast), Category="Utilities|Text|In App Wallet")
	static FText Conv_ThirdwebInAppWalletSourceToText(EThirdwebInAppWalletSource Source);
	
	UFUNCTION(BlueprintPure, DisplayName="To In App Wallet Source (String)", meta=(CompactNodeTitle="=>", BlueprintAutocast), Category="Utilities|String|In App Wallet")
	static EThirdwebInAppWalletSource Conv_StringToThirdwebInAppWalletSource(FString Source);

	UFUNCTION(BlueprintPure, DisplayName="To In App Wallet Source (Text)", meta=(CompactNodeTitle="=>", BlueprintAutocast), Category="Utilities|Text|In App Wallet")
	static EThirdwebInAppWalletSource Conv_TextToThirdwebInAppWalletSource(FText Source);

};
