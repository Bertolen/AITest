// Fill out your copyright notice in the Description page of Project Settings.


#include "BGeneration.h"
#include <cmath>

BGeneration::BGeneration(int taillePop, int nbEn, int nbSor, int nbCchCch, int* tailleCouches) :
	taillePopulation(taillePop), nbEntrees(nbEn), nbSortie(nbSor), nbCouchesCachees(nbCchCch)
{
	// création des réseaux
	reseaux = new BReseauNeurones*[taillePopulation];
	for (int i = 0; i < taillePopulation; i++)
		reseaux[i] = new BReseauNeurones(nbEntrees, nbSortie, nbCouchesCachees, tailleCouches);

	// création des fitness
	fitness = new double[taillePopulation];
}

BGeneration::~BGeneration()
{
	// suppression des réseaux
	for (int i = 0; i < taillePopulation; i++)
		delete reseaux[i];
	delete[] reseaux;

	// suppression des fitness
	delete[] fitness;
}

void BGeneration::testePopulation(BMatrix const& entree)
{
	// suppression des réseaux
	for (int i = 0; i < taillePopulation; i++) {
		fitness[i] = calculeFitness(reseaux[i]->calculeSortie(entree));
	}
}

double BGeneration::calculeFitness(BMatrix const& sortie)
{
	double* sor = new double[nbSortie];
	sortie.getData(sor);
	double fit = sqrt(pow(sor[0] - 0.5, 2) + pow(sor[1] - 0.5, 2));
	delete[] sor;
	return -fit;
}

void BGeneration::printFitness() const
{
	FString ligne = "";
	for (int i = 0; i < taillePopulation; i++)
		ligne.Appendf(TEXT("%0.3f\t"), fitness[i]);
	UE_LOG(LogTemp, Log, TEXT("Fitness de la generation :"));
	UE_LOG(LogTemp, Log, TEXT("%s"), *ligne);
}

void BGeneration::printBestFitness(BMatrix const& entree)
{
	testePopulation(entree);

	int best_i = 0;
	double best_fit = fitness[0];

	for (int i = 1; i < taillePopulation; i++) {
		if (best_fit < fitness[i]) {
			best_i = i;
			best_fit = fitness[i];
		}
	}

	UE_LOG(LogTemp, Log, TEXT("Meilleur fitness de la generation : %0.3f, à l'indice %d sur %d"), best_fit, best_i, taillePopulation);
	UE_LOG(LogTemp, Log, TEXT("Pour la sortie"));
	reseaux[best_i]->calculeSortie(entree).print();
}
