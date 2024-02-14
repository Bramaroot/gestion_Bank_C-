#include <iostream>
#include<cstring>
#include<fstream>
using namespace std;
#define N 10
string const monFichier("C:/Users/pc/Desktop/Po/texte.txt");
int i,nb = 0;
bool test = false;

//..............Structure Tableau..........
typedef struct client
{
  long compt;
 string nom;
 long sold;
}pers;

pers info[N];

//...........Structure Dynamique........
typedef struct compte
{
	int number;
	string name;
	float money;
	struct compte *suit;

}node;

node *head = NULL;

void mise_jour(int nb);
void charger_comptes();
void update();

//..............Prototype Tableau.............
void ajout(int nb);
void Affiche(int nb);
void sup(int nb);
void modif(int nb,float ch);
void versement(int nb,float num);
void retire(int nb,float ch);
void virement(int nb,float num);
void UnCompt(int nb,float chif);
void tableau();

//..............Prototype Dynamique.............
void add_compte();
void affichage();
void del();
void edit();
void Add_Money();
void retirement();
void Transaction();
void find_compte();
void Dynamique();

//######################### Fonction main #####################################

int main(int argc, char const *argv[])
{
	int choix;
	do{
		cout<<"\n A. TABLEAUX  ";
		cout<<"\n C. ALLOCATION DYNAMIQUE ";
		cout<<"\n C. Quitter le Programme  ";
		cout<<"\n\n   Votre Choix : ";
        cin >> choix;

		switch(choix)
		{
			case 1: tableau(); break;
			case 2: Dynamique(); break;
			case 3: break;
			default: cout<<"\n Choix Incorrect (soit 1 soit 2)."; break;
		}

	}while(choix != 3);
	return 0;
}

void ajout(int nb)
{
	ofstream monflux(monFichier.c_str(),ios::app);

		for(i=nb-1; i<nb; i++)
		{
			do{
				cout<<"\n Numeros de Compte : ";
		        cin>>info[i].compt;
		        if(info[i].compt == info[i-1].compt)
		        	cout<<"\n Ce Numero de Compte existe deja."<<endl;
			}while(info[i].compt == info[i-1].compt);

		 cin.ignore();
		 cout<<"\n Nom Prenom = ";
		 getline(cin,info[i].nom);
		 cout<<"\n Solde = ";
		 cin>>info[i].sold;

		 monflux<<info[i].nom
		 		<<"\t"<<info[i].compt
		 		<<"\t"<<info[i].sold<<endl;
		}

}


void Affiche(int nb)
{
	if (nb == 0)
	 cout<<"\n....La liste est vide ...."<<endl;
	else
	{
	 for(int i=0; i<nb; i++)
       { 
		cout<<"\n Nom : "<<info[i].nom<<endl;
		cout<<"\n Num Compte : "<<info[i].compt<<endl;
		cout<<"\n Solde : "<<info[i].sold<<endl;
	   }
	}
}

void sup(int nb)
{
	int num;

	 cout<<"\n Entrer le numero de compte a Supprimer : ";
	 cin >> num;

	 for (i = 0; i < nb; ++i)
	 {
	 	if(num == info[i].compt)
	 	{
	 		for(int j = i; j< nb-1; j++)
	 			info[j] = info[j+1];

	 		test = true;
	 	}
	 }
	 if(test == false)
	 	cout<<"\n Ce Compte n\'existe pas .. "<<endl;

	 mise_jour(nb);

}

void modif(int nb,float ch)
{
	for (i = 0; i < nb; i++)
	{
		if(info[i].compt == ch)
        {
        	 cout<<"\n Entrer les nouvelles donnees du compte . ";
   		     cout<<"\n Nom Prenom = ";
			 cin>>info[i].nom;
			 cout<<"\n Numeros de Compte : ";
			 cin>>info[i].compt;
			 cout<<"\n Solde = ";
			 cin>>info[i].sold;
        }

	}
	mise_jour(nb);
}
void versement(int nb,float num)
{
	float som = 0;
	for(i=0; i<nb; i++)
	{
		if(num == info[i].compt)
		{
			do{
				cout<<"\n Entrer la Somme a Verser : ";
				cin>>som;
				if(som < 0)
					cout<<"\n La Somme a verser est Negative, vous devez Entrer un Somme positive "<<endl;
				else
				info[i].sold += som;

			}while(som < 0);

		}
	}
	mise_jour(nb);
}
void retire(int nb,float ch)
{
	float ret = 0;
	for(i=0; i<nb; i++)
	{
		if(ch == info[i].compt)
		{
			do{
				cout<<"\n Entrer la Somme a Retirer : ";
			cin>>ret;
			if(ret < 0)
				cout<<"\n La Somme a Retirer est Negative, vous devez Entrer un Somme positive "<<endl;
			else if(ret >= info[i].sold)
				cout<<"\n Mon Pauvre, votre solde n'attend pas cette somme.."<<endl;
			else
			info[i].sold -= ret;

			}while(ret<0);

		}
	}
	mise_jour(nb);
}
void virement(int nb,float num)
{
	float chif(0),vir(0);
	cout<<"Numero de l'expediteur :";
	cin>>vir;
	cout<<"Numero du destinataire :";
	cin>>chif;
	for(i=0; i<nb; i++)
	{
		if(vir==info[i].compt)
		{   do{
		
			cout<<"Montant du versement ? :";
			cin>>num;
			if(num < 0)
			cout<<"Transfere impossible montant  negatif!"<<endl;
			else
			info[i].sold-=num;
		    }while(num < 0);
		}
		if(chif==info[i].compt)
		info[i].sold+=num;
	}
	mise_jour(nb);
   
}


void UnCompt(int nb,float chif)
{
  for(int i=0; i<nb; i++)
    {
    	if(info[i].compt == chif)
    	{	
        cout<<"\n Nom : "<<info[i].nom<<endl;
		cout<<"\n Num Compte : "<<info[i].compt<<endl;
		cout<<"\n Solde : "<<info[i].sold<<endl;
	    }
    }
}

void tableau()
{
	int Pchoix,Dchoix,Tchoix,nb=0;
    float ch, num(0);
 Pchoix = 0;

	ifstream monflux(monFichier.c_str());

	string nom,prenom;

	int sold,compt;

	if(monflux)
	{

		while(monflux >> nom >> prenom >> compt >> sold)
		{
			info[nb].nom = nom +" "+prenom;
			info[nb].compt = compt;
			info[nb].sold = sold;

		    nb++;
		}
	}
		else
		cout<<"\n Ce Fichier n\'existe pas ."<<endl;


 while(Pchoix!=3)
  {
  		cout<<"\n.......Gestionaire de Comptes Banquaire...."<<endl;
  		cout<<".............YOUNG CODERS BANQ..............."<<endl;
  		cout<<".....Votre argent notre Securite !"<<endl;
		cout<<"\n 1.Gestion des Comptes"<<endl;
		cout<<" 2.Transaction des Comptes"<<endl;
		cout<<" 3.Quitter le Programme"<<endl;
		cout<<"\n Fait votre Choix : ";
		cin>>Pchoix;

		switch(Pchoix)
			{
			 case 1:
			   Dchoix = 0;
			  while(Dchoix!=5)
			  {
			  		cout<<"\n .....Gestion des Comptes..... \n"<<endl;
					cout<<" 1.Ajouter un compte "<<endl;
					cout<<" 2.Supprimer un compte "<<endl;
					cout<<" 3.Modifier un compte "<<endl;
					cout<<" 4.Afficher tous les comptes "<<endl;
					cout<<" 5.Quitter le sous menu (retour au menu principal) "<<endl;
					cout<<"\n Fait votre Choix : ";
					cin>>Dchoix;

					switch(Dchoix)
					{
						case 1: nb++;
								ajout(nb);
								cout<<"\n ...Ajout effectuer avec succes..."<<endl;
							break;
						case 2:
								if(nb == 0)
									cout<<"\n ...La liste est vide..."<<endl;
								else
								{
									sup(nb);
									cout<<"\n ...Suppression effectuer avec succes..."<<endl;
									nb--;
								}
						    break;
						case 3:
								if(nb == 0)
									cout<<"\n ...La liste est vide..."<<endl;
								else
								{
									
									cout<<"\n Entrer le numeros du compte a modifier : ";
									cin>>ch;
									modif(nb,ch);
									cout<<"\n ...Modification effectuer avec succes..."<<endl;
								}
						    break;
						case 4:
								if(nb == 0)
									cout<<"\n ...La liste est vide..."<<endl;
								else
								  Affiche(nb);break;
						case 5:break;
					}
			   }
				break;

				case 2:
				Tchoix = 0;
				while(Tchoix!=6)
				{
					cout<<"\n.....Transaction des Comptes....\n"<<endl;
					cout<<" 1.Verser une somme dans un compte "<<endl;
					cout<<" 2.Retirer une somme du compte "<<endl;
					cout<<" 3.Virer une somme du compte vers un autre "<<endl;
					cout<<" 4.Afficher un compte "<<endl;
					cout<<" 5.Afficher tous les comptes "<<endl;
					cout<<" 6.Quitter le sous menu (retour au menu principal) "<<endl;
					cout<<"\n Fait votre Choix : ";
					cin>>Tchoix;

					switch(Tchoix)
					{
						case 1:
								if(nb == 0)
									cout<<"\n ...La liste est vide..."<<endl;
								else
								{
									
									cout<<"\n Entrer le numeros du compte : ";
									cin>>num;
									versement(nb,num);
									cout<<"\n ...Versement effectuer avec succes..."<<endl;
								}
							break;
					    case 2:
					    		if(nb == 0)
									cout<<"\n ...La liste est vide..."<<endl;
								else
								{
						    		
									cout<<"\n Entrer le numeros du compte  : ";
									cin>>ch;
									retire(nb,ch);
								}
							break;
						case 3:
								if(nb == 0)
									cout<<"\n ...La liste est vide..."<<endl;
								else
								{
									virement(nb,num);
									cout<<"\n ...virement effectuer avec succes..."<<endl;
								}
							break;
						case 4:
								if(nb == 0)
									cout<<"\n ...La liste est vide..."<<endl;
								else
								{
									float chif;
									cout<<"\n Entrer le numeros du compte  : ";
									cin>>chif;
									UnCompt(nb,chif);
								}
							break;
						case 5:
								if(nb == 0)
									cout<<"\n ...La liste est vide..."<<endl;
								else
								  Affiche(nb);
							break;
						case 6:break;
					}
				}
				break;
				case 3: cout<<"\n.......FIN DU PROGRAMME......"<<endl;break;

			}

	}

}

//########################## Fonction Pour Dynamique #########################

void add_compte()
{
 	 node *ptr = new(node);

   	cout <<"\n Numeros du compte : ";
   	cin >> ptr->number;
   	cin.ignore();
   	cout<<"\n Votre Name : ";
   	getline(cin,ptr->name);
   	cout<<"\n Montant du liquide : ";
   	cin >> ptr->money;

    ptr->suit = head;
    head = ptr;
}

void affichage()
{
	node *ptr;
    ptr = head;

	if(ptr == NULL)
		cout<<"\n La liste est vide.."<<endl;

	else{
		while(ptr!=NULL){
		cout<<"\n Nom : "<<ptr->name
			<<"\n Numeros du compte : "<<ptr->number
			<<"\n Solde : "<<ptr->money<<endl;
			ptr = ptr->suit;
	   }

	}
}
void del()
{
	
	int num;
	node *ptr,*ptr1;
	ptr = head;
	ptr1 = ptr->next;

	cout<<"\nLe numero du compte a supprimer : ";
	cin>>num;

	if( ptr->number == num)
		  {
			head = head->next;
			delete(ptr);
			cout<<"\nVotre compte a ete supprimer avec succes " <<endl;
		  }
		else
		  {
		  	ptr1 = ptr->next;
		  	while(ptr1 != NULL)
		  	  {
				if(ptr1->number == num)
					break;
				else
					{
						ptr =ptr1;
						ptr1=ptr1->next;
					}
			  }
			if(ptr1!=NULL)
			  {
			  	ptr->next=ptr1->next;
			  	delete(ptr1);
			  	cout<<"\nVotre compte a ete supprimer avec succes ." <<endl;
			  }

		  }

	update();

}

void edit()
{
	node *ptr;
	ptr = head;

	if(ptr == NULL)
		cout<<"\n La liste est vide...."<<endl;

	else{
		int xl;
		cout<<"\n Entrer le Numeros du compte a Modifier : ";
		cin>>xl;

	    while (ptr != NULL)
		     {
		     	bool tst = false;
		     	if(ptr->number == xl)
				{
					cout <<"\n Numeros du compte : ";
				   	cin >> ptr->number;
				   	cin.ignore();
				   	cout<<"\n Votre Name : ";
				   	getline(cin,ptr->name);
				   	cout<<"\n Montant du Blee : ";
				   	cin >> ptr->money;
				   	tst = true;
				}
				else{
					ptr = ptr->suit;

					if(tst == false && ptr == NULL)
				      cout<<"\n Ce Compte n\'existe pas."<<endl;
				    }

		     }
		}
		update();
}

void Add_Money()
{
	node *ptr;
	ptr = head;
	int xl,num;
	bool tst;

	if(ptr == NULL)
		cout<<"\n La liste est vide...."<<endl;

	else{

		cout<<"\n Entrer le Numeros du compte : ";
		cin>>xl;

		cout<<"\n Montant du versement : ";
		cin>>num;

	    while (ptr != NULL)
		     {
		     	if(ptr->number == xl)
		     	{
		     		 ptr->money += num;
		     		 tst = true;
		     	}
		     	ptr = ptr->suit;
		     }

	}
	update();
}

void retirement()
{
	node *ptr;
	ptr = head;
	int xl,num;
 	bool tst;


	if(ptr == NULL)
		cout<<"\n La liste est vide...."<<endl;

	else{

		cout<<"\n Entrer le Numeros du compte Pour retrait : ";
		cin>>xl;

		cout<<"\n Montant du retrait : ";
		cin>>num;

	    while (ptr != NULL)
		     {
		     	if(ptr->number == xl)
		     	{
		     		 ptr->money -= num;
		     		 tst = true;
		     	}
		     	ptr = ptr->suit;

		     }

	}
	update();

}

void Transaction()
{
	node *ptr;
	ptr = head;
	int xl,xld,num;
 	bool tst;


	if(ptr == NULL)
		cout<<"\n La liste est vide...."<<endl;

	else{

		cout<<"\n Entrer le Numeros du compte de l\'expediteur : ";
		cin>>xl;

		cout<<"\n Montant du retrait : ";
		cin>>num;

		cout<<"\n Entrer le Numeros du compte du destinateur : ";
		cin>>xld;

	    while (ptr != NULL)
		     {
		     	if(ptr->number == xl)
		     		 ptr->money -= num;

		     		 if(ptr->number == xld)
		     		 	ptr->money += num;
		     	

		     	ptr = ptr->suit;

		     }

	}
	update();
}
void find_compte()
{
	node *ptr;
    ptr = head;
    int xl;

	if(ptr == NULL)
		cout<<"\n La liste est vide.."<<endl;

	else{

		cout<<"\n Constitution du Compte recherche : ";
		cin>>xl;

		while(ptr!=NULL){

			if(ptr->number == xl)
		    cout<<"\n Nom : "<<ptr->name
			<<"\n Numeros du compte : "<<ptr->number
			<<"\n Solde : "<<ptr->money<<endl;
			ptr = ptr->suit;
	   }

	}
}

void charger_comptes()
{
    ifstream fichier(monFichier.c_str());

    if (fichier)
    {
        int num;
        string nom;
        string prenom;
        double solde;

        while (fichier >> nom >> prenom >> num >> solde)
        {
            node* ptr;
            ptr = new(node);

            ptr->number = num;
            ptr->name = nom +" "+prenom;
            ptr->money = solde;

            ptr->next = head;
            head = ptr;
        }

    }
	update();
}

void update()
{
	 ofstream fichier(monFichier.c_str());
	  if (fichier)
	   {
            node* ptr = head;
            while (ptr != NULL)
            {
                fichier <<ptr->name << "\t"
                        <<ptr->number << "\t"
                        <<ptr->money << endl;
                ptr = ptr->next;
            }

        } else
            cout << "Impossible d'ouvrir le fichier pour la sauvegarde des comptes." << endl;
}


void mise_jour(int nb)
{
	ofstream monflux(monFichier.c_str());

	for (i = 0; i < nb; ++i)
	{
		monflux<<info[i].nom
			   <<"\t"<<info[i].compt
			   <<"\t"<<info[i].sold<<endl;
	}
}

//################################ Fonction Principale ############################
void Dynamique()
{
    int Pchoix,Dchoix,Tchoix;
	cout<<"\n\t-----Gestoin des comptes Bancaire Dinamique-------"<<endl;
 charger_comptes();
Pchoix = 0;
while(Pchoix!=3)
  {
  		cout<<"\n.......Gestionaire de Comptes Banquaire...."<<endl;
  		cout<<"\n........YOUNG CODERS BANQ..................."<<endl;
		cout<<"\n 1.Gestion des Comptes"<<endl;
		cout<<" 2.Transaction des Comptes"<<endl;
		cout<<" 3.Quitter le Programme"<<endl;
		cout<<"\n Fait votre Choix : ";
		cin>>Pchoix;

		switch(Pchoix)
			{
			case 1:
			   Dchoix = 0;
			  while(Dchoix!=5)
			  {
			  		cout<<"\n .....Gestion des Comptes..... "<<endl;
					cout<<" 1.Ajouter un compte "<<endl;
					cout<<" 2.Supprimer un compte "<<endl;
					cout<<" 3.Modifier un compte "<<endl;
					cout<<" 4.Afficher tous les comptes "<<endl;
					cout<<" 5.Quitter le sous menu (retour au menu principal) "<<endl;
					cout<<"\n Fait votre Choix : ";
					cin>>Dchoix;

					switch(Dchoix)
					{
						case 1: add_compte(); break;
						case 2: del(); break;
						case 3: edit(); break;
						case 4: affichage(); break;
						case 5:break;
					}
			   }
				break;

			case 2:
				Tchoix = 0;
				while(Tchoix!=6)
				{
					cout<<"\n.....Transaction des Comptes...."<<endl;
					cout<<" 1.Verser une somme dans un compte "<<endl;
					cout<<" 2.Retirer une somme du compte "<<endl;
					cout<<" 3.Virer une somme du compte vers un autre "<<endl;
					cout<<" 4.Afficher un compte "<<endl;
					cout<<" 5.Afficher tous les comptes "<<endl;
					cout<<" 6.Quitter le sous menu (retour au menu principal) "<<endl;
					cout<<"\n Fait votre Choix : ";
					cin>>Tchoix;

					switch(Tchoix)
					{
						case 1: Add_Money(); break;
					    case 2: retirement(); break;
						case 3: Transaction(); break;
						case 4: find_compte(); break;
						case 5: affichage();
							break;
						case 6:break;
					}
				}
				break;
				case 3: cout<<"\n.......FIN DU PROGRAMME......"<<endl;break;

			}
			if(Pchoix==3)
				break;
	}

}
