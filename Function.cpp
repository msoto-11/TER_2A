#ifndef _FUNCTION_CPP

#include "Function.h"
#include <cmath>

Function::Function(DataFile* data_file)
: _sigma(data_file->Get_sigma()), _xmin(data_file->Get_xmin()), _xmax(data_file->Get_xmax())
{}

// Condition initiale
double Function::InitialCondition(const double x) const
{
  return sin(x-_xmax)*sin(x-_xmin);
}

// Solution exacte
double Function::ExactSolution(const double x, const double t) const
{
  return sin(x-_xmax)*sin(x-_xmin)*exp(-t);
}

// Fonction source
double Function::SourceFunction(const double x, const double t) const
{
  return -_sigma*(cos(x-_xmax)*cos(x-_xmin)*exp(-t)*2.0-sin(x-_xmax)*sin(x-_xmin)
    *exp(-t)*2.0)-sin(x-_xmax)*sin(x-_xmin)*exp(-t);
}

#define _FUNCTION_CPP
#endif
