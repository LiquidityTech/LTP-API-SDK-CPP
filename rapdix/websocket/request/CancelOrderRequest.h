#pragma once
#include <string>
#include <nlohmann/json.hpp>

namespace rapdix {
namespace websocket {
namespace request {

class CancelOrderArgs {
public:
    CancelOrderArgs() = default;
    
    // getter 方法
    const std::string& getOrderId() const { return orderId; }
    const std::string& getClientOrderId() const { return clientOrderId; }
    
    class Builder {
    public:
        Builder& orderId(const std::string& value) { orderId_ = value; return *this; }
        Builder& clientOrderId(const std::string& value) { clientOrderId_ = value; return *this; }
        
        CancelOrderArgs build() { 
            // 确保至少有一个参数不为空
            if (orderId_.empty() && clientOrderId_.empty()) {
                throw std::runtime_error("Either orderId or clientOrderId must be provided");
            }
            return CancelOrderArgs(*this); 
        }
        
        static Builder create() { return Builder(); }
        
    private:
        friend class CancelOrderArgs;
        std::string orderId_;
        std::string clientOrderId_;
    };
    
    static Builder create() { return Builder::create(); }
    
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(CancelOrderArgs, orderId, clientOrderId)
    
private:
    CancelOrderArgs(const Builder& b) :
        orderId(b.orderId_),
        clientOrderId(b.clientOrderId_) {}
        
    std::string orderId;
    std::string clientOrderId;
};

class CancelOrderRequest {
public:
    class Builder {
    public:
        Builder& id(const std::string& value) {
            id_ = value;
            return *this;
        }
        
        Builder& args(const CancelOrderArgs& value) {
            args_ = value;
            return *this;
        }
        
        CancelOrderRequest build() {
            return CancelOrderRequest(*this);
        }
        
        static Builder create() { return Builder(); }
        
    private:
        friend class CancelOrderRequest;
        std::string id_;
        CancelOrderArgs args_;
    };
    
    std::string toJsonString() const {
        nlohmann::json j;
        j["id"] = id;
        j["action"] = "cancel_order";
        
        nlohmann::json argsJson;
        const auto& orderId = args.getOrderId();
        if (!orderId.empty()) argsJson["orderId"] = orderId;
        
        const auto& clientOrderId = args.getClientOrderId();
        if (!clientOrderId.empty()) argsJson["clientOrderId"] = clientOrderId;
        
        j["args"] = argsJson;
        return j.dump();
    }
    
    static Builder create() { return Builder::create(); }
    
private:
    CancelOrderRequest(const Builder& builder) :
        id(builder.id_),
        args(builder.args_) {}
        
    std::string id;
    CancelOrderArgs args;
    
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(CancelOrderRequest, id, args)
};

} // namespace request
} // namespace websocket
} // namespace rapdix 