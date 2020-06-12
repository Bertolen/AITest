// Fill out your copyright notice in the Description page of Project Settings.


#include "BMatrix.h"
#include <stdexcept>

using namespace std;

BMatrix::BMatrix(int _M, int _N) : M(_M), N(_N)
{
	if (M <= 0) M = 1;
	if (N <= 0) N = 1;

	data = new double* [M];
	for (int i = 0; i < M; i++) {
		data[i] = new double[N];
		for (int j = 0; j < N; j++)
			data[i][j] = 0;
	}
}

BMatrix::BMatrix(BMatrix const& orig) : M(orig.getM()), N(orig.getN())
{
	data = new double* [M];
	for (int i = 0; i < M; i++) {
		data[i] = new double[N];
		for (int j = 0; j < N; j++)
			data[i][j] = orig.get(i, j);
	}
}

BMatrix::~BMatrix()
{
	for (int i = 0; i < M; i++)
		delete[] data[i];
	delete[] data;
}

int BMatrix::getM() const
{
	return M;
}

int BMatrix::getN() const
{
	return N;
}

void BMatrix::set(int row, int col, double value)
{
	if (0 > row || row >= M)
		throw out_of_range("tried to set a row out of bounds : " + std::to_string(row) + " max " + std::to_string(M - 1));
	if (0 > col || col >= N)
		throw out_of_range("tried to set a column out of bounds : " + std::to_string(col) + " max " + std::to_string(N - 1));
	data[row][col] = value;
}

double BMatrix::get(int row, int col) const
{
	if (0 > row || row >= M)
		throw out_of_range("tried to read a row out of bounds : " + std::to_string(row) + " max " + std::to_string(M - 1));
	if (0 > col || col >= N)
		throw out_of_range("tried to read a column out of bounds : " + std::to_string(col) + " max " + std::to_string(N - 1));
	return data[row][col];
}

int BMatrix::getDataSize() const
{
	return M * N;
}

void BMatrix::getData(double *dataArray) const
{
	int cpt = 0;

	for (int i = 0; i < M; i++)	{
		for (int j = 0; j < N; j++)	{
			dataArray[cpt] = data[i][j];
			cpt++;
		}
	}
}

void BMatrix::setData(double* dataArray)
{
	int cpt = 0;

	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			data[i][j] = dataArray[cpt];
			cpt++;
		}
	}
}

void BMatrix::print()
{
	FString ligne = "";
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			ligne.Appendf(TEXT("%0.3f\t"), get(i, j));
		}
		UE_LOG(LogTemp, Log, TEXT("%s"), *ligne);
		ligne = "";
	}
}

void BMatrix::recopie(BMatrix const& B)
{
	if (M != B.getM() || N != B.getN())
		throw length_error("Tried to copy matrices that don't have the same size. " + std::to_string(M) + "x" + std::to_string(N) + " and " + std::to_string(B.getM()) + "x" + std::to_string(B.getN()));

	for (int i = 0; i < M; i++)
		for (int j = 0; j < N; j++)
			set(i, j, B.get(i, j));
}

BMatrix& BMatrix::operator+=(BMatrix const& B)
{
	if (M != B.getM() || N != B.getN())
		throw length_error("Tried to add two matrices that don't have the same size. " + std::to_string(M) + "x" + std::to_string(N) + " and " + std::to_string(B.getM()) + "x" + std::to_string(B.getN()));

	for (int i = 0; i < M; i++) 
		for (int j = 0; j < N; j++) 
			set(i, j, get(i, j) + B.get(i, j));

	return *this;	
}

BMatrix operator+(BMatrix const& A, BMatrix const& B)
{
	BMatrix copie(A);
	copie += B;
	return copie;
}

BMatrix& BMatrix::operator*=(double const& B)
{
	for (int i = 0; i < M; i++) 
		for (int j = 0; j < N; j++) 
			set(i, j, get(i, j) * B);

	return *this;
}

BMatrix operator*(BMatrix const& A, double const& B)
{
	BMatrix copie(A);
	copie *= B;
	return copie;
}

BMatrix operator*(BMatrix const& A, BMatrix const& B)
{
	if (A.getN() != B.getM())
		throw length_error("Tried to multiply two matrices that don't have matching rows and columns count. " + std::to_string(A.getM()) + "x" + std::to_string(A.getN()) + " and " + std::to_string(B.getM()) + "x" + std::to_string(B.getN()));

	BMatrix C(A.getM(), B.getN());

	// boucle sur toutes les valeurs de C
	for (int i = 0; i < C.getM(); i++) {
		for (int j = 0; j < C.getN(); j++) {
			//Calcul de la valeur de C en i,j
			double val = 0;
			for (int k = 0; k < A.getN(); k++)
				val += A.get(i, k) * B.get(k, j);
			C.set(i, j, val);
		}
	}

	return C;
}

BMatrix& BMatrix::operator=(BMatrix const& B)
{

	if (M == B.getM() && N == B.getN())	{
		recopie(B);
	}
	else {
		// on commence par effacer les données 
		for (int i = 0; i < M; i++)
			delete[] data[i];
		delete[] data;

		// on modifie les dimensions
		M = B.getM();
		N = B.getN();

		// on aloue les nouvelles données
		data = new double* [M];
		for (int i = 0; i < M; i++) {
			data[i] = new double[N];
			for (int j = 0; j < N; j++)
				data[i][j] = B.get(i, j);
		}
	}

	return *this;
}