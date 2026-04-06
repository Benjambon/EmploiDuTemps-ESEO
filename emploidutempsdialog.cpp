#include "emploidutempsdialog.h"
#include <QHeaderView>
#include <QBrush>
#include <QColor>

EmploiDuTempsDialog::EmploiDuTempsDialog(QString dataPath, QWidget *parent)
    : QWidget(parent), m_dataPath(dataPath)
{
    QDate dateDuJour = QDate::currentDate();
    int jourDeLaSemaine = dateDuJour.dayOfWeek();

    this->dateLundiCourant = dateDuJour.addDays(1 - jourDeLaSemaine);

    this->chargerDonnees();
    this->init_components();
    this->init_layout();
    this->init_slots();

    this->majAffichageSemaine();
    this->radioGroupe->setChecked(true);
}

void EmploiDuTempsDialog::chargerDonnees()
{
    this->listeEnseignants = Enseignant::readFromJSON(m_dataPath + "enseignants.json");
    this->listeGroupes = GroupeEtudiant::readFromJSON(m_dataPath + "groupes.json");
    this->listeCreneaux = Creneau::readFromJSON(m_dataPath + "creneaux.json");
}



void EmploiDuTempsDialog::init_components()
{
    this->radioGroupe = new QRadioButton("Groupe d'étudiants", this);
    this->radioEnseignant = new QRadioButton("Enseignant", this);
    this->comboSelection = new QComboBox(this);
    this->comboSelection->setMinimumSize(170, 30);

    this->btnSemainePrecedente = new QPushButton("< Précédent", this);
    this->labelSemaine = new QLabel("Semaine 1", this);
    this->labelSemaine->setAlignment(Qt::AlignCenter);
    this->btnSemaineSuivante = new QPushButton("Suivant >", this);

    this->tableCalendrier = new QTableWidget(5, 5, this);
    this->tableCalendrier->setHorizontalHeaderLabels({"Lundi", "Mardi", "Mercredi", "Jeudi", "Vendredi"});
    this->tableCalendrier->setVerticalHeaderLabels({"8h-10h", "10h-12h", "", "14h-16h", "16h-18h"});

    this->tableCalendrier->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    this->tableCalendrier->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    this->tableCalendrier->verticalHeader()->setSectionResizeMode(2, QHeaderView::Fixed);
    this->tableCalendrier->setRowHeight(2, 30);

    this->tableCalendrier->setSpan(2, 0, 1, 5);

    QTableWidgetItem* itemPause = new QTableWidgetItem("Pause Déjeuner");
    itemPause->setTextAlignment(Qt::AlignCenter);
    itemPause->setBackground(QBrush(QColor(230, 230, 230)));

    QFont font = itemPause->font();
    if (font.pointSize() <= 0) {
        font.setPointSize(10);
    }

    font.setItalic(true);
    itemPause->setFont(font);

    this->tableCalendrier->setItem(2, 0, itemPause);
    this->tableCalendrier->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void EmploiDuTempsDialog::init_layout()
{
    this->layoutPrincipal = new QVBoxLayout(this);

    this->layoutSelection = new QHBoxLayout();
    this->layoutSelection->addWidget(this->radioGroupe);
    this->layoutSelection->addWidget(this->radioEnseignant);
    this->layoutSelection->addWidget(this->comboSelection);
    this->layoutSelection->addStretch();

    this->layoutSemaine = new QHBoxLayout();
    this->layoutSemaine->addWidget(this->btnSemainePrecedente);
    this->layoutSemaine->addWidget(this->labelSemaine);
    this->layoutSemaine->addWidget(this->btnSemaineSuivante);

    this->layoutPrincipal->addLayout(this->layoutSelection);
    this->layoutPrincipal->addLayout(this->layoutSemaine);
    this->layoutPrincipal->addWidget(this->tableCalendrier);
}

void EmploiDuTempsDialog::init_slots()
{
    connect(this->btnSemainePrecedente, &QPushButton::clicked, this, &EmploiDuTempsDialog::on_btnSemainePrecedente_clicked);
    connect(this->btnSemaineSuivante, &QPushButton::clicked, this, &EmploiDuTempsDialog::on_btnSemaineSuivante_clicked);
    connect(this->radioGroupe, &QRadioButton::toggled, this, &EmploiDuTempsDialog::on_radio_toggled);
    connect(this->radioEnseignant, &QRadioButton::toggled, this, &EmploiDuTempsDialog::on_radio_toggled);
    connect(this->comboSelection, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &EmploiDuTempsDialog::on_comboSelection_currentIndexChanged);
}


void EmploiDuTempsDialog::majAffichageSemaine()
{
    int weekNum = this->dateLundiCourant.weekNumber();
    this->labelSemaine->setText("Semaine " + QString::number(weekNum));

    QStringList headers;
    QString nomsJours[] = {"Lundi", "Mardi", "Mercredi", "Jeudi", "Vendredi"};

    for (int i = 0; i < 5; ++i) {
        QDate dateDuJour = this->dateLundiCourant.addDays(i);
        QString texteColonne = nomsJours[i] + "\n" + dateDuJour.toString("dd/MM");
        headers << texteColonne;
    }
    this->tableCalendrier->setHorizontalHeaderLabels(headers);

    this->chargerDonnees();
    this->majEmploiDuTemps();
}

void EmploiDuTempsDialog::on_radio_toggled()
{
    this->comboSelection->clear();

    if (this->radioGroupe->isChecked()) {
        for (size_t i = 0; i < this->listeGroupes.size(); ++i) {
            this->comboSelection->addItem(QString::fromStdString(this->listeGroupes[i].getNom()), static_cast<int>(i));
        }
    } else if (this->radioEnseignant->isChecked()) {
        for (size_t i = 0; i < this->listeEnseignants.size(); ++i) {
            QString nom = QString::fromStdString(this->listeEnseignants[i].getNom());
            QString prenom = QString::fromStdString(this->listeEnseignants[i].getPrenom());
            QString texteAffichage = nom + " " + prenom;

            this->comboSelection->addItem(texteAffichage, static_cast<int>(i));
        }
    }
}

void EmploiDuTempsDialog::on_comboSelection_currentIndexChanged(int index)
{
    Q_UNUSED(index);
    this->chargerDonnees();
    this->majEmploiDuTemps();
}

void EmploiDuTempsDialog::on_btnSemainePrecedente_clicked()
{
    this->dateLundiCourant = this->dateLundiCourant.addDays(-7);
    this->majAffichageSemaine();
}

void EmploiDuTempsDialog::on_btnSemaineSuivante_clicked()
{
    this->dateLundiCourant = this->dateLundiCourant.addDays(7);
    this->majAffichageSemaine();
}

void EmploiDuTempsDialog::majEmploiDuTemps()
{

    for (int row = 0; row < 5; ++row) {
        if (row == 2) continue;
        for (int col = 0; col < 5; ++col) {
            this->tableCalendrier->setItem(row, col, new QTableWidgetItem(""));
        }
    }

    int currentIndex = this->comboSelection->currentIndex();
    if (currentIndex < 0) return;

    bool isGroupe = this->radioGroupe->isChecked();
    QString filtreNom;
    QString filtrePrenom;

    if (isGroupe && currentIndex < static_cast<int>(this->listeGroupes.size())) {
        filtreNom = QString::fromStdString(this->listeGroupes[currentIndex].getNom());
    } else if (!isGroupe && currentIndex < static_cast<int>(this->listeEnseignants.size())) {
        filtreNom = QString::fromStdString(this->listeEnseignants[currentIndex].getNom());
        filtrePrenom = QString::fromStdString(this->listeEnseignants[currentIndex].getPrenom());
    }

    for (const Creneau& c : this->listeCreneaux) {
        if (isGroupe) {
            if (QString::fromStdString(c.getEcue().getGroupeEtudiant().getNom()) != filtreNom) continue;
        } else {
            if (QString::fromStdString(c.getEcue().getEnseignant().getNom()) != filtreNom ||
                QString::fromStdString(c.getEcue().getEnseignant().getPrenom()) != filtrePrenom) continue;
        }

        int joursDifference = this->dateLundiCourant.daysTo(c.getDate());
        if (joursDifference < 0 || joursDifference > 4) continue;

        int row = -1;
        switch(c.getHoraire()) {
        case eHoraire::MATIN1: row = 0; break;
        case eHoraire::MATIN2: row = 1; break;
        case eHoraire::APRESMIDI1: row = 3; break;
        case eHoraire::APRESMIDI2: row = 4; break;
        default: break;
        }

        if (row != -1) {
            QString texte = QString::fromStdString(c.getEcue().getNom()) + "\n" +
                            Ecue::typeCoursToString(c.getTypeCours()) + " - Salle " +
                            QString::fromStdString(c.getSalle().getNumero());

            if (isGroupe) {
                texte += "\n" + QString::fromStdString(c.getEcue().getEnseignant().getNom());
            } else {
                texte += "\nGroupe " + QString::fromStdString(c.getEcue().getGroupeEtudiant().getNom());
            }

            QTableWidgetItem* item = new QTableWidgetItem(texte);
            item->setTextAlignment(Qt::AlignCenter);

            item->setBackground(QBrush(QColor(235, 245, 251)));

            this->tableCalendrier->setItem(row, joursDifference, item);
        }
    }
}
void EmploiDuTempsDialog::rafraichir()
{
    this->chargerDonnees();

    int indexSauvegarde = this->comboSelection->currentIndex();

    this->comboSelection->blockSignals(true);
    this->on_radio_toggled();
    this->comboSelection->blockSignals(false);

    if (indexSauvegarde >= 0 && indexSauvegarde < this->comboSelection->count()) {
        this->comboSelection->setCurrentIndex(indexSauvegarde);
    }

    this->majEmploiDuTemps();
}
