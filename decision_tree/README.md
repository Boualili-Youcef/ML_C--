## Documentation du Projet : Arbre de Décision

### Introduction

Ce projet implémente un **algorithme d'apprentissage supervisé** : l'arbre de décision. Cet outil est particulièrement utile pour la **classification** et la **régression**. Il construit un modèle prédictif en formulant une série de questions sur les données d'entrée.

### Objectifs

* **Construction d'un arbre de décision :** Implémenter une structure de données arborescente pour représenter les décisions successives.
* **Calcul de probabilités empiriques :** Évaluer la probabilité d'une classe à chaque nœud de l'arbre en fonction des données d'entraînement.
* **Prédiction :** Utiliser l'arbre construit pour classer de nouvelles données.

### Structure du Projet

Le projet est organisé en plusieurs fichiers :

* **Noeud.hpp/.cpp :** Définition et implémentation de la classe `Noeud`, représentant un nœud dans l'arbre de décision.
* **DataLoader.hpp/.cpp :** Gestion de l'importation et du prétraitement des données.
* **Main.cpp :** Point d'entrée du programme, où l'arbre est construit et utilisé pour effectuer des prédictions.

### Classe Noeud

La classe `Noeud` est la brique de base de l'arbre de décision. Elle contient :
* **Attribut :** L'attribut sur lequel la décision est prise à ce nœud.
* **Enfant gauche/droit :** Pointers vers les nœuds enfants.
* **Valeur seuil :** La valeur seuil utilisée pour la division des données.
* **Classe prédite (pour les feuilles) :** La classe la plus probable si le nœud est une feuille.
* **Impuretés :** Une mesure de l'hétérogénéité des données à ce nœud (e.g., indice de Gini, entropie).

### Algorithme de Construction
* **Sélection de l'attribut :** À chaque nœud, on sélectionne l'attribut qui maximise la réduction de l'impureté.
* **Création des enfants :** On crée deux nœuds enfants en fonction de la valeur de l'attribut sélectionné.
* **Arrêt de la récursion :** On arrête la construction d'un sous-arbre lorsque :
   * Toutes les instances appartiennent à la même classe.
   * Il n'y a plus d'attribut à tester.
   * La profondeur maximale de l'arbre est atteinte.

### Prédiction
Pour prédire la classe d'une nouvelle instance, on parcourt l'arbre de décision en posant les questions successives jusqu'à atteindre une feuille. La classe prédite est celle associée à cette feuille.

### Évaluation
L'efficacité de l'arbre de décision peut être évaluée à l'aide de métriques telles que :
* **Taux de bonne classification :** Proportion d'instances correctement classées.
* **Matrice de confusion :** Tableau croisé permettant d'analyser les erreurs de classification.
* **Courbe ROC :** Pour les problèmes de classification binaire, elle permet de visualiser le compromis entre le taux de vrais positifs et le taux de faux positifs.

### Améliorations Possibles
* **Gestion des données manquantes**
* **Élagage de l'arbre**
* **Méthodes de sélection d'attributs**
* **Ensembles d'arbres**

### Conclusion
Les arbres de décision sont un outil puissant et intuitif pour la modélisation prédictive. Ce projet fournit une base solide pour explorer et approfondir cette technique.

**Pour une documentation encore plus complète, vous pouvez ajouter des sections sur :**
* **Les données utilisées**
* **Les hyperparamètres**
* **Les résultats expérimentaux**
* **Le code source**

**BOUALILI Youcef**
**07/12/2024**