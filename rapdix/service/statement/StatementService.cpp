#include "StatementService.h"
#include "rapdix/util/HttpClient.h"
#include "rapdix/constants/RapidxAPIConstants.h"
#include <iostream>

QueryStatementResponse StatementService::queryStatement(const QueryStatementRequest& request) {
    try {
        return HttpClient::getInstance().doGet<QueryStatementResponse>(
            RapidxAPIConstants::STATEMENT,
            request.toJsonString()
        );
    } catch (const std::exception& e) {
        std::cerr << "queryStatement error: " << e.what() << std::endl;
        throw;
    }
}

QueryTradingStatsResponse StatementService::queryTradingStats(const QueryTradingStatsRequest& request) {
    try {
        return HttpClient::getInstance().doGet<QueryTradingStatsResponse>(
            RapidxAPIConstants::USER_TRADING_STATS,
            request.toJsonString()
        );
    } catch (const std::exception& e) {
        std::cerr << "queryTradingStats error: " << e.what() << std::endl;
        throw;
    }
} 