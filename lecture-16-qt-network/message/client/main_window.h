#pragma once

#include <QTextEdit>
#include <QPushButton>
#include <QWidget>

#include "protocol.h"

class MainWindow: public QWidget {
	Q_OBJECT

private:
	QTextEdit* _textEdit;
	QPushButton* _button;

private slots:
	void getMessages();
	void responded(Protocol::QueryType queryType, Protocol::Buffer& response);
	void failed();

public:
	MainWindow();

	MainWindow(const MainWindow&) = delete;
	MainWindow& operator=(const MainWindow&) = delete;
};
