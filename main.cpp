#include <QCoreApplication>
#include <mqqt.h>
#include <iostream>
#include <QMqttSubscription>
#include <pipeline_new.h>


int main(int argc, char *argv[])
{
    std::cout<<"?????????? \n"<<std::endl;
    QCoreApplication a(argc, argv);
    mqqt Mqtt;
    // std::cout<<"Da chay xong QTmqtt \n"<<std::endl;
    pipeline_nvstreammux pipeline;
    QObject::connect(&Mqtt, &mqqt::AddStream, &pipeline, &pipeline_nvstreammux::OnAddStream);
    QObject::connect(&Mqtt, &mqqt::RemoveStream, &pipeline, &pipeline_nvstreammux::OnRemoveStream); 
    pipeline.PipelineNvstreammux(argc, argv);
    QString message = QString::fromLocal8Bit(argv[1]);
    return a.exec();
}
