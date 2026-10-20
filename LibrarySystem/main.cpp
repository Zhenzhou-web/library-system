#define _CRT_SECURE_NO_WARNINGS
#include<mysql.h>
#include<windows.h>
#include<cstdlib>
#include"Database.h"

#include<iostream>

int main() {
	SetConsoleOutputCP(CP_UTF8);
	try {
		const char* dbPassword = std::getenv("DB_PASSWORD");
		if (dbPassword == nullptr) {
			std::cerr << "DB_PASSWORD is not set" << std::endl;
			return 1;
		}
		Database db("127.0.0.1", "root", dbPassword, "library_db", 3306);
		MYSQL* conn = db.handle();
		if (conn == nullptr) {
			std::cerr << "Failed to get database connection" << std::endl;
			return 1;
		}
		std::cout << "Connected successfully" << std::endl;
		if ((mysql_query(conn, "SELECT VERSION(),DATABASE(),NOW()"))) {
			std::cerr << "mysql_query() failed: " << mysql_error(conn) << std::endl;
			return 1;
		}
		MYSQL_RES* res = mysql_store_result(conn);
		if (res == nullptr) {
			std::cerr << "mysql_store_result() failed: " << mysql_error(conn) << std::endl;
			return 1;
		}
		MYSQL_ROW row = mysql_fetch_row(res);
		if (row != nullptr) {
			std::cout << "版本" << row[0]<<std::endl;
			std::cout << "数据库" << row[1]<<std::endl;
			std::cout << "时间" << row[2]<<std::endl;
		}
		mysql_free_result(res);
	}
	catch (const std::exception& e) {
		std::cerr << "Exception: " << e.what() << std::endl;
		return 1;
	}
	return 0;
}