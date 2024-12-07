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

file(COPY ${CMAKE_SOURCE_DIR}/dataset/tp_donnees.csv DESTINATION ${CMAKE_BINARY_DIR}/data)
