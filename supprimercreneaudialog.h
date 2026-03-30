#ifndef SUPPRIMERCRENEAUDIALOG_H
#define SUPPRIMERCRENEAUDIALOG_H

#include <QDialog>
#include <QComboBox>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <vector>
#include "creneau.h"
#include <QPushButton>

class SupprimerCreneauDialog : public QDialog
{
    Q_OBJECT

private:
    QComboBox* comboCreneaux;
    QDialogButtonBox* buttonBox;
    QVBoxLayout* layout;

    void init_components(const std::vector<Creneau>& listeCreneaux);
    void init_layout(void);
    void init_slots(void);

public:
    SupprimerCreneauDialog(const std::vector<Creneau>& listeCreneaux, QWidget *parent = nullptr);
    int getSelectedIndex(void) const;
};

#endif // SUPPRIMERCRENEAUDIALOG_H
