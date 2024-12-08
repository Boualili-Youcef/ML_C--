# Définir la version minimale de CMake
cmake_minimum_required(VERSION 3.10)

# Définir le nom du projet
project(DecisionTree)

# Définir la norme C++ à utiliser
set(CMAKE_CXX_STANDARD 17)

# Ajouter le répertoire src contenant les fichiers source et headers
include_directories(src)

# Ajouter l'exécutable en spécifiant les fichiers .cpp
add_executable(DecisionTree src/main.cpp src/DataLoader.cpp src/Noeud.cpp)

# Copier le fichier .csv vers le répertoire de sortie, si nécessaire
configure_file(${CMAKE_SOURCE_DIR}/dataset/tp_donnees.csv ${CMAKE_BINARY_DIR}/data/tp_donnees.csv COPYONLY)

# Ajouter une commande personnalisée pour exécuter l'exécutable et ensuite le script Python
# Pour chaque execution faut faire une modification dans le CmakeLists.txt pour que ca rebuild
add_custom_command(TARGET DecisionTree POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E echo "Exécution du programme C++..."
    COMMAND ${CMAKE_COMMAND} -E env ./DecisionTree
    COMMAND ${CMAKE_COMMAND} -E echo "Exécution du script Python..."
    COMMAND ${CMAKE_COMMAND} -E env python3 ${CMAKE_SOURCE_DIR}/src/display.py
    COMMENT "Exécution du programme et du script Python après la compilation"
)
