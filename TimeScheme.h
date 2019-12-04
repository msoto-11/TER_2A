#ifndef _TIME_SCHEME_H

#include "SpaceScheme.h"

class TimeScheme
{
  protected:
    // Pas de temps
    double _dt;
    // Temps en cours
    double _t;
    double _sigma;
    // Vecteur initial et vecteur solution
    Eigen::VectorXd _sol0, _sol;
    // Pointeur vers le laplacien
    Laplacian* _lap;
    // Matrice du Laplacien
    Eigen::SparseMatrix<double> _LapMatrix;

  public:
    // Constructeur par défaut
    TimeScheme();
    // Destructeur par défaut - Si la classe ne contient pas de destructeur par défaut
    // alors le compilateur en génère un implicitement.
    virtual ~TimeScheme();
    // Initialisation de vos différentes variables
    void Initialize(DataFile* data_file, Laplacian* lap);
    // Enregistre la solution dans un fichier
    void SaveSolution(int n);
    // Une étape du schéma en temps
    virtual void Integrate() = 0;
    // Permet de récupérer _sol
    const Eigen::VectorXd & GetIterateSolution() const {return _sol;};
};

class EulerScheme : public TimeScheme
{
  public:
    // Une étape du schéma en temps
    void Integrate();
};


#define _TIME_SCHEME_H
#endif
