#pragma once
#include <string>
#include <nlohmann/json.hpp>

class GetPositionTierRequest {
public:
    class Builder {
    public:
        Builder& sym(const std::string& value) {
            sym_ = value;
            return *this;
        }
        
        GetPositionTierRequest build() {
            return GetPositionTierRequest(*this);
        }
        
    private:
        friend class GetPositionTierRequest;
        std::string sym_;
    };
    
    static Builder builder() { return Builder(); }
    
    std::string toJsonString() const {
        nlohmann::json j;
        if (!sym.empty()) j["sym"] = sym;
        return j.empty() ? "{}" : j.dump();
    }
    
private:
    GetPositionTierRequest(const Builder& builder) :
        sym(builder.sym_) {}
        
    std::string sym;
}; 