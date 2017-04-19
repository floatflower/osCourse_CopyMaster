#ifndef COPYFILE_H
#define COPYFILE_H

#include <QObject>
#include <QProgressBar>
#include <QThread>

class CopyFile : public QThread
{
    Q_OBJECT
public:
    explicit CopyFile(QObject *parent = 0);
    void run() Q_DECL_OVERRIDE;
    void setInfo(QProgressBar* progressBar, QString originFileName, QString targetFileName);
private:
    QProgressBar* m_progressBar;
    QString m_originFileName;
    QString m_targetFileName;
signals:
    void setProgress(int value);
};

#endif // COPYFILE_H
