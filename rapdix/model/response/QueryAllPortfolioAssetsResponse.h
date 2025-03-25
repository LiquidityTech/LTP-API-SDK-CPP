#pragma once
#include <string>
#include <vector>
#include <ostream>
#include <nlohmann/json.hpp>

class QueryAllPortfolioAssetsResponse {
public:
    struct AssetData {
        std::string portfolioId;
        std::string coin;
        std::string exchangeType;
        std::string available;
        std::string frozen;
        std::string equity;
        std::string balance;
        std::string borrow;
        std::string overdraw;
        std::string debt;
        std::string marginValue;
        std::string indexPrice;
        std::string virtualBorrow;
        std::string debtMargin;
        std::string perpMargin;
        std::string createAt;
        std::string updateAt;
        std::string maxTransferable;
        std::string upnl;
        std::string equityValue;
        
        NLOHMANN_DEFINE_TYPE_INTRUSIVE(AssetData,
            portfolioId, coin, exchangeType, available, frozen,
            equity, balance, borrow, overdraw, debt, marginValue,
            indexPrice, virtualBorrow, debtMargin, perpMargin,
            createAt, updateAt, maxTransferable, upnl, equityValue)
    };

    struct PortfolioAssets {
        std::string portfolioId;
        std::vector<AssetData> assets;
        
        NLOHMANN_DEFINE_TYPE_INTRUSIVE(PortfolioAssets,
            portfolioId, assets)
    };

    QueryAllPortfolioAssetsResponse() : code(0) {}
    
    // Getters
    int getCode() const { return code; }
    const std::string& getMessage() const { return message; }
    const std::vector<PortfolioAssets>& getData() const { return data; }
    
    // 输出运算符重载
    friend std::ostream& operator<<(std::ostream& os, const QueryAllPortfolioAssetsResponse& response) {
        os << "QueryAllPortfolioAssetsResponse{code=" << response.code 
           << ", message='" << response.message << "'";
        if (!response.data.empty()) {
            os << ", portfolios=[";
            for (const auto& portfolio : response.data) {
                os << "\n  Portfolio{id='" << portfolio.portfolioId << "', assets=[";
                for (const auto& asset : portfolio.assets) {
                    os << "\n    {coin='" << asset.coin
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
                os << "\n  ]}";
            }
            os << "\n]";
        }
        os << "}";
        return os;
    }
    
    // JSON 序列化
    friend void from_json(const nlohmann::json& j, QueryAllPortfolioAssetsResponse& response) {
        j.at("code").get_to(response.code);
        j.at("message").get_to(response.message);
        if (j.contains("data")) {
            // 如果 data 是空对象，就当作空数组处理
            if (j.at("data").is_object() && j.at("data").empty()) {
                response.data.clear();
            } else {
                j.at("data").get_to(response.data);
            }
        }
    }
    
    friend void to_json(nlohmann::json& j, const QueryAllPortfolioAssetsResponse& response) {
        j = {
            {"code", response.code},
            {"message", response.message}
        };
        if (!response.data.empty()) {
            j["data"] = response.data;
        }
    }
    
private:
    int code;
    std::string message;
    std::vector<PortfolioAssets> data;
}; 