// Fill out your copyright notice in the Description page of Project Settings.


#include "BSmartCharacter.h"
#include "BMatrix.h"
#include "BCoucheNeurones.h"
#include "BReseauNeurones.h"
#include "BGeneration.h"

// Sets default values
ABSmartCharacter::ABSmartCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABSmartCharacter::BeginPlay()
{
	Super::BeginPlay();
	try	{
		BGeneration gen(50, 5, 2);
		BMatrix entree(5, 1);

		entree.set(0, 0, 0);
		entree.set(1, 0, 1);
		entree.set(2, 0, 2);
		entree.set(3, 0, 3);
		entree.set(4, 0, 4);

		gen.printBestFitness(entree);
		gen.printFitness();
	}
	catch (const std::exception& e) {
		UE_LOG(LogTemp, Error, TEXT("%s"), *FString(e.what()));
	}
}

// Called every frame
void ABSmartCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABSmartCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

