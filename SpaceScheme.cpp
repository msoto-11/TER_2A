#ifndef _SPACESCHEME_CPP

#include "SpaceScheme.h"
#include <fstream>
#include <iostream>

using namespace std;
using namespace Eigen;

// Constructeur
Laplacian::Laplacian(Function* function, DataFile* data_file) :
_xmin(data_file->Get_xmin()), _xmax(data_file->Get_xmax()),
_Nx(data_file->Get_Nx()), _hx(data_file->Get_hx()), _sigma(data_file->Get_sigma()),
_results(data_file->Get_results()), _function(function)
{
	_x.resize(_Nx); // (x_min+h, ..., x_max-h)
	for (int i = 0 ; i < _Nx ; ++i)
		_x[i] = _xmin + (i+1)*_hx;

	system(("mkdir -p ./" + _results).c_str());
}

// Construit la matrice 1D du laplacien
// LapMat = - Delta
void Laplacian::LaplacianMatrix() {
	_LapMat.resize(_Nx,_Nx);
	vector<Triplet<double> > triplets(3*_Nx-2);
  int num = 0;
  for (int i = 0; i < _Nx; ++i)
	{
      triplets[num++] = {i, i, 2.0/pow(_hx,2)};
    if (i > 0)
			triplets[num++] = {i, i-1, -1./pow(_hx,2)};

    if (i < _Nx-1)
			triplets[num++] = {i, i+1, -1./pow(_hx,2)};
  }
	_LapMat.setFromTriplets(triplets.begin(), triplets.end());
}

// Construit la condition initiale
VectorXd Laplacian::InitialCondition() {
	VectorXd sol0(_Nx);
	for (int i = 0 ; i < _Nx ; ++i)
	{
		sol0[i] = _function->InitialCondition(_x[i]);
	}
	return sol0;
}

// Le terme source
void Laplacian::SourceTerm(const double t) {
	_source_term.resize(_Nx);
	for (int i = 0 ; i < _Nx ; ++i)
	{
		_source_term[i] = _function->SourceFunction(_x[i], t);
	}
	_source_term.resize(2);
}

// Solution exacte
VectorXd Laplacian::ExactSolution(const double t) {
	VectorXd exact_sol(_Nx);
	for (int i = 0 ; i < _Nx ; ++i)
	{
		exact_sol[i] = _function->ExactSolution(_x[i], t);
	}
	return exact_sol;
}


// Enregistre la solution
void Laplacian::SaveSol(const VectorXd sol, const double t, int n) {
	assert((sol.size() == _x.size())
	 && "Problème de taille dans la fonction SaveSol.");
	string name_file = _results + "/solution_" + std::to_string(n) + ".txt";
	ofstream solution;
	solution.open(name_file, ios::out);

	solution << _xmin << " " << 0 << endl;
	for (int i = 0; i < _Nx; i++)
	{
		solution << _x(i) << " " << sol(i) << endl;
	}
	solution << _xmax << " " << 0 << endl;

	solution.close();
}

#define _SPACESCHEME_CPP
#endif
