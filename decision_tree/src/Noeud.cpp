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
vector<map<int, double>> Noeud::proba_empirique(const vector<DataPoint> &data)
{
    vector<map<int, double>> proba;

    if (data.size() == 0)
    {
        return proba;
    }
    map<int, int> label_map = label_counts(data);
    for (const auto &label : label_map)
    {
        map<int, double> proba_label;
        proba_label[label.first] = (double)label.second / (double)data.size();
        proba.push_back(proba_label);
    }
    return proba;
}

void Noeud::show_proba_empirique(const vector<map<int, double>> &result)
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
double Noeud::entropy(const vector<DataPoint> &data)
{
    vector<map<int, double>> pe_value = proba_empirique(data);
    double entropy = 0.0;

    for (const auto &class_probas : pe_value)
    {
        for (const auto &proba : class_probas)
        {
            if (proba.second > 0.0)
            {
                entropy += proba.second * log2(proba.second);
            }
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

    double seuil;

    vector<DataPoint> sorted_data = data;
    sort(sorted_data.begin(), sorted_data.end(),
         [index](const DataPoint &a, const DataPoint &b)
         {
             return a.features[index] < b.features[index];
         });

    for (size_t i = 0; i < sorted_data.size() - 1; ++i)
    {
        if (sorted_data[i].features[index] != sorted_data[i + 1].features[index])
        {
            seuil = (sorted_data[i].features[index] + sorted_data[i + 1].features[index]) / 2;
            seuils.insert(seuil);
        }
    }

    // Remplissage du vecteur des questions avec les seuils trouvés
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

// All questions now
vector<Question> Noeud::liste_questions(const vector<DataPoint> &data)
{
    vector<string> attributes = loader.getColumnNames();
    vector<Question> liste_questions;
    for (size_t i = 0; i < attributes.size() - 1; ++i)
    {
        vector<Question> tmp = list_separ_attributs(data, attributes[i]);
        liste_questions.insert(liste_questions.end(), tmp.begin(), tmp.end());
    }
    return liste_questions;
}

double Noeud::gain_entropie(const vector<DataPoint> &data, const Question &question)
{
    vector<vector<DataPoint>> data_split = split(data, question);
    vector<DataPoint> d1 = data_split[0];
    vector<DataPoint> d2 = data_split[1];

    double r1 = (double)d1.size() / data.size();
    double r2 = (double)d2.size() / data.size();

    return entropy(data) - r1 * entropy(d1) - r2 * entropy(d2);
}

Question Noeud::best_split(const vector<DataPoint> &data)
{
    double gain_max = -std::numeric_limits<double>::infinity();
    vector<Question> questions = liste_questions(data);

    if (questions.empty())
    {
        return {"end", -1}; // We can do better her !!
    }

    Question best_question;

    for (const Question &question : questions)
    {
        double gain_question = gain_entropie(data, question);
        if (gain_question > gain_max)
        {
            gain_max = gain_question;
            best_question = question;
        }
    }

    return best_question;
}

void Noeud::grow(const vector<DataPoint> &data, int profondeur)
{
    if (data.empty())
    {
        cout << "Aucune donnée, profondeur: " << profondeur << endl;
        hauteur = profondeur;
        this->proba = proba_empirique(data);
        return;
    }

    donnees = data;
    double entropy_value = this->entropy(data);

    Question best_question = best_split(data);

    if (best_question.attribut == "end" && best_question.seuil == -1)
    {
        cout << "Fin de la séparation à profondeur: " << profondeur << endl;
        hauteur = profondeur;
        this->proba = proba_empirique(data);
        return;
    }

    vector<vector<DataPoint>> d = split(data, best_question);
    vector<DataPoint> d1 = d[0];
    vector<DataPoint> d2 = d[1];

    if (entropy_value > 0 && d1.size() > 0 && d2.size() > 0 && profondeur_max > profondeur)
    {
        node_question = best_question;
        profondeur++;
        enfants["left"] = make_unique<Noeud>(profondeur_max);
        enfants["right"] = make_unique<Noeud>(profondeur_max);
        enfants["left"]->grow(d1, profondeur);
        enfants["right"]->grow(d2, profondeur);
    }
    else
    {
        hauteur = profondeur;
        this->proba = proba_empirique(data);
        this->show_proba_empirique(proba);
    }
}

vector<map<int, double>> Noeud::getProba()
{
    return proba;
}
