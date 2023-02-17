// Fill out your copyright notice in the Description page of Project Settings.


#include "../Managers/ChessCamera.h"
#include "../Managers/ChessGameModeBase.h"
#include "Camera/CameraComponent.h"
#include "../Pieces/ChessPiece.h"
#include "../Board/ChessBoardCell.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
AChessCamera::AChessCamera()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
    RootComponent = CreateDefaultSubobject<USceneComponent>("RootSceneComponent");
    MainCamera = CreateDefaultSubobject<UCameraComponent>("Main Camera");

    CameraArm = CreateDefaultSubobject <USpringArmComponent>("CameraArm");
    FVector Loc = FVector(200, 200, 0);
    FRotator Rot = FRotator(25, 0, 0);
    CameraArm->SetupAttachment(RootComponent);
    CameraArm->bEnableCameraLag = true;
    CameraArm->TargetArmLength = 300.0f;
    CameraArm->SetWorldLocation(Loc);
    CameraArm->SetWorldRotation(Rot);

    ForwardCamera = CreateDefaultSubobject<USceneComponent>("ForwardCamera");
    ForwardCamera->SetupAttachment(RootComponent);

    MainCamera->AttachToComponent(CameraArm, FAttachmentTransformRules::KeepRelativeTransform);

    AutoPossessPlayer = EAutoReceiveInput::Player0;

    playerController = Cast<APlayerController>(GetController());

}

// Called when the game starts or when spawned
void AChessCamera::BeginPlay()
{
    Super::BeginPlay();

    m_Gamemode = Cast<AChessGameModeBase>(GetWorld()->GetAuthGameMode());
}

// Called every frame
void AChessCamera::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}

void AChessCamera::LeftClickTriggered(FVector MousePos)
{
    FHitResult hit;
    FCollisionQueryParams Parms;
    Parms.AddIgnoredActor(this);

    UWorld* World = GetWorld();

    FVector Direction = MousePos - MainCamera->GetComponentLocation();
    //DrawDebugLine(GetWorld(), MainCamera->GetComponentLocation(), MainCamera->GetComponentLocation() + Direction * DistanceFromCamera, FColor::Green, true, 10.0f);

    if (World->LineTraceSingleByChannel(hit, MainCamera->GetComponentLocation(), MainCamera->GetComponentLocation() + Direction * DistanceFromCamera, ECollisionChannel::ECC_GameTraceChannel1, Parms))
    {

        if (hit.GetActor()->ActorHasTag("ChessPiece"))
        {
            AChessPiece* HitPiece = Cast<AChessPiece>(hit.GetActor());
            if (HitPiece->GetTeam() == m_Gamemode->GetCurrentTeam())
            {
                if (LastSelectedPiece)
                {
                    LastSelectedPiece->PieceUnselected();
                }

                LastSelectedPiece = HitPiece;
                HitPiece->PieceSelected();
            }
            else
            {
                if (LastSelectedPiece)
                {
                    AChessBoardCell* newCell = HitPiece->GetCurrentCell();
                    LastSelectedPiece->CheckSelectedCell(newCell);
                }
            }
        }

        if (hit.GetActor()->ActorHasTag("BoardCell"))
        {
            AChessBoardCell* HitCell = Cast<AChessBoardCell>(hit.GetActor());

            if (LastSelectedPiece)
            {
                LastSelectedPiece->CheckSelectedCell(HitCell);
            }
            int x, y;
            HitCell->GetIndex(x, y);
            AChessPiece* piece;
            piece = HitCell->GetChessPieceOnCell();
            if (piece)
            {
                UE_LOG(LogTemp, Warning, TEXT("Cell Hit at %i , %i with piece %s"), x, y, *piece->GetName());
            }
            else
            {
                UE_LOG(LogTemp, Warning, TEXT("Cell Hit at %i , %i with no piece"), x, y);
            }
        }

    }
}

void AChessCamera::MouseWheelSpun(float wheelValue)
{
    //wheelValue = FMath::Clamp(wheelValue, -1.0f, 1.0f);
    float newValue;
    newValue = FMath::Clamp((CameraArm->TargetArmLength - wheelValue * m_MouseSpeed), 100.0f, 500.0f);
    CameraArm->TargetArmLength = FMath::Lerp(CameraArm->TargetArmLength, newValue, 1.0f);
}

