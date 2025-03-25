#include "AssetService.h"
#include "rapdix/util/HttpClient.h"
#include "rapdix/constants/RapidxAPIConstants.h"
#include <iostream>

QueryPortfolioFundsHistoryResponse AssetService::queryPortfolioFundsHistory(
    const QueryPortfolioFundsHistoryRequest& request) {
    try {
        return HttpClient::getInstance().doGet<QueryPortfolioFundsHistoryResponse>(
            RapidxAPIConstants::ASSET_PORTFOLIO_FUNDS_HISTORY,
            request.toJsonString()
        );
    } catch (const std::exception& e) {
        std::cerr << "queryPortfolioFundsHistory error: " << e.what() << std::endl;
        throw;
    }
}

QueryPortfolioAssetsResponse AssetService::queryPortfolioAssets(
    const QueryPortfolioAssetsRequest& request) {
    try {
        return HttpClient::getInstance().doGet<QueryPortfolioAssetsResponse>(
            RapidxAPIConstants::ASSET_PORTFOLIO_ASSETS,
            request.toJsonString()
        );
    } catch (const std::exception& e) {
        std::cerr << "queryPortfolioAssets error: " << e.what() << std::endl;
        throw;
    }
}

QueryAllPortfolioAssetsResponse AssetService::queryAllPortfolioAssets() {
    try {
        return HttpClient::getInstance().doGet<QueryAllPortfolioAssetsResponse>(
            RapidxAPIConstants::ASSET_ALL_PORTFOLIO,
            "{}"  
        );
    } catch (const std::exception& e) {
        std::cerr << "queryAllPortfolioAssets error: " << e.what() << std::endl;
        throw;
    }
} 