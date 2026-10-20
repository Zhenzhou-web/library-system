#pragma once
#include<mysql.h>
#include<string>
class Database {
public:
	Database(const std::string& host,const std::string& user, const std::string& password, const std::string& database, unsigned int port);
	~Database();
	Database(const Database&) = delete;
	Database& operator=(const Database&) = delete;
	MYSQL* handle()const { return conn_; }
private:
	MYSQL* conn_ = nullptr;
};