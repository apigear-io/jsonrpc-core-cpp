/*
* MIT License
*
* Copyright (c) 2021 ApiGear
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*/
#include "qjsonrpc.h"

#include "jsonrpc/rpcprotocol.h"
#include "jsonrpc/stdoutlogger.h"
#include "nlohmann/json.hpp"

QJsonRpc::QJsonRpc(QObject *parent)
    : QObject(parent)
    , m_socket(new QWebSocket(QString(), QWebSocketProtocol::VersionLatest, this))
    , m_log(new StdoutLogger())
    , m_session(new RpcProtocol(this, this, m_log, MessageFormat::JSON))

{
    connect(m_socket, &QWebSocket::connected, this, &QJsonRpc::onConnected);
    connect(m_socket, &QWebSocket::disconnected, this, &QJsonRpc::onDisconnected);
    connect(m_socket, &QWebSocket::textMessageReceived, this, &QJsonRpc::handleTextMessage);
}


void QJsonRpc::open(QUrl url)
{
    m_socket->open(url);
}

void QJsonRpc::onConnected()
{
    m_log->info("on connected");
    emit ready();
}

void QJsonRpc::onDisconnected()
{
    m_log->info("on disconnected");
}

void QJsonRpc::writeMessage(string message)
{
    m_log->debug("write message to socket " + message);
    if(QAbstractSocket::ConnectedState == m_socket->state()) {
        m_socket->sendTextMessage(QString::fromStdString(message));
    } else {
        m_log->debug("socket not connected");
    }
}

void QJsonRpc::handleTextMessage(const QString &message)
{
    m_session->handleMessage(message.toStdString());
}

void QJsonRpc::doCall(const QString &method, const QVariantMap &params)
{
    CallResponseFunc func = [](CallResponseArg) { qDebug() << "call result"; };
    m_session->doCall(method.toStdString(), variantToJson(params), func);
}

void QJsonRpc::doNotify(const QString &method, const QVariantMap &params)
{
    m_session->doNotify(method.toStdString(), variantToJson(params));
}

void QJsonRpc::doRegisterCall(const QString &method)
{
    CallRequestFunc func = [](CallRequestArg arg) {
        qDebug() << "registered method called";
        CallResponseArg response;
        response.result = arg.params;
        return response;
    };
    m_session->onCall(method.toStdString(), func);
}


json QJsonRpc::variantToJson(const QVariant &var)
{
    const QByteArray data = QJsonDocument::fromVariant(var).toJson();
    return json::parse(data);
}

QVariant QJsonRpc::jsonToVariant(json j)
{
    const QByteArray data(j.dump().c_str());
    QJsonDocument doc = QJsonDocument::fromJson(data);
    return doc.toVariant();
}

void QJsonRpc::onNotify(string method, Params params)
{
    emit notify(QString::fromStdString(method), jsonToVariant(params));
}
