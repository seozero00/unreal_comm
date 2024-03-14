// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Networking.h" // Networking 헤더 포함

#include "UDPReceiver.generated.h"

UCLASS()
class YOURPROJECT_API UUDPReceiver : public UObject
{
    GENERATED_BODY()

public:
    // UDP 수신을 시작하는 함수 선언
    UFUNCTION(BlueprintCallable, Category = "UDP")
        static void StartUDPReceiver(int32 Port);

private:
    // UDP 수신을 처리하는 쓰레드 함수 선언
    static void UDPReceiverThread(int32 Port);

    // UDP 수신 상태를 나타내는 변수 선언
    static bool bReceiverRunning;
};
