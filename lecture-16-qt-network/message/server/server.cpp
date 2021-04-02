#include "server.h"

#include <stdexcept>

#include <QTcpSocket>

#include "protocol.h"

using namespace std;

void Server::newConnection() {
    auto socket = _server.nextPendingConnection();
    if (socket == nullptr) {
        return;
    }

    _streams[socket] = stringstream();

    QObject::connect(socket, &QTcpSocket::readyRead, this, &Server::readyRead);
    QObject::connect(socket, &QTcpSocket::disconnected, this, &Server::disconnected);
}

void Server::readyRead() {
    auto socket = qobject_cast<QTcpSocket*>(QObject::sender());
    auto& stream = _streams[socket];
    while (socket->bytesAvailable() > 0) {
        auto data = socket->readAll();
        for (auto b : data) {
            stream.put(b);
        }
    }

    if (!Protocol::canRecv(stream)) {
        return;
    }

    // ОБРАБОТКА ЗАПРОСА И ОТПРАВКА ОТВЕТА
    Protocol::readUnsigned(stream); // Извлекаем размер тела запроса из буфера
    const auto requestType = (RequestType)Protocol::readUnsigned(stream);

    switch (requestType) {

    case RequestType::GetMessages:
    {
        const auto index = Protocol::GetMessages::recvRequest(stream);

        vector<string> response;
        if (index < _messages.size()) {
            response.insert(response.end(), _messages.begin() + index, _messages.end());
        }

        stream = stringstream();
        Protocol::GetMessages::sendResponse(stream, response);

        auto buffer = stream.str();
        socket->write(buffer.c_str(), buffer.size());
    }

    case RequestType::SendMessage:
    {
        // TODO
    }

    }

    socket->close();
}

void Server::disconnected() {
    auto socket = qobject_cast<QTcpSocket*>(QObject::sender());
    socket->deleteLater();
    _streams.erase(socket);
}

Server::Server(const QHostAddress& address, quint16 port) {
    QObject::connect(&_server, &QTcpServer::newConnection, this, &Server::newConnection);
    if (!_server.listen(address, port)) {
        throw runtime_error(_server.errorString().toStdString());
    }
}

QHostAddress Server::address() const {
    return _server.serverAddress();
}

quint16 Server::port() const {
    return _server.serverPort();
}
