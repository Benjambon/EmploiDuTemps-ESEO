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

    // Ajout dynamique des boutons Créneau
    QPushButton *btnAjouterCreneau = new QPushButton(txtAjouter, this);
    QPushButton *btnSupprimerCreneau = new QPushButton(txtSupprimer, this);

    btnAjouterCreneau->setIcon(iconAjouter);
    btnSupprimerCreneau->setIcon(iconSupprimer);

    QGroupBox *groupeCreneau = new QGroupBox("Créneaux");
    QHBoxLayout *layoutCreneau = new QHBoxLayout;
    layoutCreneau->addWidget(btnAjouterCreneau);
    layoutCreneau->addWidget(btnSupprimerCreneau);
    groupeCreneau->setLayout(layoutCreneau);
    layoutPrincipal->addWidget(groupeCreneau);

    // Connexion manuelle des signaux
    connect(btnAjouterCreneau, &QPushButton::clicked, this, &MainWindow::on_btnAjouterCreneau_clicked);
    connect(btnSupprimerCreneau, &QPushButton::clicked, this, &MainWindow::on_btnSupprimerCreneau_clicked);

    layoutPrincipal->addStretch();
    systemeOnglets->addTab(ongletGestion, "Gestion des données");

    // ==========================================
    // ONGLET 2 : EMPLOI DU TEMPS
    // ==========================================
    QWidget *ongletEmploi = new QWidget();
    QVBoxLayout *layoutEmploi = new QVBoxLayout(ongletEmploi);

    // Utilisation de l'attribut de classe au lieu d'une variable locale
    m_interfaceEmploi = new EmploiDuTempsDialog(m_dataPath, ongletEmploi);
    m_interfaceEmploi->setWindowFlags(Qt::Widget);
    layoutEmploi->addWidget(m_interfaceEmploi);

    systemeOnglets->addTab(ongletEmploi, "Emploi du temps");

    connect(systemeOnglets, &QTabWidget::currentChanged, this, [this](int index) {
        // L'index 1 correspond au deuxième onglet ("Emploi du temps")
        if (index == 1 && m_interfaceEmploi) {
            m_interfaceEmploi->rafraichir();
        }
    });

    // ==========================================
    // ONGLET 3 : TABLEAUX
    // ==========================================
    QWidget *ongletTableaux = new QWidget();
    QVBoxLayout *layoutTableaux = new QVBoxLayout(ongletTableaux);

    m_interfaceTableaux = new TableauxDialog(m_dataPath, ongletTableaux);
    layoutTableaux->addWidget(m_interfaceTableaux);

    systemeOnglets->addTab(ongletTableaux, "Tableaux ECUE");

    connect(systemeOnglets, &QTabWidget::currentChanged, this, [this](int index) {
        if (index == 1 && m_interfaceEmploi) {
            m_interfaceEmploi->rafraichir();
        }
        if (index == 2 && m_interfaceTableaux) {
            m_interfaceTableaux->rafraichir();
        }
    });

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
    QString cheminEcue = m_dataPath + "ecue.json";
    QString cheminCreneaux = m_dataPath + "creneaux.json";

    std::vector<Ecue> listeE = Ecue::readFromJSON(cheminEcue);
    std::vector<Creneau> listeC = Creneau::readFromJSON(cheminCreneaux);

    if (listeE.empty()) {
        QMessageBox::information(this, "Liste des ECUEs", "Aucun ECUE n'est enregistré.");
        return;
    }

    QDialog dialog(this);
    dialog.setWindowTitle("Détails des ECUEs");
    dialog.resize(950, 400);

    QVBoxLayout layout(&dialog);
    QTableWidget table(listeE.size(), 10, &dialog);

    table.setHorizontalHeaderLabels({
        "Nom", "Enseignant", "Groupe",
        "CM", "TD", "TP Info", "TP Elec",
        "Exam Salle", "Exam Info", "Exam Elec"
    });

    for (size_t i = 0; i < listeE.size(); ++i) {
        Ecue currentEcue = listeE[i];
        std::map<eTypeCours, int> heuresConsommees;

        for (size_t j = 0; j < listeC.size(); ++j) {
            if (listeC[j].getEcue().getNom() == currentEcue.getNom()) {
                heuresConsommees[listeC[j].getTypeCours()] += 2;
            }
        }

        std::map<eTypeCours, int> totales = currentEcue.getHeuresTotales();

        table.setItem(i, 0, new QTableWidgetItem(QString::fromStdString(currentEcue.getNom())));
        table.setItem(i, 1, new QTableWidgetItem(QString::fromStdString(currentEcue.getEnseignant().getNom())));
        table.setItem(i, 2, new QTableWidgetItem(QString::fromStdString(currentEcue.getGroupeEtudiant().getNom())));

        // Fonction lambda pour formater l'affichage des heures (Restantes / Totales)
        auto formatHeure = [&](eTypeCours type) {
            int tot = totales[type];
            if (tot == 0) return QString("-");
            int rest = tot - heuresConsommees[type];
            return QString("%1h / %2h").arg(rest).arg(tot);
        };

        table.setItem(i, 3, new QTableWidgetItem(formatHeure(eTypeCours::CM)));
        table.setItem(i, 4, new QTableWidgetItem(formatHeure(eTypeCours::TD)));
        table.setItem(i, 5, new QTableWidgetItem(formatHeure(eTypeCours::TP_INFO)));
        table.setItem(i, 6, new QTableWidgetItem(formatHeure(eTypeCours::TP_ELEC)));
        table.setItem(i, 7, new QTableWidgetItem(formatHeure(eTypeCours::EXAMEN_EN_SALLE)));
        table.setItem(i, 8, new QTableWidgetItem(formatHeure(eTypeCours::EXAMEN_INFO)));
        table.setItem(i, 9, new QTableWidgetItem(formatHeure(eTypeCours::EXAMEN_ELEC)));

        // Centrage du texte pour les colonnes contenant les heures
        for(int col = 3; col <= 9; ++col) {
            if(table.item(i, col)) {
                table.item(i, col)->setTextAlignment(Qt::AlignCenter);
            }
        }
    }

    // Ajustement de la taille des colonnes pour une meilleure lisibilité
    table.horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table.horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    table.horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
    table.horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeToContents);
    table.setEditTriggers(QAbstractItemView::NoEditTriggers); // Rend le tableau en lecture seule

    layout.addWidget(&table);

    QPushButton btnFermer("Fermer", &dialog);
    layout.addWidget(&btnFermer);
    connect(&btnFermer, &QPushButton::clicked, &dialog, &QDialog::accept);

    dialog.exec();
}

// --------------------------------------------------------
// Gestion des Créneaux
// --------------------------------------------------------

void MainWindow::on_btnAjouterCreneau_clicked()
{
    QString fichierJson = m_dataPath + "creneaux.json";

    // Chargement de toutes les données nécessaires
    std::vector<Ecue> listeE = Ecue::readFromJSON(m_dataPath + "ecue.json");
    std::vector<Salle> listeS = Salle::readFromJSON(m_dataPath + "salles.json");
    std::vector<Creneau> listeC = Creneau::readFromJSON(fichierJson);

    if (listeE.empty() || listeS.empty()) {
        QMessageBox::warning(this, "Erreur", "Il faut au moins un ECUE et une salle pour créer un créneau.");
        return;
    }

    // Appel au contrôleur avec la liste des créneaux (listeC) pour la vérification des conflits
    Creneau* nouveauCreneau = Controleur_creneau::creationCreneau(listeE, listeS, listeC);

    if (nouveauCreneau != nullptr) {
        // On ajoute le nouveau créneau à la liste existante et on sauvegarde
        listeC.push_back(*nouveauCreneau);
        Creneau::writeToJSON(listeC, fichierJson);

        QMessageBox::information(this, "Succès", "Le créneau a été ajouté et sauvegardé.");
        delete nouveauCreneau;
    }
}

void MainWindow::on_btnSupprimerCreneau_clicked()
{
    QString fichierJson = m_dataPath + "creneaux.json";
    std::vector<Creneau> liste = Creneau::readFromJSON(fichierJson);

    if (liste.empty()) {
        QMessageBox::information(this, "Information", "Il n'y a aucun créneau à supprimer.");
        return;
    }

    int index = Controleur_creneau::supprimerCreneau(liste);

    if (index >= 0 && static_cast<size_t>(index) < liste.size()) {
        liste.erase(liste.begin() + index);
        Creneau::writeToJSON(liste, fichierJson);
        QMessageBox::information(this, "Succès", "Le créneau a été supprimé avec succès.");
    }
}



