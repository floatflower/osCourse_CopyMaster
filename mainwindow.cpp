#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "copyfile.h"
#include <QThread>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->ui->copyProgress->setMinimum(0);
    this->ui->copyProgress->setMaximum(100);
    this->m_copyStatus = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_startCopy_clicked()
{
    if(m_copyStatus == 1) return;
    this->m_copy = new CopyFile(this);
    m_copy->setInfo(this->ui->copyProgress,this->ui->originFile->text(),this->ui->targetLocation->text());
    connect(m_copy, SIGNAL(setProgress(int)), this, SLOT(setProgess(int)));
    m_copy->start();
    this->m_copyStatus = 1;
    this->ui->startCopy->setEnabled(false);
}

void MainWindow::setProgess(int value)
{
    this->ui->copyProgress->setValue(value);
}

void MainWindow::on_browseOrigin_clicked()
{
    QString originFileName = QFileDialog::getOpenFileName(this,
                                                          tr("Open file"),
                                                          "C:\\",
                                                          tr("All files(*)"));
    this->ui->originFile->setText(originFileName);
}

void MainWindow::on_browseTarget_clicked()
{
    QString targetLocation = QFileDialog::getExistingDirectory(this, tr("Open Directory"),"C:\\");
    this->ui->targetLocation->setText(targetLocation);
}

void MainWindow::on_stopCopy_clicked()
{
    this->m_copy->terminate();
    this->ui->startCopy->setText(tr("繼續拷貝"));
    this->ui->startCopy->setEnabled(true);
    this->m_copyStatus = 2;
}
