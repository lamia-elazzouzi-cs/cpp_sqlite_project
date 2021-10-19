#ifndef AGENCE_H
#define AGENCE_H

    #include <iostream>
    #include <string>
    #include <vector>
    #include <iomanip>

    #include "DBAbstraction.h"
    using namespace std;


    class Agence:DBAbstraction{
        public:

            // Constructor
            Agence(string pathToFile);

            //Table Vendeur(idVendeur,nomVendeur,adrVendeur,numVendeur):
            void insertVendeur(string nom, string adr, string num);
            void tableDisplayVendeur();
            void displayVendeurById(int idVendeur);
            void deleteVendeurById(int idVendeur);
            void updateVendeurById(int idVendeur, string nomV,string adrV,string numV);


            //Table Client(idClient,nomClient,adrClient,numClient):
            void insertClient(string nom, string adr, string num);
            void tableDisplayClient();
            void displayClientById(int idclient);
            void deleteClientById(int idClient);
            void updateClientById(int idClient, string nomC,string adrC,string numC);


            //Table BienImmo(idBien,typeBien,etatDeVente,idVendeur,prixInit,descrSurface):
            void insertBienImmo(string type,string etat,int idVendeur,string prix,string surface);
            void tableDisplayBienImmo();
            void displayBienImmoById(int idBienImmo);
            void deleteBienImmoById(int idBienImmo);
            void updateBienImmoById(int id, string type,string etat,int idVendeur,string prix,string surface);


            //Table RDV(idRDV,idClient,idBien,dateRDV,heureRDV):
            void insertRDV(int idClient,int idBien,string dateRDV,string heureRDV);
            void tableDisplayRDV();
            void displayRDVById(int idRDV);
            void deleteRDVById(int idRDV);
            void updateRDVById(int id,int idclient,int idbien,string daterdv,string heurerdv);


            //Table Contrat(idContrat,idBien,idVendeur,idClient,typePayement,sommePayement):
            void insertContrat(int idBien,int idVendeur,int idClient,string payement,string somme);
            void tableDisplayContrat();
            void displayContratyId(int idContrat);
            void deleteContratById(int idContrat);
            void updateContratById(int id,int idbien,int IdVendeur,int idclient,string typePaye,string somme);


        private:

            void createVendeurTable();
            void createClientTable();
            void createBienImmoTable();
            void createRDVTable();
            void createContratTable();
    };

#endif // AGENCE_H
