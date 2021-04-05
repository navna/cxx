#include "main_window.h"

#include <sstream>

#include <QHostAddress>
#include <QMessageBox>
#include <QVBoxLayout>

#include "protocol.h"
#include "server_request.h"

using namespace std;

void MainWindow::getMessages() {
	const auto buffer = Protocol::GetMessages::makeRequest(0); // TODO [Client] Индекс определять "умным" способом
	const auto serverRequest = new ServerRequest(QHostAddress::LocalHost, 5000, buffer, 5000);

	QObject::connect(serverRequest, &ServerRequest::responded, this, &MainWindow::responded);
	QObject::connect(serverRequest, &ServerRequest::failed, this, &MainWindow::failed);

	_textEdit->setText(QString());
	_button->setEnabled(false);
}

void MainWindow::responded(Protocol::QueryType queryType, Protocol::Buffer& response) {
	switch (queryType) {

	case Protocol::QueryType::GetMessages:
	{
		const auto messages = Protocol::GetMessages::parseResponse(response);
		QString response;
		for (auto& message : messages) {
			response += QString(message.c_str()) + "\n";
		}
		_textEdit->setText(response);
		break;
	}

	case Protocol::QueryType::SendMessage:
	{
		// TODO [Client] Обработать событие успешной отправки сообщения
		break;
	}

	default:
	{
		_textEdit->setText("Неизвестный тип ответа!");
	}

	}

	_button->setEnabled(true);
}

void MainWindow::failed() {
	_textEdit->setText(QString("Не удалось отправить запрос или получить ответ!"));
	_button->setEnabled(true);
}


MainWindow::MainWindow() : _textEdit(new QTextEdit), _button(new QPushButton) {
	_button->setText("Отправить запрос на сервер");

	const auto rootLayout = new QVBoxLayout;
	rootLayout->addWidget(_textEdit);
	rootLayout->addWidget(_button);
	rootLayout->setAlignment(_button, Qt::AlignRight);
	setLayout(rootLayout);

	QObject::connect(_button, &QAbstractButton::clicked, this, &MainWindow::getMessages);
}
