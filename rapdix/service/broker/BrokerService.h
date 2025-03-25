#pragma once
#include "rapdix/model/request/GetBrokerPositionTierRequest.h"
#include "rapdix/model/response/GetBrokerPositionTierResponse.h"
#include "rapdix/model/request/SetSubPortfolioFeeRateRequest.h"
#include "rapdix/model/response/SetSubPortfolioFeeRateResponse.h"
#include "rapdix/model/request/GetFeeRateRequest.h"
#include "rapdix/model/response/GetFeeRateResponse.h"
#include "rapdix/model/request/GetSubFeeRateRequest.h"
#include "rapdix/model/response/GetSubFeeRateResponse.h"
#include "rapdix/model/request/GetClearingStatementRequest.h"
#include "rapdix/model/response/GetClearingStatementResponse.h"
#include "rapdix/model/request/GetCollectionRecordRequest.h"
#include "rapdix/model/response/GetCollectionRecordResponse.h"

class BrokerService {
public:
    static GetBrokerPositionTierResponse getPositionTier(const GetBrokerPositionTierRequest& request);
    static SetSubPortfolioFeeRateResponse setSubPortfolioFeeRate(const SetSubPortfolioFeeRateRequest& request);
    static GetFeeRateResponse getFeeRate(const GetFeeRateRequest& request);
    static GetSubFeeRateResponse getSubFeeRate(const GetSubFeeRateRequest& request);
    static GetClearingStatementResponse getClearingStatement(const GetClearingStatementRequest& request);
    static GetCollectionRecordResponse getCollectionRecord(const GetCollectionRecordRequest& request);
}; 