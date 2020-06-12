// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BReseauNeurones.h"

/**
 * 
 */
class AITEST_API BGeneration
{
protected:
	int taillePopulation;
	int nbEntrees;
	int nbSortie;
	int nbCouchesCachees;
	BReseauNeurones** reseaux;
	double* fitness;

public:
	BGeneration(int taillePop, int nbEn, int nbSor, int nbCchCch = 0, int* tailleCouches = NULL);
	~BGeneration();

	//méthodes principales
	void testePopulation(BMatrix const& entree);

	// méthodes esthétiques
	void printFitness() const;
	void printBestFitness(BMatrix const& entree);

protected:
	double calculeFitness(BMatrix const& sortie);
};
