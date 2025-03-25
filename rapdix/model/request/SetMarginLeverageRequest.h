#pragma once
#include <string>
#include <nlohmann/json.hpp>

class SetMarginLeverageRequest {
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
        
        Builder& leverage(const std::string& value) {
            leverage_ = value;
            return *this;
        }
        
        SetMarginLeverageRequest build() {
            return SetMarginLeverageRequest(*this);
        }
        
    private:
        friend class SetMarginLeverageRequest;
        std::string exchangeType_;
        std::string coin_;
        std::string leverage_;
    };
    
    static Builder builder() { return Builder(); }
    
    std::string toJsonString() const {
        nlohmann::json j;
        j["exchangeType"] = exchangeType;  // 必填
        j["coin"] = coin;                  // 必填
        j["leverage"] = leverage;          // 必填
        return j.dump();
    }
    
private:
    SetMarginLeverageRequest(const Builder& builder) :
        exchangeType(builder.exchangeType_),
        coin(builder.coin_),
        leverage(builder.leverage_) {}
        
    std::string exchangeType;
    std::string coin;
    std::string leverage;
}; 