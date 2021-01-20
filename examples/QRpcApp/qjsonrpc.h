#pragma once

#include <QtCore>
#include <QtWebSockets>
#include "jsonrpc/types.h"

class RpcProtocol;


class QJsonRpc : public QObject, public IMessageWriter, public IRpcProtocolListener
{
    Q_OBJECT
public:
    QJsonRpc(QObject *parent=nullptr);
    Q_INVOKABLE void open(QUrl url);
    Q_INVOKABLE void doCall(const QString& method, const QVariantMap &params);
    Q_INVOKABLE void doNotify(const QString& method, const QVariantMap &params);
    Q_INVOKABLE void doRegisterCall(const QString& method);
Q_SIGNALS:
    void notify(const QString& method, const QVariant& params);
    void ready();
public:
    void onConnected();
    void onDisconnected();
    void writeMessage(std::string message) override;
    void handleTextMessage(const QString& message);
    json variantToJson(const QVariant& var);
    QVariant jsonToVariant(json j);
private:
    ILogger *m_log;
    QWebSocket *m_socket;
    RpcProtocol *m_session;

    // IRpcProtocolListener interface
public:
    void onNotify(string method, Params params) override;
};
