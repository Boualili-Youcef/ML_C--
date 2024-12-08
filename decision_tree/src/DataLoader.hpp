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
    static std::vector<std::string> columnNames;

public:
    // Fonction pour charger le fichier CSV
    vector<DataPoint> loadCSV(const string &filePath);
    int getAttributeIndex(const string &attributeName) const;
    void head(const vector<DataPoint> &data, int size = 5);

    static const std::vector<std::string> &getColumnNames();
};
