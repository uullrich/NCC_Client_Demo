#include "ClientDemo.h"

#include <iostream>

#include "ResponseHandler.h"
#include "Response.h"
#include "CommandSender.h"

ClientDemo::ClientDemo(const std::string &ip, unsigned short port) {
    initResponseInterface();

    ResponseHandler responseHandler{_responseInterface};
    _commandConnector = std::make_unique<CommandConnector>(ip, port, responseHandler,
                                                           [&](const std::shared_ptr<CommandSender> &commandSender) {
                                                               connectionEstablished(commandSender);
                                                           });
}

void ClientDemo::initResponseInterface() {
    _responseInterface
            << (ResponseExecutionInterface(this) << Path{"test"}
                                                 << &ClientDemo::setTestResponse
                                                 << &ClientDemo::getTestResponse
                                                 << &ClientDemo::setDataTestResponse
                                                 << &ClientDemo::getDataTestResponse
                                                 << &ClientDemo::errorTestResponse);
}

void ClientDemo::connectionEstablished(const std::shared_ptr<CommandSender> &commandSender) {
    std::cout << "Connection established handler called" << std::endl;

    _commandSender = commandSender;

    commandSender->get("test");

    commandSender->getData("test");

    commandSender->setData("test", "Hallo Welt!");

    commandSender->set("test", "1");
}

void ClientDemo::setTestResponse(Response &response) {
    std::cout << "SET Test response received" << std::endl;

    //Trigger another command
    _commandSender->get("test");
}

void ClientDemo::getTestResponse(Response &response) {
    std::cout << "GET Test response received with value: "
              << response.value << std::endl;
}

void ClientDemo::setDataTestResponse(Response &response) {
    std::cout
            << "SET-DATA Test response received" << std::endl;
}

void ClientDemo::getDataTestResponse(Response &response) {
    std::string payload(response.data.begin(),
                        response.data.end());
    std::cout
            << "GET-DATA Test response received with payload: "
            << payload << std::endl;
}

void ClientDemo::errorTestResponse(Response &response) {
    std::string payload(response.data.begin(),
                        response.data.end());
    std::cout
            << "Error Test response received with error payload: "
            << payload << std::endl;
}