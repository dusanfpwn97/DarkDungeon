// Copyright (C) Pakyman Prod. 2020. All Rights Reserved.


#include "AI/Components/ACFCommandsManagerComponent.h"
#include "AI/Commands/ACFBaseCommand.h"
#include "AI/ACFAIController.h"

// Sets default values for this component's properties
UACFCommandsManagerComponent::UACFCommandsManagerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UACFCommandsManagerComponent::BeginPlay()
{
	Super::BeginPlay();
	controllerOwner = Cast<AACFAIController>(GetOwner());
}


void UACFCommandsManagerComponent::TerminateCurrentCommand()
{
	if (currentCommand) {
		currentCommand->EndCommand(controllerOwner);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Invalid Command - UACFCommandsManagerComponent::TerminateCurrentCommand"));
	}

}

void UACFCommandsManagerComponent::TriggerCommand_Implementation(const FGameplayTag& command)
{
	if (commands.Contains(command))
	{
		UACFBaseCommand** comm = commands.Find(command);

		if (*comm)
		{
			UACFBaseCommand* commptr = *comm;

			if (commptr && controllerOwner)
			{
				controllerOwner->SetWaitDurationTimeBK(commptr->EstimatedDurationWait);

				commandToExecute.Enqueue(commptr);
			}
		}
	}


}

bool UACFCommandsManagerComponent::TriggerCommand_Validate(const FGameplayTag& command)
{
	return true;
}

void UACFCommandsManagerComponent::ExecutePendingCommand_Implementation()
{
	UACFBaseCommand* commptr;
	if (commandToExecute.Dequeue(commptr))
	{
		currentCommand = commptr;
		controllerOwner->SetWaitDurationTimeBK(currentCommand->EstimatedDurationWait);
		currentCommand->ExecuteCommand(controllerOwner);
	}
}

bool UACFCommandsManagerComponent::ExecutePendingCommand_Validate()
{
	return true;
}