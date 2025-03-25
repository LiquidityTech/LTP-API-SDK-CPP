#pragma once
#include <string>
#include <nlohmann/json.hpp>

class QueryStatementRequest {
public:
    class Builder {
    public:
        Builder& coin(const std::string& value) {
            coin_ = value;
            return *this;
        }
        
        Builder& sym(const std::string& value) {
            sym_ = value;
            return *this;
        }
        
        Builder& statementType(const std::string& value) {
            statementType_ = value;
            return *this;
        }
        
        Builder& exchange(const std::string& value) {
            exchange_ = value;
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
        
        QueryStatementRequest build() {
            return QueryStatementRequest(*this);
        }
        
    private:
        friend class QueryStatementRequest;
        std::string coin_;
        std::string sym_;
        std::string statementType_;
        std::string exchange_;
        std::string startTime_;
        std::string endTime_;
        std::string page_;
        std::string pageSize_;
    };
    
    static Builder builder() { return Builder(); }
    
    std::string toJsonString() const {
        nlohmann::json j;
        if (!coin.empty()) j["coin"] = coin;
        if (!sym.empty()) j["sym"] = sym;
        if (!statementType.empty()) j["statementType"] = statementType;
        if (!exchange.empty()) j["exchange"] = exchange;
        if (!startTime.empty()) j["startTime"] = startTime;
        if (!endTime.empty()) j["endTime"] = endTime;
        if (!page.empty()) j["page"] = page;
        if (!pageSize.empty()) j["pageSize"] = pageSize;
        return j.empty() ? "{}" : j.dump();
    }
    
private:
    QueryStatementRequest(const Builder& builder) :
        coin(builder.coin_),
        sym(builder.sym_),
        statementType(builder.statementType_),
        exchange(builder.exchange_),
        startTime(builder.startTime_),
        endTime(builder.endTime_),
        page(builder.page_),
        pageSize(builder.pageSize_) {}
        
    std::string coin;
    std::string sym;
    std::string statementType;
    std::string exchange;
    std::string startTime;
    std::string endTime;
    std::string page;
    std::string pageSize;
}; 