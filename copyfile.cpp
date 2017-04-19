#include "copyfile.h"
#include <QFile>
#include <QFileInfo>
#include <QMessageBox>
#include <QTextStream>
#include <QDataStream>
#include <QDebug>

CopyFile::CopyFile(QObject *parent) : QThread(parent)
{

}
void CopyFile::run()
{
    QFile originFile(this->m_originFileName);
    QFileInfo fileInfo = originFile.fileName();
    QString originFileName = fileInfo.fileName();
    qint64 originFileSize = originFile.size();

    if(!originFile.open(QIODevice::ReadOnly)) {
        qDebug("Cannot read from destination");
        return;
    }

    QFile targetFile(this->m_targetFileName+"/"+originFileName);

    if(!targetFile.open(QIODevice::WriteOnly | QIODevice::Append)) {
        qDebug("Cannot write to destination");
        return;
    }

    QDataStream in(&originFile);
    QDataStream out(&targetFile);
    int i = 0;
    char *s = new char[1024];
    while(!in.atEnd())
    {
        int realSize = in.readRawData(s,1024);
        out.writeRawData(s, realSize);
        i += realSize;
        emit setProgress(i/(float)originFileSize * 100);
    }
    originFile.close();
    targetFile.close();
}

void CopyFile::setInfo(QProgressBar *progressBar, QString originFileName, QString targetFileName)
{
    this->m_progressBar = progressBar;
    this->m_originFileName = originFileName;
    this->m_targetFileName = targetFileName;
}
