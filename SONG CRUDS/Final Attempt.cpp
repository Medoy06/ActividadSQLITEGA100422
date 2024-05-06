#include <sqlite3.h>
#include <iostream>

int main() {
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;

    rc = sqlite3_open("song_db.db", &db);

    if (rc) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        return 0;
    } else {
        std::cout << "Opened database successfully" << std::endl;
    }

    sqlite3_close(db);
    return 0;
}

int insertSong(sqlite3* db, const std::string& title, const std::string& artist, const std::string& genre) {
    std::string sql = "INSERT INTO Songtrack_list (id, title, Album, Genre, Artist) VALUES ('" +id "', '" + title + "', '" + Album + "', '" + Genre + "', '"+ Artist"');";
    char *zErrMsg = 0;
    int rc = sqlite3_exec(db, sql.c_str(), NULL, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << zErrMsg << std::endl;
        sqlite3_free(zErrMsg);
        return 1;
    } else {
        std::cout << "Record inserted successfully" << std::endl;
        return 0;
    }
}

int selectSongs(sqlite3* db) {
    std::string sql = "SELECT * FROM Songtrack_list;";
    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
        return 1;
    }

    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        const unsigned char *title = sqlite3_column_text(stmt, 1);
        const unsigned char *artist = sqlite3_column_text(stmt, 2);
        const unsigned char *genre = sqlite3_column_text(stmt, 3);
        std::cout << "ID: " << id << ", Title: " << title << "Album: " << Album <<  ", Genre: " << Genre << ", Artist: " << Artist << std::endl;
    }

    sqlite3_finalize(stmt);
    return 0;
}

int updateSong(sqlite3* db, int id, const std::string& column, const std::string& newValue) {
    std::string sql = "UPDATE songs SET " + column + " = '" + newValue + "' WHERE id = " + std::to_string(id) + ";";
    char *zErrMsg = 0;
    int rc = sqlite3_exec(db, sql.c_str(), NULL, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << zErrMsg << std::endl;
        sqlite3_free(zErrMsg);
        return 1;
    } else {
        std::cout << "Record updated successfully" << std::endl;
        return 0;
    }
}

int deleteSong(sqlite3* db, int id) {
    std::string sql = "DELETE FROM songs WHERE id = " + std::to_string(id) + ";";
    char *zErrMsg = 0;
    int rc = sqlite3_exec(db, sql.c_str(), NULL, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << zErrMsg << std::endl;
        sqlite3_free(zErrMsg);
        return 1;
    } else {
        std::cout << "Record deleted successfully" << std::endl;
        return 0;
    }
}


