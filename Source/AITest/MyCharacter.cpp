// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "BMatrix.h"
#include "BCoucheNeurones.h"
#include "BReseauNeurones.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	try	{
		int nbEntrees = 5;
		int nbSorties = 2;
		int nbCouchesCachees = 2;
		int taillesCouchesCachees[2] = { 4, 3 };
		BReseauNeurones reseau(nbEntrees, nbSorties, nbCouchesCachees, taillesCouchesCachees);
		BMatrix sortie(nbSorties,1);
		BMatrix entree(nbEntrees, 1);
		int nbInfo = reseau.getDataSize();
		double* adn = new double[nbInfo];
		FString ligne = "";

		// Initialisation de l'entree
		entree.set(0, 0, 1);
		entree.set(1, 0, 2);
		entree.set(2, 0, 3);
		entree.set(3, 0, 4);
		entree.set(4, 0, 5);

		// Affichage de l'ADN initial
		reseau.getData(adn);
		ligne = "";
		for (int i = 0; i < nbInfo; i++)
				ligne.Appendf(TEXT("%0.3f\t"), adn[i]);
		UE_LOG(LogTemp, Log, TEXT("ADN initial :"),);
		UE_LOG(LogTemp, Log, TEXT("%s"), *ligne);

		// Calcul de la sortie initiale
		sortie.recopie(reseau.calculeSortie(entree));
		sortie.getData(adn);
		ligne = "";
		for (int i = 0; i < nbSorties; i++)
			ligne.Appendf(TEXT("%0.3f\t"), adn[i]);
		UE_LOG(LogTemp, Log, TEXT("Sortie initiale :"), );
		UE_LOG(LogTemp, Log, TEXT("%s"), *ligne);

		// Modification de l'ADN
		reseau.getData(adn);
		adn[1] = 5;
		reseau.setData(adn);

		// Affichage de l'ADN final
		reseau.getData(adn);
		ligne = "";
		for (int i = 0; i < nbInfo; i++)
			ligne.Appendf(TEXT("%0.3f\t"), adn[i]);
		UE_LOG(LogTemp, Log, TEXT("ADN final :"), );
		UE_LOG(LogTemp, Log, TEXT("%s"), *ligne);

		// Calcul de la sortie finale
		sortie.recopie(reseau.calculeSortie(entree));
		sortie.getData(adn);
		ligne = "";
		for (int i = 0; i < nbSorties; i++)
			ligne.Appendf(TEXT("%0.3f\t"), adn[i]);
		UE_LOG(LogTemp, Log, TEXT("Sortie finale :"), );
		UE_LOG(LogTemp, Log, TEXT("%s"), *ligne);

		delete[] adn;
	}
	catch (const std::exception& e) {
		UE_LOG(LogTemp, Error, TEXT("%s"), *FString(e.what()));
	}
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

