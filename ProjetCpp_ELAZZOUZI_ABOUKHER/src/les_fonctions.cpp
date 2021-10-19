#include "les_fonctions.h"

void showAllTables(Agence& db){

    cout<<"--------------------------------------Base de donnees: Agence"<<endl;
    system("pause");
    db.tableDisplayVendeur();
    system("pause");
    db.tableDisplayClient();
    system("pause");
    db.tableDisplayBienImmo();
    system("pause");
    db.tableDisplayRDV();
    system("pause");
    db.tableDisplayContrat();

    system("pause");
}

void generalMenu(Agence& db){

    int choix=-1;
    int goodbye=100;
    showAllTables(db);
    cout<<"Pour selectionner une table entrer son Id:"<<endl;
    cout<<"\t 1 (pour Vendeur)"<<endl;
    cout<<"\t 2 (pour Client)"<<endl;
    cout<<"\t 3 (pour BienImmo)"<<endl;
    cout<<"\t 4 (pour RDV)"<<endl;
    cout<<"\t 5 (pour Contrat)"<<endl;
    cout<<"\n\n\t Pour quitter le programme, entrer 0."<<endl;
    cout<<"Votre choix: ";
    cin>>choix;
    while(choix<0 || choix>5){
        cout<<"Donner un choix valide: ";
        cin>>choix;
    }

    system("cls");
    if(choix==1){
        try{
            menuTableVendeur(db);
        }catch(int goodbye){
            generalMenu(db);
        }
    }
    if(choix==2){
        try{
            menuTableClient(db);
        }catch(int goodbye){
            generalMenu(db);
        }
    }
    if(choix==3){
        try{
            menuTableBienImmo(db);
        }catch(int goodbye){
            generalMenu(db);
        }
    }
    if(choix==4){
        try{
            menuTableRDV(db);
        }catch(int goodbye){
            generalMenu(db);
        }
    }
    if(choix==5){
        try{
            menuTableContrat(db);
        }catch(int goodbye){
            generalMenu(db);
        }
    }

    if(choix==0){throw goodbye;}
}


void menuTableVendeur(Agence& db){
    int choix=0;
    system("cls");
    db.tableDisplayVendeur();
    system("pause");

    cout<<"\n\nOptions Table Vendeur:"<<endl;
    cout<<"\t ->Pour ajouter un Vendeur, entrer 0"<<endl;
    cout<<"\t ->Pour {modifier,consulter,supprimer}, entrer un ID qui figure dans la table"<<endl;
    cout<<"\t ->Pour abandonner, entrer 9999"<<endl;
    cout<<"\nVotre choix: ";
    cin>>choix;
    while(choix<0 || choix>9999){
        cout<<"Donner un choix valide: ";
        cin>>choix;
    }
    if(choix==0){
        // NOUVEAU VENDEUR :
        system("cls");cin.ignore();
        string nom=" ",adr=" ",num=" ";
        cout<<"Nouveau Vendeur: "<<endl;
        //infos:
        cout<<"\t-> Donner le Nom: ";
        getline(cin,nom);
        cout<<"\t-> Donner l\'adresse: ";
        getline(cin,adr);
        cout<<"\t-> Donner le numero de tel: ";
        getline(cin,num);
        cout<<endl<<"INFO: "<<nom<<" - "<<adr<<" - "<<num<<endl;
        db.insertVendeur(nom,adr,num);
        menuTableVendeur(db);
    }
    if(choix>0 && choix<9999){
        system("cls");
        db.displayVendeurById(choix);
        //Mini menu vendeur:
        int miniOption=0;
        cout<<"Si le vendeur numero"<<choix<<" existe, choisissez une des options suivantes:\n"<<endl;
        cout<<"Pour modifier le vendeur, entrer 1"<<endl;
        cout<<"Pour supprimer le vendeur, entrer 2"<<endl;
        cout<<"Pour abandonner, entrer 0"<<endl;
        cout<<"\nVotre choix: ";
        cin>>miniOption;
        while(miniOption>2){
            cout<<"Entrer une option valide: ";
            cin>>miniOption;
        }
        if(miniOption==1){
            // Opération de Modification:
            cin.ignore();
            string nom=" ",adr=" ",num=" ";
            cout<<"\t-> Donner le Nom: ";
            getline(cin,nom);
            cout<<"\t-> Donner l\'adresse: ";
            getline(cin,adr);
            cout<<"\t-> Donner le numero de tel: ";
            getline(cin,num);
            cout<<endl<<"INFO: "<<nom<<" - "<<adr<<" - "<<num<<endl;
            db.updateVendeurById(choix,nom,adr,num);
            menuTableVendeur(db);
        }
        if(miniOption==2){
            // Opération de suppression:
            db.deleteVendeurById(choix);
            menuTableVendeur(db);
        }
        if(miniOption==0){
            // Récursivité:
            menuTableVendeur(db);
        }
    }
    if(choix==9999){
        system("cls");
        throw choix;
    }

}


void menuTableClient(Agence& db){
    int choix=0;
    system("cls");
    db.tableDisplayClient();
    system("pause");

    cout<<"\n\nOptions Table Client:"<<endl;
    cout<<"\t ->Pour ajouter un Client, entrer 0"<<endl;
    cout<<"\t ->Pour {modifier,consulter,supprimer}, entrer un ID qui figure dans la table"<<endl;
    cout<<"\t ->Pour abandonner, entrer 9999"<<endl;
    cout<<"\nVotre choix: ";
    cin>>choix;
    while(choix<0 || choix>9999){
        cout<<"Donner un choix valide: ";
        cin>>choix;
    }
    if(choix==0){
        // NOUVEAU CLIENT :
        system("cls");
        cin.ignore();

        string nom=" ",adr=" ",num=" ";
        cout<<"Nouveau Vendeur: "<<endl;
        //infos:
        cout<<"\t-> Donner le Nom: ";
        getline(cin,nom);
        cout<<"\t-> Donner l\'adresse: ";
        getline(cin,adr);
        cout<<"\t-> Donner le numero de tel: ";
        getline(cin,num);
        cout<<endl<<"INFO: "<<nom<<" - "<<adr<<" - "<<num<<endl;
        db.insertClient(nom,adr,num);
        menuTableClient(db);
    }
    if(choix>0 && choix<9999){
        system("cls");
        db.displayClientById(choix);
        //Mini menu Client:
        int miniOption=0;
        cout<<"Si le client numero"<<choix<<" existe, choisissez une des options suivantes:\n"<<endl;
        cout<<"Pour modifier le client, entrer 1"<<endl;
        cout<<"Pour supprimer le client, entrer 2"<<endl;
        cout<<"Pour abandonner, entrer 0"<<endl;
        cout<<"\nVotre choix: ";
        cin>>miniOption;
        while(miniOption>2 || miniOption<0){
            cout<<"Entrer une option valide: ";
            cin>>miniOption;
        }
        if(miniOption==1){
            // Opération de Modification:
            cin.ignore();
            string nom=" ",adr=" ",num=" ";
            cout<<"\t-> Donner le Nom: ";
            getline(cin,nom);
            cout<<"\t-> Donner l\'adresse: ";
            getline(cin,adr);
            cout<<"\t-> Donner le numero de tel: ";
            getline(cin,num);
            cout<<endl<<"INFO: "<<nom<<" - "<<adr<<" - "<<num<<endl;
            db.updateClientById(choix,nom,adr,num);
            menuTableClient(db);
        }
        if(miniOption==2){
            // Opération de suppression:
            db.deleteClientById(choix);
            menuTableClient(db);
        }
        if(miniOption==0){
            // Récursivité:
            menuTableClient(db);
        }
    }
    if(choix==9999){
        system("cls");
        throw choix;
    }

}


void menuTableBienImmo(Agence& db){
    int choix=0;
    system("cls");
    db.tableDisplayBienImmo();
    system("pause");

    cout<<"\n\nOptions Table BienImmo:"<<endl;
    cout<<"\t ->Pour ajouter un BienImmo, entrer 0"<<endl;
    cout<<"\t ->Pour {modifier,consulter,supprimer}, entrer un ID qui figure dans la table"<<endl;
    cout<<"\t ->Pour abandonner, entrer 9999"<<endl;
    cout<<"\nVotre choix: ";
    cin>>choix;
    while(choix<0 || choix>9999){
        cout<<"Donner un choix valide: ";
        cin>>choix;
    }
    if(choix==0){
        // NOUVEAU BienIMMO :
        system("cls");
        cin.ignore();

        string type=" ",etat=" ",prix=" ",descr=" ";
        int idvendeur;
        cout<<"Nouveau BienImmo: "<<endl;
        //infos:
        cout<<"\t-> Donner le type de l\'immobilier: ";
        getline(cin,type);
        cout<<"\t-> Donner l\'etat de vente: ";
        getline(cin,etat);
        cout<<"\t-> Donner le prix de vente initial: ";
        getline(cin,prix);
        cout<<"\t-> Donner les specifications de l'immobilier: ";
        getline(cin,descr);
        cout<<"\t-> Donner l\'id du Vendeur: ";
        cin>>idvendeur;
        db.insertBienImmo(type,etat,idvendeur,prix,descr);
        menuTableBienImmo(db);
    }
    if(choix>0 && choix<9999){
        system("cls");
        db.displayBienImmoById(choix);
        //Mini menu Client:
        int miniOption=0;
        cout<<"Si le BienImmo numero"<<choix<<" existe, choisissez une des options suivantes:\n"<<endl;
        cout<<"Pour modifier le BienImmo, entrer 1"<<endl;
        cout<<"Pour supprimer le BienImmo, entrer 2"<<endl;
        cout<<"Pour abandonner, entrer 0"<<endl;
        cout<<"\nVotre choix: ";
        cin>>miniOption;
        while(miniOption>2 || miniOption<0){
            cout<<"Entrer une option valide: ";
            cin>>miniOption;
        }
        if(miniOption==1){
            // Opération de Modification:
            cin.ignore();
            string type=" ",etat=" ",prix=" ",descr=" ";
            int idvendeur;
            cout<<"Nouveau BienImmo: "<<endl;
            //infos:
            cout<<"\t-> Donner le type de l\'immobilier: ";
            getline(cin,type);
            cout<<"\t-> Donner l\'etat de vente: ";
            getline(cin,etat);
            cout<<"\t-> Donner le prix de vente initial: ";
            getline(cin,prix);
            cout<<"\t-> Donner les specifications de l'immobilier: ";
            getline(cin,descr);
            cout<<"\t-> Donner l\'id du Vendeur: ";
            cin>>idvendeur;
            db.updateBienImmoById(choix,type,etat,idvendeur,prix,descr);
            menuTableBienImmo(db);
        }
        if(miniOption==2){
            // Opération de suppression:
            db.deleteBienImmoById(choix);
            menuTableBienImmo(db);
        }
        if(miniOption==0){
            // Récursivité:
            menuTableBienImmo(db);
        }
    }
    if(choix==9999){
        system("cls");
        throw choix;
    }

}

void menuTableRDV(Agence& db){
    int choix=0;
    system("cls");
    db.tableDisplayRDV();
    system("pause");

    cout<<"\n\nOptions Table RDV:"<<endl;
    cout<<"\t ->Pour ajouter un RDV, entrer 0"<<endl;
    cout<<"\t ->Pour {modifier,consulter,supprimer}, entrer un ID qui figure dans la table"<<endl;
    cout<<"\t ->Pour abandonner, entrer 9999"<<endl;
    cout<<"\nVotre choix: ";
    cin>>choix;
    while(choix<0 || choix>9999){
        cout<<"Donner un choix valide: ";
        cin>>choix;
    }
    if(choix==0){
        // NOUVEAU RDV :
        system("cls");
        cin.ignore();

        string date=" ",heure=" ";
        int idclient,idbien;
        cout<<"Nouveau RDV: "<<endl;
        //infos:
        cout<<"\t-> Donner la date du RDV: ";
        getline(cin,date);
        cout<<"\t-> Donner l\'heure du RDV: ";
        getline(cin,heure);
        cout<<"\t-> Donner l\'ID du Client: ";
        cin>>idclient;
        cout<<"\t-> Donner l\'ID du BienImmo: ";
        cin>>idbien;
        db.insertRDV(idclient,idbien,date,heure);
        menuTableRDV(db);
    }
    if(choix>0 && choix<9999){
        system("cls");
        db.displayRDVById(choix);
        //Mini menu RDV:
        int miniOption=0;
        cout<<"Si le RDV numero"<<choix<<" existe, choisissez une des options suivantes:\n"<<endl;
        cout<<"Pour modifier le RDV, entrer 1"<<endl;
        cout<<"Pour supprimer le RDV, entrer 2"<<endl;
        cout<<"Pour abandonner, entrer 0"<<endl;
        cout<<"\nVotre choix: ";
        cin>>miniOption;
        while(miniOption>2 || miniOption<0){
            cout<<"Entrer une option valide: ";
            cin>>miniOption;
        }
        if(miniOption==1){
            // Opération de Modification:
            cin.ignore();

            cout<<"Nouveau RDV: "<<endl;
            //infos:
            string date=" ",heure=" ";
            int idclient,idbien;
            cout<<"Nouveau RDV: "<<endl;
            //infos:
            cout<<"\t-> Donner la date du RDV: ";
            getline(cin,date);
            cout<<"\t-> Donner l\'heure du RDV: ";
            getline(cin,heure);
            cout<<"\t-> Donner l\'ID du Client: ";
            cin>>idclient;
            cout<<"\t-> Donner l\'ID du BienImmo: ";
            cin>>idbien;

            db.updateRDVById(choix,idclient,idbien,date,heure);
            menuTableRDV(db);
        }
        if(miniOption==2){
            // Opération de suppression:
            db.deleteRDVById(choix);
            menuTableRDV(db);
        }
        if(miniOption==0){
            // Récursivité:
            menuTableRDV(db);
        }
    }
    if(choix==9999){
        system("cls");
        throw choix;
    }

}


void menuTableContrat(Agence& db){
    int choix=0;
    system("cls");
    db.tableDisplayContrat();
    system("pause");

    cout<<"\n\nOptions Table Contrat:"<<endl;
    cout<<"\t ->Pour ajouter un Contrat, entrer 0"<<endl;
    cout<<"\t ->Pour {modifier,consulter,supprimer}, entrer un ID qui figure dans la table"<<endl;
    cout<<"\t ->Pour abandonner, entrer 9999"<<endl;
    cout<<"\nVotre choix: ";
    cin>>choix;
    while(choix<0 || choix>9999){
        cout<<"Donner un choix valide: ";
        cin>>choix;
    }
    if(choix==0){
        // NOUVEAU RDV :
        system("cls");
        cin.ignore();

        string typepaye=" ",sommepaye=" ";
        int idclient,idbien,idvendeur;
        cout<<"Nouveau RDV: "<<endl;
        //infos:
        cout<<"\t-> Donner le type de payement: ";
        getline(cin,typepaye);
        cout<<"\t-> Donner la somme payee: ";
        getline(cin,sommepaye);
        cout<<"\t-> Donner l\'ID du Client: ";
        cin>>idclient;
        cout<<"\t-> Donner l\'ID du BienImmo: ";
        cin>>idbien;
        cout<<"\t-> Donner l\'ID du Vendeur: ";
        cin>>idvendeur;

        db.insertContrat(idbien,idvendeur,idclient,typepaye,sommepaye);

        menuTableContrat(db);
    }
    if(choix>0 && choix<9999){
        system("cls");
        db.displayContratyId(choix);
        //Mini menu Contrat:
        int miniOption=0;
        cout<<"Si le Contrat numero"<<choix<<" existe, choisissez une des options suivantes:\n"<<endl;
        cout<<"Pour modifier le contrat, entrer 1"<<endl;
        cout<<"Pour supprimer le contrat, entrer 2"<<endl;
        cout<<"Pour abandonner, entrer 0"<<endl;
        cout<<"\nVotre choix: ";
        cin>>miniOption;
        while(miniOption>2 || miniOption<0){
            cout<<"Entrer une option valide: ";
            cin>>miniOption;
        }
        if(miniOption==1){
            // Opération de Modification://Table Contrat(idContrat,idBien,idVendeur,idClient,typePayement,sommePayement):
            cin.ignore();

            cout<<"Nouveau Contrat: "<<endl;
            //infos:

            string typepaye=" ",sommepaye=" ";
            int idclient,idbien,idvendeur;
            cout<<"\t-> Donner le type de payement: ";
            getline(cin,typepaye);
            cout<<"\t-> Donner la somme payee: ";
            getline(cin,sommepaye);
            cout<<"\t-> Donner l\'ID du Client: ";
            cin>>idclient;
            cout<<"\t-> Donner l\'ID du BienImmo: ";
            cin>>idbien;
            cout<<"\t-> Donner l\'ID du Vendeur: ";
            cin>>idvendeur;


            db.updateContratById(choix,idbien,idvendeur,idclient,typepaye,sommepaye);
            menuTableContrat(db);
        }
        if(miniOption==2){
            // Opération de suppression:
            db.deleteContratById(choix);
            menuTableContrat(db);
        }
        if(miniOption==0){
            // Récursivité:
            menuTableContrat(db);
        }
    }
    if(choix==9999){
        system("cls");
        throw choix;
    }

}


