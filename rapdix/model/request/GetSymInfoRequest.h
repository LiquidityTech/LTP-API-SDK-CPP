#pragma once
#include <string>
#include <nlohmann/json.hpp>

class GetSymInfoRequest {
public:
    class Builder {
    public:
        Builder& sym(const std::string& value) {
            sym_ = value;
            return *this;
        }
        
        GetSymInfoRequest build() {
            return GetSymInfoRequest(*this);
        }
        
    private:
        friend class GetSymInfoRequest;
        std::string sym_;
    };
    
    static Builder builder() { return Builder(); }
    
    std::string toJsonString() const {
        nlohmann::json j;
        if (!sym.empty()) j["sym"] = sym;
        return j.empty() ? "{}" : j.dump();
    }
    
private:
    GetSymInfoRequest(const Builder& builder) :
        sym(builder.sym_) {}
        
    std::string sym;
}; 