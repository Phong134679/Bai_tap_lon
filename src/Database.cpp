#include "../include/Database.h"
#include <iostream>

using namespace std;

Database::Database() : db(nullptr) {}

Database::~Database() {
    if (db) sqlite3_close(db);
}

bool Database::connect(const string& filename) {
    int exit = sqlite3_open(filename.c_str(), &db);
    if (exit) {
        cerr << "Error open DB: " << sqlite3_errmsg(db) << endl;
        return false;
    }
    return true;
}

bool Database::createUserTable() {
    string sql = "CREATE TABLE IF NOT EXISTS USERS(" \
                 "ID INTEGER PRIMARY KEY AUTOINCREMENT, " \
                 "USERNAME TEXT NOT NULL UNIQUE, " \
                 "PASSWORD TEXT NOT NULL, " \
                 "IS_AUTO INTEGER NOT NULL);";
    char* errMsg;
    int exit = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg);
    if (exit != SQLITE_OK) {
        cerr << "Error Create Table: " << errMsg << endl;
        sqlite3_free(errMsg);
        return false;
    }
    return true;
}

bool Database::userExists(const string& username) {
    string sql = "SELECT 1 FROM USERS WHERE USERNAME = ? LIMIT 1;";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) return false;
    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
    bool exists = (sqlite3_step(stmt) == SQLITE_ROW);
    sqlite3_finalize(stmt);
    return exists;
}

bool Database::insertUser(const string& username, const string& hashedPassword, bool isAuto) {
    string sql = "INSERT INTO USERS (USERNAME, PASSWORD, IS_AUTO) VALUES (?, ?, ?);";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) return false;
    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, hashedPassword.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 3, isAuto ? 1 : 0);
    bool success = (sqlite3_step(stmt) == SQLITE_DONE);
    sqlite3_finalize(stmt);
    return success;
}

bool Database::validateUser(const string& username, const string& hashedPassword, int& isAuto) {
    string sql = "SELECT IS_AUTO FROM USERS WHERE USERNAME = ? AND PASSWORD = ?;";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) return false;
    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, hashedPassword.c_str(), -1, SQLITE_STATIC);
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        isAuto = sqlite3_column_int(stmt, 0);
        sqlite3_finalize(stmt);
        return true;
    }
    sqlite3_finalize(stmt);
    return false;
}

bool Database::updatePassword(const string& username, const string& newHashedPassword) {
    string sql = "UPDATE USERS SET PASSWORD = ?, IS_AUTO = 0 WHERE USERNAME = ?;";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) return false;
    sqlite3_bind_text(stmt, 1, newHashedPassword.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, username.c_str(), -1, SQLITE_STATIC);
    bool success = (sqlite3_step(stmt) == SQLITE_DONE);
    sqlite3_finalize(stmt);
    return success;
}

sqlite3* Database::getDB() {
    return db;
}