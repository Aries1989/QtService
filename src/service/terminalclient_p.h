#ifndef QTSERVICE_TERMINALCLIENT_P_H
#define QTSERVICE_TERMINALCLIENT_P_H

#include <QtCore/QObject>
#include <QtCore/QDataStream>
#include <QtNetwork/QLocalSocket>
#include "qtservice_global.h"

#include "service.h"

class QConsole;

namespace QtService {

class TerminalClient : public QObject
{
	Q_OBJECT

public:
	explicit TerminalClient(Service::TerminalMode mode, Service *service);
	~TerminalClient() override;

	int exec(int &argc, char **argv, int flags);

private Q_SLOTS:
	void doConnect();

	void connected();
	void disconnected();
	void error(QLocalSocket::LocalSocketError socketError);
	void socketReady();

	void consoleReady();

private:
	Service *_service;
	const Service::TerminalMode _mode;
	QStringList _cmdArgs;

	QLocalSocket *_socket = nullptr;
	QDataStream _stream;
	QFile *_outFile = nullptr;

	QFile *_inFile = nullptr;
	QConsole *_inConsole = nullptr;

	bool _exitFailed = false;

	static void cerrMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &message);
};

}

#endif // QTSERVICE_TERMINALCLIENT_P_H
