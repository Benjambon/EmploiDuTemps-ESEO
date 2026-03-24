#ifndef SUPPRIMERECUEDIALOG_H
#define SUPPRIMERECUEDIALOG_H

#include <QDialog>
#include <QComboBox>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <vector>
#include "ecue.h"

class SupprimerEcueDialog : public QDialog
{
    Q_OBJECT

private:
    QComboBox* comboEcues;
    QDialogButtonBox* buttonBox;
    QVBoxLayout* layout;

    void init_components(const std::vector<Ecue>& listeEcues);
    void init_layout(void);
    void init_slots(void);

public:
    SupprimerEcueDialog(const std::vector<Ecue>& listeEcues, QWidget *parent = nullptr);
    int getSelectedIndex(void) const;
};

#endif // SUPPRIMERECUEDIALOG_H
