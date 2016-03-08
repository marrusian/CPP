#include <QStatusBar>
#include <QMessageBox>
#include <QFileDialog>
#include <QCloseEvent>
#include <QSettings>
#include <QCheckBox>

#include "FindDialog/finddialog.h"
#include "GoToCellDialog/gotocelldialog.h"
#include "Sort/sortdialog.h"

#include "mainwindow.h"

QStringList MainWindow::recentFiles;

MainWindow::MainWindow(void)
{
	setupUi(this);

	setAttribute(Qt::WA_DeleteOnClose);

//    spreadsheet = new Spreadsheet;
//    setCentralWidget(spreadsheet);

    createActions();
    createMenus();
    createContextMenu();
    createStatusBar();

    readSettings();

    findDialog = 0;

    setCurrentFile("");
}

void MainWindow::createActions(void)
{
	// File Menu
	connect(newAction, SIGNAL(triggered()), this, SLOT(newFile()));
	connect(openAction, SIGNAL(triggered()), this, SLOT(open()));
	connect(saveAction, SIGNAL(triggered()), this, SLOT(save()));
	connect(saveAsAction, SIGNAL(triggered()), this, SLOT(saveAs()));
	for(int i = 0; i < MaxRecentFiles; ++i){
        recentFileActions[i] = new QAction(this);
        recentFileActions[i]->setVisible(false);
        connect(recentFileActions[i], SIGNAL(triggered()),
                this, SLOT(openRecentFile()));
    }
    connect(closeAction, SIGNAL(triggered()), this, SLOT(close()));
    connect(exitAction, SIGNAL(triggered()), qApp, SLOT(closeAllWindows()));

    // Edit Menu
//    connect(cutAction, SIGNAL(triggered()), spreadsheet, SLOT(cut()));
//    connect(copyAction, SIGNAL(triggered()), spreadsheet, SLOT(copy()));
//    connect(pasteAction, SIGNAL(triggered()), spredsheet, SLOT(paste()));
//    connect(deleteAction, SIGNAL(triggered()), spreadsheet, SLOT(del()));
//    connect(selectRowAction, SIGNAL(triggered()), spreadsheet, SLOT(selectCurrentRow()));
//    connect(selectColumnAction, SIGNAL(triggered()), spreadsheet, SLOT(selectCurrentColumn()));
//    connect(selectAllAction, SIGNAL(triggered()), spreadsheet, SLOT(selectAll()));
    connect(findAction, SIGNAL(triggered()), this, SLOT(find()));
    connect(goToCellAction, SIGNAL(triggered()), this, SLOT(goToCell()));

    // Tools Menu
//    connect(recalculateAction, SIGNAL(triggered()), spreadsheet, SLOT(recalculate()));
    connect(sortAction, SIGNAL(triggered()), this, SLOT(sort()));

    // Options Menu
//    connect(showGridAction, SIGNAL(toggled(bool)), spreadsheet, SLOT(setShowGrid(bool)));
//    connect(autoRecalcAction, SIGNAL(toggled(bool)), spreadsheet, SLOT(setAutoRecalculate(bool)));

    // About Menu
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(about()));
    connect(aboutQtAction, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
}

void MainWindow::createMenus(void)
{
	separatorAction = fileMenu->addSeparator();

    for(int i = 0; i < MaxRecentFiles; ++i)
        fileMenu->addAction(recentFileActions[i]);
}

void MainWindow::createContextMenu(void)
{
//    spreadsheet->addAction(cutAction);
//    spreadsheet->addAction(copyAction);
//    spreadsheet->addAction(pasteAction);
//    spreadsheet->setContextMenuPolicy(Qt::ActionsContextMenu);
}

void MainWindow::createStatusBar(void)
{
	locationLabel = new QLabel(" W999 ");
	locationLabel->setAlignment(Qt::AlignHCenter);
	locationLabel->setMinimumSize(locationLabel->sizeHint());

	formulaLabel = new QLabel;
	formulaLabel->setIndent(3);

	statusBar()->addWidget(locationLabel);
	statusBar()->addWidget(formulaLabel, 1);

//	connect(spreadsheet, SIGNAL(currentCellChanged(int, int, int, int)),
//            this, SLOT(updateStatusBar()));
//    connect(spreadsheet, SIGNAL(modified()), this, SLOT(spreadsheetModified()));
    updateStatusBar();
}

void MainWindow::updateStatusBar(void)
{
//    locationLabel->setText(spreadsheet->currentLocation());
//    formulaLabel->setText(spreadsheet->currentFormula());
}

void MainWindow::spreadsheetModified(void)
{
    setWindowModified(true);
    updateStatusBar();
}

void MainWindow::newFile(void)
{
	MainWindow *win = new MainWindow;
	win->show();
}

bool MainWindow::okToContinue(void)
{
	if(isWindowModified()) {
		int ret = QMessageBox::warning(this, tr("Spreadsheet"),
									   tr("The document has been modified\n"
									   	  "Do you want to save your changes?"),
									   QMessageBox::Yes | QMessageBox::No
									   | QMessageBox::Cancel);

		switch(ret) {
			case QMessageBox::Yes    : return save();
			case QMessageBox::Cancel : return false;
			default                  : return true;
		}
	}

    return true;
}

void MainWindow::open(void)
{
	if(okToContinue()) {
		QString fileName = QFileDialog::getOpenFileName(this,
									tr("Open Spreadsheet"), ".",
									tr("Spreadsheet files (*.sp)"));
		if(!fileName.isEmpty())
			loadFile(fileName);
	}
}

bool MainWindow::loadFile(const QString& fileName)
{
//    if(!spreadsheet->readFile(fileName)) {
//        statusBar()->showMessage(tr("Loading canceled"), 2000);
//        return false;
//    }

    setCurrentFile(fileName);
    statusBar()->showMessage(tr("File loaded"), 2000);
    return true;
}

bool MainWindow::save(void)
{
	return curFile.isEmpty()? saveAs() : save();
}

bool MainWindow::saveFile(const QString &fileName)
{
//    if(!spreadsheet->writeFile(filename)) {
//        statusBar()->showMessage(tr("Saving canceled"), 2000);
//        return false;
//    }

    setCurrentFile(fileName);
    statusBar()->showMessage(tr("File saved"), 2000);
    return true;
}

bool MainWindow::saveAs(void)
{
    QString fileName = QFileDialog::getSaveFileName(this,
                              tr("Save spreadsheet"), ".",
                              tr("Spreadsheet files (*.sp)"));

    if(fileName.isEmpty())
        return false;

    return saveFile(fileName);
}

void MainWindow::closeEvent(QCloseEvent* event)
{
	if(okToContinue()) {
		writeSettings();
		event->accept();
	}
	else
		event->ignore();
}

void MainWindow::setCurrentFile(const QString &fileName)
{
    curFile = fileName;
    setWindowModified(false);

    QString shownName = tr("Untitled");
    if(!curFile.isEmpty()) {
        shownName = strippedName(curFile);
        recentFiles.removeAll(curFile);
        recentFiles.prepend(curFile);
        updateAllRecentFileActions();
    }

    setWindowTitle(tr("%1[*] - %2").arg(shownName)
                                   .arg(tr("Spreadsheet")));
}

QString MainWindow::strippedName(const QString &fullFileName)
{
    return QFileInfo(fullFileName).fileName();
}

void MainWindow::updateAllRecentFileActions(void)
{
	foreach(QWidget *win, QApplication::topLevelWidgets())
		if(MainWindow *mainWin = qobject_cast<MainWindow*>(win))
			mainWin->updateRecentFileActions();
}

void MainWindow::updateRecentFileActions(void)
{
    QMutableStringListIterator i(recentFiles);

    while(i.hasNext())
        if(!QFile::exists(i.next()))
            i.remove();

    for(int j = 0; j < MaxRecentFiles; ++j)
        if(j < recentFiles.count()) {
            QString text = tr("&%1 %2").arg(j+1)
                           .arg(strippedName(recentFiles[j]));
            recentFileActions[j]->setText(text);
            recentFileActions[j]->setData(recentFiles[j]);
            recentFileActions[j]->setVisible(true);
        }
        else
            recentFileActions[j]->setVisible(false);

    separatorAction->setVisible(!recentFiles.isEmpty());
}

void MainWindow::openRecentFile(void)
{
    if(okToContinue()) {
        QAction *action = qobject_cast<QAction*>(sender());
        if(action)
            loadFile(action->data().toString());
    }
}

void MainWindow::find(void)
{
    if(!findDialog) {
        findDialog = new FindDialog(this);

        QSettings settings("Software Inc.", "Spreadsheet");
        settings.beginGroup("findDialog");
        bool matchCase = settings.value("matchCase", true).toBool();
        findDialog->caseCheckBox->setChecked(matchCase);

        bool searchBackward = settings.value("searchBackward", false).toBool();
        findDialog->backwardCheckBox->setChecked(searchBackward);
        settings.endGroup();

//        connect(findDialog, SIGNAL(findNext(const QString&,Qt::CaseSensitivity)),
//                spreadsheet, SLOT(findNext(const QString&, Qt::CaseSensitivity)));
//        connect(findDialog, SIGNAL(findPrevious(const QString&,Qt::CaseSensitivity)),
//                spreadsheet, SLOT(findPrevious(const QString&, Qt::CaseSensitivity)));
    }

    findDialog->show();
    findDialog->raise();
    findDialog->activateWindow();
}

void MainWindow::goToCell(void)
{
    GoToCellDialog dialog(this);
    if(dialog.exec()) {
        QString str = dialog.lineEdit->text().toUpper();
//        spreadsheet->setCurrentCell(str.mid(1).toInt(),
//                                    str[0].unicode() - 'A');
    }
}

void MainWindow::sort(void)
{
    SortDialog dialog(this);
//    QTableWidgetSelectionRange range = spreadsheet->selectedRange();
//    dialog.setColumnRange('A' + range.leftColumn(),
//                         'A' + range.rightColumn());

    if(dialog.exec()) {
//        SpreadsheetCompare compare;

//        compare.keys[0] = dialog.primaryColumnCombo->currentIndex();
//        compare.keys[1] = dialog.secondaryColumnCombo->currentIndex()-1;
//        compare.keys[2] = dialog.tertiaryColumnCombo->currentIndex()-1;

//        compare.ascending[0] = dialog.primaryOrderCombo->currentIndex() == 0;
//        compare.ascending[1] = dialog.secondaryOrderCombo->currentIndex() == 0;
//        compare.ascending[2] = dialog.tertiaryOrderCombo->currentIndex() == 0;

//        spreadsheet->sort(compare);
    }
}

void MainWindow::about()
{
    QMessageBox::about(this, tr("About Spreadsheet"),
            tr("<h2>Spreadsheet 1.1</h2>"
               "<p>Copyright &copy; 2008 Software Inc.</p>"
               "<p>Spreadsheet is a small application that "
               "demonstrates QAction, QMainWindow, QMenuBar, "
               "QStatusBar, QTableWidget, QToolBar, and many other "
               "Qt classes.</p>"));
}

void MainWindow::writeSettings(void)
{
    QSettings settings("Software Inc.", "Spreadsheet");

    settings.setValue("geometry", saveGeometry());
    settings.setValue("recentFiles", recentFiles);
    settings.setValue("showGrid", showGridAction->isChecked());
    settings.setValue("autoRecalc", autoRecalcAction->isChecked());

    if(findDialog) {
        settings.beginGroup("findDialog");
        settings.setValue("matchCase", findDialog->caseCheckBox->isChecked());
        settings.setValue("searchBackward", findDialog->backwardCheckBox->isChecked());
        settings.endGroup();
    }
}

void MainWindow::readSettings(void)
{
    QSettings settings("Software Inc.", "Spreadsheet");

    restoreGeometry(settings.value("geometry").toByteArray());

    recentFiles = settings.value("recentFiles").toStringList();
    updateAllRecentFileActions();

    bool showGrid = settings.value("showGrid", true).toBool();
    showGridAction->setChecked(showGrid);

    bool autoRecalc = settings.value("autoRecalc", true).toBool();
    autoRecalcAction->setChecked(autoRecalc);
}