#pragma once


#include "types.h"


class JsonRpc
{
public:
    JsonRpc();
    static json callMessage(Id id, string method, Params params);
    static json resultMessage(Id callId, string method, json result);
    static json notifyMessage(string method, Params params);
    static json errorMessage(Id callId, int code, string message);

};

