#include "mainwindow.h"
#include "ui_mainwindow.h"

// Inclusions nécessaires pour le formulaire dynamique
#include <QDialog>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QMessageBox>
#include "enseignant.h"
#include <vector>

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

// Implémentation du clic sur le bouton
void MainWindow::on_btnAjouterEnseignant_clicked()
{
    // Création de la fenêtre de dialogue
    QDialog dialog(this);
    dialog.setWindowTitle("Ajouter un enseignant");

    // Création des mises en page (layouts)
    QVBoxLayout *layoutMain = new QVBoxLayout(&dialog);
    QFormLayout *layoutForm = new QFormLayout();

    // Création des champs de saisie
    QLineEdit *editNom = new QLineEdit(&dialog);
    QLineEdit *editPrenom = new QLineEdit(&dialog);
    QLineEdit *editMail = new QLineEdit(&dialog);

    // Ajout des champs dans le formulaire avec leurs étiquettes
    layoutForm->addRow("Nom :", editNom);
    layoutForm->addRow("Prénom :", editPrenom);
    layoutForm->addRow("Mail :", editMail);

    // Ajout du formulaire à la mise en page principale
    layoutMain->addLayout(layoutForm);

    // Création des boutons Créer et Annuler
    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, &dialog);
    buttonBox->button(QDialogButtonBox::Ok)->setText("Créer");
    buttonBox->button(QDialogButtonBox::Cancel)->setText("Annuler");
    layoutMain->addWidget(buttonBox);

    // Connexion des boutons pour fermer la fenêtre
    connect(buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

    // Affichage de la fenêtre et attente de la validation
    if (dialog.exec() == QDialog::Accepted) {
        // Le bouton "Créer" a été cliqué.
        // Les données peuvent être récupérées ici plus tard :
        // QString nom = editNom->text();
        // QString prenom = editPrenom->text();
        // QString mail = editMail->text();
    }}
void MainWindow::on_btnAfficherEnseignants_clicked()
    {
        QString fichierJson = m_dataPath + "enseignants.json";

        // Lecture du fichier JSON
        std::vector<Enseignant> listeEnseignants = Enseignant::readFromJSON(fichierJson);

        // Vérification si le fichier est vide ou n'existe pas
        if (listeEnseignants.empty()) {
            QMessageBox::information(this, "Liste des enseignants", "Aucun enseignant n'est enregistré.");
            return;
        }

        // Construction du texte à afficher
        QString texteAffichage = "Voici la liste des enseignants :\n\n";
        for (size_t i = 0; i < listeEnseignants.size(); ++i) {
            texteAffichage += QString::fromStdString(listeEnseignants[i].toString()) + "\n";
        }

        // Affichage de la liste dans une fenêtre
        QMessageBox::information(this, "Liste des enseignants", texteAffichage);
    }

