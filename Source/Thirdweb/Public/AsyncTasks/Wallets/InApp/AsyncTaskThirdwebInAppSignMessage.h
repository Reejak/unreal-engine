// Copyright (c) 2025 Thirdweb. All Rights Reserved.

#pragma once

#include "AsyncTaskThirdwebInAppBase.h"
#include "AsyncTaskThirdwebInAppSignMessage.generated.h"

UCLASS(meta=(HasDedicatedAsyncNode))
class THIRDWEB_API UAsyncTaskThirdwebInAppSignMessage : public UAsyncTaskThirdwebInAppBase
{
	GENERATED_BODY()

public:
	virtual void Activate() override;

	UFUNCTION(BlueprintCallable,
		meta=(BlueprintInternalUseOnly="true", WorldContext="WorldContextObject", AutoCreateRefTerm="Message"),
		DisplayName="Sign Message",
		Category="Thirdweb|Wallets|InApp")
	static UAsyncTaskThirdwebInAppSignMessage* SignMessage(UObject* WorldContextObject, const FInAppWalletHandle& Wallet, const FString& Message);

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FSignMessageDelegate, const FString&, SignedMessage, const FString&, Error);

	UPROPERTY(BlueprintAssignable)
	FSignMessageDelegate Success;

	UPROPERTY(BlueprintAssignable)
	FSignMessageDelegate Failed;

protected:
	UPROPERTY(Transient)
	FString UnsignedMessage;

private:
	UFUNCTION()
	void HandleResponse(const FString& SignedMessage);

	UFUNCTION()
	virtual void HandleFailed(const FString& Error);
};
