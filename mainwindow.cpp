#include "mainwindow.h"
#include "ui_mainwindow.h"

// Inclusions pour l'interface graphique
#include <QDialog>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QMessageBox>
#include <QComboBox>

// Inclusions pour la logique métier
#include <vector>
#include "enseignant.h"
#include "groupeetudiant.h"
#include "salle.h"

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
    QDialog dialog(this);
    dialog.setWindowTitle("Ajouter un enseignant");

    QVBoxLayout *layoutMain = new QVBoxLayout(&dialog);
    QFormLayout *layoutForm = new QFormLayout();

    QLineEdit *editNom = new QLineEdit(&dialog);
    QLineEdit *editPrenom = new QLineEdit(&dialog);
    QLineEdit *editMail = new QLineEdit(&dialog);

    layoutForm->addRow("Nom :", editNom);
    layoutForm->addRow("Prénom :", editPrenom);
    layoutForm->addRow("Mail :", editMail);

    layoutMain->addLayout(layoutForm);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, &dialog);
    buttonBox->button(QDialogButtonBox::Ok)->setText("Créer");
    buttonBox->button(QDialogButtonBox::Cancel)->setText("Annuler");
    layoutMain->addWidget(buttonBox);

    connect(buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

    if (dialog.exec() == QDialog::Accepted) {
        std::string nom = editNom->text().toStdString();
        std::string prenom = editPrenom->text().toStdString();
        std::string mail = editMail->text().toStdString();

        Enseignant nouvelEnseignant;
        if (mail.empty()) {
            nouvelEnseignant = Enseignant(nom, prenom);
        } else {
            nouvelEnseignant = Enseignant(nom, prenom, mail);
        }

        QString fichierJson = m_dataPath + "enseignants.json";
        std::vector<Enseignant> liste = Enseignant::readFromJSON(fichierJson);

        liste.push_back(nouvelEnseignant);
        Enseignant::writeToJSON(liste, fichierJson);

        QMessageBox::information(this, "Succès", "L'enseignant a été ajouté et sauvegardé.");
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

// --------------------------------------------------------
// Gestion des Groupes d'Étudiants
// --------------------------------------------------------

void MainWindow::on_btnAjouterGroupe_clicked()
{
    QDialog dialog(this);
    dialog.setWindowTitle("Ajouter un groupe");

    QVBoxLayout *layoutMain = new QVBoxLayout(&dialog);
    QFormLayout *layoutForm = new QFormLayout();
    QLineEdit *editNom = new QLineEdit(&dialog);

    layoutForm->addRow("Nom du groupe :", editNom);
    layoutMain->addLayout(layoutForm);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, &dialog);
    buttonBox->button(QDialogButtonBox::Ok)->setText("Créer");
    buttonBox->button(QDialogButtonBox::Cancel)->setText("Annuler");
    layoutMain->addWidget(buttonBox);

    connect(buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

    if (dialog.exec() == QDialog::Accepted) {
        std::string nom = editNom->text().toStdString();

        GroupeEtudiant nouveauGroupe(nom);

        QString fichierJson = m_dataPath + "groupes.json";
        std::vector<GroupeEtudiant> liste = GroupeEtudiant::readFromJSON(fichierJson);

        liste.push_back(nouveauGroupe);
        GroupeEtudiant::writeToJSON(liste, fichierJson);

        QMessageBox::information(this, "Succès", "Le groupe a été ajouté et sauvegardé.");
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

// --------------------------------------------------------
// Gestion des Salles
// --------------------------------------------------------

void MainWindow::on_btnAjouterSalle_clicked()
{
    QDialog dialog(this);
    dialog.setWindowTitle("Ajouter une salle");

    QVBoxLayout *layoutMain = new QVBoxLayout(&dialog);
    QFormLayout *layoutForm = new QFormLayout();

    QLineEdit *editNumero = new QLineEdit(&dialog);
    QComboBox *comboType = new QComboBox(&dialog);

    comboType->addItem("Salle standard", TypeSalle::SALLE);
    comboType->addItem("Electronique", TypeSalle::ELECTRONIQUE);
    comboType->addItem("Informatique", TypeSalle::INFORMATIQUE);

    layoutForm->addRow("Numéro :", editNumero);
    layoutForm->addRow("Type :", comboType);
    layoutMain->addLayout(layoutForm);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, &dialog);
    buttonBox->button(QDialogButtonBox::Ok)->setText("Créer");
    buttonBox->button(QDialogButtonBox::Cancel)->setText("Annuler");
    layoutMain->addWidget(buttonBox);

    connect(buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

    if (dialog.exec() == QDialog::Accepted) {
        std::string numero = editNumero->text().toStdString();
        TypeSalle type = static_cast<TypeSalle>(comboType->currentData().toInt());

        Salle nouvelleSalle(numero, type);

        if (!nouvelleSalle.isSalleValid()) {
            QMessageBox::warning(this, "Erreur", "Le numéro de salle doit contenir exactement 3 chiffres.");
            return;
        }

        QString fichierJson = m_dataPath + "salles.json";
        std::vector<Salle> liste = Salle::readFromJSON(fichierJson);

        liste.push_back(nouvelleSalle);
        Salle::writeToJSON(liste, fichierJson);

        QMessageBox::information(this, "Succès", "La salle a été ajoutée et sauvegardée.");
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
