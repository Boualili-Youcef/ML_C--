#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <set>
#include <map>

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
    vector<Question> question;
    // enfants = {}; // TODO les enfants
    int profondeur_max;
    double proba;
    int hauteur = 0;

public:
    Noeud(int max_depth = numeric_limits<int>::max());

    vector<map<int, double>> proba_empirique(vector<DataPoint> data);
    void show_proba_empirique(vector<map<int, double>> result);
};