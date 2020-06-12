// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BMatrix.h"

#include <random>

/**
 * 
 */
class AITEST_API BCoucheNeurones
{
protected:
	// propriétés
	BMatrix* poid;
	BMatrix* biai;
	int nbEntrees;
	int taille;

public:
	BCoucheNeurones(int _nbEntrees, int _taille, bool randomize = false);
	~BCoucheNeurones();

	// accesseurs
	void setPoid(BMatrix const& p);
	void setBiai(BMatrix const& b);
	void print();
	int getDataSize() const;
	void getData(double* dataArray) const;
	void setData(double* dataArray);

	// méthode principale
	BMatrix calculeSortie(BMatrix const& entree);
};
