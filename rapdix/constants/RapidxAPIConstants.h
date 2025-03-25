#pragma once
#include <string>

namespace RapidxAPIConstants {
    // Account
    const std::string ACCOUNT = "/api/v1/trading/account";
    
    // Assets
    const std::string ASSET_PORTFOLIO_FUNDS_HISTORY = "/api/v1/asset/bills";
    const std::string ASSET_PORTFOLIO_DETAIL = "/api/v1/trading/portfolio/assets";
    const std::string ASSET_ALL_PORTFOLIO = "/api/v1/user/asset";
    
    // Order
    const std::string ORDER = "/api/v1/trading/order";
    const std::string ORDERS = "/api/v1/trading/orders";
    const std::string ORDER_HISTORY = "/api/v1/trading/history/orders";
    const std::string ORDER_HISTORY_ARCHIVE = "/api/v1/trading/archive/history/orders";
    const std::string ORDER_CANCEL_ALL = "/api/v1/trading/cancelAll";
    
    // Position
    const std::string LEVERAGE_SET = "/api/v1/trading/position/leverage";
    const std::string LEVERAGE_GET = "/api/v1/trading/perp/leverage";
    const std::string POSITION = "/api/v1/trading/position";
    const std::string POSITIONS = "/api/v1/trading/positions";
    const std::string POSITIONS_HISTORY = "/api/v1/trading/history/position";
    
    // Transaction
    const std::string TRANSACTION = "/api/v1/trading/executions";
    const std::string TRANSACTION_PAGEABLE = "/api/v1/trading/executions/pageable";
    const std::string TRANSACTION_PAGEABLE_ARCHIVE = "/api/v1/trading/archive/executions/pageable";
    
    // Statement
    const std::string STATEMENT = "/api/v1/trading/statement";
    const std::string USER_TRADING_STATS = "/api/v1/trading/user/tradingStats";
    
    // Trading Rules
    const std::string MARGIN_LEVERAGE = "/api/v1/trading/margin/leverage";
    const std::string SYM_INFO = "/api/v1/trading/sym/info";
    const std::string FUNDING_RATE = "/api/v1/market/fundingRate";
    const std::string MARK_PRICE = "/api/v1/market/markPrice";
    const std::string USER_FEE_RATE = "/api/v1/trading/userFeeRate";
    const std::string POSITION_TIER = "/api/v1/trading/positionBracket";
    const std::string LOAN_TIER = "/api/v1/trading/loan/info";
    const std::string DISCOUNT_RATE = "/api/v1/trading/coin/discount";
    const std::string USER_INTEREST = "/api/v1/interest/user";
    
    // Broker
    const std::string BROKER_POSITION_TIER = "/api/v1/trading/broker/positionBracket";
    const std::string SUB_PORTFOLIO_FEE_RATE = "/api/v1/broker/subFeeRate";
    const std::string BROKER_FEE_RATE = "/api/v1/broker/feeRate";
    const std::string BROKER_SUB_FEE_RATE = "/api/v1/broker/sub/feeRate";
    const std::string CLEARING_STATEMENT = "/api/v1/broker/clearingStatement";
    const std::string COLLECTION_RECORD = "/api/v1/broker/collectionRecord";
    
    // Asset API
    static constexpr const char* ASSET_PORTFOLIO_ASSETS = "/api/v1/trading/portfolio/assets";
    
    static const std::string SUB_FEE_RATE = "/api/v1/broker/sub/feeRate";
} 