#pragma once

#include <QHostAddress>
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

#include <string>
#include <unordered_map>
#include <vector>

#include "protocol.h"

class Server final : public QObject {
	Q_OBJECT

private:
	QTcpServer _server;
	std::unordered_map<QTcpSocket*, typename Protocol::Buffer> _buffers;
	std::vector<std::string> _messages = { "first message", "second message", "third message" }; // TODO [Server] Убрать предопределённые сообщения

private slots:
	void newConnection();
	void readyRead();
	void disconnected();

public:
	Server(const QHostAddress& address, quint16 port);
	Server(const Server&) = delete;

	Server& operator=(const Server&) = delete;

	QHostAddress address() const;
	quint16 port() const;
};
