#ifndef ENSEIGNANTDIALOG_H
#define ENSEIGNANTDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QDialogButtonBox>
#include <QFormLayout>
#include <string>

class EnseignantDialog : public QDialog
{
    Q_OBJECT

private:
    QLineEdit* editNom;
    QLineEdit* editPrenom;
    QLineEdit* editMail;
    QDialogButtonBox* buttonBox;
    QFormLayout* formlayout;

    void init_components(void);
    void init_layout(void);
    void init_slots(void);

public:
    EnseignantDialog(QWidget *parent = nullptr);

    std::string getNom(void) const;
    std::string getPrenom(void) const;
    std::string getMail(void) const;
};

#endif // ENSEIGNANTDIALOG_H
