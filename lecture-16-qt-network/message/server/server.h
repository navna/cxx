#pragma once

#include <QHostAddress>
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

class Server final : public QObject {
	Q_OBJECT

private:
	QTcpServer _server;
	std::unordered_map<QTcpSocket*, std::stringstream> _streams;
	std::vector<std::string> _messages = { "first message", "second message", "third message" };

private slots:
	void newConnection();
	void readyRead();
	void disconnected();

public:
	Server(const QHostAddress& address, quint16 port);

	QHostAddress address() const;

	quint16 port() const;

	Server(const Server&) = delete;
	Server& operator=(const Server&) = delete;
};
