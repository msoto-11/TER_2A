# Compilateur utilisé
CC=g++

# Options en mode optimisé - La variable NDEBUG est définie
OPTIM_FLAG = -O3 -DNDEBUG -I Eigen/Eigen -std=c++11 -Wall
# Options en mode debug - La variable NDEBUG n’est pas définie
DEBUG_FLAG = -g -I Eigen/Eigen -std=c++11 -Wall

# On choisit comment on compile
CXX_FLAGS = $(OPTIM_FLAG)

# Le nom de l'exécutable
PROG = run

# Les fichiers source à compiler
SRC = main.cc TimeScheme.cpp SpaceScheme.cpp DataFile.cpp Function.cpp

# La commande complète : compile seulement si un fichier a été modifié
$(PROG) : $(SRC)
	$(CC) $(SRC) $(CXX_FLAGS) -o $(PROG)
# Évite de devoir connaitre le nom de l'exécutable
all : $(PROG)

# Supprime l'exécutable, les fichiers binaires (.o) et les fichiers
# temporaires de sauvegarde (~)
clean :
	rm -f *.o *~ $(PROG)
