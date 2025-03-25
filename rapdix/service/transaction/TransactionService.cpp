#include "TransactionService.h"
#include "rapdix/util/HttpClient.h"
#include "rapdix/constants/RapidxAPIConstants.h"
#include <iostream>

QueryTransactionsResponse TransactionService::queryTransactions(const QueryTransactionsRequest& request) {
    try {
        return HttpClient::getInstance().doGet<QueryTransactionsResponse>(
            RapidxAPIConstants::TRANSACTION,
            request.toJsonString()
        );
    } catch (const std::exception& e) {
        std::cerr << "queryTransactions error: " << e.what() << std::endl;
        throw;
    }
}

QueryTransactionsPageableResponse TransactionService::queryTransactionsPageable(const QueryTransactionsPageableRequest& request) {
    try {
        return HttpClient::getInstance().doGet<QueryTransactionsPageableResponse>(
            RapidxAPIConstants::TRANSACTION_PAGEABLE,
            request.toJsonString()
        );
    } catch (const std::exception& e) {
        std::cerr << "queryTransactionsPageable error: " << e.what() << std::endl;
        throw;
    }
}

QueryArchivedTransactionsResponse TransactionService::queryArchivedTransactions(const QueryArchivedTransactionsRequest& request) {
    try {
        return HttpClient::getInstance().doGet<QueryArchivedTransactionsResponse>(
            RapidxAPIConstants::TRANSACTION_PAGEABLE_ARCHIVE,
            request.toJsonString()
        );
    } catch (const std::exception& e) {
        std::cerr << "queryArchivedTransactions error: " << e.what() << std::endl;
        throw;
    }
} 