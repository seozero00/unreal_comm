// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Networking.h" // Networking ��� ����

#include "UDPReceiver.generated.h"

UCLASS()
class YOURPROJECT_API UUDPReceiver : public UObject
{
    GENERATED_BODY()

public:
    // UDP ������ �����ϴ� �Լ� ����
    UFUNCTION(BlueprintCallable, Category = "UDP")
        static void StartUDPReceiver(int32 Port);

private:
    // UDP ������ ó���ϴ� ������ �Լ� ����
    static void UDPReceiverThread(int32 Port);

    // UDP ���� ���¸� ��Ÿ���� ���� ����
    static bool bReceiverRunning;
};
