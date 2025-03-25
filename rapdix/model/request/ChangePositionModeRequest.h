#pragma once
#include <string>
#include <nlohmann/json.hpp>

class ChangePositionModeRequest {
public:
    class Builder {
    public:
        Builder& exchangeType(const std::string& value) {
            exchangeType_ = value;
            return *this;
        }
        
        Builder& positionMode(const std::string& value) {
            positionMode_ = value;
            return *this;
        }
        
        ChangePositionModeRequest build() {
            return ChangePositionModeRequest(*this);
        }
        
    private:
        friend class ChangePositionModeRequest;
        std::string exchangeType_;
        std::string positionMode_;
    };
    
    static Builder builder() { return Builder(); }
    
    std::string toJsonString() const {
        nlohmann::json j = *this;
        return j.dump();
    }
    
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(ChangePositionModeRequest,
        exchangeType,
        positionMode
    )
    
private:
    ChangePositionModeRequest(const Builder& builder) :
        exchangeType(builder.exchangeType_),
        positionMode(builder.positionMode_) {}
        
    std::string exchangeType;
    std::string positionMode;
}; 