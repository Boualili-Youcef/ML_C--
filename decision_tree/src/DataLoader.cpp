#include <DataLoader.hpp>

// Fonction pour charger le fichier CSV
vector<DataPoint> DataLoader::loadCSV(const string &filePath)
{
    vector<DataPoint> dataset;
    ifstream file(filePath);

    if (!file.is_open())
    {
        cerr << "Erreur : Impossible d'ouvrir le fichier " << filePath << endl;
        return dataset;
    }

    string line;

    // Lire l'en-tête (première ligne)
    if (getline(file, line))
    {
        stringstream ss(line);
        string columnName;

        // Diviser l'en-tête en colonnes et les ajouter à columnNames
        while (getline(ss, columnName, ','))
        {
            columnNames.push_back(columnName);
        }
    }

    // Lire les données ligne par ligne
    while (getline(file, line))
    {
        stringstream ss(line);
        string value;
        vector<double> features;

        // Lire chaque valeur dans la ligne
        while (getline(ss, value, ','))
        {
            features.push_back(stod(value)); // Convertir en double
        }

        if (!features.empty())
        {
            // La dernière colonne est le label
            int label = static_cast<int>(features.back());
            features.pop_back(); // Supprimer le label des features

            // Ajouter le DataPoint au dataset
            dataset.push_back({features, label});
        }
    }

    file.close();
    return dataset;
}

double DataLoader::getAttribute(const DataPoint &point, const std::string &attributeName)
{
    for (size_t i = 0; i < columnNames.size(); ++i)
    {
        if (columnNames[i] == attributeName)
        {
            return point.features[i];
        }
    }
    return 0.0;
}

// Fonction de verification de chargement
void DataLoader::head(const vector<DataPoint> &data, int size)
{

    if (size > data.size())
    {
        size = data.size();
    }

    for (size_t i = 0; i < columnNames.size() - 1; i++)
    {

        cout << columnNames[i] << ", ";
    }

    cout << columnNames[columnNames.size() - 1] << endl;

    for (size_t i = 0; i < size - 1; i++)
    {
        cout << "{feature : ";
        for (size_t j = 0; j < data[i].features.size() - 1; j++)
        {
            cout << data[i].features[j] << ", ";
        }
        cout << data[i].features[data[i].features.size() - 1] << "} ,";
        cout << " {label : " << data[i].label << "}" << endl;
    }
}
