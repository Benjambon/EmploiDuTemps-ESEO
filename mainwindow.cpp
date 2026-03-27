#include "mainwindow.h"


MainWindow::MainWindow(QString dataPath, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_dataPath(dataPath)
{
    ui->setupUi(this);
    this->init_style();
    this->init_layout();
    ui->tabWidget->setTabText(0, "Emploi du temps");
    QVBoxLayout* tabLayout = new QVBoxLayout(ui->tab);
    EmploiDuTempsDialog* edtDialog = new EmploiDuTempsDialog(m_dataPath, this);
    tabLayout->addWidget(edtDialog);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init_style(void)
{
    // Le préfixe ":/" indique que l'on cherche dans le fichier de ressources (.qrc)
QFile file(":/styles/styles.qss");
    if (file.open(QFile::ReadOnly | QFile::Text))
    {
        QString styleSheet = QTextStream(&file).readAll();
        // qApp applique le style à l'application entière, pas seulement à MainWindow
        qApp->setStyleSheet(styleSheet);
        file.close();
        qDebug() << "Style QSS charge avec succes.";
    }
    else
    {
        qDebug() << "Erreur : Impossible de charger le fichier QSS.";
    }
}

void MainWindow::init_layout(void)
{
    // 1. Création du système d'onglets
    QTabWidget *systemeOnglets = new QTabWidget(this);

    // ==========================================
    // ONGLET 1 : GESTION DES DONNÉES
    // ==========================================
    QWidget *ongletGestion = new QWidget();
    QVBoxLayout *layoutPrincipal = new QVBoxLayout(ongletGestion);
    layoutPrincipal->setSpacing(20);
    layoutPrincipal->setContentsMargins(30, 30, 30, 30);

    // Simplification des textes
    QString txtAjouter = "Ajouter";
    QString txtSupprimer = "Supprimer";
    QString txtAfficher = "Afficher";

    ui->btnAjouterEnseignant->setText(txtAjouter);
    ui->btnSupprimerEnseignant->setText(txtSupprimer);
    ui->btnAfficherEnseignants->setText(txtAfficher);

    ui->btnAjouterGroupe->setText(txtAjouter);
    ui->btnSupprimerGroupe->setText(txtSupprimer);
    ui->btnAfficherGroupes->setText(txtAfficher);

    ui->btnAjouterSalle->setText(txtAjouter);
    ui->btnSupprimerSalle->setText(txtSupprimer);
    ui->btnAfficherSalles->setText(txtAfficher);

    ui->btnAjouterEcue->setText(txtAjouter);
    ui->btnSupprimerEcue->setText(txtSupprimer);
    ui->btnAfficherEcues->setText(txtAfficher);

    // Ajout des icônes (vos fichiers SVG avec fond blanc)
    QIcon iconAjouter(":/icons/plus.svg");
    QIcon iconSupprimer(":/icons/minus.svg");
    QIcon iconAfficher(":/icons/eye.svg");

    ui->btnAjouterEnseignant->setIcon(iconAjouter);
    ui->btnSupprimerEnseignant->setIcon(iconSupprimer);
    ui->btnAfficherEnseignants->setIcon(iconAfficher);

    ui->btnAjouterGroupe->setIcon(iconAjouter);
    ui->btnSupprimerGroupe->setIcon(iconSupprimer);
    ui->btnAfficherGroupes->setIcon(iconAfficher);

    ui->btnAjouterSalle->setIcon(iconAjouter);
    ui->btnSupprimerSalle->setIcon(iconSupprimer);
    ui->btnAfficherSalles->setIcon(iconAfficher);

    ui->btnAjouterEcue->setIcon(iconAjouter);
    ui->btnSupprimerEcue->setIcon(iconSupprimer);
    ui->btnAfficherEcues->setIcon(iconAfficher);

    // Création des groupes (Ajouter, Supprimer, Afficher)
    QGroupBox *groupeEnseignants = new QGroupBox("Enseignants");
    QHBoxLayout *layoutEns = new QHBoxLayout;
    layoutEns->addWidget(ui->btnAjouterEnseignant);
    layoutEns->addWidget(ui->btnSupprimerEnseignant);
    layoutEns->addWidget(ui->btnAfficherEnseignants);
    groupeEnseignants->setLayout(layoutEns);
    layoutPrincipal->addWidget(groupeEnseignants);

    QGroupBox *groupeEtudiants = new QGroupBox("Groupes d'Étudiants");
    QHBoxLayout *layoutGrp = new QHBoxLayout;
    layoutGrp->addWidget(ui->btnAjouterGroupe);
    layoutGrp->addWidget(ui->btnSupprimerGroupe);
    layoutGrp->addWidget(ui->btnAfficherGroupes);
    groupeEtudiants->setLayout(layoutGrp);
    layoutPrincipal->addWidget(groupeEtudiants);

    QGroupBox *groupeSalles = new QGroupBox("Salles");
    QHBoxLayout *layoutSal = new QHBoxLayout;
    layoutSal->addWidget(ui->btnAjouterSalle);
    layoutSal->addWidget(ui->btnSupprimerSalle);
    layoutSal->addWidget(ui->btnAfficherSalles);
    groupeSalles->setLayout(layoutSal);
    layoutPrincipal->addWidget(groupeSalles);

    QGroupBox *groupeEcue = new QGroupBox("ECUE");
    QHBoxLayout *layoutEcu = new QHBoxLayout;
    layoutEcu->addWidget(ui->btnAjouterEcue);
    layoutEcu->addWidget(ui->btnSupprimerEcue);
    layoutEcu->addWidget(ui->btnAfficherEcues);
    groupeEcue->setLayout(layoutEcu);
    layoutPrincipal->addWidget(groupeEcue);

    layoutPrincipal->addStretch();
    systemeOnglets->addTab(ongletGestion, "Gestion des données");

    // ==========================================
    // ONGLET 2 : EMPLOI DU TEMPS
    // ==========================================
    QWidget *ongletEmploi = new QWidget();
    QVBoxLayout *layoutEmploi = new QVBoxLayout(ongletEmploi);

    // Intégration de votre boîte de dialogue
    EmploiDuTempsDialog *interfaceEmploi = new EmploiDuTempsDialog(m_dataPath, ongletEmploi);
    interfaceEmploi->setWindowFlags(Qt::Widget);
    layoutEmploi->addWidget(interfaceEmploi);

    systemeOnglets->addTab(ongletEmploi, "Emploi du temps");

    // ==========================================
    // APPLICATION À LA FENÊTRE
    // ==========================================
    this->setCentralWidget(systemeOnglets);
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

    QString texteAffichage = "<h3>Liste des ECUE</h3>";
    texteAffichage += "<table border='1' cellspacing='0' cellpadding='5' style='border-collapse: collapse;'>";
    texteAffichage += "<tr bgcolor='#f0f0f0'>";
    texteAffichage += "<th>Nom</th><th>Groupe</th><th>Enseignant</th><th>Détail des heures (Rest. / Tot.)</th>";
    texteAffichage += "</tr>";

    for (size_t i = 0; i < liste.size(); ++i) {
        QString nom = QString::fromStdString(liste[i].getNom());
        QString groupe = QString::fromStdString(liste[i].getGroupeEtudiant().getNom());
        QString prof = QString::fromStdString(liste[i].getEnseignant().getNom());

        // Création de la chaîne de détail des heures
        QString heuresStr = "";
        std::map<eTypeCours, int> totales = liste[i].getHeuresTotales();
        std::map<eTypeCours, int> restantes = liste[i].getHeuresRestantes();

        for (auto const& pair : totales) {
            QString typeNom = Ecue::typeCoursToString(pair.first);
            QString total = QString::number(pair.second);
            QString restant = QString::number(restantes[pair.first]);

            heuresStr += "<b>" + typeNom + "</b> : " + restant + "h / " + total + "h<br>";
        }

        texteAffichage += "<tr>";
        texteAffichage += "<td>" + nom + "</td>";
        texteAffichage += "<td>" + groupe + "</td>";
        texteAffichage += "<td>" + prof + "</td>";
        texteAffichage += "<td>" + heuresStr + "</td>";
        texteAffichage += "</tr>";
    }

    texteAffichage += "</table>";

    QMessageBox msgBox(this);
    msgBox.setWindowTitle("Liste des ECUE");
    msgBox.setText(texteAffichage);
    msgBox.setTextFormat(Qt::RichText);
    msgBox.exec();
}

