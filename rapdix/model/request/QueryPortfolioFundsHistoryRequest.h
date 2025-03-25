#pragma once
#include <string>
#include <nlohmann/json.hpp>

class QueryPortfolioFundsHistoryRequest {
public:
    class Builder {
    public:
        Builder& currency(const std::string& value) {
            currency_ = value;
            return *this;
        }
        
        Builder& type(const std::string& value) {
            type_ = value;
            return *this;
        }
        
        Builder& status(const std::string& value) {
            status_ = value;
            return *this;
        }
        
        Builder& startTime(const std::string& value) {
            startTime_ = value;
            return *this;
        }
        
        Builder& endTime(const std::string& value) {
            endTime_ = value;
            return *this;
        }
        
        Builder& page(const std::string& value) {
            page_ = value;
            return *this;
        }
        
        Builder& pageSize(const std::string& value) {
            pageSize_ = value;
            return *this;
        }
        
        QueryPortfolioFundsHistoryRequest build() {
            return QueryPortfolioFundsHistoryRequest(*this);
        }
        
    private:
        friend class QueryPortfolioFundsHistoryRequest;
        std::string currency_;
        std::string type_;
        std::string status_;
        std::string startTime_;
        std::string endTime_;
        std::string page_;
        std::string pageSize_;
    };
    
    static Builder builder() { return Builder(); }
    
    std::string toJsonString() const {
        nlohmann::json j;
        if (!currency.empty()) j["currency"] = currency;
        if (!type.empty()) j["type"] = type;
        if (!status.empty()) j["status"] = status;
        if (!startTime.empty()) j["startTime"] = startTime;
        if (!endTime.empty()) j["endTime"] = endTime;
        if (!page.empty()) j["page"] = page;
        if (!pageSize.empty()) j["pageSize"] = pageSize;
        return j.empty() ? "{}" : j.dump();
    }
    
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(QueryPortfolioFundsHistoryRequest,
        currency, type, status, startTime, endTime, page, pageSize)
    
private:
    QueryPortfolioFundsHistoryRequest(const Builder& builder) :
        currency(builder.currency_),
        type(builder.type_),
        status(builder.status_),
        startTime(builder.startTime_),
        endTime(builder.endTime_),
        page(builder.page_),
        pageSize(builder.pageSize_) {}
        
    std::string currency;
    std::string type;
    std::string status;
    std::string startTime;
    std::string endTime;
    std::string page;
    std::string pageSize;
}; 