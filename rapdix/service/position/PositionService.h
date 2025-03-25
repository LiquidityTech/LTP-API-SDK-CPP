#pragma once
#include "rapdix/model/request/SetLeverageRequest.h"
#include "rapdix/model/response/SetLeverageResponse.h"
#include "rapdix/model/request/GetLeverageRequest.h"
#include "rapdix/model/response/GetLeverageResponse.h"
#include "rapdix/model/request/ClosePositionRequest.h"
#include "rapdix/model/response/ClosePositionResponse.h"
#include "rapdix/model/request/ClosePositionsRequest.h"
#include "rapdix/model/response/ClosePositionsResponse.h"
#include "rapdix/model/request/QueryPositionRequest.h"
#include "rapdix/model/response/QueryPositionResponse.h"
#include "rapdix/model/request/QueryHistoryPositionRequest.h"
#include "rapdix/model/response/QueryHistoryPositionResponse.h"

class PositionService {
public:
    static SetLeverageResponse setLeverage(const SetLeverageRequest& request);
    static GetLeverageResponse getLeverage(const GetLeverageRequest& request);
    static ClosePositionResponse closePosition(const ClosePositionRequest& request);
    static ClosePositionsResponse closePositions(const ClosePositionsRequest& request);
    static QueryPositionResponse queryPosition(const QueryPositionRequest& request);
    static QueryHistoryPositionResponse queryHistoryPosition(const QueryHistoryPositionRequest& request);
}; 