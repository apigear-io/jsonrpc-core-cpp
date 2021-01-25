#pragma once

#include "types.h"

#include <string>

namespace ApiGear { namespace JSONRPC {

class StdoutLogger : public ILogger {
public:
//    StdoutLogger();
//    virtual ~StdoutLogger() override;
    void info(std::string message) override;
    void debug(std::string message) override;
    void warning(std::string message) override;
    void error(std::string message) override;
};
}} // ApiGear // JSONRPC
