#include <iostream>
#include <vector>

#include <DataLoader.hpp>

int main()
{
    // Charger le dataset
    DataLoader csv;
    vector<DataPoint> data = csv.loadCSV("../dataset/tp_donnees.csv");
    csv.head(data, 15);

    return 0;
}