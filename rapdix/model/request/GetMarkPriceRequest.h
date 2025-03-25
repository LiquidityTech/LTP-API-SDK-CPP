#pragma once
#include <string>
#include <nlohmann/json.hpp>

class GetMarkPriceRequest {
public:
    class Builder {
    public:
        Builder& sym(const std::string& value) {
            sym_ = value;
            return *this;
        }
        
        GetMarkPriceRequest build() {
            return GetMarkPriceRequest(*this);
        }
        
    private:
        friend class GetMarkPriceRequest;
        std::string sym_;
    };
    
    static Builder builder() { return Builder(); }
    
    std::string toJsonString() const {
        nlohmann::json j;
        if (!sym.empty()) j["sym"] = sym;
        return j.empty() ? "{}" : j.dump();
    }
    
private:
    GetMarkPriceRequest(const Builder& builder) :
        sym(builder.sym_) {}
        
    std::string sym;
}; 