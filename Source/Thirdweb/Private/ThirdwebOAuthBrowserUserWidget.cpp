﻿// Copyright (c) 2024 Thirdweb. All Rights Reserved.

#include "ThirdwebOAuthBrowserUserWidget.h"

#include "ThirdwebLog.h"
#include "ThirdwebOAuthBrowserWidget.h"

#include "Blueprint/WidgetTree.h"

#include "Components/Overlay.h"
#include "Components/OverlaySlot.h"
#include "Components/PanelWidget.h"

const FString UThirdwebOAuthBrowserUserWidget::BackendUrlPrefix = TEXT("https://embedded-wallet.thirdweb.com/");

TSharedRef<SWidget> UThirdwebOAuthBrowserUserWidget::RebuildWidget()
{
	// RebuildWidget is not called until the widget is first added to the
	// viewport.

	UPanelWidget* RootWidget = Cast<UPanelWidget>(GetRootWidget());

	if (!RootWidget)
	{
		RootWidget = WidgetTree->ConstructWidget<UOverlay>(UOverlay::StaticClass(), TEXT("RootWidget"));
		WidgetTree->RootWidget = RootWidget;
	}

	if (RootWidget)
	{
		Browser = WidgetTree->ConstructWidget<UThirdwebOAuthBrowserWidget>(UThirdwebOAuthBrowserWidget::StaticClass(), TEXT("ThirdwebOauthBrowser"));
		Browser->OnUrlChanged.AddUniqueDynamic(this, &ThisClass::HandleUrlChanged);
		UPanelSlot* PanelSlot = RootWidget->AddChild(Browser);
		if (UOverlaySlot* RootWidgetSlot = Cast<UOverlaySlot>(PanelSlot))
		{
			TW_LOG(Warning, TEXT("ThirdwebOAuthBrowserUserWidget::RebuildWidget()"));
			RootWidgetSlot->SetHorizontalAlignment(HAlign_Fill);
			RootWidgetSlot->SetVerticalAlignment(VAlign_Fill);
			
		}
	}

	return Super::RebuildWidget();
}

#if WITH_EDITOR
const FText UThirdwebOAuthBrowserUserWidget::GetPaletteCategory()
{
	return NSLOCTEXT("Thirdweb", "Thirdweb", "Thirdweb");
}
#endif

void UThirdwebOAuthBrowserUserWidget::OnWidgetRebuilt()
{
	Super::OnWidgetRebuilt();
	SetVisible(false);
}

void UThirdwebOAuthBrowserUserWidget::Authenticate(const FWalletHandle& InAppWallet)
{
	if (!InAppWallet.IsValid())
	{
		TW_LOG(Error, TEXT("OAuthBrowserUserWidget::Authenticate::Wallet invalid"));\
		return OnError.Broadcast(TEXT("Invalid Wallet"));
	}
	Wallet = InAppWallet;
	
	if (Browser)
	{
		FString Error;
		if (FString Link; Wallet.FetchOAuthLoginURL(Browser->DummyUrl, Link, Error))
		{
			TW_LOG(Verbose, TEXT("OAuthBrowserUserWidget::Authenticate::Authenticating against %s"), *Link);
			return Browser->Authenticate(Link);
		}
		OnError.Broadcast(Error);
	}
}

// ReSharper disable once CppPassValueParameterByConstReference
void UThirdwebOAuthBrowserUserWidget::HandleUrlChanged(FString Url)
{
	TW_LOG(Verbose, TEXT("OAuthBrowserUserWidget::HandleUrlChanged::%s"), *Url);
	if (Url.IsEmpty() || Url.StartsWith(BackendUrlPrefix))
	{
		return SetVisible(false);
	}
	if (Url.StartsWith(Browser->DummyUrl))
	{
		SetVisible(false);
		FString Left, Right;
		if (Url.Split(TEXT("authResult="), &Left, &Right, ESearchCase::IgnoreCase))
		{
			FString Error;
			if (Wallet.SignInWithOAuth(Right, Error))
			{
				return OnSuccess.Broadcast();
			}
			return OnError.Broadcast(Error);
		}
		return OnError.Broadcast(TEXT("Failed to match AuthResult in url"));
		
	}
	SetVisible(true);
}

void UThirdwebOAuthBrowserUserWidget::SetVisible(const bool bVisible)
{
	// Mobile webview needs to be visible to work
	if (bVisible)
	{
#if PLATFORM_IOS | PLATFORM_ANDROID
		SetRenderOpacity(1.0f);
#else
		SetVisibility(ESlateVisibility::Visible);
#endif
	}
	else
	{
#if PLATFORM_IOS | PLATFORM_ANDROID
		SetRenderOpacity(0.01f);
#else
		SetVisibility(ESlateVisibility::Hidden);
#endif
	}
}
