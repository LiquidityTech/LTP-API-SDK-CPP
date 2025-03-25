#pragma once
#include <string>
#include <nlohmann/json.hpp>

namespace rapdix {
namespace websocket {
namespace request {

class CancelOrdersArgs {
public:
    CancelOrdersArgs() = default;
    
    class Builder {
    public:
        Builder() = default;
        
        Builder& exchangeType(const std::string& value) {
            exchangeType_ = value;
            return *this;
        }
        
        CancelOrdersArgs build() {
            CancelOrdersArgs args;
            args.exchangeType = exchangeType_;
            return args;
        }
        
    private:
        std::string exchangeType_;
    };
    
    static Builder builder() { return Builder(); }
    
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(CancelOrdersArgs, exchangeType)
    
    std::string exchangeType;
};

class CancelOrdersRequest {
public:
    CancelOrdersRequest() = default;
    
    class Builder {
    public:
        Builder() = default;
        
        Builder& id(const std::string& value) {
            id_ = value;
            return *this;
        }
        
        Builder& args(const CancelOrdersArgs& value) {
            args_ = value;
            return *this;
        }
        
        CancelOrdersRequest build() {
            CancelOrdersRequest request;
            request.id = id_;
            request.args = args_;
            return request;
        }
        
    private:
        std::string id_;
        CancelOrdersArgs args_;
    };
    
    static Builder builder() { return Builder(); }
    
    std::string toJsonString() const {
        nlohmann::json j;
        j["action"] = "cancel_orders";
        j["id"] = id;
        j["args"] = args;
        return j.dump();
    }
    
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(CancelOrdersRequest, id, args)
    
private:
    std::string id;
    CancelOrdersArgs args;
};

} // namespace request
} // namespace websocket
} // namespace rapdix 