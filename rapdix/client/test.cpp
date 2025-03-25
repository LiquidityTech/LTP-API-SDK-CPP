#include "../service/order/OrderService.h"
#include "../service/account/AccountService.h"
#include "../service/asset/AssetService.h"
#include "../service/position/PositionService.h"
#include "../service/transaction/TransactionService.h"
#include "../service/statement/StatementService.h"
#include "../service/rules/RulesService.h"
#include "../service/broker/BrokerService.h"
#include <iostream>
#include <ctime>

void testPlaceOrder() {
    std::cout << "Testing placeOrder..." << std::endl;
    
    auto request = PlaceOrderRequest::builder()
        .sym("BINANCE_PERP_BTC_USDT")
        .side("BUY")
        .orderType("LIMIT")
        .orderQty("1")
        .limitPrice("110")
        .build();
    
    PlaceOrderResponse response = OrderService::placeOrder(request);
}

void testReplaceOrder() {
    std::cout << "Testing replaceOrder..." << std::endl;
    
    auto request = ReplaceOrderRequest::builder()
        .orderId("2009123201750331")
        .replaceQty("0.002")
        .replacePrice("41000")
        .build();
    
    ReplaceOrderResponse response = OrderService::replaceOrder(request);
    std::cout << "Response: " << response << std::endl;
}

void testCancelOrder() {
    std::cout << "Testing cancelOrder..." << std::endl;
    
    auto request = CancelOrderRequest::builder()
        .orderId("2009173327879491")  // Replace with actual order ID
        //.clientOrderId("your_client_order_id")  // Or use client order ID
        .build();
    
    CancelOrderResponse response = OrderService::cancelOrder(request);
    std::cout << "Response: " << response << std::endl;
}

void testQueryOrder() {
    std::cout << "Testing queryOrder..." << std::endl;
    
    auto request = QueryOrderRequest::builder()
        .orderId("2009129149278787")  // Replace with actual order ID
        //.clientOrderId("your_client_order_id")  // Or use client order ID
        .build();
    
    QueryOrderResponse response = OrderService::queryOrder(request);
    std::cout << "Response: " << response << std::endl;
}

void testQueryOpenOrders() {
    std::cout << "Testing queryOpenOrders..." << std::endl;
    
    auto request = QueryOpenOrdersRequest::builder()
        // .sym("BINANCE_PERP_BTC_USDT")  // Optional
        // .exchangeType("BINANCE")        // Optional
        .build();
    
    QueryOpenOrdersResponse response = OrderService::queryOpenOrders(request);
    std::cout << "Response: " << response << std::endl;
}

void testQueryHistoryOrders() {
    std::cout << "Testing queryHistoryOrders..." << std::endl;
    
    auto request = QueryHistoryOrdersRequest::builder()
        .sym("BINANCE_PERP_BTC_USDT")
        //.exchange("BINANCE")
        //.businessType("PERP")
        //.begin("1641004800000")  // 2022-01-01 00:00:00
        //.end("1641091199999")    // 2022-01-01 23:59:59
        //.filterExecuted(true)
        //.page("1")
        //.pageSize("10")
        .build();
    
    QueryHistoryOrdersResponse response = OrderService::queryHistoryOrders(request);
    std::cout << "Response: " << response << std::endl;
}

void testQueryHistoryOrdersArchive() {
    std::cout << "Testing queryHistoryOrdersArchive..." << std::endl;
    
    auto request = QueryHistoryOrdersArchiveRequest::builder()
        .sym("BINANCE_PERP_BTC_USDT")
        //.exchange("BINANCE")
        //.businessType("PERP")
        //.begin("1641004800000")  // 2022-01-01 00:00:00
        //.end("1641091199999")    // 2022-01-01 23:59:59
        //.filterExecuted(true)
        //.page("1")
        //.pageSize("10")
        .build();
    
    QueryHistoryOrdersResponse response = OrderService::queryHistoryOrdersArchive(request);
    std::cout << "Response: " << response << std::endl;
}

void testCancelAllOrders() {
    std::cout << "Testing cancelAllOrders..." << std::endl;
    
    auto request = CancelAllOrdersRequest::builder()
        // .sym("BINANCE_PERP_BTC_USDT")  // Optional
        // .exchangeType("BINANCE")        // Optional
        .build();
    
    CancelAllOrdersResponse response = OrderService::cancelAllOrders(request);
    std::cout << "Response: " << response << std::endl;
}

void testChangePositionMode() {
    std::cout << "Testing changePositionMode..." << std::endl;
    
    auto request = ChangePositionModeRequest::builder()
        .exchangeType("BINANCE")
        .positionMode("NET")  // Or "BOTH"
        .build();
    
    ChangePositionModeResponse response = AccountService::changePositionMode(request);
    std::cout << "Response: " << response << std::endl;
}

void testQueryAccount() {
    std::cout << "Testing queryAccount..." << std::endl;
    
    QueryAccountResponse response = AccountService::queryAccount();
    std::cout << "Response: " << response << std::endl;
}

void testQueryPortfolioFundsHistory() {
    std::cout << "Testing queryPortfolioFundsHistory..." << std::endl;
    
    auto request = QueryPortfolioFundsHistoryRequest::builder()
        //.currency("USDT")
        //.type("1")  // 0:deposit 1:transfer 2:withdraw
        //.status("1")  // 0:pending 1:succeed 2:failed
        //.startTime("1641004800000")
        //.endTime("1641091199999")
        //.page("1")
        //.pageSize("10")
        .build();
    
    QueryPortfolioFundsHistoryResponse response = AssetService::queryPortfolioFundsHistory(request);
    std::cout << "Response: " << response << std::endl;
}

void testQueryPortfolioAssets() {
    std::cout << "Testing queryPortfolioAssets..." << std::endl;
    
    auto request = QueryPortfolioAssetsRequest::builder()
        //.exchangeType("BINANCE")
        //.pageNum("1")
        //.pageSize("10")
        .build();
    
    QueryPortfolioAssetsResponse response = AssetService::queryPortfolioAssets(request);
    std::cout << "Response: " << response << std::endl;
}

void testQueryAllPortfolioAssets() {
    std::cout << "Testing queryAllPortfolioAssets..." << std::endl;
    
    QueryAllPortfolioAssetsResponse response = AssetService::queryAllPortfolioAssets();
    std::cout << "Response: " << response << std::endl;
}

void testSetLeverage() {
    std::cout << "Testing setLeverage..." << std::endl;
    
    auto request = SetLeverageRequest::builder()
        .leverage("10")  // Set leverage to 10x
        .sym("BINANCE_PERP_BTC_USDT")  // Set trading pair
        .build();
    
    SetLeverageResponse response = PositionService::setLeverage(request);
    std::cout << "Response: " << response << std::endl;
}

void testGetLeverage() {
    std::cout << "Testing getLeverage..." << std::endl;
    
    auto request = GetLeverageRequest::builder()
        .sym("BINANCE_PERP_BTC_USDT")  // Optional, returns all pairs' leverage if not specified
        .build();
    
    GetLeverageResponse response = PositionService::getLeverage(request);
    std::cout << "Response: " << response << std::endl;
}

void testClosePosition() {
    std::cout << "Testing closePosition..." << std::endl;
    
    auto request = ClosePositionRequest::builder()
        .sym("BINANCE_PERP_BTC_USDT")
        //.positionSide("LONG")  // Required for hedge mode
        .build();
    
    ClosePositionResponse response = PositionService::closePosition(request);
    std::cout << "Response: " << response << std::endl;
}

void testClosePositions() {
    std::cout << "Testing closePositions..." << std::endl;
    
    auto request = ClosePositionsRequest::builder()
        .symList("BINANCE_PERP_BTC_USDT,BINANCE_PERP_ETH_USDT")  // Optional, comma-separated pairs
        //.positionSide("NONE")  // Optional, NONE/LONG/SHORT
        //.closeAllPos("true")   // Optional, default false
        .build();
    
    ClosePositionsResponse response = PositionService::closePositions(request);
    std::cout << "Response: " << response << std::endl;
}

void testQueryPosition() {
    std::cout << "Testing queryPosition..." << std::endl;
    
    auto request = QueryPositionRequest::builder()
        .sym("BINANCE_PERP_BTC_USDT")  // Optional, returns all positions
        .build();
    
    QueryPositionResponse response = PositionService::queryPosition(request);
    std::cout << "Response: " << response << std::endl;
}

void testQueryHistoryPosition() {
    std::cout << "Testing queryHistoryPosition..." << std::endl;
    
    auto request = QueryHistoryPositionRequest::builder()
        .sym("BINANCE_PERP_BTC_USDT")  // Optional
        //.exchange("BINANCE")          // Optional
        //.begin("1641004800000")       // Optional, default query 90 days ago
        //.end("1641091199999")         // Optional
        //.page("1")                    // Optional, default 1
        //.pageSize("10")               // Optional, default 1000, max 1000
        .build();
    
    QueryHistoryPositionResponse response = PositionService::queryHistoryPosition(request);
    std::cout << "Response: " << response << std::endl;
}

void testQueryTransactions() {
    std::cout << "Testing queryTransactions..." << std::endl;
    
    auto request = QueryTransactionsRequest::builder()
        //.orderId("123456")           // Optional
        .sym("BINANCE_PERP_BTC_USDT")  // Optional
        //.begin("1641004800000")      // Optional, default query 7 days ago
        //.end("1641091199999")        // Optional
        //.limit("100")                // Optional, default 1000, max 1000
        .build();
    
    QueryTransactionsResponse response = TransactionService::queryTransactions(request);
    std::cout << "Response: " << response << std::endl;
}

void testQueryTransactionsPageable() {
    std::cout << "Testing queryTransactionsPageable..." << std::endl;
    
    auto request = QueryTransactionsPageableRequest::builder()
        //.orderId("123456")           // Optional
        .sym("BINANCE_PERP_BTC_USDT")  // Optional
        //.begin("1641004800000")      // Optional, default query 90 days ago
        //.end("1641091199999")        // Optional
        //.page("1")                   // Optional, default 1
        //.pageSize("10")              // Optional, default 1000, max 1000
        .build();
    
    QueryTransactionsPageableResponse response = TransactionService::queryTransactionsPageable(request);
    std::cout << "Response: " << response << std::endl;
}

void testQueryArchivedTransactions() {
    std::cout << "Testing queryArchivedTransactions..." << std::endl;
    
    auto request = QueryArchivedTransactionsRequest::builder()
        //.orderId("123456")           // Optional
        .sym("BINANCE_PERP_BTC_USDT")  // Optional
        //.begin("1641004800000")      // Optional, default query 90 days ago
        //.end("1641091199999")        // Optional
        //.page("1")                   // Optional, default 1
        //.pageSize("10")              // Optional, default 1000, max 1000
        .build();
    
    QueryArchivedTransactionsResponse response = TransactionService::queryArchivedTransactions(request);
    std::cout << "Response: " << response << std::endl;
}

void testQueryStatement() {
    std::cout << "Testing queryStatement..." << std::endl;
    
    auto request = QueryStatementRequest::builder()
        //.coin("USDT")                  // Optional
        .sym("BINANCE_PERP_BTC_USDT")    // Optional
        //.statementType("FUNDING_FEE")  // Optional, FUNDING_FEE/DEDUCT_INTEREST/LIQUIDATION_FEE
        //.exchange("BINANCE")           // Optional
        //.startTime("1641004800000")    // Optional, default 7 days ago
        //.endTime("1641091199999")      // Optional, default now
        //.page("1")                     // Optional, default 1
        //.pageSize("10")                // Optional, default 1000, max 1000
        .build();
    
    QueryStatementResponse response = StatementService::queryStatement(request);
    std::cout << "Response: " << response << std::endl;
}

void testQueryTradingStats() {
    std::cout << "Testing queryTradingStats..." << std::endl;
    
    // Get current time (seconds)
    auto now = std::time(nullptr);
    auto thirtyDaysAgo = now - (1 * 24 * 60 * 60);  // 30 days ago (seconds)
    
    auto request = QueryTradingStatsRequest::builder()
        //.exchange("BINANCE")      // Optional
        //.businessType("PERP")     // Optional
        .begin(std::to_string(thirtyDaysAgo))    // 30 days ago (seconds)
        .end(std::to_string(now))                // Now (seconds)
        .build();
    
    QueryTradingStatsResponse response = StatementService::queryTradingStats(request);
    std::cout << "Response: " << response << std::endl;
}

void testSetMarginLeverage() {
    std::cout << "Testing setMarginLeverage..." << std::endl;
    
    auto request = SetMarginLeverageRequest::builder()
        .exchangeType("BINANCE")  // Required
        .coin("BTC")              // Required
        .leverage("5")            // Required
        .build();
    
    SetMarginLeverageResponse response = RulesService::setMarginLeverage(request);
    std::cout << "Response: " << response << std::endl;
}

void testGetMarginLeverage() {
    std::cout << "Testing getMarginLeverage..." << std::endl;
    
    auto request = GetMarginLeverageRequest::builder()
        .exchangeType("BINANCE")  // Optional
        .coin("BTC")              // Optional
        .page("1")                // Optional
        .pageSize("10")           // Optional
        .build();
    
    GetMarginLeverageResponse response = RulesService::getMarginLeverage(request);
    std::cout << "Response: " << response << std::endl;
}

void testGetSymInfo() {
    std::cout << "Testing getSymInfo..." << std::endl;
    
    auto request = GetSymInfoRequest::builder()
        .sym("BINANCE_PERP_BTC_USDT")  // Optional
        .build();
    
    GetSymInfoResponse response = RulesService::getSymInfo(request);
    std::cout << "Response: " << response << std::endl;
}

void testGetFundingRate() {
    std::cout << "Testing getFundingRate..." << std::endl;
    
    auto request = GetFundingRateRequest::builder()
        .sym("BINANCE_PERP_BTC_USDT")  // Required
        .build();
    
    GetFundingRateResponse response = RulesService::getFundingRate(request);
    std::cout << "Response: " << response << std::endl;
}

void testGetMarkPrice() {
    std::cout << "Testing getMarkPrice..." << std::endl;
    
    auto request = GetMarkPriceRequest::builder()
        .sym("BINANCE_PERP_BTC_USDT")  // Optional
        .build();
    
    GetMarkPriceResponse response = RulesService::getMarkPrice(request);
    std::cout << "Response: " << response << std::endl;
}

void testGetUserFeeRate() {
    std::cout << "Testing getUserFeeRate..." << std::endl;
    
    GetUserFeeRateResponse response = RulesService::getUserFeeRate();
    std::cout << "Response: " << response << std::endl;
}

void testGetPositionTier() {
    std::cout << "Testing getPositionTier..." << std::endl;
    
    auto request = GetPositionTierRequest::builder()
        .sym("BINANCE_PERP_BTC_USDT")  // Optional
        .build();
    
    GetPositionTierResponse response = RulesService::getPositionTier(request);
    std::cout << "Response: " << response << std::endl;
}

void testGetLoanTier() {
    std::cout << "Testing getLoanTier..." << std::endl;
    
    auto request = GetLoanTierRequest::builder()
        .exchangeType("BINANCE")  // Optional
        .coin("BTC")              // Optional
        .build();
    
    GetLoanTierResponse response = RulesService::getLoanTier(request);
    std::cout << "Response: " << response << std::endl;
}

void testGetDiscountRate() {
    std::cout << "Testing getDiscountRate..." << std::endl;
    
    auto request = GetDiscountRateRequest::builder()
        .coin("BTC")  // Optional
        .build();
    
    GetDiscountRateResponse response = RulesService::getDiscountRate(request);
    std::cout << "Response: " << response << std::endl;
}

void testGetUserInterest() {
    std::cout << "Testing getUserInterest..." << std::endl;
    
    auto request = GetUserInterestRequest::builder()
        .exchangeType("BINANCE")  // Required
        .build();
    
    GetUserInterestResponse response = RulesService::getUserInterest(request);
    std::cout << "Response: " << response << std::endl;
}

void testGetBrokerPositionTier() {
    std::cout << "Testing getBrokerPositionTier..." << std::endl;
    
    auto request = GetBrokerPositionTierRequest::builder()
        .sym("BINANCE_PERP_BTC_USDT")  // Optional
        .build();
    
    GetBrokerPositionTierResponse response = BrokerService::getPositionTier(request);
    std::cout << "Response: " << response << std::endl;
}

void testSetSubPortfolioFeeRate() {
    std::cout << "Testing setSubPortfolioFeeRate..." << std::endl;
    
    auto request = SetSubPortfolioFeeRateRequest::builder()
        .portfolioId("your_portfolio_id")  // Optional
        .exchange("BINANCE")  // Required
        .instType("SPOT")  // Required
        .chgType("ABSOLUTE")  // Required
        .chgTaker("0.001")  // chgTaker and chgMaker must be filled in
        //.chgMaker("0.0008")
        //.effDate("2024-03-15")  // Optional
        .build();
    
    SetSubPortfolioFeeRateResponse response = BrokerService::setSubPortfolioFeeRate(request);
    std::cout << "Response: " << response << std::endl;
}

void testGetFeeRate() {
    std::cout << "Testing getFeeRate..." << std::endl;
    
    auto request = GetFeeRateRequest::builder()
        .exchange("BINANCE")  // Optional
        .instType("SPOT")     // Optional
        .portfolioIds("portfolio1,portfolio2")  // Optional, up to 20, comma-separated
        .build();
    
    GetFeeRateResponse response = BrokerService::getFeeRate(request);
    std::cout << "Response: " << response << std::endl;
}

void testGetSubFeeRate() {
    std::cout << "Testing getSubFeeRate..." << std::endl;
    
    auto request = GetSubFeeRateRequest::builder()
        .exchange("BINANCE")  // Optional
        .instType("SPOT")     // Optional
        .build();
    
    GetSubFeeRateResponse response = BrokerService::getSubFeeRate(request);
    std::cout << "Response: " << response << std::endl;
}

void testGetClearingStatement() {
    std::cout << "Testing getClearingStatement..." << std::endl;
    
    auto now = std::time(nullptr);
    auto oneDayAgo = now - (24 * 60 * 60); 
    
    auto request = GetClearingStatementRequest::builder()
        .exchange("BINANCE") 
        .instType("SPOT")     
        .coin("BTC")          
        .begin(std::to_string(oneDayAgo))  
        .end(std::to_string(now))          
        .pageNum("1")         
        .pageSize("10")       
        .build();
    
    GetClearingStatementResponse response = BrokerService::getClearingStatement(request);
    std::cout << "Response: " << response << std::endl;
}

void testGetCollectionRecord() {
    std::cout << "Testing getCollectionRecord..." << std::endl;
    
    // Get current time (seconds)
    auto now = std::time(nullptr);
    auto oneDayAgo = now - (24 * 60 * 60);  // 1 day ago
    
    auto request = GetCollectionRecordRequest::builder()
        .exchange("BINANCE")  // Optional
        .instType("SPOT")     // Optional
        .coin("BTC")          // Optional
        .begin(std::to_string(oneDayAgo))  // Optional, default query 1 day ago
        .end(std::to_string(now))          // Optional
        .pageNum("1")         // Optional, default 1
        .pageSize("10")       // Optional, default 1000, max 1000
        .build();
    
    GetCollectionRecordResponse response = BrokerService::getCollectionRecord(request);
    std::cout << "Response: " << response << std::endl;
}

int main() {
    try {
        // Add tests to run here
        //testPlaceOrder();
        //testReplaceOrder();
        //testCancelOrder();
        //testQueryOrder();
        //testQueryOpenOrders();
        //testQueryHistoryOrders();
        //testQueryHistoryOrdersArchive();
        //testCancelAllOrders();
        //testChangePositionMode();
        //testQueryAccount();
        //testQueryPortfolioFundsHistory();
        //testQueryPortfolioAssets();
        //testQueryAllPortfolioAssets();
        //testSetLeverage();
        //testGetLeverage();
        //testClosePosition();
        //testClosePositions();
        //testQueryPosition();
        //testQueryHistoryPosition();
        //testQueryTransactions();
        //testQueryTransactionsPageable();
        //testQueryArchivedTransactions();
        //testQueryStatement();
        //testQueryTradingStats();
        //testSetMarginLeverage();
        //testGetMarginLeverage();
        //testGetSymInfo();
        //testGetFundingRate();
        //testGetMarkPrice();
        //testGetPositionTier();
        //testGetLoanTier();
        //testGetDiscountRate();
        //testGetUserInterest();
        //testGetBrokerPositionTier();
        //testSetSubPortfolioFeeRate();
        //testGetFeeRate();
        //testGetSubFeeRate();
        testGetClearingStatement();
        testGetCollectionRecord();
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
} 