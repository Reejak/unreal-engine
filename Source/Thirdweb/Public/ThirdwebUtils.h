﻿// Copyright (c) 2025 Thirdweb. All Rights Reserved.

#pragma once

#include "ThirdwebMacros.h"
#include "Dom/JsonObject.h"
#include "Serialization/JsonTypes.h"

struct FThirdwebIPFSUploadResult;
enum class EThirdwebEngineTransactionOnChainStatus : uint8;
enum class EThirdwebEngineTransactionStatus : uint8;
struct FWalletHandle;
struct FInAppWalletHandle;
struct FSmartWalletHandle;
class FJsonValue;
class IHttpRequest;
class UTexture2D;
class UTexture2DDynamic;
enum class EThirdwebOAuthProvider : uint8;

namespace ThirdwebUtils
{
	extern const TCHAR* ZeroAddress;

	/**
	 * Checks if the provided Ethereum address is checksummed.
	 *
	 * @param Address The Ethereum address to check.
	 * @return True if the address is checksummed, false otherwise.
	 */
	extern THIRDWEB_API bool IsChecksummedAddress(const FString& Address);

	/**
	 * Checks if the provided Ethereum address is valid.
	 *
	 * @param Address The Ethereum address to check.
	 * @param bWithChecksum Set to true to validate the address with checksum.
	 * @return True if the address is valid, false otherwise.
	 */
	extern THIRDWEB_API bool IsValidAddress(const FString& Address, const bool bWithChecksum = false);

	/**
	 * Converts the provided Ethereum address to a checksummed address.
	 *
	 * @param Address The Ethereum address to convert.
	 * @return The checksummed Ethereum address.
	 */
	extern THIRDWEB_API FString ToChecksummedAddress(const FString& Address);

	/**
	 * Converts an EThirdwebOAuthProvider enum value to its corresponding FText representation.
	 *
	 * @param Provider The EThirdwebOAuthProvider enum value to convert.
	 * @return The FText representation of the specified EThirdwebOAuthProvider, or "Invalid" if the provider is not recognized.
	 */
	extern THIRDWEB_API FText ToText(const EThirdwebOAuthProvider Provider);
	extern THIRDWEB_API FText ToText(const EThirdwebEngineTransactionStatus Status);
	extern THIRDWEB_API FText ToText(const EThirdwebEngineTransactionOnChainStatus Status);

	/**
	 * Converts an EThirdwebOAuthProvider enum value to its string representation.
	 *
	 * @param Provider The EThirdwebOAuthProvider enum value to convert.
	 * @return The string representation of the specified EThirdwebOAuthProvider.
	 */
	extern THIRDWEB_API FString ToString(const EThirdwebOAuthProvider Provider);
	extern THIRDWEB_API FString ToString(const EThirdwebEngineTransactionStatus Status);
	extern THIRDWEB_API FString ToString(const EThirdwebEngineTransactionOnChainStatus Status);

	/**
	 * Converts the given FText to its corresponding EThirdwebOAuthProvider enum value.
	 *
	 * @param Text The FText representation of the OAuth provider to convert.
	 * @return The corresponding EThirdwebOAuthProvider enum value, or EThirdwebOAuthProvider::None if the provider is not recognized.
	 */
	extern THIRDWEB_API EThirdwebOAuthProvider ToOAuthProvider(const FText& Text);
	extern THIRDWEB_API EThirdwebEngineTransactionStatus ToTransactionStatus(const FText& Text);
	extern THIRDWEB_API EThirdwebEngineTransactionOnChainStatus ToOnChainStatus(const FText& Text);

	/**
	 * Converts the given FString to its corresponding EThirdwebOAuthProvider enum value.
	 *
	 * @param String The FString representation of the OAuth provider to convert.
	 * @return The corresponding EThirdwebOAuthProvider enum value, or EThirdwebOAuthProvider::None if the provider is not recognized.
	 */
	extern THIRDWEB_API EThirdwebOAuthProvider ToOAuthProvider(const FString& String);
	extern THIRDWEB_API EThirdwebEngineTransactionStatus ToTransactionStatus(const FString& String);
	extern THIRDWEB_API EThirdwebEngineTransactionOnChainStatus ToOnChainStatus(const FString& String);

	extern FString ParseAuthResult(const FString& AuthResult);
	extern UTexture2D* CreateQrCode(const FString& Text);

	namespace Maps
	{
		extern const TMap<EThirdwebOAuthProvider, FText> OAuthProviderToText;
		extern const TMap<EThirdwebEngineTransactionStatus, FText> TransactionStatusToText;
		extern const TMap<EThirdwebEngineTransactionOnChainStatus, FText> OnChainStatusToText;
	}

	namespace Json
	{
		extern TSharedPtr<FJsonObject> ToJson(const FString& String);
		extern TArray<TSharedPtr<FJsonValue>> ToJsonArray(const FString& String);
		// Meant for dynamic string arrays that hold different value types
		extern TArray<TSharedPtr<FJsonValue>> ToJsonArray(const TArray<FString>& DynamicArray);
		extern TSharedPtr<FJsonValue> ToJsonValue(const FString& String);
		extern FString ToString(const TSharedPtr<FJsonObject>& JsonObject);
		extern FString ToString(const TSharedPtr<FJsonValue>& JsonValue);
		extern FString AsString(const TSharedPtr<FJsonValue>& JsonValue);
		extern bool ParseEngineResponse(const FString& Content, TSharedPtr<FJsonValue>& JsonValue, FString& Error);
		extern bool ParseEngineResponse(const FString& Content, TSharedPtr<FJsonObject>& JsonObject, FString& Error);
		extern bool ParseEngineResponse(const FString& Content, TArray<TSharedPtr<FJsonValue>>& JsonArray, FString& Error);
		extern FString ParseEngineError(const TSharedPtr<FJsonObject>& Error);

		template <EJson JsonType>
		bool IsNotNullField(const TSharedPtr<FJsonObject>& JsonObject, const FString FieldName)
		{
			return JsonObject.IsValid() && JsonObject->HasField(FieldName) ? !JsonObject->GetField<JsonType>(FieldName)->IsNull() : false;
		}
	}

	namespace Internal
	{
		extern FString MaskSensitiveString(const FString& InString, const FString& MatchString, const FString& MaskCharacter = TEXT("*"), const int32 ShowBeginCount = 4, const int32 ShowEndCount = 4);
		extern TArray<FString> MaskSensitiveString(
			const TArray<FString>& InStrings,
			const FString& MatchString,
			const FString& MaskCharacter = TEXT("*"),
			const int32 ShowBeginCount = 4,
			const int32 ShowEndCount = 4
		);
		extern TArray<FString> MaskSensitiveString(
			const TArray<FString>& InStrings,
			const TArray<FString>& MatchStrings,
			const FString& MaskCharacter = TEXT("*"),
			const int32 ShowBeginCount = 4,
			const int32 ShowEndCount = 4
		);
		extern void LogRequest(const TSharedRef<IHttpRequest>& Request, const TArray<FString>& SensitiveStrings = {});

		extern int64 ParseInt64(const FString& String);
		extern FString BytesToString(const TArray<uint8>& Bytes);
		extern TArray<uint8> StringToBytes(const FString& String);
		extern UTexture2DDynamic* BytesToTexture2DDynamic(const TArray<uint8>& Bytes);

		extern FString GetPluginVersion();
		extern FString GenerateUUID();

		extern void SendConnectEvent(const FWalletHandle Wallet);
		extern void SendConnectEvent(const FInAppWalletHandle Wallet);
		extern void SendConnectEvent(const FSmartWalletHandle Wallet);

		extern TSharedRef<IHttpRequest> CreateEngineRequest(const FString& Verb = TEXT("GET"));

		extern FString ReplaceIpfs(const FString& Url, const FString& Gateway);
	}

	namespace Storage
	{
		DECLARE_DELEGATE_OneParam(FDownloadBytesSuccessDelegate, const TArray<uint8>& /* Bytes */);
		extern THIRDWEB_API void Download(const FString& Url, const FDownloadBytesSuccessDelegate& Success, const FStringDelegate& Error);

		template <typename T = FJsonObject>
		extern THIRDWEB_API T ConvertDownloadResult(const TArray<uint8>& Bytes);

		DECLARE_DELEGATE_OneParam(FUploadSuccessDelegate, const FThirdwebIPFSUploadResult& /* Result */);
		extern void UploadInternal(const FString& Filename, const TArray<uint8>& Content, const FUploadSuccessDelegate& Success, const FStringDelegate& Error);

		template <typename T = FString>
		extern THIRDWEB_API void Upload(const FString& Filename, const T Content, const FUploadSuccessDelegate& Success, const FStringDelegate& Error);
	}
}
