#include "jsonrpc.h"

using json = nlohmann::json;

JsonRpc::JsonRpc()
{
}

json JsonRpc::callMessage(Id id, string method, Params params)
{
    json j;
    j["jsonrpc"] = "2.0";
    j["id"] = id;
    j["method"] = method;
    j["params"] = params;
    return j;
}

json JsonRpc::resultMessage(Id callId, string method, json result)
{
    json j;
    j["jsonrpc"] = "2.0";
    j["id"] = callId;
    j["result"] = result;
    return j;
}

json JsonRpc::notifyMessage(string method, Params params)
{
    json j;
    j["jsonrpc"] = "2.0";
    j["method"] = method;
    j["params"] = params;
    return j;
}

json JsonRpc::errorMessage(Id id, int code, string message)
{
    json err;
    err["code"] = code;
    err["message"] = message;

    json j;
    j["jsonrpc"] = "2.0";
    if (id)
    {
        j["id"] = id;
    }
    j["error"] = err;
    return j;
}
