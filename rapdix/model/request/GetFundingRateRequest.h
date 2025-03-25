#pragma once
#include <string>
#include <nlohmann/json.hpp>

class GetFundingRateRequest {
public:
    class Builder {
    public:
        Builder& sym(const std::string& value) {
            sym_ = value;
            return *this;
        }
        
        GetFundingRateRequest build() {
            return GetFundingRateRequest(*this);
        }
        
    private:
        friend class GetFundingRateRequest;
        std::string sym_;
    };
    
    static Builder builder() { return Builder(); }
    
    std::string toJsonString() const {
        nlohmann::json j;
        j["sym"] = sym;  // 必填
        return j.dump();
    }
    
private:
    GetFundingRateRequest(const Builder& builder) :
        sym(builder.sym_) {}
        
    std::string sym;
}; 