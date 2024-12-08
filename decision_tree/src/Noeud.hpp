#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <set>
#include <map>
#include <cmath>

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
    // enfants = {}; // TODO les enfants
    int profondeur_max;
    double proba;
    int hauteur = 0;

public:
    Noeud(int max_depth = numeric_limits<int>::max());

    vector<map<int, double>> proba_empirique(vector<DataPoint> data);
    void show_proba_empirique(vector<map<int, double>> result);
    double entropy(vector<DataPoint> data);
    vector<vector<DataPoint>> split(const vector<DataPoint> &data, const Question &question);
    vector<Question> list_separ_attributs(const vector<DataPoint> &data, const string &attribute);
    void show_questions(const vector<Question>& questions, int size = 10);

};