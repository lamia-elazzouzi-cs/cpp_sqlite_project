#ifndef LES_FONCTIONS_H
#define LES_FONCTIONS_H

#include "windows.h"
#include "DBAbstraction.h"
#include "Agence.h"

using namespace std;


void showAllTables(Agence& db);

void menuTableVendeur(Agence& db);
void menuTableClient(Agence& db);
void menuTableBienImmo(Agence& db);
void menuTableRDV(Agence& db);
void menuTableContrat(Agence& db);

void generalMenu(Agence& db);

#endif // LES_FONCTIONS_H
