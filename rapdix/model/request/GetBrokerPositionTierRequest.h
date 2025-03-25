#pragma once
#include <string>
#include <nlohmann/json.hpp>

class GetBrokerPositionTierRequest {
public:
    class Builder {
    public:
        Builder& sym(const std::string& value) {
            sym_ = value;
            return *this;
        }
        
        GetBrokerPositionTierRequest build() {
            return GetBrokerPositionTierRequest(*this);
        }
        
    private:
        friend class GetBrokerPositionTierRequest;
        std::string sym_;
    };
    
    static Builder builder() { return Builder(); }
    
    std::string toJsonString() const {
        nlohmann::json j;
        if (!sym.empty()) j["sym"] = sym;  // 可选
        return j.empty() ? "{}" : j.dump();
    }
    
private:
    GetBrokerPositionTierRequest(const Builder& builder) :
        sym(builder.sym_) {}
        
    std::string sym;
}; 