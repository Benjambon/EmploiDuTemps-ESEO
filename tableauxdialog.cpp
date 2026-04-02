#include "tableauxdialog.h"

TableauxDialog::TableauxDialog(QString dataPath, QWidget *parent)
    : QWidget(parent), m_dataPath(dataPath)
{
    this->chargerDonnees();
    this->init_components();
    this->init_layout();
    this->init_slots();

    this->radioGroupe->setChecked(true);
}

void TableauxDialog::chargerDonnees()
{
    this->listeEnseignants = Enseignant::readFromJSON(m_dataPath + "enseignants.json");
    this->listeGroupes = GroupeEtudiant::readFromJSON(m_dataPath + "groupes.json");
    this->listeEcues = Ecue::readFromJSON(m_dataPath + "ecue.json");
    this->listeCreneaux = Creneau::readFromJSON(m_dataPath + "creneaux.json");
}

void TableauxDialog::init_components()
{
    this->radioGroupe = new QRadioButton("Groupe d'étudiants", this);
    this->radioEnseignant = new QRadioButton("Enseignant", this);
    this->comboSelection = new QComboBox(this);
    this->comboSelection->setMinimumSize(170, 30);

    this->tableEcues = new QTableWidget(0, 10, this);
    this->tableEcues->setHorizontalHeaderLabels({
        "ECUE", "Enseignant", "Groupe",
        "CM", "TD", "TP Info", "TP Elec",
        "Exam Salle", "Exam Info", "Exam Elec"
    });
    this->tableEcues->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    this->tableEcues->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    this->tableEcues->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
    this->tableEcues->horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeToContents);
    this->tableEcues->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void TableauxDialog::init_layout()
{
    QVBoxLayout* layoutPrincipal = new QVBoxLayout(this);
    QHBoxLayout* layoutSelection = new QHBoxLayout();

    layoutSelection->addWidget(this->radioGroupe);
    layoutSelection->addWidget(this->radioEnseignant);
    layoutSelection->addWidget(this->comboSelection);
    layoutSelection->addStretch();

    layoutPrincipal->addLayout(layoutSelection);
    layoutPrincipal->addWidget(this->tableEcues);
}

void TableauxDialog::init_slots()
{
    connect(this->radioGroupe, &QRadioButton::toggled, this, &TableauxDialog::on_radio_toggled);
    connect(this->radioEnseignant, &QRadioButton::toggled, this, &TableauxDialog::on_radio_toggled);
    connect(this->comboSelection, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &TableauxDialog::on_comboSelection_currentIndexChanged);
}

void TableauxDialog::on_radio_toggled()
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
            this->comboSelection->addItem(nom + " " + prenom, static_cast<int>(i));
        }
    }
}

void TableauxDialog::on_comboSelection_currentIndexChanged(int index)
{
    Q_UNUSED(index);
    this->majTableau();
}

void TableauxDialog::majTableau()
{
    this->tableEcues->setRowCount(0);

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

    std::vector<Ecue> ecuesFiltres;
    for (const Ecue& e : this->listeEcues) {
        if (isGroupe) {
            if (QString::fromStdString(e.getGroupeEtudiant().getNom()) == filtreNom) {
                ecuesFiltres.push_back(e);
            }
        } else {
            if (QString::fromStdString(e.getEnseignant().getNom()) == filtreNom &&
                QString::fromStdString(e.getEnseignant().getPrenom()) == filtrePrenom) {
                ecuesFiltres.push_back(e);
            }
        }
    }

    this->tableEcues->setRowCount(ecuesFiltres.size());

    for (size_t i = 0; i < ecuesFiltres.size(); ++i) {
        Ecue currentEcue = ecuesFiltres[i];
        std::map<eTypeCours, int> heuresConsommees;

        for (size_t j = 0; j < this->listeCreneaux.size(); ++j) {
            if (this->listeCreneaux[j].getEcue().getNom() == currentEcue.getNom()) {
                heuresConsommees[this->listeCreneaux[j].getTypeCours()] += 2;
            }
        }

        std::map<eTypeCours, int> totales = currentEcue.getHeuresTotales();

        this->tableEcues->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(currentEcue.getNom())));
        this->tableEcues->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(currentEcue.getEnseignant().getNom())));
        this->tableEcues->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(currentEcue.getGroupeEtudiant().getNom())));

        auto formatHeure = [&](eTypeCours type) {
            int tot = totales[type];
            if (tot == 0) return QString("-");
            int rest = tot - heuresConsommees[type];
            return QString("%1h / %2h").arg(rest).arg(tot);
        };

        this->tableEcues->setItem(i, 3, new QTableWidgetItem(formatHeure(eTypeCours::CM)));
        this->tableEcues->setItem(i, 4, new QTableWidgetItem(formatHeure(eTypeCours::TD)));
        this->tableEcues->setItem(i, 5, new QTableWidgetItem(formatHeure(eTypeCours::TP_INFO)));
        this->tableEcues->setItem(i, 6, new QTableWidgetItem(formatHeure(eTypeCours::TP_ELEC)));
        this->tableEcues->setItem(i, 7, new QTableWidgetItem(formatHeure(eTypeCours::EXAMEN_EN_SALLE)));
        this->tableEcues->setItem(i, 8, new QTableWidgetItem(formatHeure(eTypeCours::EXAMEN_INFO)));
        this->tableEcues->setItem(i, 9, new QTableWidgetItem(formatHeure(eTypeCours::EXAMEN_ELEC)));

        for(int col = 3; col <= 9; ++col) {
            if(this->tableEcues->item(i, col)) {
                this->tableEcues->item(i, col)->setTextAlignment(Qt::AlignCenter);
            }
        }
    }
}

void TableauxDialog::rafraichir()
{
    this->chargerDonnees();
    int indexSauvegarde = this->comboSelection->currentIndex();
    this->comboSelection->blockSignals(true);
    this->on_radio_toggled();
    this->comboSelection->blockSignals(false);

    if (indexSauvegarde >= 0 && indexSauvegarde < this->comboSelection->count()) {
        this->comboSelection->setCurrentIndex(indexSauvegarde);
    }
    this->majTableau();
}
