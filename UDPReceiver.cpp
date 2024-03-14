#include "UDPReceiver.h"
#include <sstream>

bool UUDPReceiver::bReceiverRunning = false;

void UUDPReceiver::StartUDPReceiver(int32 Port)
{
    if (!bReceiverRunning)
    {
        bReceiverRunning = true;

        FRunnableThread* Thread = FRunnableThread::Create(&UUDPReceiver::UDPReceiverThread, TEXT("UDPReceiverThread"), 0, TPri_BelowNormal);
    }
}

void UUDPReceiver::UDPReceiverThread(int32 Port)
{
    const FString& ThreadName = FThread::GetThreadName(FThread::GetThreadId());

    UE_LOG(LogTemp, Warning, TEXT("%s: UDP Receiver Thread started"), *ThreadName);

    ISocketSubsystem* SocketSubsystem = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM);
    FSocket* ReceiverSocket = SocketSubsystem->CreateSocket(NAME_DGram, TEXT("UDPReceiver"), false);

    FIPv4Endpoint ReceiverEndpoint(FIPv4Address::Any, Port);

    if (ReceiverSocket->Bind(ReceiverEndpoint))
    {
        uint8 Buffer[1024];
        int32 BytesRead = 0;
        FIPv4Endpoint SenderEndpoint;

        while (bReceiverRunning)
        {
            if (ReceiverSocket->Wait(ESocketWaitConditions::WaitForRead, FTimespan::FromMilliseconds(100)))
            {
                if (ReceiverSocket->RecvFrom(Buffer, sizeof(Buffer), BytesRead, SenderEndpoint))
                {
                    FString ReceivedData = FString(UTF8_TO_TCHAR(reinterpret_cast<const char*>(Buffer)));
                    UE_LOG(LogTemp, Warning, TEXT("%s: Received data from %s: %s"), *ThreadName, *SenderEndpoint.ToString(), *ReceivedData);
                }
            }
        }
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("%s: Failed to bind UDP socket"), *ThreadName);
    }

    if (ReceiverSocket)
    {
        ReceiverSocket->Close();
        ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(ReceiverSocket);
    }

    bReceiverRunning = false;
    UE_LOG(LogTemp, Warning, TEXT("%s: UDP Receiver Thread stopped"), *ThreadName);
}