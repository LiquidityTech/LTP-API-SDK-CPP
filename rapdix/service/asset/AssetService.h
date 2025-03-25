#pragma once
#include "rapdix/model/request/QueryPortfolioFundsHistoryRequest.h"
#include "rapdix/model/response/QueryPortfolioFundsHistoryResponse.h"
#include "rapdix/model/request/QueryPortfolioAssetsRequest.h"
#include "rapdix/model/response/QueryPortfolioAssetsResponse.h"
#include "rapdix/model/response/QueryAllPortfolioAssetsResponse.h"

class AssetService {
public:
    static QueryPortfolioFundsHistoryResponse queryPortfolioFundsHistory(
        const QueryPortfolioFundsHistoryRequest& request);
        
    static QueryPortfolioAssetsResponse queryPortfolioAssets(
        const QueryPortfolioAssetsRequest& request);
        
    static QueryAllPortfolioAssetsResponse queryAllPortfolioAssets();
}; 