#pragma once
#include "rapdix/model/request/SetMarginLeverageRequest.h"
#include "rapdix/model/response/SetMarginLeverageResponse.h"
#include "rapdix/model/request/GetMarginLeverageRequest.h"
#include "rapdix/model/response/GetMarginLeverageResponse.h"
#include "rapdix/model/request/GetSymInfoRequest.h"
#include "rapdix/model/response/GetSymInfoResponse.h"
#include "rapdix/model/request/GetFundingRateRequest.h"
#include "rapdix/model/response/GetFundingRateResponse.h"
#include "rapdix/model/request/GetMarkPriceRequest.h"
#include "rapdix/model/response/GetMarkPriceResponse.h"
#include "rapdix/model/response/GetUserFeeRateResponse.h"
#include "rapdix/model/request/GetPositionTierRequest.h"
#include "rapdix/model/response/GetPositionTierResponse.h"
#include "rapdix/model/request/GetLoanTierRequest.h"
#include "rapdix/model/response/GetLoanTierResponse.h"
#include "rapdix/model/request/GetDiscountRateRequest.h"
#include "rapdix/model/response/GetDiscountRateResponse.h"
#include "rapdix/model/request/GetUserInterestRequest.h"
#include "rapdix/model/response/GetUserInterestResponse.h"

class RulesService {
public:
    static SetMarginLeverageResponse setMarginLeverage(const SetMarginLeverageRequest& request);
    static GetMarginLeverageResponse getMarginLeverage(const GetMarginLeverageRequest& request);
    static GetSymInfoResponse getSymInfo(const GetSymInfoRequest& request);
    static GetFundingRateResponse getFundingRate(const GetFundingRateRequest& request);
    static GetMarkPriceResponse getMarkPrice(const GetMarkPriceRequest& request);
    static GetUserFeeRateResponse getUserFeeRate();
    static GetPositionTierResponse getPositionTier(const GetPositionTierRequest& request);
    static GetLoanTierResponse getLoanTier(const GetLoanTierRequest& request);
    static GetDiscountRateResponse getDiscountRate(const GetDiscountRateRequest& request);
    static GetUserInterestResponse getUserInterest(const GetUserInterestRequest& request);
}; 