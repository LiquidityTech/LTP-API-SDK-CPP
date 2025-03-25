#include "RulesService.h"
#include "rapdix/util/HttpClient.h"
#include "rapdix/constants/RapidxAPIConstants.h"
#include <iostream>

SetMarginLeverageResponse RulesService::setMarginLeverage(const SetMarginLeverageRequest& request) {
    try {
        return HttpClient::getInstance().doPost<SetMarginLeverageResponse>(
            RapidxAPIConstants::MARGIN_LEVERAGE,
            request.toJsonString()
        );
    } catch (const std::exception& e) {
        std::cerr << "setMarginLeverage error: " << e.what() << std::endl;
        throw;
    }
}

GetMarginLeverageResponse RulesService::getMarginLeverage(const GetMarginLeverageRequest& request) {
    try {
        return HttpClient::getInstance().doGet<GetMarginLeverageResponse>(
            RapidxAPIConstants::MARGIN_LEVERAGE,
            request.toJsonString()
        );
    } catch (const std::exception& e) {
        std::cerr << "getMarginLeverage error: " << e.what() << std::endl;
        throw;
    }
}

GetSymInfoResponse RulesService::getSymInfo(const GetSymInfoRequest& request) {
    try {
        return HttpClient::getInstance().doGet<GetSymInfoResponse>(
            RapidxAPIConstants::SYM_INFO,
            request.toJsonString()
        );
    } catch (const std::exception& e) {
        std::cerr << "getSymInfo error: " << e.what() << std::endl;
        throw;
    }
}

GetFundingRateResponse RulesService::getFundingRate(const GetFundingRateRequest& request) {
    try {
        return HttpClient::getInstance().doGet<GetFundingRateResponse>(
            RapidxAPIConstants::FUNDING_RATE,
            request.toJsonString()
        );
    } catch (const std::exception& e) {
        std::cerr << "getFundingRate error: " << e.what() << std::endl;
        throw;
    }
}

GetMarkPriceResponse RulesService::getMarkPrice(const GetMarkPriceRequest& request) {
    try {
        return HttpClient::getInstance().doGet<GetMarkPriceResponse>(
            RapidxAPIConstants::MARK_PRICE,
            request.toJsonString()
        );
    } catch (const std::exception& e) {
        std::cerr << "getMarkPrice error: " << e.what() << std::endl;
        throw;
    }
}

GetUserFeeRateResponse RulesService::getUserFeeRate() {
    try {
        return HttpClient::getInstance().doGet<GetUserFeeRateResponse>(
            RapidxAPIConstants::USER_FEE_RATE,
            "{}"  
        );
    } catch (const std::exception& e) {
        std::cerr << "getUserFeeRate error: " << e.what() << std::endl;
        throw;
    }
}

GetPositionTierResponse RulesService::getPositionTier(const GetPositionTierRequest& request) {
    try {
        return HttpClient::getInstance().doGet<GetPositionTierResponse>(
            RapidxAPIConstants::POSITION_TIER,
            request.toJsonString()
        );
    } catch (const std::exception& e) {
        std::cerr << "getPositionTier error: " << e.what() << std::endl;
        throw;
    }
}

GetLoanTierResponse RulesService::getLoanTier(const GetLoanTierRequest& request) {
    try {
        return HttpClient::getInstance().doGet<GetLoanTierResponse>(
            RapidxAPIConstants::LOAN_TIER,
            request.toJsonString()
        );
    } catch (const std::exception& e) {
        std::cerr << "getLoanTier error: " << e.what() << std::endl;
        throw;
    }
}

GetDiscountRateResponse RulesService::getDiscountRate(const GetDiscountRateRequest& request) {
    try {
        return HttpClient::getInstance().doGet<GetDiscountRateResponse>(
            RapidxAPIConstants::DISCOUNT_RATE,
            request.toJsonString()
        );
    } catch (const std::exception& e) {
        std::cerr << "getDiscountRate error: " << e.what() << std::endl;
        throw;
    }
}

GetUserInterestResponse RulesService::getUserInterest(const GetUserInterestRequest& request) {
    try {
        return HttpClient::getInstance().doGet<GetUserInterestResponse>(
            RapidxAPIConstants::USER_INTEREST,
            request.toJsonString()
        );
    } catch (const std::exception& e) {
        std::cerr << "getUserInterest error: " << e.what() << std::endl;
        throw;
    }
} 