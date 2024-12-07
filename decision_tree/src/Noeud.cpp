#include <Noeud.hpp>

Noeud::Noeud(int max_depth)
    : profondeur_max(max_depth), proba(0.0), hauteur(0) {};

map<int, int> label_counts(const vector<DataPoint> &data)
{
    map<int, int> counts;
    for (const DataPoint &point : data)
    {
        counts[point.label]++;
    }
    return counts;
}

vector<map<int, double>> Noeud::proba_empirique(vector<DataPoint> data)
{
    if (data.size() == 0)
    {
        return {};
    }
    map<int, int> label_map = label_counts(data);
    vector<map<int, double>> proba;
    for (const auto &label : label_map)
    {
        map<int, double> proba_label;
        proba_label[label.first] = (double)label.second / (double)data.size();
        proba.push_back(proba_label);
    }
    return proba;
}

void Noeud::show_proba_empirique(vector<map<int, double>> result)
{
    cout << "{";
    for (size_t i = 0; i < result.size(); i++)
    {
        for (const auto &proba : result[i])
        {
            cout << proba.first << " : " << proba.second ;
        }
        if (i != result.size() - 1)
        {
            cout << "; ";
        }
    }
    cout << "}" << endl;
}
