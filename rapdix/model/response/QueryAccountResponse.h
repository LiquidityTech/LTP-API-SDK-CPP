#pragma once
#include <string>
#include <vector>
#include <ostream>
#include <nlohmann/json.hpp>

class QueryAccountResponse {
public:
    // 先声明 AccountData 结构体
    struct AccountData {
        std::string portfolioId;
        std::string exchangeType;
        std::string equity;
        std::string maintainMargin;
        std::string positionValue;
        std::string uniMMR;
        std::string accountStatus;
        std::string marginValue;
        std::string frozenMargin;
        std::string perpMargin;
        std::string debtMargin;
        std::string openLossMargin;
        std::string validMargin;
        std::string availableMargin;
        std::string upnl;
        std::string positionMode;
        
        NLOHMANN_DEFINE_TYPE_INTRUSIVE(AccountData,
            portfolioId, exchangeType, equity, maintainMargin, positionValue,
            uniMMR, accountStatus, marginValue, frozenMargin, perpMargin,
            debtMargin, openLossMargin, validMargin, availableMargin,
            upnl, positionMode)
    };

    QueryAccountResponse() = default;
    
    // Getters
    int getCode() const { return code; }
    const std::string& getMessage() const { return message; }
    const std::vector<AccountData>& getData() const { return data; }
    
    // 输出运算符重载
    friend std::ostream& operator<<(std::ostream& os, const QueryAccountResponse& response) {
        os << "QueryAccountResponse{code=" << response.code 
           << ", message='" << response.message << "'";
        if (response.code == 200000 && !response.data.empty()) {  // 成功响应
            os << ", accounts=[";
            for (const auto& account : response.data) {
                os << "\n  {portfolioId='" << account.portfolioId
                   << "', exchangeType='" << account.exchangeType
                   << "', equity='" << account.equity
                   << "', maintainMargin='" << account.maintainMargin
                   << "', positionValue='" << account.positionValue
                   << "', uniMMR='" << account.uniMMR
                   << "', accountStatus='" << account.accountStatus
                   << "', marginValue='" << account.marginValue
                   << "', frozenMargin='" << account.frozenMargin
                   << "', perpMargin='" << account.perpMargin
                   << "', debtMargin='" << account.debtMargin
                   << "', openLossMargin='" << account.openLossMargin
                   << "', validMargin='" << account.validMargin
                   << "', availableMargin='" << account.availableMargin
                   << "', upnl='" << account.upnl
                   << "', positionMode='" << account.positionMode
                   << "'}";
            }
            os << "\n]";
        }
        os << "}";
        return os;
    }
    
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(QueryAccountResponse, code, message, data)
    
private:
    int code;
    std::string message;
    std::vector<AccountData> data;
}; 