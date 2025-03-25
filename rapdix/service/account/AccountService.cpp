#include "AccountService.h"
#include "rapdix/util/HttpClient.h"
#include "rapdix/constants/RapidxAPIConstants.h"
#include <iostream>

ChangePositionModeResponse AccountService::changePositionMode(const ChangePositionModeRequest& request) {
    try {
        std::cout << "Sending request: " << request.toJsonString() << std::endl;
        return HttpClient::getInstance().doPost<ChangePositionModeResponse>(
            RapidxAPIConstants::ACCOUNT,
            request.toJsonString()
        );
    } catch (const std::exception& e) {
        std::cerr << "changePositionMode error: " << e.what() << std::endl;
        throw;
    }
}

QueryAccountResponse AccountService::queryAccount() {
    try {
        return HttpClient::getInstance().doGet<QueryAccountResponse>(
            RapidxAPIConstants::ACCOUNT,
            "{}"  
        );
    } catch (const std::exception& e) {
        std::cerr << "queryAccount error: " << e.what() << std::endl;
        throw;
    }
} 