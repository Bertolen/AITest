// Fill out your copyright notice in the Description page of Project Settings.


#include "BCoucheNeurones.h"
#include <stdexcept>

BCoucheNeurones::BCoucheNeurones(int _nbEntrees, int _taille, bool randomize) : nbEntrees(_nbEntrees), taille(_taille)
{
	// allocation dynamique
	biai = new BMatrix(taille, 1);
	poid = new BMatrix(taille, nbEntrees);
	
	// si c'est demandé on alimente les matrices aléatoirement.
	if (randomize) {
		std::uniform_real_distribution<double> unif(-1, 1);
		std::random_device rd;  //Will be used to obtain a seed for the random number engine
		std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
		for (int i = 0; i < taille; i++) {
			for (int j = 0; j < nbEntrees; j++) 
				poid->set(i, j, unif(gen));
			biai->set(i, 0, unif(gen));
		}
	}
}

BCoucheNeurones::~BCoucheNeurones()
{
	delete biai;
	delete poid;
}

void BCoucheNeurones::setPoid(BMatrix const& p)
{
	if (p.getM() != poid->getM() || p.getN() != poid->getN())
		throw std::length_error("Tried to replace neuronal weights with a wrong sized matrix : " + std::to_string(p.getM()) + "x" + std::to_string(p.getN()) + " instead of " + std::to_string(poid->getM()) + "x" + std::to_string(poid->getN()));

	poid->recopie(p);
}

void BCoucheNeurones::setBiai(BMatrix const& b)
{
	if (b.getM() != biai->getM() || b.getN() != biai->getN())
		throw std::length_error("Tried to replace neuronal biais with a wrong sized matrix : " + std::to_string(b.getM()) + "x" + std::to_string(b.getN()) + " instead of " + std::to_string(biai->getM()) + "x" + std::to_string(biai->getN()));

	biai->recopie(b);
}

void BCoucheNeurones::print()
{
	UE_LOG(LogTemp, Log, TEXT("Couche avec %d entrants et %d noeuds"), nbEntrees, taille);
	UE_LOG(LogTemp, Log, TEXT("Avec des poids de : "));
	poid->print();
	UE_LOG(LogTemp, Log, TEXT("et des biais de : "));
	biai->print();
}

int BCoucheNeurones::getDataSize() const
{
	return poid->getDataSize() + biai->getDataSize();
}

void BCoucheNeurones::getData(double* dataArray) const
{
	int cpt = 0;

	// poid en premier
	for (int i = 0; i < poid->getM(); i++) {
		for (int j = 0; j < poid->getN(); j++) {
			dataArray[cpt] = poid->get(i, j);
			cpt++;
		}
	}

	// biai ensuite
	for (int i = 0; i < biai->getM(); i++) {
		for (int j = 0; j < biai->getN(); j++) {
			dataArray[cpt] = biai->get(i, j);
			cpt++;
		}
	}
}

void BCoucheNeurones::setData(double* dataArray)
{
	poid->setData(dataArray);
	biai->setData(&(dataArray[poid->getDataSize()]));
}

BMatrix BCoucheNeurones::calculeSortie(BMatrix const& entree)
{
	BMatrix sortie = (*poid) * entree + (*biai);
	return sortie;
}
