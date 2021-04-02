#include <iostream>
#include <stdexcept>

#include <QCoreApplication>

#include "server.h"

using namespace std;

int main(int argc, char** argv) {
	QCoreApplication app(argc, argv);
	
	try {
		Server server(QHostAddress::LocalHost, 5000);
		cout << "The server is running on " << server.address().toString().toStdString() << ":" << server.port() << "." << endl;
		return QCoreApplication::exec();
	}
	catch (const exception& e) {
		cout << e.what() << endl;
	}
}
