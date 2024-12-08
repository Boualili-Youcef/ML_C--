#include <Noeud.hpp>

Noeud::Noeud(int max_depth)
    : profondeur_max(max_depth), proba(0.0), hauteur(0) {};

// Part proba empririque
map<int, int> label_counts(const vector<DataPoint> &data)
{
    map<int, int> counts;
    for (const DataPoint &point : data)
    {
        counts[point.label]++;
    }
    return counts;
}

// int is the value of the label
// double is the empirical value
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
            cout << proba.first << " : " << proba.second;
        }
        if (i != result.size() - 1)
        {
            cout << "; ";
        }
    }
    cout << "}" << endl;
}

// Part entropy
double Noeud::entropy(vector<DataPoint> data)
{
    vector<map<int, double>> pe_value = proba_empirique(data);
    double entropy;
    for (size_t i = 0; i < pe_value.size(); i++)
    {
        for (const auto &proba : pe_value[i])
        {
            entropy += proba.second * log2(proba.second);
        }
    }
    return -entropy;
}

// Spliting the data depending on the question
vector<vector<DataPoint>> Noeud::split(const vector<DataPoint> &data, const Question &question)
{
    vector<DataPoint> d1;
    vector<DataPoint> d2;

    int index = loader.getAttributeIndex(question.attribut);

    for (const auto &d : data)
    {
        if (d.features[index] < question.seuil)
        {
            d1.push_back(d);
        }
        else
        {
            d2.push_back(d);
        }
    }

    return {d1, d2};
}

// Constucting a vectore of all possible question concidering an attribute
vector<Question> Noeud::list_separ_attributs(const vector<DataPoint> &data, const string &attribute)
{
    int index = loader.getAttributeIndex(attribute);
    vector<Question> vec_question;
    set<double> seuils;

    for (size_t i = 0; i < data.size() - 1; ++i)
    {
        seuils.insert((data[i].features[index] + data[i + 1].features[index]) / 2);
    }
    for (const double &s : seuils)
    {

        vec_question.push_back({attribute, s});
    }
    return vec_question;
}

// Display questions
void Noeud::show_questions(const vector<Question> &questions, int size)
{
    cout << "{";
    for (const auto &question : questions)
    {
        size--;
        cout << "(" << question.attribut << ", " << question.seuil << ") ";
        if (size == 0)
        {
            break;
        }
    }
    cout << "}" << endl;
}

// 