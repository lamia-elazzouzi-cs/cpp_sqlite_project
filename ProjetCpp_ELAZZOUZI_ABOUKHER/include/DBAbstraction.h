#ifndef DBABSTRACTION_H
#define DBABSTRACTION_H
#include "windows.h"
#include <string>
#include "../SQLite_files/sqlite3.h"

using namespace std;

class DBAbstraction{
    public:
        DBAbstraction(string pathToFile);
        ~DBAbstraction();

    protected:
        sqlite3* db;
        HANDLE hConsole;

        /* ***** HELPER METHODS : (to execute queries)***** */
        bool executeQueryNoResultsBack(sqlite3_stmt* myStatement);
        bool executeQueryNoResultsBack(string sql);
        bool prepareQueryWithResults(string sql, sqlite3_stmt*& myStatement);

    private:
};

#endif // DBABSTRACTION_H
