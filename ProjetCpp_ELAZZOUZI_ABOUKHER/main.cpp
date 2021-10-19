#include <iostream>
#include <string>
#include <stdlib.h>
#include "windows.h"
#include "SQLite_files/sqlite3.h"
#include "DBAbstraction.h"
#include "Agence.h"
#include "les_fonctions.h"
using namespace std;
int main()
{
    try{
        //create/open an Agence db abstraction object
        Agence db("SQLite_DB\\AgenceDB.sqlite");
        system("pause");
        system("cls");

        try{
            generalMenu(db);
        }catch(int goodbye){
            return 1;
        }

    }catch(int goodbye){
        return 1;
    }
    return 0;
}

