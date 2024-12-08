#include <iostream>
#include <vector>

#include <DataLoader.hpp>
#include <Noeud.hpp>

int main()
{
    // Charger le dataset
    DataLoader csv;
    vector<DataPoint> data = csv.loadCSV("../dataset/tp_donnees.csv");
    csv.head(data, 4);

    Noeud node = Noeud(15);
    vector<map<int, double>> result = node.proba_empirique(data);
    node.show_proba_empirique(result);
    cout << "Entropy : " << node.entropy(data) << endl
         << endl;

    vector<vector<DataPoint>> split = node.split(data, {"Age", 16});
    csv.head(split[0]);
    cout << " ************************* " << endl;
    csv.head(split[1]);

    cout << endl;
    vector<Question> quesions = node.list_separ_attributs(data, "Age");
    node.show_questions(quesions);

    cout << endl;
    vector<Question> liste_quesions = node.liste_questions(data);
    node.show_questions(liste_quesions);

    cout << endl;
    cout << "Gain : " << node.gain_entropie(data, {"Genre", 0.5}) << endl;

    cout << endl;
    Question question = node.best_split(data);
    cout << "Best_question : (" << question.attribut << ", " << question.seuil << ")" << endl;

    cout << endl;
    node.grow(data, 0);

    cout << endl;
    for (int i = 0; i < 25; ++i)
    {
        vector<map<int, double>> result = node.prediction(data[i].features);
        node.show_proba_empirique(result);

    }
    cout << "fin" << endl;

    cout << "Precision : " << node.precision(data) << endl;
    return 0;
}


