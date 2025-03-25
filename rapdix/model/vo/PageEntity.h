#pragma once
#include <vector>

template<typename T>
class PageEntity {
public:
    // 构造函数
    PageEntity() = default;
    
    PageEntity(int page, int pageSize, int pageNum, int totalSize, const std::vector<T>& list)
        : page_(page), pageSize_(pageSize), pageNum_(pageNum), totalSize_(totalSize), list_(list) {}
    
    // Getters
    int getPage() const { return page_; }
    int getPageSize() const { return pageSize_; }
    int getPageNum() const { return pageNum_; }
    int getTotalSize() const { return totalSize_; }
    const std::vector<T>& getList() const { return list_; }
    
    // Setters
    void setPage(int page) { page_ = page; }
    void setPageSize(int pageSize) { pageSize_ = pageSize; }
    void setPageNum(int pageNum) { pageNum_ = pageNum; }
    void setTotalSize(int totalSize) { totalSize_ = totalSize; }
    void setList(const std::vector<T>& list) { list_ = list; }
    
    // Builder 模式
    class Builder {
    public:
        Builder& page(int page) {
            page_ = page;
            return *this;
        }
        
        Builder& pageSize(int pageSize) {
            pageSize_ = pageSize;
            return *this;
        }
        
        Builder& pageNum(int pageNum) {
            pageNum_ = pageNum;
            return *this;
        }
        
        Builder& totalSize(int totalSize) {
            totalSize_ = totalSize;
            return *this;
        }
        
        Builder& list(const std::vector<T>& list) {
            list_ = list;
            return *this;
        }
        
        PageEntity<T> build() {
            return PageEntity<T>(page_, pageSize_, pageNum_, totalSize_, list_);
        }
        
    private:
        int page_ = 0;
        int pageSize_ = 0;
        int pageNum_ = 0;
        int totalSize_ = 0;
        std::vector<T> list_;
    };
    
    static Builder builder() {
        return Builder();
    }

private:
    int page_ = 0;
    int pageSize_ = 0;
    int pageNum_ = 0;
    int totalSize_ = 0;
    std::vector<T> list_;
}; 