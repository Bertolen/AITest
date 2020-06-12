// Fill out your copyright notice in the Description page of Project Settings.


#include "BReseauNeurones.h"

BReseauNeurones::BReseauNeurones(int _nbEntrees, int _nbSorties, int _nbCouchesCachees, int* _tailleCouchesCachees) : 
	nbEntrees(_nbEntrees), nbSorties(_nbSorties), nbCouchesCachees(_nbCouchesCachees), tailleCouchesCachees(_tailleCouchesCachees)
{
	if (nbCouchesCachees < 0) nbCouchesCachees = 0;

	// allocation du tableau de couches
	couchesNeurones = new BCoucheNeurones*[nbCouchesCachees + 1];

	// dans le cas o� on a des couches cach�es
	if (nbCouchesCachees > 0) {
		// la premi�re couche cach�e est branch�e sur les entr�es du r�seau
		couchesNeurones[0] = new BCoucheNeurones(nbEntrees, tailleCouchesCachees[0], true);

		// chaque couche cach�e a autant d'entr�es que la taille de la couche pr�c�dente
		for (int i = 1; i < nbCouchesCachees; i++)
			couchesNeurones[i] = new BCoucheNeurones(tailleCouchesCachees[i - 1], tailleCouchesCachees[i], true);

		// la derni�re couche est la sortie, elle ne compte pas dans les couches cachees
		couchesNeurones[nbCouchesCachees] = new BCoucheNeurones(tailleCouchesCachees[nbCouchesCachees - 1], nbSorties, true);
	}
	else {
		// Si on a une seule couche on la branche direct des deux c�t�s
		couchesNeurones[0] = new BCoucheNeurones(nbEntrees, nbSorties, true);
	}
}

BReseauNeurones::~BReseauNeurones()
{
	// suppresion des couches
	for (int i = 0; i < nbCouchesCachees + 1; i++)
		delete couchesNeurones[i];

	// suppresion du tableau
	delete[] couchesNeurones;
}

int BReseauNeurones::getDataSize() const
{
	int dataSize = 0;
	for (int i = 0; i < nbCouchesCachees + 1; i++)
		dataSize += couchesNeurones[i]->getDataSize();
	return dataSize;
}

void BReseauNeurones::getData(double* dataArray) const
{
	int offset = 0;
	for (int i = 0; i < nbCouchesCachees + 1; i++) {
		couchesNeurones[i]->getData( &(dataArray[offset]) );
		offset += couchesNeurones[i]->getDataSize();
	}
}

void BReseauNeurones::setData(double* dataArray)
{
	int offset = 0;
	for (int i = 0; i < nbCouchesCachees + 1; i++) {
		couchesNeurones[i]->setData(&(dataArray[offset]));
		offset += couchesNeurones[i]->getDataSize();
	}
}

BMatrix BReseauNeurones::calculeSortie(BMatrix const& entree)
{
	BMatrix sortie = couchesNeurones[0]->calculeSortie(entree);

	for(int i = 1; i < nbCouchesCachees + 1; i++)
		sortie = couchesNeurones[i]->calculeSortie(sortie);

	return sortie;
}