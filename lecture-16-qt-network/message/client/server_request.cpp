#include "server_request.h"

#include "protocol.h"

using namespace std;

void ServerRequest::connected() {
	_socket.write(_request.c_str(), _request.size());
	_socket.flush();
}

void ServerRequest::readyRead() {
	if (_responded || _socket.bytesAvailable() == 0) {
		return;
	}

	auto data = _socket.readAll();
	_response.insert(_response.end(), data.begin(), data.end());

	if (!Protocol::canParse(_response)) {
		return;
	}

	// ОСНОВНОЙ КОД ОБРАБОТКИ

	Protocol::readUnsigned(_response); // Извлекаем размер тела ответа из буфера
	const auto queryType = (Protocol::QueryType)Protocol::readUnsigned(_response);

	// Генерируем сигнал об успешном выполнении запроса
	emit responded(queryType, _response);
	_responded = true;

	_socket.close();
	deleteLater();
}

void ServerRequest::timeout() {
	if (_responded) {
		return;
	}

	// Генерируем сигнал об ошибке выполнении запроса
	emit failed();
	_responded = true;

	_socket.close();
	deleteLater();
}

ServerRequest::ServerRequest(const QHostAddress& address, quint16 port, const Protocol::Buffer& request, int timeout) : _request(request.begin(), request.end()) {
	connect(&_socket, &QAbstractSocket::connected, this, &ServerRequest::connected);
	connect(&_socket, &QAbstractSocket::readyRead, this, &ServerRequest::readyRead);
	connect(&_timeoutTimer, &QTimer::timeout, this, &ServerRequest::timeout);

	_socket.connectToHost(address, port);

	_timeoutTimer.setSingleShot(true);
	_timeoutTimer.start(timeout);
}
