#ifndef GTCD_H
#define GTCD_H

#include <QDialog>

class QLabel;
class QLineEdit;
class QDialogButtonBox;

class GTCD : public QDialog
{
    Q_OBJECT;

public:
    GTCD(QWidget *parent = 0);

private slots:
    void enableOkButton(void);

private:
    QLabel *label;
    QLineEdit *lineEdit;
    QDialogButtonBox *buttonBox;
};

#endif
