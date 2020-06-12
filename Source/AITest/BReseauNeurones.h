// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BCoucheNeurones.h"
#include "BMatrix.h"

/**
 * 
 */
class AITEST_API BReseauNeurones
{
protected:
	int nbEntrees;
	int nbSorties;
	int nbCouchesCachees;

	BCoucheNeurones** couchesNeurones;

public:
	BReseauNeurones(int _nbEntrees, int _nbSorties, int _nbCouchesCachees = 0, int* tailleCouchesCachees = NULL);
	~BReseauNeurones();

	// accesseurs
	int getDataSize() const;
	void getData(double* dataArray) const;
	void setData(double* dataArray);

	BMatrix calculeSortie(BMatrix const& entree);
};
