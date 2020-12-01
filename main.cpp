#include <iostream>
#include <string>
#include <list>
#include <fstream>
#include <vector>  // std::cout
#include <algorithm>    // std::find

using namespace std;
//fonction pour découper chaque ligne du fichier regle.txt
void decoupage(string regle, list<string>& premisses, list<string>& conclusion)
{
    string fait = "";
    premisses.clear();
    conclusion.clear();

    bool drapeau = false;

    for (std::string::iterator it = regle.begin(); it != regle.end(); ++it) {
        switch (*it) {
        case ' ': {
            if (!drapeau) {
                premisses.push_back(fait);
                fait = "";
            }
        } break;

        case '>': {
            drapeau = true;
        } break;

        case '.': {
            conclusion.push_back(fait);
            fait = "";
        } break;

        default: {
            fait = fait + *it;
        } break;
        }
    }
}
//pour comparer des chaines de caracteres
bool comparaison(list<string> lst1, list<string> lst2){
    list<string>::iterator iter1;
    list<string>::iterator iter2;
    int cont = 0;
for (iter1 = lst1.begin(); iter1 != lst1.end(); ++iter1)
    {
            iter2= find (lst2.begin(), lst2.end(), *iter1);
            if (iter2 == lst2.end()) cont++;
            //else return false;
    }
        if(cont == 0) return true;
        else return false;
}
//pour verifier si une lettre se trouve dans une chaine
bool se_trouve(list<string> lst, string element){
    std::list<string>::iterator iter;
      iter= find (lst.begin(), lst.end(), element);
      if (iter != lst.end()) return true;
}
int main()
{
    cout << "La liste des fichiers présent dans le répertoire : " << endl;
    system("dir *.txt");
    cout << endl;

    string nom_fichier;

    string domaine;

    std::list < std::string > faits;//la liste des faits

    cout << "veuillez choisir le domaine, utiliser:\n gr pour geometrie,\n bt pour botanique,";
    cout << " \n n'importe quelle autre lettre pour domaine par defaut:" << endl;

    cin >> domaine;

    if(domaine == "gr"){
      nom_fichier = "geometrie.txt";
      //base de faits pour géometrie
      faits = {"les_4_cotes_sont_egaux", "angle_droit"};
    }
    else if(domaine == "bt"){
      nom_fichier = "botanique.txt";
      //base de faits pour botanique
      faits = {"rhizome", "fleur", "graine", "un_cotyledone"};
    }
    else{
        nom_fichier = "REGLE.txt";
        //base de faits par default
        faits = {"A", "E", "G", "D"};
    }
cout <<nom_fichier<< endl;
     struct bdr { //base de regle
            string nom_de_regle;
            bool active;
            list<string> pr;
            list<string> cls;
            };
            vector<bdr> regles; //le vecteur des base de regeles

            string fait;// le fait initial tapé par l'user

            list<int> tmp;//vecteur des index temporaires

            string but;//le a atteindre

            string stg;//la stratégie à suivre


    ifstream fichier_Input(nom_fichier, ios::in); // Ouverture du fichier en lecture

    if (fichier_Input) // si l'ouverture a réussi
    {
        cout << "  l'ouverture a réussi" << endl;

        string Enregistrement;

        int i=0;
        while (!fichier_Input.eof()) {
            i++;
            getline(fichier_Input, Enregistrement);
            list<string> premisses, conclusion;
            decoupage(Enregistrement, premisses, conclusion);
            struct bdr ma_bdr;
            ma_bdr.nom_de_regle = Enregistrement;
            ma_bdr.active = true;
            ma_bdr.pr = premisses;
            ma_bdr.cls = conclusion;
            regles.push_back(ma_bdr);
        }

    cout << "veuillez donner le but:";

    cin >> but;

    //la base de faits initiale
    list<string>::iterator ftiter;
    cout << "la base de faits initiale est [";
    for (ftiter = faits.begin(); ftiter != --(faits.end()); ++ftiter)
        cout << *ftiter << ", ";
         for (ftiter = --(faits.end()); ftiter != faits.end(); ++ftiter)
        cout << *ftiter << "]";
    cout << endl;
    //fin la base de faits initiale

    cout << "veuillez donner la strategie, utiliser\n l pour largeur et\n p profondeur:";

    cin >> stg;

    while((stg != "l")&&(stg != "p"))
        {
        cout<< "entree invalide, utiliser l pour largeur et p profondeur:";
        cin >> stg;
    }

    if(stg == "p") cout << "chainage avant en profondeur"<< endl<< endl;

    if(stg == "l") cout << "chainage avant en largeur"<< endl<< endl;

    int cycle = 0;//compteur des cycles

    bool arret = false;//condition d'arrêt

    while((!arret)&&(!se_trouve(faits, but))){

    cycle ++;

    int cont_arret = 0;

          cout << "cycle:"<< cycle <<  endl;

          cout << "conflit = {"<< endl;

    for(int index = 0; index < regles.size(); index++)
    {

     list<string>::iterator Liter;

        if((comparaison(regles.at(index).pr, faits))&&(regles.at(index).active)){//si les premisses de
            //la regle se trouvent dans la base des faits et la regle est active
        cout <<index+1<<": "<<regles.at(index).nom_de_regle<< endl;

        tmp.push_back(index);//on garde l'index dans le vecteur tmp
     }
    else{
        if(cycle != 1) cont_arret++;
        }

    }

      cout << "} "<<   endl;//pour l'ensemble des regles applicables
     tmp.sort();
     tmp.unique();
    list<int>::iterator tmpiter;
    list<int>::iterator debut;
    list<string>::iterator tmpLiter;
    //
        if(stg == "l"){
            for(tmpiter = tmp.begin(); tmpiter != tmp.end(); ++tmpiter){
           if((regles.at(*tmpiter).active)){
            if(!comparaison(regles.at(*tmpiter).cls, faits))
            for(tmpLiter = regles.at(*tmpiter).cls.begin(); tmpLiter != regles.at(*tmpiter).cls.end(); ++tmpLiter)
            faits.push_back(*tmpLiter);
        //if(!comparaison(faits, regles.at(*debut).cls)) faits.push_back(regles.at(*debut).cls);
        regles.at(*tmpiter).active = false;
    }
    }
    }
    //
     //partie spécifique pour profondeur
     if(stg == "p"){
    cout << "regle executable ";
        debut = tmp.begin();
    for(tmpiter = tmp.begin(); tmpiter != tmp.end(); ++tmpiter){
    if((regles.at(*tmpiter).active)){
            if(!comparaison(regles.at(*debut).cls, faits))
            for(tmpLiter = regles.at(*debut).cls.begin(); tmpLiter != regles.at(*debut).cls.end(); ++tmpLiter)
            faits.push_back(*tmpLiter);
    }
    }
    if(regles.at(*debut).active) cout <<*debut+1<<": "<<regles.at(*debut).nom_de_regle<<""<<   endl;
        regles.at(*debut).active = false;
    if(tmp.size() > 0) tmp.remove(*debut);
     }//fin "p"
        ///////////////////////////////////
     list<string>::iterator ftiter;
    cout << "  la nouvelle base de faits est [";
    for (ftiter = faits.begin(); ftiter != --(faits.end()); ++ftiter)
        cout << *ftiter << ", ";
         for (ftiter = --(faits.end()); ftiter != faits.end(); ++ftiter)
        cout << *ftiter << "]";
    cout << endl << endl;

    if(cont_arret == regles.size()) arret = true;

    } // fin while((!arret)&&(!se_trouve(faits, but)))


          if((se_trouve(faits, but))) cout << "succes but atteint!" << endl << endl;

          if(((arret)&&(!se_trouve(faits, but)))) cout << "echec but n'a pas atteint!" << endl << endl;

        fichier_Input.close(); // on ferme le fichier
    }

    else // si l'ouverture échoué
        cerr << "Impossible d'ouvrir le fichier !" << endl;

    return 0;
}
