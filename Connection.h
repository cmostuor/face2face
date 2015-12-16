/**
 *	Handels the network traffic
 */

#ifndef CONNECTION_H
#define CONNECTION_H

#include <QThread>
#include <QTimer>
#include <qudpsocket.h>
#include <qtcpsocket.h>
#include <qtcpserver.h>
#include <QString>
#include <qhostaddress.h>
#include <qvector3d.h>
#include <qbytearray.h>
#include <iostream>
#include "ModellMessage.h"


class Connection :  public QThread
{
	
	Q_OBJECT
	
	//for establishing connection
	QTimer* ping;
    QUdpSocket uSocket;

	QTcpSocket* tSocket;
	bool tSocketIsConnecting;
	QTcpServer* tServer;
	bool isServer;
    bool connected;
	int port;

public:
	Connection(int _port = 15155);
	~Connection(void);

public slots:
	void udpReceived();
	void sendPing();
	//tcp:
	void tcpConnected();
	void tcpDisconnected();
	void tcpError(QAbstractSocket::SocketError error);
	void tcpDataReceived();
	void tServerConnected();
	void sendMessage(ModellMessage message);

signals:
	void receivedMessage(ModellMessage message);

	

};


#endif // CONNECTION_H
