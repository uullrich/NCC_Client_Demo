#include "../include/CommandConnector.h"
#include "../include/CommandSender.h"
#include "../include/ResponseExecutionInterface.h"
#include "../include/Response.h"
#include "../include/ResponseHandler.h"

#include <iostream>

int main() {
    auto connectionEstablishedHandler = [](const std::shared_ptr<CommandSender> &commandSender) {
        printf("Connection established handler called\n");
        commandSender->get("test");

        commandSender->getData("test");

        commandSender->setData("test", "Hallo Welt!");

        commandSender->set("test", "1");
    };

    std::vector<ResponseExecutionInterface> execIf{{
                                                           {"test"},
                                                           [](Response &response) {
                                                               std::cout << "SET Test response received" << std::endl;
                                                           },
                                                           [](Response &response) {
                                                               std::cout << "GET Test response received with value: "
                                                                         << response.value << std::endl;
                                                           },
                                                           [](Response &response) {
                                                               std::cout
                                                                       << "SET-DATA Test response received"
                                                                       << std::endl;
                                                           },
                                                           [](Response &response) {
                                                               std::string payload(response.data.begin(),
                                                                                   response.data.end());
                                                               std::cout
                                                                       << "GET-DATA Test response received with payload: "
                                                                       << payload << std::endl;
                                                           },
                                                           [](Response &response) {
                                                               std::string payload(response.data.begin(),
                                                                                   response.data.end());
                                                               std::cout
                                                                       << "Error Test response received with error payload: "
                                                                       << payload << std::endl;
                                                           }
                                                   }
    };

    ResponseHandler responseHandler{execIf};
    CommandConnector cc{"127.0.0.1", 33344, responseHandler, connectionEstablishedHandler};
}