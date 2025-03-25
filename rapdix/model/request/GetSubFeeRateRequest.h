#pragma once
#include <string>
#include <nlohmann/json.hpp>

class GetSubFeeRateRequest {
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
        
        GetSubFeeRateRequest build() {
            return GetSubFeeRateRequest(*this);
        }
        
    private:
        friend class GetSubFeeRateRequest;
        std::string exchange_;
        std::string instType_;
    };
    
    static Builder builder() { return Builder(); }
    
    std::string toJsonString() const {
        nlohmann::json j;
        if (!exchange.empty()) j["exchange"] = exchange;
        if (!instType.empty()) j["instType"] = instType;
        return j.empty() ? "{}" : j.dump();
    }
    
private:
    GetSubFeeRateRequest(const Builder& builder) :
        exchange(builder.exchange_),
        instType(builder.instType_) {}
        
    std::string exchange;
    std::string instType;
}; 