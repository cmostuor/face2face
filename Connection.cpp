#include "Connection.h"

Connection::Connection(int _port)
{
	isServer = false;
	tSocketIsConnecting = false;
	connected = false;
    ping = new QTimer();
	port = _port;
	tSocket = new QTcpSocket();
	tServer = new QTcpServer();
	//listening on ports for signals
	uSocket.bind(port);
	std::cout << "listening on UDP port " << port << " for another Viewer "<< std::endl;
	tServer->listen( QHostAddress::Any, port+1);
	std::cout << "listening on TCP port " << port +1 << " for another Viewer "<< std::endl;
	
	
    //connect slots and signals:
    QObject::connect(ping, SIGNAL(timeout()), this, SLOT(sendPing()));
	//connect tcpSocket-Signals:
	QObject::connect(&uSocket, SIGNAL(readyRead()), this, SLOT(udpReceived()));
	QObject::connect(tSocket, SIGNAL(connected()), this, SLOT(tcpConnected()));
	QObject::connect(tSocket, SIGNAL(disconnected()), this, SLOT(tcpDisconnected()));
	QObject::connect(tSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(tcpError(QAbstractSocket::SocketError )));
	QObject::connect(tSocket, SIGNAL(readyRead()), this, SLOT(tcpDataReceived()));
	//connect tcpServer-Signals:
	QObject::connect(tServer, SIGNAL(newConnection()), this, SLOT(tServerConnected()));

}

Connection::~Connection(void)
{
	//close all connections and delete pointer
	tServer->close();
	tSocket->close();
	uSocket.close();
    delete ping;
	delete tSocket;
	delete tServer;
}

//public slots:
void Connection::udpReceived(){
	//create QByteArray in the right size
	QByteArray packet;
	packet.resize(uSocket.pendingDatagramSize());
	QHostAddress address;
	uSocket.readDatagram(packet.data(), packet.size(), &address);
	//check if it's from the right programm
	if(packet.startsWith("QModelViewer Hello")){
		//if so connect to the Server
		uSocket.aboutToClose();
		std::cout << "found another Viewer at "<< address.toString().toStdString() << std::endl;
		tSocket->connectToHost(address.toString(), port+1);
	}
	
}

void Connection::sendPing(){
	//check if already connected
	if(!connected){
		//if not send ping
		uSocket.close();
		std::cout << "ping" << std::endl;
		uSocket.writeDatagram("QModelViewer Hello", QHostAddress::Broadcast, port);
	}
	
}

//tcp slots:

void Connection::tcpConnected(){
	std::cout << "connected" << std::endl;
	//close UDP port
	uSocket.close();
	connected = true;
	isServer = false;
}
void Connection::tcpDisconnected(){
	std::cout << "disconnected" << std::endl;
	//open UDP and TCP ports again
	uSocket.bind(port);
	connected = false;
}
void Connection::tcpError(QAbstractSocket::SocketError error){
	//report tcp errors
	std::cout << "Error: " << error <<std::endl;
	connected = false;
}
void Connection::tcpDataReceived(){
	//std::cout << "data received" << std::endl;
	QString input;
	//read the seralized data
	while (tSocket->canReadLine()){
		input = tSocket->readLine();
		//std::cout << input.toStdString() << std::endl;
		emit receivedMessage(ModellMessage(input));
	}
}

void Connection::tServerConnected(){
	isServer = true;
	std::cout << "Client connected -> this is the Server " << std::endl;
	
	//disconnect old tSocket:
	QObject::disconnect(&uSocket, SIGNAL(readyRead()), this, SLOT(udpReceived()));
	QObject::disconnect(tSocket, SIGNAL(connected()), this, SLOT(tcpConnected()));
	QObject::disconnect(tSocket, SIGNAL(disconnected()), this, SLOT(tcpDisconnected()));
	QObject::disconnect(tSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(tcpError(QAbstractSocket::SocketError )));
	QObject::disconnect(tSocket, SIGNAL(readyRead()), this, SLOT(tcpDataReceived()));
	
	//get connection from tServer:
	tSocket = tServer->nextPendingConnection();
	connected = true;

	//reconnect new tSocket
	QObject::connect(&uSocket, SIGNAL(readyRead()), this, SLOT(udpReceived()));
	QObject::connect(tSocket, SIGNAL(connected()), this, SLOT(tcpConnected()));
	QObject::connect(tSocket, SIGNAL(disconnected()), this, SLOT(tcpDisconnected()));
	QObject::connect(tSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(tcpError(QAbstractSocket::SocketError )));
	QObject::connect(tSocket, SIGNAL(readyRead()), this, SLOT(tcpDataReceived()));

	connected = true;
	//close UDP port
	uSocket.close();
}

void Connection::sendMessage(ModellMessage message){
	if (!connected) return;
	QString data = message.serialise();
	QTextStream stream(tSocket);
    stream << data << endl;

	
}
