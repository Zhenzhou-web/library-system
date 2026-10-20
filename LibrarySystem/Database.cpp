#include"Database.h"
#include<string>
#include<stdexcept>	

Database::Database(const std::string & host, const std::string & user, const std::string & password, const std::string & database, unsigned int port) {
    conn_ = mysql_init(nullptr);
    if (conn_ == nullptr) throw std::runtime_error("mysql failed to initialize");
    mysql_options(conn_, MYSQL_SET_CHARSET_NAME, "utf8mb4");
    if (!mysql_real_connect(conn_, host.c_str(), user.c_str(), password.c_str(), database.c_str(), port, nullptr, 0)) {
        std::string message = "连接失败(" +
        std::to_string(mysql_errno(conn_)) + "): " +
        mysql_error(conn_);
        mysql_close(conn_);
        conn_ = nullptr;
        throw std::runtime_error(message);

    }
    mysql_set_character_set(conn_, "utf8mb4");
}
Database::~Database() {
	if (conn_ != nullptr) {
		mysql_close(conn_);
	}
}
