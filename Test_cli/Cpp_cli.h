#ifndef CPP_CLI_H
#define CPP_CLI_H

#include <QDebug>
#include <QEventLoop>
#include <QObject>
#include <QTimer>
#include <QUrl>
#include <QWebSocket>

class Cpp_cli : public QObject
{
    Q_OBJECT
public:
    explicit Cpp_cli(QObject *parent = nullptr);
    ~Cpp_cli();
    void shutdown();

signals:

private:
    QWebSocket *soc;
};

#endif // CPP_CLI_H
