#ifndef _DATA_FILE_H

#include <string>
#include <vector>
#include <iostream>

class DataFile {
private:
  // Tous les paramètres contenus dans le fichier de données
  double _xmin;
  double _xmax;
  double _hx;
  int _Nx;
  double _sigma;
  double _t0;
  double _tfinal;
  double _dt;
  std::string _scheme;
  std::string _results;
  // Nom du fichier de données
  const std::string _file_name;
  // Pour savoir si l'utilisateur a donné la valeur du paramètres
  // ou les paramètres par défaut doivent être utilisés
  bool _if_xmin;
  bool _if_xmax;
  bool _if_hx;
  bool _if_sigma;
  bool _if_t0;
  bool _if_tfinal;
  bool _if_dt;
  bool _if_scheme;
  bool _if_results;

public:
  // Constructeur
  DataFile(std::string file_name);
  // La lecture du fichier
  void ReadDataFile();
  // Toutes les fonctions pour renvoyer les paramètres
  // Comme ce sont juste des fonctions Get, il est plus simple de les
  // définir directement dans le .cpp
  double Get_xmin(){return _xmin;};
  double Get_xmax(){return _xmax;};
  double Get_hx(){return _hx;};
  double Get_Nx(){return _Nx;};
  double Get_sigma(){return _sigma;};
  double Get_t0(){return _t0;};
  double Get_tfinal(){return _tfinal;};
  double Get_dt(){return _dt;};
  std::string Get_scheme(){return _scheme;};
  std::string Get_results(){return _results;};
};

#define _DATA_FILE_H
#endif
