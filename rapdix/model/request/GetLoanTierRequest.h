#pragma once
#include <string>
#include <nlohmann/json.hpp>

class GetLoanTierRequest {
public:
    class Builder {
    public:
        Builder& exchangeType(const std::string& value) {
            exchangeType_ = value;
            return *this;
        }
        
        Builder& coin(const std::string& value) {
            coin_ = value;
            return *this;
        }
        
        GetLoanTierRequest build() {
            return GetLoanTierRequest(*this);
        }
        
    private:
        friend class GetLoanTierRequest;
        std::string exchangeType_;
        std::string coin_;
    };
    
    static Builder builder() { return Builder(); }
    
    std::string toJsonString() const {
        nlohmann::json j;
        if (!exchangeType.empty()) j["exchangeType"] = exchangeType;
        if (!coin.empty()) j["coin"] = coin;
        return j.empty() ? "{}" : j.dump();
    }
    
private:
    GetLoanTierRequest(const Builder& builder) :
        exchangeType(builder.exchangeType_),
        coin(builder.coin_) {}
        
    std::string exchangeType;
    std::string coin;
}; 