#include <iostream>
#include <vector>

#include <DataLoader.hpp>
#include <Noeud.hpp>

int main()
{
    // Charger le dataset
    DataLoader csv;
    vector<DataPoint> data = csv.loadCSV("../dataset/tp_donnees.csv");
    csv.head(data, 15);

    Noeud node;
    vector<map<int, double>> result = node.proba_empirique(data);
    node.show_proba_empirique(result);

    return 0;
}