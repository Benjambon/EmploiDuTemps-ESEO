#ifndef SUPPRIMERENSEIGNANTDIALOG_H
#define SUPPRIMERENSEIGNANTDIALOG_H

#include <QDialog>
#include <QComboBox>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <vector>
#include "enseignant.h"

class SupprimerEnseignantDialog : public QDialog
{
    Q_OBJECT

private:
    QComboBox* comboEnseignants;
    QDialogButtonBox* buttonBox;
    QVBoxLayout* layout;
    void init_components(const std::vector<Enseignant>& listeEnseignants);
    void init_layout(void);
    void init_slots(void);

public:
    SupprimerEnseignantDialog(const std::vector<Enseignant>& listeEnseignants, QWidget *parent = nullptr);
    int getSelectedIndex(void) const;
};

#endif // SUPPRIMERENSEIGNANTDIALOG_H
