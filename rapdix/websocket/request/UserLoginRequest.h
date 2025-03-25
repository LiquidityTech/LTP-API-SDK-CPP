#pragma once
#include <string>
#include <nlohmann/json.hpp>

namespace rapdix {
namespace websocket {
namespace request {

class LoginArgs {
public:
    LoginArgs() = default;
    class Builder {
    public:
        Builder& apiKey(const std::string& value) {
            apiKey_ = value;
            return *this;
        }
        
        Builder& timestamp(const std::string& value) {
            timestamp_ = value;
            return *this;
        }
        
        Builder& sign(const std::string& value) {
            sign_ = value;
            return *this;
        }
        
        LoginArgs build() {
            return LoginArgs(*this);
        }
        
        static Builder create() { return Builder(); }
        
    private:
        friend class LoginArgs;
        std::string apiKey_;
        std::string timestamp_;
        std::string sign_;
    };
    
    static Builder create() { return Builder::create(); }
    
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(LoginArgs, apiKey, timestamp, sign)
    
private:
    LoginArgs(const Builder& builder) :
        apiKey(builder.apiKey_),
        timestamp(builder.timestamp_),
        sign(builder.sign_) {}
        
    std::string apiKey;
    std::string timestamp;
    std::string sign;
};

class UserLoginRequest {
public:
    class Builder {
    public:
        Builder& action(const std::string& value) {
            action_ = value;
            return *this;
        }
        
        Builder& args(const LoginArgs& value) {
            args_ = value;
            return *this;
        }
        
        UserLoginRequest build() {
            return UserLoginRequest(*this);
        }
        
        static Builder create() { return Builder(); }
        
    private:
        friend class UserLoginRequest;
        std::string action_;
        LoginArgs args_;
    };
    
    static Builder create() { return Builder::create(); }
    
    std::string toJsonString() const {
        nlohmann::json j;
        j["action"] = action;
        j["args"] = args;
        return j.dump();
    }
    
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(UserLoginRequest, action, args)
    
private:
    UserLoginRequest(const Builder& builder) :
        action(builder.action_),
        args(builder.args_) {}
        
    std::string action;
    LoginArgs args;
};

} // namespace request
} // namespace websocket
} // namespace rapdix 