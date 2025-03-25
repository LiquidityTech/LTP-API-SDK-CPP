#pragma once
#include <string>
#include <nlohmann/json.hpp>

class GetLeverageRequest {
public:
    class Builder {
    public:
        Builder& sym(const std::string& value) {
            sym_ = value;
            return *this;
        }
        
        GetLeverageRequest build() {
            return GetLeverageRequest(*this);
        }
        
    private:
        friend class GetLeverageRequest;
        std::string sym_;
    };
    
    static Builder builder() { return Builder(); }
    
    std::string toJsonString() const {
        nlohmann::json j;
        if (!sym.empty()) j["sym"] = sym;
        return j.empty() ? "{}" : j.dump();
    }
    
private:
    GetLeverageRequest(const Builder& builder) :
        sym(builder.sym_) {}
        
    std::string sym;
}; 