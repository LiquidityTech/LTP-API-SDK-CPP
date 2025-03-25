#pragma once
#include "rapdix/model/request/QueryStatementRequest.h"
#include "rapdix/model/response/QueryStatementResponse.h"
#include "rapdix/model/request/QueryTradingStatsRequest.h"
#include "rapdix/model/response/QueryTradingStatsResponse.h"

class StatementService {
public:
    static QueryStatementResponse queryStatement(const QueryStatementRequest& request);
    static QueryTradingStatsResponse queryTradingStats(const QueryTradingStatsRequest& request);
}; 