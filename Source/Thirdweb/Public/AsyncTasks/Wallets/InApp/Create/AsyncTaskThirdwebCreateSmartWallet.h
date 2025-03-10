// Copyright (c) 2025 Thirdweb. All Rights Reserved.

#pragma once

#include "AsyncTasks/AsyncTaskThirdwebBase.h"
#include "Wallets/ThirdwebInAppWalletHandle.h"
#include "AsyncTaskThirdwebCreateSmartWallet.generated.h"

struct FSmartWalletHandle;

UCLASS(meta=(HasDedicatedAsyncNode))
class THIRDWEB_API UAsyncTaskThirdwebCreateSmartWallet : public UAsyncTaskThirdwebBase
{
	GENERATED_BODY()

public:
	virtual void Activate() override;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly="true", WorldContext="WorldContextObject", AdvancedDisplay="Factory,AccountOverride"), Category="Thirdweb|Wallets|Smart")
	static UAsyncTaskThirdwebCreateSmartWallet* CreateSmartWallet(UObject* WorldContextObject,
	                                                              const FInAppWalletHandle& InAppWallet,
	                                                              const int64 ChainID,
	                                                              const bool bGasless = true,
	                                                              const FString& Factory = "",
	                                                              const FString& AccountOverride = "")
	{
		NEW_TASK
		Task->InAppWallet = InAppWallet;
		Task->ChainID = ChainID;
		Task->bGasless = bGasless;
		Task->Factory = Factory;
		Task->AccountOverride = AccountOverride;
		RR_TASK
	};

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCreateSmartWalletDelegate, const FSmartWalletHandle&, SmartWallet, const FString&, Error);

	UPROPERTY(BlueprintAssignable)
	FCreateSmartWalletDelegate Success;

	UPROPERTY(BlueprintAssignable)
	FCreateSmartWalletDelegate Failed;

protected:
	UPROPERTY(Transient)
	FInAppWalletHandle InAppWallet;

	UPROPERTY(Transient)
	int64 ChainID;

	UPROPERTY(Transient)
	bool bGasless;

	UPROPERTY(Transient)
	FString Factory;

	UPROPERTY(Transient)
	FString AccountOverride;

private:
	UFUNCTION()
	void HandleResponse(const FSmartWalletHandle& Wallet);

	UFUNCTION()
	virtual void HandleFailed(const FString& Error);
};
