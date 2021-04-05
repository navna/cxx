#pragma once

#include <string>

#include <QHostAddress>
#include <QTcpSocket>
#include <QTimer>

#include "protocol.h"

class ServerRequest final : public QObject {
	Q_OBJECT

private:
	QTcpSocket _socket;
	QTimer _timeoutTimer;
	std::string _request;
	Protocol::Buffer _response;
	bool _responded = false;

private slots:
	void connected();
	void readyRead();
	void timeout();

signals:
	void responded(Protocol::QueryType queryType, Protocol::Buffer& response);
	void failed();

public:
	ServerRequest(const QHostAddress& address, quint16 port, const Protocol::Buffer& request, int timeout);

	ServerRequest(const ServerRequest&) = delete;
	ServerRequest& operator=(const ServerRequest&) = delete;
};
