#include "main_window.h"

#include <sstream>

#include <QHostAddress>
#include <QMessageBox>
#include <QVBoxLayout>

#include "protocol.h"

using namespace std;

void MainWindow::clicked() {
	_socket = new QTcpSocket;
	_timeoutTimer = new QTimer(_socket);

	QObject::connect(_socket, &QAbstractSocket::connected, this, &MainWindow::connected);
	QObject::connect(_socket, &QAbstractSocket::readyRead, this, &MainWindow::readyRead);
	QObject::connect(_timeoutTimer, &QTimer::timeout, this, &MainWindow::timeout);

	_textEdit->setText(QString());
	_button->setEnabled(false);
	_socket->connectToHost(QHostAddress::LocalHost, 5000); // TODO Брать из GUI или аргументов командной строки

	_timeoutTimer->setSingleShot(true);
	_timeoutTimer->start(5000);
}

void MainWindow::connected() {
	if (_socket == nullptr) {
		return;
	}

	_stream = stringstream();
	Protocol::GetMessages::sendRequest(_stream, 0); // При последующих запросах запрашивать не все сообщения, а только те, что ещё не получены!

	auto buffer = _stream.str();
	_stream = stringstream();
	_socket->write(buffer.c_str(), buffer.size());
	_socket->flush();
}

void MainWindow::readyRead() {
	if (_socket == nullptr) {
		return;
	}

	while (_socket->bytesAvailable() > 0) {
		auto data = _socket->readAll();
		for (auto b : data) {
			_stream.put(b);
		}
	}

	if (!Protocol::canRecv(_stream)) {
		return;
	}

	// ОСНОВНОЙ КОД ОБРАБОТКИ
	Protocol::readUnsigned(_stream); // Извлекаем размер тела ответа из буфера
	const auto responseType = (RequestType)Protocol::readUnsigned(_stream);

	switch (responseType) {

	case RequestType::GetMessages:
	{
		const auto messages = Protocol::GetMessages::recvResponse(_stream);
		QString response;
		for (auto& message : messages) {
			response += QString(message.c_str()) + "\n";
		}
		_textEdit->setText(response);
	}

	case RequestType::SendMessage:
	{
		// TODO
	}

	}

	_button->setEnabled(true);

	_socket->close();
	_socket->deleteLater();
	_socket = nullptr;
	_timeoutTimer->stop();
	_timeoutTimer = nullptr;
}

void MainWindow::timeout() {
	if (_timeoutTimer == nullptr) {
		return;
	}

	_stream = stringstream();

	_textEdit->setText(QString("Не удалось установить соединение!"));
	_button->setEnabled(true);

	_socket->close();
	_socket->deleteLater();
	_socket = nullptr;
	_timeoutTimer = nullptr;
}


MainWindow::MainWindow() : _textEdit(new QTextEdit), _button(new QPushButton), _socket(nullptr), _timeoutTimer(nullptr) {
	_button->setText("Отправить запрос на сервер");

	const auto rootLayout = new QVBoxLayout;
	rootLayout->addWidget(_textEdit);
	rootLayout->addWidget(_button);
	rootLayout->setAlignment(_button, Qt::AlignRight);
	setLayout(rootLayout);

	QObject::connect(_button, &QAbstractButton::clicked, this, &MainWindow::clicked);
}
