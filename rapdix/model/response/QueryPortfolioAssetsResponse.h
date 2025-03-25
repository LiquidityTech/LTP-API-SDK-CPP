#pragma once
#include <string>
#include <vector>
#include <ostream>
#include <nlohmann/json.hpp>

class QueryPortfolioAssetsResponse {
public:
    struct AssetData {
        std::string portfolioId;
        std::string coin;
        std::string exchangeType;
        std::string balance;
        std::string available;
        std::string frozen;
        std::string equity;
        std::string overdraw;
        std::string borrow;
        std::string debt;
        std::string indexPrice;
        std::string marginValue;
        std::string virtualBorrow;
        std::string debtMargin;
        std::string perpMargin;
        std::string createAt;
        std::string updateAt;
        std::string maxTransferable;
        std::string upnl;
        std::string equityValue;
        
        NLOHMANN_DEFINE_TYPE_INTRUSIVE(AssetData,
            portfolioId, coin, exchangeType, balance, available,
            frozen, equity, overdraw, borrow, debt, indexPrice,
            marginValue, virtualBorrow, debtMargin, perpMargin,
            createAt, updateAt, maxTransferable, upnl, equityValue)
    };

    struct PageData {
        int page;
        int pageSize;
        int pageNum;
        int totalSize;
        std::vector<AssetData> list;
        
        NLOHMANN_DEFINE_TYPE_INTRUSIVE(PageData,
            page, pageSize, pageNum, totalSize, list)
    };

    QueryPortfolioAssetsResponse() : code(0) {}
    
    // Getters
    int getCode() const { return code; }
    const std::string& getMessage() const { return message; }
    const PageData& getData() const { return data; }
    
    // 输出运算符重载
    friend std::ostream& operator<<(std::ostream& os, const QueryPortfolioAssetsResponse& response) {
        os << "QueryPortfolioAssetsResponse{code=" << response.code 
           << ", message='" << response.message << "'";
        if (!response.data.list.empty()) {
            os << ", page=" << response.data.page
               << ", pageSize=" << response.data.pageSize
               << ", pageNum=" << response.data.pageNum
               << ", totalSize=" << response.data.totalSize
               << ", assets=[";
            for (const auto& asset : response.data.list) {
                os << "\n  {portfolioId='" << asset.portfolioId
                   << "', coin='" << asset.coin
                   << "', exchangeType='" << asset.exchangeType
                   << "', balance='" << asset.balance
                   << "', available='" << asset.available
                   << "', frozen='" << asset.frozen
                   << "', equity='" << asset.equity
                   << "', marginValue='" << asset.marginValue
                   << "', upnl='" << asset.upnl
                   << "', equityValue='" << asset.equityValue
                   << "'}";
            }
            os << "\n]";
        }
        os << "}";
        return os;
    }
    
    // JSON 序列化
    friend void from_json(const nlohmann::json& j, QueryPortfolioAssetsResponse& response) {
        j.at("code").get_to(response.code);
        j.at("message").get_to(response.message);
        if (j.contains("data")) {
            j.at("data").get_to(response.data);
        }
    }
    
    friend void to_json(nlohmann::json& j, const QueryPortfolioAssetsResponse& response) {
        j = {
            {"code", response.code},
            {"message", response.message}
        };
        if (response.data.page != 0) {  // 如果有分页数据
            j["data"] = response.data;
        }
    }
    
private:
    int code;
    std::string message;
    PageData data;
}; 