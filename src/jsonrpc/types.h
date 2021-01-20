#pragma once

#include <string>
#include <stdlib.h>
#include <stdio.h>
#include "nlohmann/json.hpp"

using json = nlohmann::json;

using namespace std;

typedef unsigned long long Id;
typedef json::object_t Params;


enum class MessageFormat : int
{
    JSON = 1,
    BSON = 2,
    MSGPACK = 3,
    CBOR = 4,
};

// https://www.jsonrpc.org/specification


class Error {
public:
    int code;
    string message;
};

// handler for call responses
class CallResponseArg {
public:
    Error error;
    json result;
};

typedef std::function<void(CallResponseArg)> CallResponseFunc;


// handler for call requests
class CallRequestArg {
public:
    Params params;
};

typedef std::function<CallResponseArg(CallRequestArg)> CallRequestFunc;


// handler for notify requests
class NotifyRequestArg {
public:
    Params params;
};

typedef std::function<void(NotifyRequestArg)> NotifyRequestFunc;


// handler for error responses
class ErrorResponseArg {
public:
    Error error;
};

typedef std::function<void(ErrorResponseArg)> ErrorResponseFunc;



class IMessageWriter
{
public:
    virtual ~IMessageWriter() {}
    // or vector<uint8_t>?? (byte array>
    virtual void writeMessage(std::string message) = 0;
};


class IMessageHandler
{
public:
    virtual ~IMessageHandler() {}
    // or vector<uint8_t>?? (byte array>
    virtual void handleMessage(std::string message) = 0;
};


class ILogger
{
public:
    virtual ~ILogger() {}
    virtual void info(std::string message) = 0;
    virtual void debug(std::string message) = 0;
    virtual void warning(std::string message) = 0;
    virtual void error(std::string message) = 0;
};


class IRpcProtocolListener
{
public:
    virtual void onNotify(std::string method, Params params) = 0;
};

