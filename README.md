# Logiciel de Gestion d'Emploi du Temps - ESEO

Application de bureau en C++ (framework Qt) destinée à la création et la gestion des emplois du temps. Elle permet l'administration des promotions, du corps enseignant, des salles et l'affectation des créneaux horaires avec détection de conflits.

## Fonctionnalités Principales

* **Gestion des ressources :** Opérations CRUD sur les enseignants, groupes d'étudiants et salles. Génération automatique des adresses email pour les enseignants.
* **Gestion des ECUEs :** Création de modules liant un enseignant, un groupe et un quota d'heures par type de cours (CM, TD, TP, Examens).
* **Planification des Créneaux :**
  * Semaine de 5 jours, 4 créneaux par jour.
  * Détection de conflits : vérification de la disponibilité de la salle, de l'enseignant et du groupe.
  * Décrémentation automatique des heures planifiées.
* **Tableaux de bord :** Suivi des heures affectées versus heures totales par ECUE.
* **Persistance des données :** Sauvegarde et chargement au format JSON.

## Technologies et Prérequis

* **Langage :** C++17
* **Framework :** Qt (Modules : core, gui, widgets, testlib)
* **Persistance :** JSON (QJsonObject, QJsonDocument)
* **Architecture :** Modèle-Vue-Contrôleur (MVC)

## Installation et Exécution

1. Cloner le dépôt.
2. Ouvrir le fichier de projet `EmploiDuTempsESEO.pro` dans Qt Creator.
3. S'assurer que le dossier `data/` contenant les fichiers JSON (`enseignants.json`, `salles.json`, `groupes.json`, `ecue.json`, `creneaux.json`) est placé à la racine de l'exécutable généré.
4. Compiler et exécuter.

## Architecture du Projet

* **Modèles :** Fichiers `.cpp` définissant les entités (Ecue, Creneau, etc.), les validations métier et l'import/export JSON.
* **Vues :** Interface utilisateur (`mainwindow.ui`, boîtes de dialogue) et style globalisé (`styles/styles.qss`).
* **Contrôleurs :** Fichiers `controleur_*.cpp` assurant la liaison entre vues et modèles et la gestion des règles métier.

## Tests Unitaires

Le projet intègre des tests automatisés via le framework QtTest.
* Validation des formats de saisie (noms, numéros de salle).
* Vérification des quotas horaires (interdiction de valeurs impaires ou négatives).
* Validation des règles de calendrier (rejet des planifications le week-end).

Les tests s'exécutent automatiquement au démarrage via le fichier `main.cpp`.
