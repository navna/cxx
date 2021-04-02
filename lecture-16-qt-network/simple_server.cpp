#include <iostream>

#include <QCoreApplication>
#include <QNetworkInterface>
#include <QTcpServer>
#include <QTcpSocket>

using namespace std;

size_t active_connections = 0;

void readyRead(QTcpSocket& socket);

void disconnected(QTcpSocket& socket);

void destroyed(QTcpSocket& socket);

void newConnection(QTcpServer& server) {
    auto socket = server.nextPendingConnection();
    if (socket == nullptr) {
        return;
    }

    cout << "NEW_CONNECTION: " << socket << endl << endl;
    ++active_connections;

    QObject::connect(socket, &QTcpSocket::readyRead, [socket]() { readyRead(*socket); });
    QObject::connect(socket, &QTcpSocket::disconnected, [socket]() { disconnected(*socket); });
    QObject::connect(socket, &QTcpSocket::destroyed, [socket]() { destroyed(*socket); });
}

void readyRead(QTcpSocket& socket) {
    string request;
    while (socket.bytesAvailable() > 0) {
        auto data = socket.readAll();
        request += data.toStdString();
    }
    cout << request;
    if (request.find("\r\n\r\n")) {
        string response = "HTTP/1.1 200 OK\r\n";
        response += "Content-Type: text/plain; charset=utf-8\r\n";
        response += "Content-Length: 20\r\n";
        response += "\r\n";
        response += "Привет мир!";
        socket.write(response.c_str(), response.size());
        socket.close();
    }
}

void disconnected(QTcpSocket& socket) {
    cout << "DISCONNECTED: " << &socket << endl << endl;
    socket.deleteLater();
}

void destroyed(QTcpSocket& socket) {
    --active_connections;
    cout << "DESTROYED: " << &socket << " (" << active_connections << ")" << endl << endl;
}

int main(int argc, char** argv) {
    QCoreApplication app(argc, argv);

    cout << "NETWORK INTERFACES:" << endl;
    for (const auto& address : QNetworkInterface::allAddresses()) {
        cout << address.toString().toStdString() << endl;
    }
    cout << endl;

    QTcpServer server;
    QObject::connect(&server, &QTcpServer::newConnection, [&server]() { newConnection(server); });
    if (server.listen(QHostAddress::LocalHost, 5000)) {
        cout << "The server is running on " << server.serverAddress().toString().toStdString() << ":" << server.serverPort() << "." << endl << endl;
        return QCoreApplication::exec();
    }
    else {
        cout << server.errorString().toStdString() << endl;
        return EXIT_FAILURE;
    }
}
