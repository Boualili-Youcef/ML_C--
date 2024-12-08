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
    cout << "Entropy : " << node.entropy(data) << endl << endl;

    vector<vector<DataPoint>> split = node.split(data, {"Age", 16});
    csv.head(split[0]);
    cout << " ************************* " << endl;
    csv.head(split[1]);

    cout << endl;
    vector<Question> quesions = node.list_separ_attributs(data, "Age");
    node.show_questions(quesions);

    return 0;
}