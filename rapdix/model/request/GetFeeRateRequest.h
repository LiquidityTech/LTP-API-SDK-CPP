#pragma once
#include <string>
#include <nlohmann/json.hpp>

class GetFeeRateRequest {
public:
    class Builder {
    public:
        Builder& exchange(const std::string& value) {
            exchange_ = value;
            return *this;
        }
        
        Builder& instType(const std::string& value) {
            instType_ = value;
            return *this;
        }
        
        Builder& portfolioIds(const std::string& value) {
            portfolioIds_ = value;
            return *this;
        }
        
        GetFeeRateRequest build() {
            return GetFeeRateRequest(*this);
        }
        
    private:
        friend class GetFeeRateRequest;
        std::string exchange_;
        std::string instType_;
        std::string portfolioIds_;
    };
    
    static Builder builder() { return Builder(); }
    
    std::string toJsonString() const {
        nlohmann::json j;
        if (!exchange.empty()) j["exchange"] = exchange;
        if (!instType.empty()) j["instType"] = instType;
        if (!portfolioIds.empty()) j["portfolioIds"] = portfolioIds;
        return j.empty() ? "{}" : j.dump();
    }
    
private:
    GetFeeRateRequest(const Builder& builder) :
        exchange(builder.exchange_),
        instType(builder.instType_),
        portfolioIds(builder.portfolioIds_) {}
        
    std::string exchange;
    std::string instType;
    std::string portfolioIds;
}; 