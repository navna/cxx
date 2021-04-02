#pragma once

#include <sstream>

#include <QTextEdit>
#include <QPushButton>
#include <QTcpSocket>
#include <QTimer>
#include <QWidget>

class MainWindow: public QWidget {
	Q_OBJECT

private:
	QTextEdit* _textEdit;
	QPushButton* _button;
	std::stringstream _stream;
	QTcpSocket* _socket;
	QTimer* _timeoutTimer;

private slots:
	void clicked();
	void connected();
	void readyRead();
	void timeout();

public:
	MainWindow();

	MainWindow(const MainWindow&) = delete;
	MainWindow& operator=(const MainWindow&) = delete;
};
