#ifndef CPP_SV_H
#define CPP_SV_H

#include <QDebug>
#include <QObject>
#include <QWebSocket>
#include <QWebSocketServer>

class Cpp_Sv : public QObject
{
    Q_OBJECT
public:
    explicit Cpp_Sv(QObject *parent = nullptr);
    void connectSv();

signals:

private:
    QWebSocketServer *sv;
    QWebSocket *soc;
};

#endif // CPP_SV_H
