#ifndef CLIENT_DEMO_H
#define CLIENT_DEMO_H

#include "../include/CommandConnector.h"
#include "../include/ResponseExecutionInterface.h"

#include <memory>
#include <string>

class CommandSender;
class Response;

class ClientDemo {
public:
    explicit ClientDemo(const std::string &ip, unsigned short port);

private:
    void initResponseInterface();
    void connectionEstablished(const std::shared_ptr<CommandSender> &commandSender);

    void setTestResponse(Response &response);
    void getTestResponse(Response &response);
    void setDataTestResponse(Response &response);
    void getDataTestResponse(Response &response);
    void errorTestResponse(Response &response);

    std::vector<ResponseExecutionInterface> _responseInterface;
    std::unique_ptr<CommandConnector> _commandConnector;
    std::shared_ptr<CommandSender> _commandSender;
};

#endif
