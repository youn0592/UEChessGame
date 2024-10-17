// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "../ChessGame.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"

#include "Interfaces/OnlineSessionInterface.h"
#include "Interfaces/OnlineFriendsInterface.h"

#include "ChessGameInstance.generated.h"

/**
 * 
 */

USTRUCT()
struct FSeverData
{
	GENERATED_BODY()

	FString Name;
	uint16 CurrentPlayers;
	uint16 MaxPlayers;
	FString HostUsername;
};

USTRUCT(BlueprintType)
struct FOnlineGameSessionData
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, Category = "Online|Session")
	FName SessionName;

	UPROPERTY(BlueprintReadWrite, Category = "Online|Session")
	FName GameMapName;

	UPROPERTY(BlueprintReadWrite, Category = "Online|Session")
	FName EntryMapName;
};

USTRUCT(BlueprintType)
struct FFriendData
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online|Friend")
	FString FriendName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online|Friend")
	FString RealFriendName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online|Friend")
	FString Presence;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online|Friend")
	FString UniqueNetID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online|Friend")
	EOnlinePresence OnlinePresence;
};

USTRUCT(BlueprintType)
struct FGameModeData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AGameModeBase> GameMode;

	UPROPERTY()
	FString GameModeName;
};

USTRUCT(BlueprintType)
struct FPlayerData
{
	GENERATED_BODY()

public:

	void AddNewPlayer(FString name) { UsernameArray.Add(name); }
	void ClearAllPlayers() { UsernameArray.Empty(); }
	void ClearClient() 
	{
		if (UsernameArray.Num() == 2)
			UsernameArray.Pop();
	}

	int GetPlayerCount() const { return UsernameArray.Num(); }

	void SetHostUsername(FString name)
	{
		if (UsernameArray.Num() == 0)
			UsernameArray.Add(name);
		else if (UsernameArray.Num() == 1 || UsernameArray.Num() == 2)
			UsernameArray[0] = name;
	}
	void SetClientUsername(FString name)
	{
		if (UsernameArray.Num() == 1)
			UsernameArray.Add(name);
		else if (UsernameArray.Num() == 2)
			UsernameArray[1] = name;
	}

	FString GetHostUsername() const { return UsernameArray.Num() >= 1 ? UsernameArray[0] : ""; }
	FString GetClientUsername() const { return UsernameArray.Num() >= 2 ? UsernameArray[1] : ""; }

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Online|Players")
	TArray<FString> UsernameArray;

};


UCLASS()
class CHESSGAME_API UChessGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	UChessGameInstance();

	void Init();

	UFUNCTION(Exec)
	void Host(FString ServerName, FString Map);

	UFUNCTION(Exec)
	void Join(uint32 Index);

	UFUNCTION(Exec)
	void Disconnect();

	UFUNCTION(Exec)
	void DisconnectImplementation();
	
public:
	//TSharedPtr<FMapData> MapToPlay;

	UPROPERTY(EditAnywhere, Category="GameModees")
	TArray<FGameModeData> GameModes;

	bool bForceLoadLobbyScreen = false;

	FPlayerData PlayerData;
	
	TArray <TSharedRef<FOnlineFriend>> FriendsList;

	//FMapData CurrentMapData;

	bool bIsSteamRunning = false;

	FOnReadFriendsListComplete OnReadFreindsListCompleteDelegate;
	FOnSessionUserInviteAcceptedDelegate OnSessionUserInviteAcceptedDelegate;
	IConsoleCommand* InviteFriendsConsoleCommand;

protected:

	FOnlineSessionSearchResult InvitationOSSR;
	int32 InitationLocalNetID;

	bool bCPPDisconnectDone = false;
	bool bBPDisconnectDone = false;

	bool bLoadingScreenActive = false;

	bool bHosting = false;
	bool bJoined = false;
	int JoinAttempts = 0;

	FTimerHandle JoinHandle;

};
