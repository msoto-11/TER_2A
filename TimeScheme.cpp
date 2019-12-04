#ifndef _TIME_SCHEME_CPP

#include "TimeScheme.h"
#include <iostream>

using namespace Eigen;
using namespace std;

// Constructeur par défaut (ne pas oublier de mettre votre pointeur à 0 !!)
TimeScheme::TimeScheme() : _lap(0)
{}

// Destructeur
TimeScheme::~TimeScheme()
{}


// Initialisation de vos différentes variables
void TimeScheme::Initialize(DataFile* data_file, Laplacian* lap)
{
  _dt = data_file->Get_dt();
  _t = data_file->Get_t0()+_dt;
  _sigma = data_file->Get_sigma();
  _lap = lap;
  _lap->LaplacianMatrix();
  _LapMatrix = _lap->GetMatrix();
  _sol0 = lap->InitialCondition();
  _sol = _sol0;
}

// Enregistre la solution : fait appel à Laplacian
void TimeScheme::SaveSolution(int n)
{
  _lap->SaveSol(_sol, _t, n);
}

// Euler Explicite
void EulerScheme::Integrate()
{
  _lap->SourceTerm(_t);
  
  assert((_LapMatrix.rows() == _lap->GetSourceTerm().size())
            && "Problème de taille 1 dans la fonction Integrate (Euler Scheme).");

  VectorXd RHS(_lap->GetSourceTerm() - _sigma*_LapMatrix*_sol);

  assert((_sol.size() == RHS.size())
            && "Problème de taille 2 dans la fonction Integrate (Euler Scheme).");

  _sol += _dt*RHS;
  _t += _dt;
}

#define _TIME_SCHEME_CPP
#endif
