#pragma once
#include <string>
#include <nlohmann/json.hpp>

namespace rapdix {
namespace websocket {
namespace request {

class PlaceOrderArgs {
public:
    PlaceOrderArgs() = default;
    
    const std::string& getSym() const { return sym; }
    const std::string& getSide() const { return side; }
    const std::string& getOrderType() const { return orderType; }
    const std::string& getTimeInForce() const { return timeInForce; }
    const std::string& getOrderQty() const { return orderQty; }
    const std::string& getLimitPrice() const { return limitPrice; }
    
    class Builder {
    public:
        Builder& clientOrderId(const std::string& value) { clientOrderId_ = value; return *this; }
        Builder& sym(const std::string& value) { sym_ = value; return *this; }
        Builder& side(const std::string& value) { side_ = value; return *this; }
        Builder& orderType(const std::string& value) { orderType_ = value; return *this; }
        Builder& timeInForce(const std::string& value) { timeInForce_ = value; return *this; }
        Builder& orderQty(const std::string& value) { orderQty_ = value; return *this; }
        Builder& limitPrice(const std::string& value) { limitPrice_ = value; return *this; }
        Builder& quoteOrderQty(const std::string& value) { quoteOrderQty_ = value; return *this; }
        Builder& reduceOnly(const std::string& value) { reduceOnly_ = value; return *this; }
        Builder& positionSide(const std::string& value) { positionSide_ = value; return *this; }
        Builder& tpTriggerPrice(const std::string& value) { tpTriggerPrice_ = value; return *this; }
        Builder& tpTriggerType(const std::string& value) { tpTriggerType_ = value; return *this; }
        Builder& tpPrice(const std::string& value) { tpPrice_ = value; return *this; }
        Builder& slTriggerPrice(const std::string& value) { slTriggerPrice_ = value; return *this; }
        Builder& slTriggerType(const std::string& value) { slTriggerType_ = value; return *this; }
        Builder& slPrice(const std::string& value) { slPrice_ = value; return *this; }
        
        PlaceOrderArgs build() { return PlaceOrderArgs(*this); }
        static Builder create() { return Builder(); }
        
    private:
        friend class PlaceOrderArgs;
        std::string clientOrderId_, sym_, side_, orderType_, timeInForce_;
        std::string orderQty_, limitPrice_, quoteOrderQty_, reduceOnly_, positionSide_;
        std::string tpTriggerPrice_, tpTriggerType_, tpPrice_;
        std::string slTriggerPrice_, slTriggerType_, slPrice_;
    };
    
    static Builder create() { return Builder::create(); }
    
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(PlaceOrderArgs, 
        clientOrderId, sym, side, orderType, timeInForce,
        orderQty, limitPrice, quoteOrderQty, reduceOnly, positionSide,
        tpTriggerPrice, tpTriggerType, tpPrice,
        slTriggerPrice, slTriggerType, slPrice)
    
private:
    PlaceOrderArgs(const Builder& b) :
        clientOrderId(b.clientOrderId_), sym(b.sym_), side(b.side_),
        orderType(b.orderType_), timeInForce(b.timeInForce_),
        orderQty(b.orderQty_), limitPrice(b.limitPrice_),
        quoteOrderQty(b.quoteOrderQty_), reduceOnly(b.reduceOnly_),
        positionSide(b.positionSide_), tpTriggerPrice(b.tpTriggerPrice_),
        tpTriggerType(b.tpTriggerType_), tpPrice(b.tpPrice_),
        slTriggerPrice(b.slTriggerPrice_), slTriggerType(b.slTriggerType_),
        slPrice(b.slPrice_) {}
        
    std::string clientOrderId, sym, side, orderType, timeInForce;
    std::string orderQty, limitPrice, quoteOrderQty, reduceOnly, positionSide;
    std::string tpTriggerPrice, tpTriggerType, tpPrice;
    std::string slTriggerPrice, slTriggerType, slPrice;
};

class PlaceOrderRequest {
public:
    class Builder {
    public:
        Builder& id(const std::string& value) {
            id_ = value;
            return *this;
        }
        
        Builder& args(const PlaceOrderArgs& value) {
            args_ = value;
            return *this;
        }
        
        PlaceOrderRequest build() {
            return PlaceOrderRequest(*this);
        }
        
        static Builder create() { return Builder(); }
        
    private:
        friend class PlaceOrderRequest;
        std::string id_;
        PlaceOrderArgs args_;
    };
    
    std::string toJsonString() const {
        nlohmann::json j;
        j["id"] = id;
        j["action"] = "place_order";
        
        nlohmann::json argsJson;
        const auto& sym = args.getSym();
        if (!sym.empty()) argsJson["sym"] = sym;
        
        const auto& side = args.getSide();
        if (!side.empty()) argsJson["side"] = side;
        
        const auto& orderType = args.getOrderType();
        if (!orderType.empty()) argsJson["orderType"] = orderType;
        
        const auto& orderQty = args.getOrderQty();
        if (!orderQty.empty()) argsJson["orderQty"] = orderQty;
        
        const auto& limitPrice = args.getLimitPrice();
        if (!limitPrice.empty()) argsJson["limitPrice"] = limitPrice;
        
        const auto& timeInForce = args.getTimeInForce();
        if (!timeInForce.empty()) argsJson["timeInForce"] = timeInForce;
        
        j["args"] = argsJson;
        return j.dump();
    }
    
    static Builder create() { return Builder::create(); }
    
private:
    PlaceOrderRequest(const Builder& builder) :
        id(builder.id_),
        args(builder.args_) {}
        
    std::string id;
    PlaceOrderArgs args;
    
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(PlaceOrderRequest, id, args)
};

} // namespace request
} // namespace websocket
} // namespace rapdix 