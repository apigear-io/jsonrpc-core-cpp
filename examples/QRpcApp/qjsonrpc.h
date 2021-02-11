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
