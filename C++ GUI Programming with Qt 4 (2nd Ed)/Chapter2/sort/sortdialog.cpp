#include <QGroupBox>
#include <QComboBox>
#include <QLayout>
#include <QChar>

#include "sortdialog.h"

SortDialog::SortDialog(QWidget *parent) : QDialog(parent)
{
    setupUi(this);

    secondaryGroupBox->hide();
    tertiaryGroupBox->hide();
    layout()->setSizeConstraint(QLayout::SetFixedSize);

    connect(moreButton, SIGNAL(toggled(bool)), this, SLOT(changeMoreButtonText(bool)));

    setColumnRange('A','Z');
}

void SortDialog::setColumnRange(QChar first, QChar last)
{
    primaryColumnCombo->clear();
    secondaryColumnCombo->clear();
    tertiaryColumnCombo->clear();

    secondaryColumnCombo->addItem(tr("None"));
    tertiaryColumnCombo->addItem(tr("None"));
    primaryColumnCombo->setMinimumSize(secondaryColumnCombo->sizeHint());

    QChar ch = first;
    while(ch <= last){
        primaryColumnCombo->addItem(QString(ch));
        secondaryColumnCombo->addItem(QString(ch));
        tertiaryColumnCombo->addItem(QString(ch));
        ch = ch.unicode() + 1;
    }
}

void SortDialog::changeMoreButtonText(bool toggled)
{
	if(toggled)
		moreButton->setText(tr("&Advanced <<<"));
	else
		moreButton->setText(tr("&Advanced >>>"));
}