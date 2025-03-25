#pragma once
#include <string>
#include <nlohmann/json.hpp>

class QueryTradingStatsRequest {
public:
    class Builder {
    public:
        Builder& exchange(const std::string& value) {
            exchange_ = value;
            return *this;
        }
        
        Builder& businessType(const std::string& value) {
            businessType_ = value;
            return *this;
        }
        
        Builder& begin(const std::string& value) {
            begin_ = value;
            return *this;
        }
        
        Builder& end(const std::string& value) {
            end_ = value;
            return *this;
        }
        
        QueryTradingStatsRequest build() {
            return QueryTradingStatsRequest(*this);
        }
        
    private:
        friend class QueryTradingStatsRequest;
        std::string exchange_;
        std::string businessType_;
        std::string begin_;
        std::string end_;
    };
    
    static Builder builder() { return Builder(); }
    
    std::string toJsonString() const {
        nlohmann::json j;
        if (!exchange.empty()) j["exchange"] = exchange;
        if (!businessType.empty()) j["businessType"] = businessType;
        j["begin"] = begin;  // 必填
        j["end"] = end;      // 必填
        return j.dump();
    }
    
private:
    QueryTradingStatsRequest(const Builder& builder) :
        exchange(builder.exchange_),
        businessType(builder.businessType_),
        begin(builder.begin_),
        end(builder.end_) {}
        
    std::string exchange;
    std::string businessType;
    std::string begin;
    std::string end;
}; 