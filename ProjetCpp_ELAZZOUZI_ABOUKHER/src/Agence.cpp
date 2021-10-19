#include "Agence.h"

// Filler text template:
template<typename T> void printElement(T t, const int& width, const char& separator){
    cout << left << setw(width) << setfill(separator) << t;
}

// Constructor:
Agence::Agence(string pathToFile) : DBAbstraction(pathToFile){

    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

//Creating the "Agence" Tables:
    SetConsoleTextAttribute(hConsole, 8);
    createVendeurTable();
    createClientTable();
    createBienImmoTable();
    createRDVTable();
    createContratTable();
    SetConsoleTextAttribute(hConsole, 15);

}


// ___________________________Création base de données -Agence- et tables:
void Agence::createVendeurTable(){
    //Table Vendeur(idVendeur,nomVendeur,adrVendeur,numVendeur)
    string sql = "CREATE TABLE if NOT EXISTS Vendeur (idVendeur INTEGER PRIMARY key AUTOINCREMENT, nomVendeur TEXT NOT NULL, adrVendeur TEXT, numVendeur TEXT NOT NULL);";
    //execute the query to create the table
    if (!executeQueryNoResultsBack(sql)){
        cout<<"---> Creating table \'Vendeur\': Failed!"<< endl;
    }
    cout<<"---> Creating table \'Vendeur\': Successful!"<<endl;
}
void Agence::createClientTable(){
    //Table Client(idClient,nomClient,adrClient,numClient)
    string sql = "CREATE TABLE if NOT EXISTS Client(idClient INTEGER PRIMARY key AUTOINCREMENT,nomClient TEXT NOT NULL,adrClient TEXT,numClient TEXT NOT NULL);";
    //execute the query to create the table
    if (!executeQueryNoResultsBack(sql)){
        cout<<"---> Creating table \'Client\': Failed!"<< endl;
    }
    cout<<"---> Creating table \'Client\': Successful!"<<endl;
}
void Agence::createBienImmoTable(){
    //Table BienImmo(idBien,typeBien,etatDeVente,idVendeur,prixInit,descrSurface)
    string sql = "CREATE TABLE if NOT EXISTS BienImmo(idBien INTEGER PRIMARY key AUTOINCREMENT,typeBien TEXT NOT NULL,etatDeVente TEXT NOT NULL,idVendeur INTEGER NOT NULL,prixInit TEXT NOT NULL,descrSurface TEXT NOT NULL,FOREIGN KEY(idVendeur) REFERENCES Vendeur(idvendeur) ON DELETE CASCADE);";
    //execute the query to create the table
    if (!executeQueryNoResultsBack(sql)){
        cout<<"---> Creating table \'BienImmo\': Failed!"<< endl;
    }
    cout<<"---> Creating table \'BienImmo\': Successful!"<<endl;
}
void Agence::createRDVTable(){
    //Table RDV(idRDV,idClient,idBien,dateRDV,heureRDV)
    string sql = "CREATE TABLE if NOT EXISTS RDV (idRDV INTEGER PRIMARY key AUTOINCREMENT,idClient INTEGER NOT NULL,idBien INTEGER NOT NULL ,dateRDV TEXT NOT NULL,heureRDV TEXT NOT NULL,FOREIGN KEY(idClient) REFERENCES Client(idClient) ON DELETE CASCADE,FOREIGN KEY(idBien) REFERENCES BienImmo(idBien) ON DELETE CASCADE);";
    //execute the query to create the table
    if (!executeQueryNoResultsBack(sql)){
        cout<<"---> Creating table \'RDV\': Failed!"<< endl;
    }
    cout<<"---> Creating table \'RDV\': Successful!"<<endl;
}
void Agence::createContratTable(){
    //Table (idContrat,idBien,idVendeur,idClient,typePayement,sommePayement)
    string sql = "CREATE TABLE if NOT EXISTS Contrat(idContrat INTEGER PRIMARY key AUTOINCREMENT,idBien INTEGER NOT NULL,idVendeur INTEGER NOT NULL,idClient INTEGER NOT NULL,typePayement TEXT NOT NULL,sommePayement TEXT NOT NULL,FOREIGN KEY(idClient) REFERENCES Client(idClient) ON DELETE CASCADE,FOREIGN KEY(idBien) REFERENCES BienImmo(idBien) ON DELETE CASCADE,FOREIGN KEY(idVendeur) REFERENCES Vendeur(idvendeur) ON DELETE CASCADE);";
    //execute the query to create the table
    if (!executeQueryNoResultsBack(sql)){
        cout<<"---> Creating table \'Contrat\': Failed!"<< endl;
    }
    cout<<"---> Creating table \'Contrat\': Successful!"<<endl;
}


// ________________________________________Operation for table 'Vendeur':
void Agence::insertVendeur(string nom, string adr, string num){
//query to insert a user
    string sql = "INSERT into Vendeur(nomVendeur,adrVendeur,numVendeur) VALUES (?,?,?);";
//create a statement pointer
    sqlite3_stmt* myStatement;
//create the statement object using the prepare()
    int statusOfPrep = sqlite3_prepare_v2(db, sql.c_str(), -1, &myStatement, NULL);
//check to see if the prepared statement was created
    if (statusOfPrep == SQLITE_OK){
//add parameters
        sqlite3_bind_text(myStatement, 1, nom.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(myStatement, 2, adr.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(myStatement, 3, num.c_str(), -1, SQLITE_STATIC);
//execute the query to insert a new user
        if (!executeQueryNoResultsBack(myStatement)){
            cout <<"---> Insertion into table Vendeur: Failed!"<< endl;
        }
        cout<<"---> Insertion into table Vendeur: Successful!"<<endl;
    }
}
void Agence::displayVendeurById(int idVendeur){
    bool indice=true;
    string vendeurNom="1",vendeurAdr="2",vendeurNum="3";

    string sql = "SELECT nomVendeur,adrVendeur,numVendeur FROM Vendeur where idVendeur=?;";
    sqlite3_stmt* myStatement;

    if (prepareQueryWithResults(sql, myStatement)){

        sqlite3_bind_int(myStatement, 1, idVendeur);

        int statusOfStep = sqlite3_step(myStatement);

        //if there is a row
        if (statusOfStep == SQLITE_ROW){
            //get the info
            vendeurNom=((char*)sqlite3_column_text(myStatement, 0));
            vendeurAdr=((char*)sqlite3_column_text(myStatement, 1));
            vendeurNum=((char*)sqlite3_column_text(myStatement, 2));
        }else{
            SetConsoleTextAttribute(hConsole, 12);
            cout<<"\nLe Vendeur avec l'id="<<idVendeur<<", n\'existe pas."<<endl;
            indice=false;
        }
        if(indice){
            SetConsoleTextAttribute(hConsole, 10);
            cout<<"\n-> Informations recuperees depuis la table \'Vendeur\': "<<endl;
            cout<<"\tID= "<<idVendeur<<endl;
            cout<<"\tNOM VENDEUR= "<<vendeurNom<<endl;
            cout<<"\tADRESSE VENDEUR= "<<vendeurAdr<<endl;
            cout<<"\tNUMERO DE TEL= "<<vendeurNum<<endl;

        }
        sqlite3_finalize(myStatement);
    }
    SetConsoleTextAttribute(hConsole, 15);

}
void Agence::deleteVendeurById(int idVendeur){
    cout<<"---> INFO vendeur to delete:"<<endl;
    displayVendeurById(idVendeur);

    string sql = "";
    sqlite3_stmt* myStatement;

    sql="DELETE FROM Vendeur WHERE idvendeur=?;";

    int statusOfPrep = sqlite3_prepare_v2(db, sql.c_str(), -1, &myStatement, NULL);
    if (statusOfPrep == SQLITE_OK){

        sqlite3_bind_int(myStatement, 1, idVendeur);

        if (!executeQueryNoResultsBack(myStatement)){

            cout <<"---> Deleting row from table Vendeur: Failed!"<< endl;
        }
        cout<<"---> Deleting row from table Vendeur: Successful!"<<endl;
    }

}
void Agence::updateVendeurById(int idVendeur, string nomV,string adrV,string numV){
    cout<<"---> INFO vendeur to delete:"<<endl;
    displayVendeurById(idVendeur);
    string sql="UPDATE Vendeur SET nomVendeur='"+nomV+"',adrVendeur='"+adrV+"',numVendeur='"+numV+"' where idVendeur=?;";
    sqlite3_stmt* myStatement;

    int statusOfPrep = sqlite3_prepare_v2(db, sql.c_str(), -1, &myStatement, NULL);

    if (statusOfPrep == SQLITE_OK){
        sqlite3_bind_int(myStatement, 1, idVendeur);
        if (!executeQueryNoResultsBack(myStatement)){
            cout <<"---> Updating table Vendeur: Failed!"<< endl;
        }
        cout<<"---> Updating table Vendeur: Successful!"<<endl;
    }

}
void Agence::tableDisplayVendeur(){

    string sql = "SELECT idVendeur,nomVendeur,adrVendeur,numVendeur FROM Vendeur;"; //query to get all of the users
    sqlite3_stmt* myStatement;  //create a statement pointer

    vector < int > vendeurIds;
    vector < string > vendeurNoms;
    vector < string > vendeurAdrs;
    vector < string > vendeurNums;

    if (prepareQueryWithResults(sql, myStatement)){	//get a statement to iterate through

        int statusOfStep = sqlite3_step(myStatement);	//get a row from the query
        int numeral = 1;	//for printing an option number

        while (statusOfStep == SQLITE_ROW){	//while there are more rows
            int id = sqlite3_column_int(myStatement, 0);	//get the user id from the row

            string nom((char*)sqlite3_column_text(myStatement, 1));
            string adr((char*)sqlite3_column_text(myStatement, 2));
            string num((char*)sqlite3_column_text(myStatement, 3));


            vendeurIds.push_back(id);
            vendeurNoms.push_back(nom);
            vendeurAdrs.push_back(adr);
            vendeurNums.push_back(num);


            numeral++;
            statusOfStep = sqlite3_step(myStatement);	//get the next row
        }
        sqlite3_finalize(myStatement);	//clean up and destroy the statement

//OCD-friendly display of the table: "| idVendeur | nomVendeur | adrVendeur | numVendeur |"
        SetConsoleTextAttribute(hConsole, 11);
        cout<<"Affichage table \' Vendeur \'"<<endl;
        SetConsoleTextAttribute(hConsole, 23);
        const char separator= ' ';
        const string descr0="Id";
        const string descr1="Nom et prenom";
        const string descr2="Adresse";
        const string descr3="numero de tel";

        int idWidth       = 5;
        int nomWidth      = descr1.size();
        int adresseWidth  = descr2.size();
        int numWidth      = descr3.size();

        int nbr=vendeurIds.size();

        for(int i=0;i<nbr;i++){
            int a=vendeurNoms[i].size();
            if(a>nomWidth){
                nomWidth=a;
            }
            a=vendeurNums[i].size();
            if(a>numWidth){
                numWidth=a;
            }
            a=vendeurAdrs[i].size();
            if(a>adresseWidth){
                adresseWidth=a;
            }
        }
        for(int j=0;j<(idWidth+nomWidth+adresseWidth+numWidth+4+3*3);j++){
            cout<<"-";
        }
        cout<<"\n| ";
        printElement(descr0,idWidth,separator);
        cout<<" | ";
        printElement(descr1,nomWidth,separator);
        cout<<" | ";
        printElement(descr2,adresseWidth,separator);
        cout<<" | ";
        printElement(descr3,numWidth,separator);
        cout<<" |"<<endl;

        for(int i=0;i<nbr;i++){
            for(int j=0;j<(idWidth+nomWidth+adresseWidth+numWidth+4+3*3);j++){
                cout<<"-";
            }
            cout<<endl;
            cout<<"| ";
            printElement(vendeurIds[i],idWidth,separator);
            cout<<" | ";
            printElement(vendeurNoms[i],nomWidth,separator);
            cout<<" | ";
            printElement(vendeurAdrs[i],adresseWidth,separator);
            cout<<" | ";
            printElement(vendeurNums[i],numWidth,separator);
            cout<<" |";
            cout<<endl;
        }
        for(int j=0;j<(idWidth+nomWidth+adresseWidth+numWidth+4+3*3);j++){
                cout<<"-";
        }



    }
    cout<<endl;
    SetConsoleTextAttribute(hConsole, 15);
}


// _________________________________________Operation for table 'Client':
void Agence::insertClient(string nom, string adr, string num){

    string sql = "INSERT into Client(nomClient,adrClient,numClient) VALUES (?,?,?);";
    sqlite3_stmt* myStatement;

    int statusOfPrep = sqlite3_prepare_v2(db, sql.c_str(), -1, &myStatement, NULL);
    if (statusOfPrep == SQLITE_OK){

        sqlite3_bind_text(myStatement, 1, nom.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(myStatement, 2, adr.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(myStatement, 3, num.c_str(), -1, SQLITE_STATIC);

        if (!executeQueryNoResultsBack(myStatement)){
            cout <<"---> Insertion into table Client: Failed!"<< endl;
        }
        cout<<"---> Insertion into table Client: Successful!"<<endl;
    }
}
void Agence::tableDisplayClient(){
    string sql = "SELECT idClient,nomClient,adrClient,numClient FROM Client;";
    sqlite3_stmt* myStatement;

    vector < int > clientIds;
    vector < string > clientNoms;
    vector < string > clientAdrs;
    vector < string > clientNums;

    if (prepareQueryWithResults(sql, myStatement)){

        int statusOfStep = sqlite3_step(myStatement);
        int numeral = 1;

        while (statusOfStep == SQLITE_ROW){
            int id = sqlite3_column_int(myStatement, 0);

            string nom((char*)sqlite3_column_text(myStatement, 1));
            string adr((char*)sqlite3_column_text(myStatement, 2));
            string num((char*)sqlite3_column_text(myStatement, 3));


            clientIds.push_back(id);
            clientNoms.push_back(nom);
            clientAdrs.push_back(adr);
            clientNums.push_back(num);


            numeral++;
            statusOfStep = sqlite3_step(myStatement);
        }
        sqlite3_finalize(myStatement);

//OCD-friendly display of the table: "| idClient |nomClient |adrClient | numClient |"
        SetConsoleTextAttribute(hConsole, 11);
        cout<<"Affichage \' Client \'"<<endl;
        SetConsoleTextAttribute(hConsole, 23);
        const char separator= ' ';
        const string descr0="Id";
        const string descr1="Nom et prenom";
        const string descr2="Adresse";
        const string descr3="numero de tel";

        int idWidth       = 5;
        int nomWidth      = descr1.size();
        int adresseWidth  = descr2.size();
        int numWidth      = descr3.size();

        int nbr=clientIds.size();

        for(int i=0;i<nbr;i++){
            int a=clientNoms[i].size();
            if(a>nomWidth){
                nomWidth=a;
            }
            a=clientNums[i].size();
            if(a>numWidth){
                numWidth=a;
            }
            a=clientAdrs[i].size();
            if(a>adresseWidth){
                adresseWidth=a;
            }
        }
        for(int j=0;j<(idWidth+nomWidth+adresseWidth+numWidth+4+3*3);j++){
            cout<<"-";
        }
        cout<<"\n| ";
        printElement(descr0,idWidth,separator);
        cout<<" | ";
        printElement(descr1,nomWidth,separator);
        cout<<" | ";
        printElement(descr2,adresseWidth,separator);
        cout<<" | ";
        printElement(descr3,numWidth,separator);
        cout<<" |"<<endl;

        for(int i=0;i<nbr;i++){
            for(int j=0;j<(idWidth+nomWidth+adresseWidth+numWidth+4+3*3);j++){
                cout<<"-";
            }
            cout<<endl;
            cout<<"| ";
            printElement(clientIds[i],idWidth,separator);
            cout<<" | ";
            printElement(clientNoms[i],nomWidth,separator);
            cout<<" | ";
            printElement(clientAdrs[i],adresseWidth,separator);
            cout<<" | ";
            printElement(clientNums[i],numWidth,separator);
            cout<<" |";
            cout<<endl;
        }
        for(int j=0;j<(idWidth+nomWidth+adresseWidth+numWidth+4+3*3);j++){
                cout<<"-";
        }



    }
    cout<<endl;
    SetConsoleTextAttribute(hConsole, 15);
}
void Agence::displayClientById(int idClient){
    bool indice=true;
    string clientNom="1",clientAdr="2",clientNum="3";

    string sql = "SELECT nomClient,adrClient,numClient FROM Client where idClient=?;";
    sqlite3_stmt* myStatement;

    if (prepareQueryWithResults(sql, myStatement)){

        sqlite3_bind_int(myStatement, 1, idClient);

        int statusOfStep = sqlite3_step(myStatement);

        //if there is a row
        if (statusOfStep == SQLITE_ROW){
            //get the info
            clientNom=((char*)sqlite3_column_text(myStatement, 0));
            clientAdr=((char*)sqlite3_column_text(myStatement, 1));
            clientNum=((char*)sqlite3_column_text(myStatement, 2));
        }else{
            SetConsoleTextAttribute(hConsole, 12);
            cout<<"\nLe Client avec l'id="<<idClient<<", n\'existe pas."<<endl;
            indice=false;
        }
        sqlite3_finalize(myStatement);
        if(indice){
            SetConsoleTextAttribute(hConsole, 10);
            cout<<"\n-> Information recuperees depuis la table \'Client\': "<<endl;
            cout<<"\tID= "<<idClient<<endl;
            cout<<"\tNOM= "<<clientNom<<endl;
            cout<<"\tADRESSE= "<<clientAdr<<endl;
            cout<<"\tNUMERO= "<<clientNum<<endl;
        }
    }
    SetConsoleTextAttribute(hConsole, 15);

}
void Agence::deleteClientById(int idClient){
    cout<<"---> INFO Client to delete:"<<endl;
    displayClientById(idClient);

    string sql = "DELETE from Client where idClient=?;";
    sqlite3_stmt* myStatement;

    int statusOfPrep = sqlite3_prepare_v2(db, sql.c_str(), -1, &myStatement, NULL);
    if (statusOfPrep == SQLITE_OK){

        sqlite3_bind_int(myStatement, 1, idClient);

        if (!executeQueryNoResultsBack(myStatement)){

            cout <<"---> Deleting row from table Client Failed!"<< endl;
        }
        cout<<"---> Deleting row from table Client: Successful!"<<endl;
    }

}
void Agence::updateClientById(int idClient, string nomC,string adrC,string numC){
    cout<<"---> INFO Client to Update:"<<endl;
    displayClientById(idClient);
    string sql="UPDATE Client SET nomClient='"+nomC+"',adrClient='"+adrC+"',numClient='"+numC+"' where idClient=?;";
    sqlite3_stmt* myStatement;

    int statusOfPrep = sqlite3_prepare_v2(db, sql.c_str(), -1, &myStatement, NULL);

    if (statusOfPrep == SQLITE_OK){
        sqlite3_bind_int(myStatement, 1, idClient);
        if (!executeQueryNoResultsBack(myStatement)){
            cout <<"---> Updating table Client: Failed!"<< endl;
        }
        cout<<"---> Updating table Client: Successful!"<<endl;
    }

}


// _______________________________________Operation for table 'BienImmo':
void Agence::insertBienImmo(string type,string etat,int idVendeur,string prix,string surface){
    //Table BienImmo(idBien,typeBien,etatDeVente,idVendeur,prixInit,descrSurface)
    string sql = "INSERT into BienImmo(typeBien,etatDeVente,idVendeur,prixInit,descrSurface) VALUES (?,?,?,?,?);";
    sqlite3_stmt* myStatement;

    int statusOfPrep = sqlite3_prepare_v2(db, sql.c_str(), -1, &myStatement, NULL);
    if (statusOfPrep == SQLITE_OK){

        sqlite3_bind_text(myStatement, 1, type.c_str(),    -1, SQLITE_STATIC);
        sqlite3_bind_text(myStatement, 2, etat.c_str(),    -1, SQLITE_STATIC);
        sqlite3_bind_int(myStatement,  3, idVendeur);
        sqlite3_bind_text(myStatement, 4, prix.c_str(),    -1, SQLITE_STATIC);
        sqlite3_bind_text(myStatement, 5, surface.c_str(), -1, SQLITE_STATIC);

        if (!executeQueryNoResultsBack(myStatement)){
            cout <<"---> Insertion into table BienImmo: Failed!"<< endl;
        }
        cout<<"---> Insertion into table BienImmo: Successful!"<<endl;
    }
}
void Agence::tableDisplayBienImmo(){

    string sql = "SELECT idBien,typeBien,etatDeVente,idVendeur,prixInit,descrSurface FROM BienImmo;";
    sqlite3_stmt* myStatement;

    vector < int > immoIds;
    vector < string > immoTypes;
    vector < string > immoEtatVente;
    vector < int > vendeursIds;
    vector < string > immoPrix;
    vector < string > immoSurface;

    if (prepareQueryWithResults(sql, myStatement)){

        int statusOfStep = sqlite3_step(myStatement);
        int numeral = 1;

        while (statusOfStep == SQLITE_ROW){

            int id = sqlite3_column_int(myStatement, 0);
            string type((char*)sqlite3_column_text(myStatement, 1));
            string etat((char*)sqlite3_column_text(myStatement, 2));
            int vendeurId=sqlite3_column_int(myStatement, 3);;
            string prix((char*)sqlite3_column_text(myStatement, 4));
            string surface((char*)sqlite3_column_text(myStatement, 5));

            immoIds.push_back(id);
            immoTypes.push_back(type);
            immoEtatVente.push_back(etat);
            vendeursIds.push_back(vendeurId);
            immoPrix.push_back(prix);
            immoSurface.push_back(surface);

            numeral++;
            statusOfStep = sqlite3_step(myStatement);
        }
        sqlite3_finalize(myStatement);

//OCD-friendly display of the table: "| idBien | typeBien | etatDeVente | idVendeur | prixInit | descrSurface |"
        SetConsoleTextAttribute(hConsole, 11);
        cout<<"Affichage table \' BienImmo \'"<<endl;
        SetConsoleTextAttribute(hConsole, 23);
        const char separator= ' ';

        const string descr0="Id";
        const string descr1="Type BienImmo";
        const string descr2="Etat vente";
        const string descr3="Id Vendeur";
        const string descr4="Prix Initial";
        const string descr5="Description";

        int idWidth               = 5;
        int typeWidth             = descr1.size();
        int etatWidth             = descr2.size();
        int idVendeurWidth        = descr3.size();
        int prixWidth             = descr4.size();
        int descriptionWidth      = descr5.size();

        int nbr=immoIds.size();

        for(int i=0;i<nbr;i++){
            int a=immoTypes[i].size();
            if(a>typeWidth){
                typeWidth=a;
            }
            a=immoEtatVente[i].size();
            if(a>etatWidth){
                etatWidth=a;
            }
            a=immoPrix[i].size();
            if(a>prixWidth){
                prixWidth=a;
            }
            a=immoSurface[i].size();
            if(a>descriptionWidth){
                descriptionWidth=a;
            }
        }
        for(int j=0;j<(idWidth+typeWidth+etatWidth+idVendeurWidth+prixWidth+descriptionWidth+4+3*5);j++){
            cout<<"-";
        }
        cout<<"\n| ";
        printElement(descr0,idWidth,separator);
        cout<<" | ";
        printElement(descr1,typeWidth,separator);
        cout<<" | ";
        printElement(descr2,etatWidth,separator);
        cout<<" | ";
        printElement(descr3,idVendeurWidth,separator);
        cout<<" | ";
        printElement(descr4,prixWidth,separator);
        cout<<" | ";
        printElement(descr5,descriptionWidth,separator);
        cout<<" |"<<endl;

        for(int i=0;i<nbr;i++){
            for(int j=0;j<(idWidth+typeWidth+etatWidth+idVendeurWidth+prixWidth+descriptionWidth+4+3*5);j++){
                cout<<"-";
            }
            cout<<endl;
            cout<<"| ";
            printElement(immoIds[i],idWidth,separator);
            cout<<" | ";
            printElement(immoTypes[i],typeWidth,separator);
            cout<<" | ";
            printElement(immoEtatVente[i],etatWidth,separator);
            cout<<" | ";
            printElement(vendeursIds[i],idVendeurWidth,separator);
            cout<<" | ";
            printElement(immoPrix[i],prixWidth,separator);
            cout<<" | ";
            printElement(immoSurface[i],descriptionWidth,separator);
            cout<<" |";
            cout<<endl;
        }
        for(int j=0;j<(idWidth+typeWidth+etatWidth+idVendeurWidth+prixWidth+descriptionWidth+4+3*5);j++){
                cout<<"-";
        }
    }
    cout<<endl;
    SetConsoleTextAttribute(hConsole, 15);
}
void Agence::displayBienImmoById(int idBienImmo){

    bool indice=true;
    int BienImmoIdVendeur;
    string BienImmoType="1",BienImmoEtat="2",BienImmoPrix="3",BienImmoDescr="4";

    string sql = "SELECT typeBien,etatDeVente,idVendeur,prixInit,descrSurface FROM BienImmo where idBien=?;";
    sqlite3_stmt* myStatement;

    if (prepareQueryWithResults(sql, myStatement)){

        sqlite3_bind_int(myStatement, 1, idBienImmo);

        int statusOfStep = sqlite3_step(myStatement);

        //if there is a row
        if (statusOfStep == SQLITE_ROW){
            //get the info
            BienImmoType      =((char*)sqlite3_column_text(myStatement, 0));
            BienImmoEtat      =((char*)sqlite3_column_text(myStatement, 1));
            BienImmoIdVendeur =sqlite3_column_int(myStatement, 2);
            BienImmoPrix      =((char*)sqlite3_column_text(myStatement, 3));
            BienImmoDescr     =((char*)sqlite3_column_text(myStatement, 4));

        }else{
            SetConsoleTextAttribute(hConsole, 12);
            cout<<"\nLe BienImmo avec l'id="<<idBienImmo<<", n\'existe pas."<<endl;
            indice=false;
        }
        sqlite3_finalize(myStatement);
        if(indice){
            SetConsoleTextAttribute(hConsole, 10);
            cout<<"\n-> Informations recuperees depuis la table \'BienImmo\': "<<endl;
            cout<<"\tID = "<<idBienImmo<<endl;
            cout<<"\tTYPE DE BIENIMMO= "<<BienImmoType<<endl;
            cout<<"\tETAT VENTE= "<<BienImmoEtat<<endl;
            cout<<"\tID VENDEUR= "<<BienImmoIdVendeur<<endl;
            cout<<"\tPRIX INITIAL= "<<BienImmoPrix<<endl;
            cout<<"\tDESCRIPTION SURFACE= "<<BienImmoDescr<<endl;
        }
    }
    SetConsoleTextAttribute(hConsole, 15);


}
void Agence::deleteBienImmoById(int idBienImmo){
    cout<<"---> INFO BienImmo to delete:"<<endl;
    displayBienImmoById(idBienImmo);

    string sql = "DELETE from BienImmo where idBien=?;";
    sqlite3_stmt* myStatement;

    int statusOfPrep = sqlite3_prepare_v2(db, sql.c_str(), -1, &myStatement, NULL);
    if (statusOfPrep == SQLITE_OK){

        sqlite3_bind_int(myStatement, 1, idBienImmo);

        if (!executeQueryNoResultsBack(myStatement)){

            cout <<"---> Deleting row from table BienImmo Failed!"<< endl;
        }
        cout<<"---> Deleting row from table BienImmo: Successful!"<<endl;
    }

}
void Agence::updateBienImmoById(int id, string type,string etat,int idVendeur,string prix,string surface){
    //typeBien,etatDeVente,idVendeur,prixInit,descrSurface FROM BienImmo

    cout<<"---> INFO BienImmo to Update:"<<endl;
    displayBienImmoById(id);
    string sql="UPDATE BienImmo SET typeBien='"+type+"',etatDeVente='"+etat+"',idVendeur="+to_string(idVendeur)+",prixInit='"+prix+"',descrSurface='"+surface+"' where idBien=?;";
    sqlite3_stmt* myStatement;

    int statusOfPrep = sqlite3_prepare_v2(db, sql.c_str(), -1, &myStatement, NULL);

    if (statusOfPrep == SQLITE_OK){
        sqlite3_bind_int(myStatement, 1, id);
        if (!executeQueryNoResultsBack(myStatement)){
            cout <<"---> Updating table BienImmo: Failed!"<< endl;
        }
        cout<<"---> Updating table BienImmo: Successful!"<<endl;
    }

}


// ____________________________________________Operation for table 'RDV':
void Agence::insertRDV(int idClient,int idBien,string dateRDV,string heureRDV){

    string sql = "INSERT into RDV(idClient,idBien,dateRDV,heureRDV) VALUES (?,?,?,?);";
    sqlite3_stmt* myStatement;

    int statusOfPrep = sqlite3_prepare_v2(db, sql.c_str(), -1, &myStatement, NULL);
    if (statusOfPrep == SQLITE_OK){

        sqlite3_bind_int(myStatement, 1, idClient);
        sqlite3_bind_int(myStatement, 2, idBien);

        sqlite3_bind_text(myStatement, 3, dateRDV.c_str() , -1, SQLITE_STATIC);
        sqlite3_bind_text(myStatement, 4, heureRDV.c_str(), -1, SQLITE_STATIC);

        if (!executeQueryNoResultsBack(myStatement)){
            cout <<"---> Insertion into table RDV: Failed!"<< endl;
        }
        cout<<"---> Insertion into table RDV: Successful!"<<endl;
    }
}
void Agence::tableDisplayRDV(){

    string sql = "SELECT idRDV,idClient,idBien,dateRDV,heureRDV FROM RDV;";
    sqlite3_stmt* myStatement;

    vector < int > idsRDV;
    vector < int > idsClient;
    vector < int > idsBien;
    vector < string > datesRDV;
    vector < string > heuresRDV;

    if (prepareQueryWithResults(sql, myStatement)){

        int statusOfStep = sqlite3_step(myStatement);
        int numeral = 1;

        while (statusOfStep == SQLITE_ROW){

            int idRDV    = sqlite3_column_int(myStatement, 0);
            int idCLIENT = sqlite3_column_int(myStatement, 1);
            int idBIEN   = sqlite3_column_int(myStatement, 2);

            string dateRDV((char*)sqlite3_column_text(myStatement, 3));
            string heureRDV((char*)sqlite3_column_text(myStatement, 4));


            idsRDV.push_back(idRDV);
            idsClient.push_back(idCLIENT);
            idsBien.push_back(idBIEN);
            datesRDV.push_back(dateRDV);
            heuresRDV.push_back(heureRDV);

            numeral++;
            statusOfStep = sqlite3_step(myStatement);
        }
        sqlite3_finalize(myStatement);

//OCD-friendly display of the table: "| idRDV | idClient | idBien | dateRDV | heureRDV |"
        SetConsoleTextAttribute(hConsole, 11);
        cout<<"Affichage table \' RDV \'"<<endl;
        const char separator= ' ';

        const string descr0="ID";
        const string descr1="ID Client";
        const string descr2="ID BienImmo";
        const string descr3="DateRDV";
        const string descr4="HeureRDV";

        int idWidth       = 5;
        int idClientWidth = descr1.size();
        int idBienWidth   = descr2.size();
        int dateWidth     = descr3.size();
        int heureWidth    = descr4.size();

        int nbr=idsRDV.size();
        SetConsoleTextAttribute(hConsole, 23);
        for(int i=0;i<nbr;i++){
            int a=datesRDV[i].size();
            if(a>dateWidth){
                dateWidth=a;
            }
            a=heuresRDV[i].size();
            if(a>heureWidth){
                heureWidth=a;
            }

        }
        for(int j=0;j<(idWidth+idClientWidth+idBienWidth+dateWidth+heureWidth+4+3*4);j++){
            cout<<"-";
        }
        cout<<"\n| ";
        printElement(descr0,idWidth,separator);
        cout<<" | ";
        printElement(descr1,idClientWidth,separator);
        cout<<" | ";
        printElement(descr2,idBienWidth,separator);
        cout<<" | ";
        printElement(descr3,dateWidth,separator);
        cout<<" | ";
        printElement(descr4,heureWidth,separator);
        cout<<" |"<<endl;

        for(int i=0;i<nbr;i++){
            for(int j=0;j<(idWidth+idClientWidth+idBienWidth+dateWidth+heureWidth+4+3*4);j++){
                cout<<"-";
            }
            cout<<endl;
            cout<<"| ";
            printElement(idsRDV[i],idWidth,separator);
            cout<<" | ";
            printElement(idsClient[i],idClientWidth,separator);
            cout<<" | ";
            printElement(idsBien[i],idBienWidth,separator);
            cout<<" | ";
            printElement(datesRDV[i],dateWidth,separator);
            cout<<" | ";
            printElement(heuresRDV[i],heureWidth,separator);
            cout<<" |";
            cout<<endl;
        }
        for(int j=0;j<(idWidth+idClientWidth+idBienWidth+dateWidth+heureWidth+4+3*4);j++){
                cout<<"-";
        }
    }
    cout<<endl;
    SetConsoleTextAttribute(hConsole, 15);

}
void Agence::displayRDVById(int idRDV){
    cout<<endl;
    bool indice=true;
    int bienImmoId,clientId;
    string RDVdate="1",RDVheure="2";

    string sql = "SELECT idClient,idBien,dateRDV,heureRDV FROM RDV where idRDV=?;";
    sqlite3_stmt* myStatement;

    if (prepareQueryWithResults(sql, myStatement)){

        sqlite3_bind_int(myStatement, 1, idRDV);

        int statusOfStep = sqlite3_step(myStatement);

        //if there is a row
        if (statusOfStep == SQLITE_ROW){
            //get the info

            bienImmoId = sqlite3_column_int(myStatement, 0);
            clientId   = sqlite3_column_int(myStatement, 1);
            RDVdate    = ((char*)sqlite3_column_text(myStatement, 2));
            RDVheure   = ((char*)sqlite3_column_text(myStatement, 3));

        }else{
            SetConsoleTextAttribute(hConsole, 12);
            cout<<"Le RDV avec l'id="<<idRDV<<", n\'existe pas."<<endl;
            indice=false;
        }
        if(indice){
            SetConsoleTextAttribute(hConsole, 10);
            cout<<"\n-> Informations recuperees depuis la table \'RDV\': "<<endl;
            cout<<"\tID= "<<idRDV<<endl;
            cout<<"\tIDBienImmo= "<<bienImmoId<<endl;
            cout<<"\tIDClient= "<<clientId <<endl;
            cout<<"\tDATE RDV= "<<RDVdate<<endl;
            cout<<"\tHEURE RDV= "<<RDVheure<<endl;
        }
        sqlite3_finalize(myStatement);
    }
    SetConsoleTextAttribute(hConsole, 15);

}
void Agence::deleteRDVById(int idRDV){
    cout<<"---> INFO RDV to delete:"<<endl;
    displayRDVById(idRDV);

    string sql = "DELETE from RDV where idRDV=?;";
    sqlite3_stmt* myStatement;

    int statusOfPrep = sqlite3_prepare_v2(db, sql.c_str(), -1, &myStatement, NULL);
    if (statusOfPrep == SQLITE_OK){

        sqlite3_bind_int(myStatement, 1, idRDV);

        if (!executeQueryNoResultsBack(myStatement)){

            cout <<"---> Deleting row from table RDV Failed!"<< endl;
        }
        cout<<"---> Deleting row from table RDV: Successful!"<<endl;
    }

}
void Agence::updateRDVById(int id,int idclient,int idbien,string daterdv,string heurerdv){
    //Table RDV(idRDV,idClient,idBien,dateRDV,heureRDV)
    cout<<"---> INFO RDV to Update:"<<endl;
    displayRDVById(id);
    string sql="UPDATE RDV SET idClient="+to_string(idclient)+",idBien="+to_string(idbien)+",dateRDV='"+daterdv+"',heureRDV='"+heurerdv+"' where idRDV=?;";
    sqlite3_stmt* myStatement;

    int statusOfPrep = sqlite3_prepare_v2(db, sql.c_str(), -1, &myStatement, NULL);

    if (statusOfPrep == SQLITE_OK){
        sqlite3_bind_int(myStatement, 1, id);
        if (!executeQueryNoResultsBack(myStatement)){
            cout <<"---> Updating table RDV: Failed!"<< endl;
        }
        cout<<"---> Updating table RDV: Successful!"<<endl;
    }

}


// _________________________________________Operation for table 'Contrat':
void Agence::insertContrat(int idBien,int idVendeur,int idClient,string payement,string somme){

    string sql = "INSERT into Contrat(idBien,idVendeur,idClient,typePayement,sommePayement) VALUES (?,?,?,?,?);";
    sqlite3_stmt* myStatement;

    int statusOfPrep = sqlite3_prepare_v2(db, sql.c_str(), -1, &myStatement, NULL);
    if (statusOfPrep == SQLITE_OK){

        sqlite3_bind_int(myStatement, 1, idVendeur);
        sqlite3_bind_int(myStatement, 2, idBien);
        sqlite3_bind_int(myStatement, 3, idClient);
        sqlite3_bind_text(myStatement,4, payement.c_str() , -1, SQLITE_STATIC);
        sqlite3_bind_text(myStatement,5, somme.c_str(), -1, SQLITE_STATIC);

        if (!executeQueryNoResultsBack(myStatement)){
            cout <<"---> Insertion into table Contrat: Failed!"<< endl;
        }
        cout<<"---> Insertion into table Contrat: Successful!"<<endl;
    }
}
void Agence::tableDisplayContrat(){

    string sql = "SELECT idContrat,idBien,idVendeur,idClient,typePayement,sommePayement FROM Contrat;";
    sqlite3_stmt* myStatement;

    vector < int > idsContrat;
    vector < int > idsBien;
    vector < int > idsVendeur;
    vector < int > idsClient;

    vector < string > types;
    vector < string > sommes;

    if (prepareQueryWithResults(sql, myStatement)){

        int statusOfStep = sqlite3_step(myStatement);
        int numeral = 1;

        while (statusOfStep == SQLITE_ROW){

            int idcontrat    = sqlite3_column_int(myStatement, 0);
            int idbien       = sqlite3_column_int(myStatement, 1);
            int idvendeur    = sqlite3_column_int(myStatement, 2);
            int idclient     = sqlite3_column_int(myStatement, 3);
            string type((char*)sqlite3_column_text(myStatement, 4));
            string somme((char*)sqlite3_column_text(myStatement, 5));

            idsContrat.push_back(idcontrat);
            idsBien.push_back(idbien);
            idsVendeur.push_back(idvendeur);
            idsClient.push_back(idclient);
            types.push_back(type);
            sommes.push_back(somme);

            numeral++;
            statusOfStep = sqlite3_step(myStatement);
        }
        sqlite3_finalize(myStatement);

//OCD-friendly display of the table: "| idContrat | idBien | idVendeur | idClient | typePayement | sommePayement |"
        SetConsoleTextAttribute(hConsole, 11);
        cout<<"Affichage table \' Contrat \'"<<endl;
        const char separator= ' ';

        const string descr0="ID";
        const string descr1="ID BienImmo";
        const string descr2="ID Vendeur";
        const string descr3="ID Client";
        const string descr4="Type Payement";
        const string descr5="Somme Payement";

        int idWidth        = 5;
        int idBienWidth    = descr1.size();
        int idVendeurWidth = descr2.size();
        int idClientWidth  = descr3.size();
        int payeWidth      = descr4.size();
        int sommeWidth     = descr5.size();

        int nbr=idsContrat.size();

        for(int i=0;i<nbr;i++){
            int a=sommes[i].size();
            if(a>sommeWidth){
                sommeWidth=a;
            }
            a=types[i].size();
            if(a>payeWidth){
                payeWidth=a;
            }
        }
        SetConsoleTextAttribute(hConsole, 23);
        for(int j=0;j<(idWidth+idClientWidth+idBienWidth+idVendeurWidth+payeWidth+sommeWidth+4+3*5);j++){
            cout<<"-";
        }
        cout<<"\n| ";
        printElement(descr0,idWidth,separator);
        cout<<" | ";
        printElement(descr1,idBienWidth,separator);
        cout<<" | ";
        printElement(descr2,idVendeurWidth,separator);
        cout<<" | ";
        printElement(descr3,idClientWidth,separator);
        cout<<" | ";
        printElement(descr4,payeWidth,separator);
        cout<<" | ";
        printElement(descr5,sommeWidth,separator);
        cout<<" |"<<endl;

        for(int i=0;i<nbr;i++){
            for(int j=0;j<(idWidth+idClientWidth+idBienWidth+idVendeurWidth+payeWidth+sommeWidth+4+3*5);j++){
                cout<<"-";
            }
            cout<<endl;
            cout<<"| ";
            printElement(idsContrat[i],idWidth,separator);
            cout<<" | ";
            printElement(idsBien[i],idBienWidth,separator);
            cout<<" | ";
            printElement(idsVendeur[i],idVendeurWidth,separator);
            cout<<" | ";
            printElement(idsClient[i],idClientWidth,separator);
            cout<<" | ";
            printElement(types[i],payeWidth,separator);
            cout<<" | ";
            printElement(sommes[i],sommeWidth,separator);
            cout<<" |";

            cout<<endl;
        }
        for(int j=0;j<(idWidth+idClientWidth+idBienWidth+idVendeurWidth+payeWidth+sommeWidth+4+3*5);j++){
                cout<<"-";
        }
    }
    cout<<endl;
    SetConsoleTextAttribute(hConsole, 15);

}
void Agence::displayContratyId(int idContrat){
    cout<<endl;
    bool indice=true;

    int bienImmoId,vendeurId,clientId;
    string typepaye="1",somme="2";

    string sql = "SELECT idBien,idVendeur,idClient,typePayement,sommePayement FROM Contrat where idContrat=?;";
    sqlite3_stmt* myStatement;

    if (prepareQueryWithResults(sql, myStatement)){

        sqlite3_bind_int(myStatement, 1, idContrat);

        int statusOfStep = sqlite3_step(myStatement);

        //if there is a row
        if (statusOfStep == SQLITE_ROW){
            //get the info

            bienImmoId = sqlite3_column_int(myStatement, 0);
            vendeurId  = sqlite3_column_int(myStatement, 1);
            clientId   = sqlite3_column_int(myStatement, 2);

            typepaye   = ((char*)sqlite3_column_text(myStatement, 3));
            somme      = ((char*)sqlite3_column_text(myStatement, 4));

        }else{
            SetConsoleTextAttribute(hConsole, 12);
            cout<<"Le contract avec l'id="<<idContrat<<", n\'existe pas."<<endl;
            indice=false;
        }
        sqlite3_finalize(myStatement);
        if(indice){
            SetConsoleTextAttribute(hConsole, 10);
            cout<<"\n-> Information recuperees depuis la table \'Contrat\': "<<endl;
            cout<<"\tID= "<<idContrat<<endl;
            cout<<"\tID BienImmo= "<<bienImmoId<<endl;
            cout<<"\tID Vendeur= "<<vendeurId <<endl;
            cout<<"\tID Client= "<<clientId <<endl;
            cout<<"\tType de Payement= "<<typepaye<<endl;
            cout<<"\tSomme payee= "<<somme<<endl;
        }
    }
    SetConsoleTextAttribute(hConsole, 15);
}
void Agence::deleteContratById(int idContrat){
    cout<<"---> INFO Contrat to delete:"<<endl;
    displayContratyId(idContrat);

    string sql = "DELETE from Contrat where idContrat=?;";
    sqlite3_stmt* myStatement;
    int statusOfPrep = sqlite3_prepare_v2(db, sql.c_str(), -1, &myStatement, NULL);
    if (statusOfPrep == SQLITE_OK){

        sqlite3_bind_int(myStatement, 1, idContrat);

        if (!executeQueryNoResultsBack(myStatement)){
            cout <<"---> Deleting row from table CONTRAT Failed!"<< endl;
        }
        cout<<"---> Deleting row from table CONTRAT: Successful!"<<endl;

    }

}
void Agence::updateContratById(int id,int idbien,int IdVendeur,int idclient,string typePaye,string somme){
    //Table Contrat(idBien,idVendeur,idClient,typePayement,sommePayement)
    cout<<"---> INFO CONTRAT to Update:"<<endl;
    displayContratyId(id);
    string sql="UPDATE Contrat SET idBien="+to_string(idbien)+",idVendeur="+to_string(IdVendeur)+",idClient="+to_string(idclient)+",typePayement='"+typePaye+"',sommePayement='"+somme+"' where idContrat=?;";
    sqlite3_stmt* myStatement;

    int statusOfPrep = sqlite3_prepare_v2(db, sql.c_str(), -1, &myStatement, NULL);

    if (statusOfPrep == SQLITE_OK){
        sqlite3_bind_int(myStatement, 1, id);
        if (!executeQueryNoResultsBack(myStatement)){
            cout <<"---> Updating table Contrat: Failed!"<< endl;
        }
        cout<<"---> Updating table Contrat: Successful!"<<endl;
    }

}








