#pragma once
#include <string>
#include <nlohmann/json.hpp>

class CancelAllOrdersRequest {
public:
    class Builder {
    public:
        Builder& exchangeType(const std::string& value) {
            exchangeType_ = value;
            return *this;
        }
        
        Builder& sym(const std::string& value) {
            sym_ = value;
            return *this;
        }
        
        CancelAllOrdersRequest build() {
            return CancelAllOrdersRequest(*this);
        }
        
    private:
        friend class CancelAllOrdersRequest;
        std::string exchangeType_;
        std::string sym_;
    };
    
    static Builder builder() { return Builder(); }
    
    std::string toJsonString() const {
        if (exchangeType.empty() && sym.empty()) {
            return "";
        }
        
        nlohmann::json j = *this;
        for (auto it = j.begin(); it != j.end();) {
            if (it.value().is_string() && it.value().get<std::string>().empty()) {
                it = j.erase(it);
            } else {
                ++it;
            }
        }
        return j.dump();
    }
    
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(CancelAllOrdersRequest,
        exchangeType,
        sym
    )
    
private:
    CancelAllOrdersRequest(const Builder& builder) :
        exchangeType(builder.exchangeType_),
        sym(builder.sym_) {}
        
    std::string exchangeType;
    std::string sym;
}; 