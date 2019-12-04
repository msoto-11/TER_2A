#ifndef _SPACESCHEME_H

#include <string>
#include "Dense"
#include "Sparse"
#include "Function.h"

class Laplacian {
	private:
		// x_min, x_max, Nx, hx
		const double _xmin;
		const double _xmax;
		const int _Nx;
		const double _hx;
		// sigma (paramètre devant le laplacien)
		const double _sigma;
		// dossier de résultat
		const std::string _results;
		// matrice du laplacien
		Eigen::SparseMatrix<double> _LapMat;
		// vecteur x = {x_min + hx, ... , x_max - hx}
		Eigen::VectorXd _x;
		// vecteur source
		Eigen::VectorXd _source_term;
		// Pointeur contenant toutes vos fonctions
		Function* _function;

	public:
		// Constructeur
		Laplacian(Function* function, DataFile* data_file);
		// Construit la matrice du laplacien
		void LaplacianMatrix();
		// Construit un vecteur contenant la condition initiale aux points
		// de discrétisation
		Eigen::VectorXd InitialCondition();
		// Construit un vecteur contenant le terme source aux points
		// de discrétisation
		void SourceTerm(const double t);
		// Construit un vecteur contenant la solution exacte aux points
		// de discrétisation
		Eigen::VectorXd ExactSolution(const double t);
		// Pour enregistrer la solution
		void SaveSol(const Eigen::VectorXd sol, const double t, int n);
		// Pour récuperer la matrice du laplacien
		const Eigen::SparseMatrix<double> & GetMatrix(){return _LapMat;};
		// Pour récupérer le terme source
		const Eigen::VectorXd & GetSourceTerm(){return _source_term;};
};

#define _SPACESCHEME_H
#endif
