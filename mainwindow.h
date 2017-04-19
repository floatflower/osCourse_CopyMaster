#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include <QProgressBar>
#include "copyfile.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_startCopy_clicked();
    void setProgess(int value);
    void on_browseOrigin_clicked();

    void on_browseTarget_clicked();

    void on_stopCopy_clicked();

signals:
    void start(QProgressBar* progressBar, QString originFileName, QString targetLocation);
private:
    Ui::MainWindow *ui;
    CopyFile *m_copy;
    int m_copyStatus;
};

#endif // MAINWINDOW_H
