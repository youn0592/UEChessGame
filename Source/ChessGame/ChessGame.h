// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

UENUM()
enum EPieceTeam
{
    White,
    Black,
    Empty
};

UENUM()
enum EPieceType
{
    Default = -1,
    Pawn,
    Rook,
    Bishop,
    Knight,
    Queen,
    King
};

UENUM()
enum class EOnlinePresence
{
    Offline,
    Online,
    Busy,
    Away
};