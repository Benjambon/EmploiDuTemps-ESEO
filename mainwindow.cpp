#include "mainwindow.h"
#include "ui_mainwindow.h"

// Inclusions nécessaires pour le formulaire dynamique
#include <QDialog>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QDialogButtonBox>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
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
    }
}
