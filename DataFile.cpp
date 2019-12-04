#ifndef _DATA_FILE_CPP

#include "DataFile.h"
#include <fstream>
#include <iostream>
#include <cmath>

using namespace std;

// Constructeur
DataFile::DataFile(std::string file_name)
: _file_name(file_name), _if_xmin(false), _if_xmax(false), _if_hx(false), _if_sigma(false),
_if_t0(false), _if_tfinal(false), _if_dt(false), _if_scheme(false), _if_results(false)
{}

// Lecture du fichier de données
void DataFile::ReadDataFile()
{
  ifstream data_file(_file_name.data());
  if (!data_file.is_open())
  {
    cout << "Unable to open file " << _file_name << endl;
    abort();
  }
  else
  {
    cout << "--------------------------------------------------" << endl;
    cout << "Reading data file " << _file_name << endl;
  }

  string file_line;

  // Parcourir le fichier pour rechercher les paramètres
  while (!data_file.eof())
  {
    getline(data_file, file_line);
    if (file_line.find("x_min") != std::string::npos)
    {
      data_file >> _xmin; _if_xmin = true;
    }

    if (file_line.find("x_max") != std::string::npos)
    {
      data_file >> _xmax; _if_xmax = true;
    }

    if (file_line.find("hx") != std::string::npos)
    {
      data_file >> _hx; _if_hx = true;
    }

    if (file_line.find("t0") != std::string::npos)
    {
      data_file >> _t0; _if_t0 = true;
    }

    if (file_line.find("tfinal") != std::string::npos)
    {
      data_file >> _tfinal; _if_tfinal = true;
    }

    if (file_line.find("dt") != std::string::npos)
    {
      data_file >> _dt; _if_dt = true;
    }

    if (file_line.find("sigma") != std::string::npos)
    {
      data_file >> _sigma; _if_sigma = true;
    }

    if (file_line.find("scheme") != std::string::npos)
    {
      data_file >> _scheme; _if_scheme = true;
      if (_scheme != "ExplicitEuler")
      {
        cout << "Only Explicit Euler is implemented." << endl;
        exit(0);
      }
    }

    if (file_line.find("results") != std::string::npos)
    {
      data_file >> _results; _if_results = true;
    }
  }

  // Initialisation par défaut des paramètres non fixés dans le fichier
  // Un message prévient l'utilisateur
  if (!_if_xmin)
  {
    cout << "--------------------------------------------------" << endl;
    cout << "Beware - The default value (0.) is used for x_min." << endl;
    _xmin = 0.;
  }
  if (!_if_xmax)
  {
    cout << "--------------------------------------------------" << endl;
    cout << "Beware - The default value (1.) is used for x_max." << endl;
    _xmax = 1.;
  }
  if (!_if_hx)
  {
    cout << "--------------------------------------------------" << endl;
    cout << "Beware - The default value (0.01) is used for hx." << endl;
    _hx = 0.01;
  }
  if (!_if_t0)
  {
    cout << "--------------------------------------------------" << endl;
    cout << "Beware - The default value (0.) is used for t0." << endl;
    _t0 = 0.;
  }
  if (!_if_tfinal)
  {
    cout << "--------------------------------------------------" << endl;
    cout << "Beware - The default value (0.1) is used for tfinal." << endl;
    _tfinal = 0.1;
  }
  if (!_if_dt)
  {
    cout << "--------------------------------------------------" << endl;
    cout << "Beware - The default value (0.001) is used for dt." << endl;
    _dt = 0.001;
  }
  if (!_if_sigma)
  {
    cout << "--------------------------------------------------" << endl;
    cout << "Beware - The default value (1.) is used for sigma." << endl;
    _sigma = 1.;
  }
  if (!_if_scheme)
  {
    cout << "--------------------------------------------------" << endl;
    cout << "Beware - The default scheme (Explicit Euler scheme) is used." << endl;
    _scheme = "ExplicitEuler";
  }
  if (!_if_results)
  {
    cout << "--------------------------------------------------" << endl;
    cout << "Beware - The default results folder name (results) is used." << endl;
    _results = "results";
  }
  cout << "--------------------------------------------------" << endl;

  cout << "-------------- Adapt dt and hx -------------------" << endl;
  cout << "-------------- xmax = xmin + (Nx+1)*hx -----------" << endl;
  cout << "-------------- tfinal = t0 + nb_it*dt ------------" << endl;
  // Calcul de _Nx et adaptation de _dx pour que (xmax - xmin) = (Nx+1)*hx
  _Nx = int(ceil((_xmax-_xmin)/_hx)-1);
  _hx = (_xmax-_xmin)/(_Nx+1.);
  // Calcul du nombre d'itérations en temps
  int nb_iterations = int(ceil((_tfinal-_t0)/_dt));
  // Adapter le pas de temps pour avoir _tfinal = _t0 + nb_iterations*_dt
	_dt = (_tfinal-_t0) / nb_iterations;
  cout << "--------------------------------------------------" << endl;
}

#define _DATA_FILE_CPP
#endif
