#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <set>
#include <map>
#include <cmath>
#include <algorithm>
#include <memory>
#include <random>

#include <DataLoader.hpp>

using namespace std;

struct Question
{
    string attribut;
    double seuil;
};

class Noeud
{
private:
    DataLoader loader;
    vector<Question> question;
    Question node_question = {"end", -1};
    map<std::string, std::unique_ptr<Noeud>> enfants;
    vector<DataPoint> donnees;
    int profondeur_max;
    vector<map<int, double>> proba;
    int hauteur = 0;

public:
    Noeud(int profondeur_max = 5);

    vector<map<int, double>> proba_empirique(const vector<DataPoint> &data);
    void show_proba_empirique(const vector<map<int, double>> &result);
    double entropy(const vector<DataPoint> &data);
    vector<vector<DataPoint>> split(const vector<DataPoint> &data, const Question &question);
    vector<Question> list_separ_attributs(const vector<DataPoint> &data, const string &attribute);
    void show_questions(const vector<Question> &questions, int size = 10);
    vector<Question> liste_questions(const vector<DataPoint> &data);
    double gain_entropie(const vector<DataPoint> &data, const Question &question);
    Question best_split(const vector<DataPoint> &data);
    void grow(const vector<DataPoint> &data, int profondeur = 0);
    vector<map<int, double>> getProba();
    vector<map<int, double>> prediction(const vector<double> &x);
    double precision(const vector<DataPoint> &data);
    vector<vector<DataPoint>> split_train_test(const vector<DataPoint> &data);
    void train_data(const vector<DataPoint> &data, int depth); // Pas au point 
};