#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_menuWindow.h"

class QAction;
class QLabel;
class FindDialog;
// class Spreadsheet;

class MainWindow : public QMainWindow, public Ui::MainWindow
{
    Q_OBJECT

public:
    MainWindow(void);

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void newFile();
    void open();
    bool save();
    bool saveAs();
    void find();
    void goToCell();
    void sort();
    void about();
    void openRecentFile();
    void updateStatusBar();
    void spreadsheetModified();

private:
    void createActions();
    void createMenus();
    void createContextMenu();
    void createStatusBar();

    void readSettings();
    void writeSettings();

    bool okToContinue();

    bool loadFile(const QString &fileName);
    bool saveFile(const QString &fileName);

    void setCurrentFile(const QString &fileName);
    void updateAllRecentFileActions();
    void updateRecentFileActions();

    QString strippedName(const QString &fullFileName);

 //   Spreadsheet *spreadsheet;
    FindDialog *findDialog;

    QLabel *locationLabel, *formulaLabel;

    static QStringList recentFiles; // Global to the whole app.
    QString curFile;

    enum {MaxRecentFiles = 5};
    QAction *recentFileActions[MaxRecentFiles];  
    QAction *separatorAction;
};

#endif