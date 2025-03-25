#include "BrokerService.h"
#include "rapdix/util/HttpClient.h"
#include "rapdix/constants/RapidxAPIConstants.h"
#include <iostream>

GetBrokerPositionTierResponse BrokerService::getPositionTier(const GetBrokerPositionTierRequest& request) {
    try {
        return HttpClient::getInstance().doGet<GetBrokerPositionTierResponse>(
            RapidxAPIConstants::BROKER_POSITION_TIER,
            request.toJsonString()
        );
    } catch (const std::exception& e) {
        std::cerr << "getPositionTier error: " << e.what() << std::endl;
        throw;
    }
}

SetSubPortfolioFeeRateResponse BrokerService::setSubPortfolioFeeRate(const SetSubPortfolioFeeRateRequest& request) {
    try {
        return HttpClient::getInstance().doPost<SetSubPortfolioFeeRateResponse>(
            RapidxAPIConstants::SUB_PORTFOLIO_FEE_RATE,
            request.toJsonString()
        );
    } catch (const std::exception& e) {
        std::cerr << "setSubPortfolioFeeRate error: " << e.what() << std::endl;
        throw;
    }
}

GetFeeRateResponse BrokerService::getFeeRate(const GetFeeRateRequest& request) {
    try {
        return HttpClient::getInstance().doGet<GetFeeRateResponse>(
            RapidxAPIConstants::BROKER_FEE_RATE,
            request.toJsonString()
        );
    } catch (const std::exception& e) {
        std::cerr << "getFeeRate error: " << e.what() << std::endl;
        throw;
    }
}

GetSubFeeRateResponse BrokerService::getSubFeeRate(const GetSubFeeRateRequest& request) {
    try {
        return HttpClient::getInstance().doGet<GetSubFeeRateResponse>(
            RapidxAPIConstants::SUB_FEE_RATE,
            request.toJsonString()
        );
    } catch (const std::exception& e) {
        std::cerr << "getSubFeeRate error: " << e.what() << std::endl;
        throw;
    }
}

GetClearingStatementResponse BrokerService::getClearingStatement(const GetClearingStatementRequest& request) {
    try {
        return HttpClient::getInstance().doGet<GetClearingStatementResponse>(
            RapidxAPIConstants::CLEARING_STATEMENT,
            request.toJsonString()
        );
    } catch (const std::exception& e) {
        std::cerr << "getClearingStatement error: " << e.what() << std::endl;
        throw;
    }
}

GetCollectionRecordResponse BrokerService::getCollectionRecord(const GetCollectionRecordRequest& request) {
    try {
        return HttpClient::getInstance().doGet<GetCollectionRecordResponse>(
            RapidxAPIConstants::COLLECTION_RECORD,
            request.toJsonString()
        );
    } catch (const std::exception& e) {
        std::cerr << "getCollectionRecord error: " << e.what() << std::endl;
        throw;
    }
} 