// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <string>

/** A bare-bones immutable data type for M-by-N matrices.
 * 
 */
class AITEST_API BMatrix
{
protected:
	int M;
	int N;
	double** data;

public:
	BMatrix(int _M, int _N);
	BMatrix(BMatrix const& orig);
	~BMatrix();

	// getters et setters
	int getM() const;
	int getN() const;
	void set(int row, int col, double value);
	double get(int row, int col) const;
	int getDataSize() const;
	void getData(double* dataArray) const;
	void setData(double* dataArray);
	void print();
	void recopie(BMatrix const& B);

	// opérations arithmétiques
	BMatrix& operator+=(BMatrix const& B);
	BMatrix& operator*=(double const& B);
	BMatrix& operator=(BMatrix const& B);
};


BMatrix operator+(BMatrix const& A, BMatrix const& B);
BMatrix operator*(BMatrix const& A, BMatrix const& B);
BMatrix operator*(BMatrix const& A, double const& B);