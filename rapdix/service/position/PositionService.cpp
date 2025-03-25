#include "PositionService.h"
#include "rapdix/util/HttpClient.h"
#include "rapdix/constants/RapidxAPIConstants.h"
#include <iostream>

SetLeverageResponse PositionService::setLeverage(const SetLeverageRequest& request) {
    try {
        return HttpClient::getInstance().doPost<SetLeverageResponse>(
            RapidxAPIConstants::LEVERAGE_SET,
            request.toJsonString()
        );
    } catch (const std::exception& e) {
        std::cerr << "setLeverage error: " << e.what() << std::endl;
        throw;
    }
}

GetLeverageResponse PositionService::getLeverage(const GetLeverageRequest& request) {
    try {
        return HttpClient::getInstance().doGet<GetLeverageResponse>(
            RapidxAPIConstants::LEVERAGE_GET,
            request.toJsonString()
        );
    } catch (const std::exception& e) {
        std::cerr << "getLeverage error: " << e.what() << std::endl;
        throw;
    }
}

ClosePositionResponse PositionService::closePosition(const ClosePositionRequest& request) {
    try {
        return HttpClient::getInstance().doDelete<ClosePositionResponse>(
            RapidxAPIConstants::POSITION,
            request.toJsonString()
        );
    } catch (const std::exception& e) {
        std::cerr << "closePosition error: " << e.what() << std::endl;
        throw;
    }
}

ClosePositionsResponse PositionService::closePositions(const ClosePositionsRequest& request) {
    try {
        return HttpClient::getInstance().doDelete<ClosePositionsResponse>(
            RapidxAPIConstants::POSITIONS,
            request.toJsonString()
        );
    } catch (const std::exception& e) {
        std::cerr << "closePositions error: " << e.what() << std::endl;
        throw;
    }
}

QueryPositionResponse PositionService::queryPosition(const QueryPositionRequest& request) {
    try {
        return HttpClient::getInstance().doGet<QueryPositionResponse>(
            RapidxAPIConstants::POSITION,
            request.toJsonString()
        );
    } catch (const std::exception& e) {
        std::cerr << "queryPosition error: " << e.what() << std::endl;
        throw;
    }
}

QueryHistoryPositionResponse PositionService::queryHistoryPosition(const QueryHistoryPositionRequest& request) {
    try {
        return HttpClient::getInstance().doGet<QueryHistoryPositionResponse>(
            RapidxAPIConstants::POSITIONS_HISTORY,
            request.toJsonString()
        );
    } catch (const std::exception& e) {
        std::cerr << "queryHistoryPosition error: " << e.what() << std::endl;
        throw;
    }
} 