#include "HttpUtil.h"
#include <iostream>

std::string HttpUtil::httpRequest(const std::string& url, const std::string& method, 
                                const std::string& payload, 
                                const std::map<std::string, std::string>& headers) {
    CURL* curl;
    std::string response_string;
    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    
    if(curl) {
        struct curl_slist *chunk = nullptr;
        for (const auto& [key, value] : headers) {
            chunk = curl_slist_append(chunk, (key + ": " + value).c_str());
        }
        
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);
        
        if (method == "POST" || method == "PUT" || method == "DELETE") {
            curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, method.c_str());
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, payload.empty() ? "" : payload.c_str());
        } else if (method == "GET") {
            curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);
        }
        
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, +[](void* contents, size_t size, 
                        size_t nmemb, std::string* userp) -> size_t {
            size_t total_size = size * nmemb;
            userp->append((char*)contents, total_size);
            return total_size;
        });
        
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);
        
        CURLcode res = curl_easy_perform(curl);
        if(res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        }
        
        curl_easy_cleanup(curl);
        curl_slist_free_all(chunk);
    }
    curl_global_cleanup();
    return response_string;
} 