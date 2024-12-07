#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

// Définition d'un point de données
struct DataPoint
{
    vector<double> features; // Liste des valeurs des attributs
    int label;               // Label de la classe
};

class DataLoader
{
private:
    std::vector<std::string> columnNames;
public:
    // Fonction pour charger le fichier CSV
    vector<DataPoint> loadCSV(const string &filePath);
    double getAttribute(const DataPoint &point, const std::string &attributeName);
    void head(const vector<DataPoint>& data, int size = 5);

};
