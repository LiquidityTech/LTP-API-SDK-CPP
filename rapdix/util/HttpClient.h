#pragma once
#include <string>
#include <map>
#include "Config.h"
#include "SignatureUtil.h"
#include "HttpUtil.h"
#include <nlohmann/json.hpp>
#include <iostream>

class HttpClient {
public:
    static HttpClient& getInstance() {
        static HttpClient instance;
        return instance;
    }

    template<typename ResponseType>
    ResponseType doPost(const std::string& path, const std::string& jsonBody) {
        return executeRequest<ResponseType>(path, jsonBody, "POST");
    }

    template<typename ResponseType>
    ResponseType doGet(const std::string& path, const std::string& jsonBody) {
        return executeRequest<ResponseType>(path, jsonBody, "GET");
    }

    template<typename ResponseType>
    ResponseType doPut(const std::string& path, const std::string& jsonBody) {
        return executeRequest<ResponseType>(path, jsonBody, "PUT");
    }

    template<typename ResponseType>
    ResponseType doDelete(const std::string& path, const std::string& jsonBody) {
        return executeRequest<ResponseType>(path, jsonBody, "DELETE");
    }

private:
    HttpClient() = default;
    HttpClient(const HttpClient&) = delete;
    HttpClient& operator=(const HttpClient&) = delete;

    template<typename ResponseType>
    ResponseType executeRequest(const std::string& path, const std::string& jsonBody, const std::string& method) {
        std::string url = Config::HOST + path;
        std::string nonce = SignatureUtil::gmtNow();
        
        std::cout << "JSON request: " << (jsonBody.empty() ? "{}" : jsonBody) << std::endl;
        
        std::string payload = SignatureUtil::getPayloadForSign(jsonBody);
        
        if (jsonBody.empty() || jsonBody == "{}") {
            payload = "&" + nonce;
        } else {
            if (!payload.empty()) {
                payload += "&";
            }
            payload += nonce;
        }
        
        std::string sign = SignatureUtil::hmacSHA256(payload, Config::SECRET_KEY);
        
        if (method == "GET" && !jsonBody.empty()) {
            url += "?" + payload;
        }
        
        std::map<std::string, std::string> headers = {
            {"Content-Type", "application/json"},
            {"nonce", nonce},
            {"signature", sign},
            {"X-MBX-APIKEY", Config::API_KEY}
        };
        std::string response = HttpUtil::httpRequest(url, method, jsonBody, headers);
        std::cout << "Server response: " << response << std::endl;

        auto j = nlohmann::json::parse(response);
        ResponseType result;
        from_json(j, result);
        return result;
    }
}; 