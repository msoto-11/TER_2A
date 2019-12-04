#ifndef _FUNCTION_H

#include "DataFile.h"

class Function {
  private:
    // Quelques variables privées utiles pour
    // construire la condition initiale et la solution exacte (sigma)
    const double _sigma;
    const double _xmin;
    const double _xmax;

	public:
    // Constructeur
    Function(DataFile* data_file);
    // Condition initiale
    double InitialCondition(const double x) const;
    // Solution exacte si elle est connue (utile pour valider le code)
    double ExactSolution(const double x, const double t) const;
    // Terme source
    double SourceFunction(const double x, const double t) const;
};

#define _FUNCTION_H
#endif
