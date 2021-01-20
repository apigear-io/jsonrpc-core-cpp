#pragma once

#include "jsonrpc.h"
#include "types.h"
#include <map>

class RpcProtocol : public IMessageHandler
{
public:
    RpcProtocol(IRpcProtocolListener *m_listener, IMessageWriter *writer, ILogger *log, MessageFormat format);
    void doCall(string method, Params params, CallResponseFunc& func);
    void doNotify(string method, Params params);
    void onCall(string method, CallRequestFunc &func);
    void onNotify(string method, NotifyRequestFunc &func);
    void onError(ErrorResponseFunc &func);

    json fromMessage(string message);
    string toMessage(json j);
    void writeJson(json j);
    // IMessageHandler interface
public:
    Id nextId();
    void handleMessage(string message) override;
    void handleCallRequest(Id id, std::string method, Params params);
    void handleCallResult(Id id, json result);
    void handleNotifyRequest(std::string method, Params params);
    void handleError(Id id, int code, std::string error);
private:
    IRpcProtocolListener *m_listener;
    IMessageWriter *m_writer;
    ILogger* m_log;
    MessageFormat m_format;
    Id m_nextId;
    std::map<Id, CallResponseFunc> m_callsPending;
    std::map<std::string, CallRequestFunc> m_callRegistry;
    std::map<std::string, NotifyRequestFunc> m_notifyRegistry;
    ErrorResponseFunc m_errorHandler;
};

