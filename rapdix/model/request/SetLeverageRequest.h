#pragma once
#include <string>
#include <nlohmann/json.hpp>

class SetLeverageRequest {
public:
    class Builder {
    public:
        Builder& leverage(const std::string& value) {
            leverage_ = value;
            return *this;
        }
        
        Builder& sym(const std::string& value) {
            sym_ = value;
            return *this;
        }
        
        SetLeverageRequest build() {
            return SetLeverageRequest(*this);
        }
        
    private:
        friend class SetLeverageRequest;
        std::string leverage_;
        std::string sym_;
    };
    
    static Builder builder() { return Builder(); }
    
    std::string toJsonString() const {
        nlohmann::json j;
        if (!leverage.empty()) j["leverage"] = leverage;
        if (!sym.empty()) j["sym"] = sym;
        return j.dump();
    }
    
private:
    SetLeverageRequest(const Builder& builder) :
        leverage(builder.leverage_),
        sym(builder.sym_) {}
        
    std::string leverage;
    std::string sym;
}; 