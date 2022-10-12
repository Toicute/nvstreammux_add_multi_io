#include "mqqt.h"
#include "iostream"
#include <QMqttSubscription>
#include <QMqttTopicFilter>

mqqt::mqqt()
{
    std::cout<<"1 \n"<<std::endl;
    Client.setPort(1883);
    Client.setHostname("10.3.2.111");
    Client.connectToHost();
    connect(&Client, &QMqttClient::connected, this, &mqqt::OnConnectBroker);
    std::cout<<"2 \n"<<std::endl;
}

void mqqt::PublishMessage(QString msg)
{
    Client.publish(QMqttTopicName("/ryu"), msg.toLocal8Bit(), 0, true);
}
void mqqt::OnConnectBroker()
{
std::cout<<"Da ket noi voi broker \n"<<std::endl;
PublishMessage("test-publish");
QString sub_name = "/ryu";
QMqttTopicFilter filter(sub_name);
QMqttSubscription *subscription = Client.subscribe(filter, 0);
connect(subscription, &QMqttSubscription::messageReceived, this, &mqqt::OnMessageReceived);
}
void mqqt::OnMessageReceived(QMqttMessage msg){
    qDebug()<<msg.payload();
    QString message = QString::fromLocal8Bit(msg.payload());
    if (message == "add"){
        printf("Da nhan tin hieu tu messageReceived \n");
        emit AddStream("file:///home/toicuteee/cong_viec/testvideo");
    }
    if (message == "remove"){
        printf("Da nhan tin hieu tu messageReceived \n");
        emit RemoveStream("3");
    }
}

