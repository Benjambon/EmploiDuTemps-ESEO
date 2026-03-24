#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDialog>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QMessageBox>
#include <QComboBox>
#include <vector>
#include "enseignant.h"
#include "groupeetudiant.h"
#include "salle.h"
#include "controleur_salle.h"
#include "controleur_groupeetudiant.h"
#include "controleur_enseignant.h"
#include "controleur_ecue.h"

MainWindow::MainWindow(QString dataPath, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_dataPath(dataPath)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// --------------------------------------------------------
// Gestion des Enseignants
// --------------------------------------------------------

void MainWindow::on_btnAjouterEnseignant_clicked()
{
    // Appel du contrôleur
    Enseignant* nouvelEnseignant = Controleur_enseignant::creationEnseignant();

    if (nouvelEnseignant != nullptr) {
        QString fichierJson = m_dataPath + "enseignants.json";
        std::vector<Enseignant> liste = Enseignant::readFromJSON(fichierJson);

        liste.push_back(*nouvelEnseignant);
        Enseignant::writeToJSON(liste, fichierJson);

        QMessageBox::information(this, "Succès", "L'enseignant a été ajouté et sauvegardé.");

        delete nouvelEnseignant;
    }
}

void MainWindow::on_btnAfficherEnseignants_clicked()
{
    QString fichierJson = m_dataPath + "enseignants.json";
    std::vector<Enseignant> listeEnseignants = Enseignant::readFromJSON(fichierJson);

    if (listeEnseignants.empty()) {
        QMessageBox::information(this, "Liste des enseignants", "Aucun enseignant n'est enregistré.");
        return;
    }

    QString texteAffichage = "Voici la liste des enseignants :\n\n";
    for (size_t i = 0; i < listeEnseignants.size(); ++i) {
        texteAffichage += QString::fromStdString(listeEnseignants[i].toString()) + "\n";
    }

    QMessageBox::information(this, "Liste des enseignants", texteAffichage);
}

void MainWindow::on_btnSupprimerEnseignant_clicked()
{
    QString fichierJson = m_dataPath + "enseignants.json";
    std::vector<Enseignant> liste = Enseignant::readFromJSON(fichierJson);

    if (liste.empty()) {
        QMessageBox::information(this, "Information", "Il n'y a aucun enseignant à supprimer.");
        return;
    }

    int index = Controleur_enseignant::supprimerEnseignant(liste);

    if (index >= 0 && static_cast<size_t>(index) < liste.size()) {
        liste.erase(liste.begin() + index);
        Enseignant::writeToJSON(liste, fichierJson);
        QMessageBox::information(this, "Succès", "L'enseignant a été supprimé avec succès.");
    }
}

// --------------------------------------------------------
// Gestion des Groupes d'Étudiants
// --------------------------------------------------------

void MainWindow::on_btnAjouterGroupe_clicked()
{
    // Appel du contrôleur
    GroupeEtudiant* nouveauGroupe = Controleur_groupeetudiant::creationGroupe();

    // Si le pointeur n'est pas nul, on sauvegarde
    if (nouveauGroupe != nullptr) {
        QString fichierJson = m_dataPath + "groupes.json";
        std::vector<GroupeEtudiant> liste = GroupeEtudiant::readFromJSON(fichierJson);

        liste.push_back(*nouveauGroupe);
        GroupeEtudiant::writeToJSON(liste, fichierJson);

        QMessageBox::information(this, "Succès", "Le groupe a été ajouté et sauvegardé.");

        // Libération de la mémoire
        delete nouveauGroupe;
    }
}

void MainWindow::on_btnAfficherGroupes_clicked()
{
    QString fichierJson = m_dataPath + "groupes.json";
    std::vector<GroupeEtudiant> liste = GroupeEtudiant::readFromJSON(fichierJson);

    if (liste.empty()) {
        QMessageBox::information(this, "Liste des groupes", "Aucun groupe n'est enregistré.");
        return;
    }

    QString texteAffichage = "Voici la liste des groupes :\n\n";
    for (size_t i = 0; i < liste.size(); ++i) {
        texteAffichage += QString::fromStdString(liste[i].toString()) + "\n";
    }

    QMessageBox::information(this, "Liste des groupes", texteAffichage);
}

void MainWindow::on_btnSupprimerGroupe_clicked()
{
    QString fichierJson = m_dataPath + "groupes.json";
    std::vector<GroupeEtudiant> liste = GroupeEtudiant::readFromJSON(fichierJson);

    if (liste.empty()) {
        QMessageBox::information(this, "Information", "Il n'y a aucun groupe à supprimer.");
        return;
    }

    int index = Controleur_groupeetudiant::supprimerGroupe(liste);

    if (index >= 0 && static_cast<size_t>(index) < liste.size()) {
        liste.erase(liste.begin() + index);
        GroupeEtudiant::writeToJSON(liste, fichierJson);
        QMessageBox::information(this, "Succès", "Le groupe a été supprimé avec succès.");
    }
}

// --------------------------------------------------------
// Gestion des Salles
// --------------------------------------------------------


void MainWindow::on_btnAjouterSalle_clicked()
{
    Salle* nouvelleSalle = Controleur_salle::creationSalle();

    // Si la salle n'est pas nulle, c'est que l'utilisateur a validé la création
    if (nouvelleSalle != nullptr) {
        QString fichierJson = m_dataPath + "salles.json";
        std::vector<Salle> liste = Salle::readFromJSON(fichierJson);

        liste.push_back(*nouvelleSalle);
        Salle::writeToJSON(liste, fichierJson);

        QMessageBox::information(this, "Succès", "La salle a été ajoutée et sauvegardée.");

        // Pensez à libérer la mémoire allouée dynamiquement par le "new" dans le contrôleur
        delete nouvelleSalle;
    }
}

void MainWindow::on_btnAfficherSalles_clicked()
{
    QString fichierJson = m_dataPath + "salles.json";
    std::vector<Salle> liste = Salle::readFromJSON(fichierJson);

    if (liste.empty()) {
        QMessageBox::information(this, "Liste des salles", "Aucune salle n'est enregistrée.");
        return;
    }

    QString texteAffichage = "Voici la liste des salles :\n\n";
    for (size_t i = 0; i < liste.size(); ++i) {
        texteAffichage += QString::fromStdString(liste[i].toString()) + "\n";
    }

    QMessageBox::information(this, "Liste des salles", texteAffichage);
}

void MainWindow::on_btnSupprimerSalle_clicked()
{
    QString fichierJson = m_dataPath + "salles.json";
    std::vector<Salle> liste = Salle::readFromJSON(fichierJson);

    if (liste.empty()) {
        QMessageBox::information(this, "Information", "Il n'y a aucune salle à supprimer.");
        return;
    }

    int index = Controleur_salle::supprimerSalle(liste);

    if (index >= 0 && static_cast<size_t>(index) < liste.size()) {
        liste.erase(liste.begin() + index);
        Salle::writeToJSON(liste, fichierJson);
        QMessageBox::information(this, "Succès", "La salle a été supprimée avec succès.");
    }
}

// --------------------------------------------------------
// Gestion des ECUE
// --------------------------------------------------------

void MainWindow::on_btnAjouterEcue_clicked()
{
    // 1. Lecture des dépendances
    std::vector<Enseignant> listeE = Enseignant::readFromJSON(m_dataPath + "enseignants.json");
    std::vector<GroupeEtudiant> listeG = GroupeEtudiant::readFromJSON(m_dataPath + "groupes.json");

    if (listeE.empty() || listeG.empty()) {
        QMessageBox::warning(this, "Erreur", "Vous devez d'abord créer au moins un enseignant et un groupe pour pouvoir créer un ECUE.");
        return;
    }

    // 2. Appel du contrôleur
    Ecue* nouvelEcue = Controleur_ecue::creationEcue(listeE, listeG);

    // 3. Sauvegarde
    if (nouvelEcue != nullptr) {
        QString fichierJson = m_dataPath + "ecue.json";
        std::vector<Ecue> liste = Ecue::readFromJSON(fichierJson);
        liste.push_back(*nouvelEcue);
        Ecue::writeToJSON(liste, fichierJson);
        QMessageBox::information(this, "Succès", "L'ECUE a été ajouté et sauvegardé.");
        delete nouvelEcue;
    }
}

void MainWindow::on_btnSupprimerEcue_clicked()
{
    QString fichierJson = m_dataPath + "ecue.json";
    std::vector<Ecue> liste = Ecue::readFromJSON(fichierJson);

    if (liste.empty()) {
        QMessageBox::information(this, "Information", "Il n'y a aucun ECUE à supprimer.");
        return;
    }

    int index = Controleur_ecue::supprimerEcue(liste);

    if (index >= 0 && static_cast<size_t>(index) < liste.size()) {
        liste.erase(liste.begin() + index);
        Ecue::writeToJSON(liste, fichierJson);
        QMessageBox::information(this, "Succès", "L'ECUE a été supprimé avec succès.");
    }
}

void MainWindow::on_btnAfficherEcues_clicked()
{
    QString fichierJson = m_dataPath + "ecue.json";
    std::vector<Ecue> liste = Ecue::readFromJSON(fichierJson);

    if (liste.empty()) {
        QMessageBox::information(this, "Liste des ECUE", "Aucun ECUE n'est enregistré.");
        return;
    }

    QString texteAffichage = "Voici la liste des ECUE :\n\n";
    for (size_t i = 0; i < liste.size(); ++i) {
        texteAffichage += QString::fromStdString(liste[i].to_string()) + "\n";
    }

    QMessageBox::information(this, "Liste des ECUE", texteAffichage);
}
