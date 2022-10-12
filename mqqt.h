#ifndef MQQT_H
#define MQQT_H
#include <QMqttClient>
#include <QThread>
#include <QMqttSubscription>

class mqqt : public QThread
{
Q_OBJECT
public:
    mqqt();
    QMqttClient Client;
    void PublishMessage(QString msg);
signals:
    void AddStream(QString source);
    void RemoveStream(QString source);

public slots:
    void OnConnectBroker();
    void OnMessageReceived(QMqttMessage msg);

};

#endif // MQQT_H
