#ifndef X264THREAD_H
#define X264THREAD_H

#include <QThread>
#include <QGLWidget>

//#include "live/BasicUsageEnvironment/include/BasicUsageEnvironment.hh"
//#include "live/mediaServer/DynamicRTSPServer.hh"
//#include "live/mediaServer/version.hh"

class x264Thread : public QThread
{
    Q_OBJECT
public:
    explicit x264Thread(QGLWidget* window);
private:
    QGLWidget* window;
    void streamImage();
//    TaskScheduler* scheduler;
//    UsageEnvironment* env;
//    UserAuthenticationDatabase* authDB;
//    RTSPServer* rtspServer;
signals:

public slots:
};

#endif // X264THREAD_H
