#include <iostream>
#include "TimeScheme.h"

using namespace std;
using namespace Eigen;

int main(int argc, char** argv)
{
  if (argc < 2)
  {
    cout << "Please, enter the name of your data file." << endl;
    abort();
  }

	// ----------------------- Fichier de données --------------------------------
	DataFile* data_file = new DataFile(argv[1]);
  // Lecture du fichier de données
	data_file->ReadDataFile();
	// Définition du nombre d'itérations en temps
	int nb_iterations = int(ceil((data_file->Get_tfinal()-data_file->Get_t0())/data_file->Get_dt()));


	// ---------------------------- Résolution  ----------------------------------
  // Pointeur contenant toutes les fonctions utiles : condition initiale
  // solution exacte et terme source
	Function* function = new Function(data_file);
  // Pointeur vers la classe Laplacian pour tout ce qui concerne la
  // discrétisation en espace (vecteur x, matrice, schéma spatial)
	Laplacian* lap = new Laplacian(function, data_file);
  // Pointeur vers la classe TimeScheme pour tout ce qui concerne la
  // discrétisation en temps (schéma en temps)
	TimeScheme* time_scheme = new EulerScheme();

  cout << "-------------------------------------------------" << endl;
  cout << "Chercher u tel que : " << endl;
  cout << "dt u - sigma Delta u = f,  B" << endl;
  cout << "-------------------------------------------------" << endl;
  cout << "(x_min, x_max, h, dt) = (" << data_file->Get_xmin() << ", "
  		 << data_file->Get_xmax() << ", "	<< data_file->Get_hx() << ", "
			 << data_file->Get_dt() << ")" << endl;
  cout << "-------------------------------------------------" << endl;

  // Initialisation
	time_scheme->Initialize(data_file, lap);
  // Sauvegarde condition initiale
  time_scheme->SaveSolution(0);
  // Boucle en temps
	for (int n = 1; n <= nb_iterations; n++)
  {
    time_scheme->Integrate();
    time_scheme->SaveSolution(n);
  }
	// ---------------------------------------------------------------------------

	//------------------- Si on connait la solution exacte -----------------------
	VectorXd exact_sol = lap->ExactSolution(data_file->Get_tfinal());
	VectorXd approx_sol = time_scheme->GetIterateSolution();
	double error = ((approx_sol-exact_sol).array().abs()).maxCoeff();
	cout << "Erreur = " << error << endl;
	cout << "-------------------------------------------------" << endl;
	// ---------------------------------------------------------------------------

  // ----------------------- Libère la mémoire ---------------------------------
  // Ne pas oublier de détruire tous les pointeurs que nous avons utilisé
	delete time_scheme;
  delete lap;
  delete data_file;
  delete function;
  // ---------------------------------------------------------------------------

	return 0;
}
