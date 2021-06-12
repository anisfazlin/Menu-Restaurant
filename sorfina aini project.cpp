#include<iostream>
#include<iomanip>
#include<fstream>
#include<cstdlib>
#include<string>
using namespace std;

const int CAKE_ROWS=4;
const int BEV_ROWS=8;


struct Menu
{
	string name;
	double price;
	int qty;
};


void orderMenu(Menu [], Menu[], Menu [], Menu [], int&,int &);
void displayOrder(int ,int, Menu[], Menu[] );
void editOrder(Menu [], Menu[], Menu [], Menu [], int &, int &);


int main ()
{
	Menu cake[CAKE_ROWS];
	Menu beverage[BEV_ROWS];
	Menu orderCake[10];
	Menu orderBeverage[10];
	
	void read_menu(Menu [], Menu[],ifstream& , ifstream&);
	ifstream menuCake, menuBeverage;
	
	
	int numC=0,numB=0;
	char edit;
	
	read_menu(cake,beverage,  menuBeverage, menuCake);
	cout<<fixed<<showpoint<<setprecision(2);
	orderMenu(cake, beverage, orderCake, orderBeverage, numC, numB);
	displayOrder(numB,numC,orderCake, orderBeverage);
	cout<<endl;
	
	cout<< "do you want to edit your order? Y-yes N-no";
	cin >> edit;
	cout<<endl;
	
	if (edit=='Y')
		editOrder(cake, beverage, orderCake, orderBeverage, numC, numB);

	displayOrder(numB,numC,orderCake,orderBeverage);


	return 0;
}

void read_menu(Menu cake[], Menu beverage[], ifstream &menuBeverage, ifstream &menuCake)
{
	menuCake.open("Cake Menu.txt");
	menuBeverage.open("Drink Menu.txt");
	
	if (menuBeverage.fail()||menuCake.fail())     //chech for successful open
	{
		cout<<"\nCannot display the menu"<<endl;
		exit(1);
	}
	
	else
	{
		for (int i=0;i<CAKE_ROWS;i++)
		{
		
			getline(menuCake,cake[i].name,':');
			menuCake>>cake[i].price;
		}
	
		for (int i=0;i<BEV_ROWS;i++)
		{
		
			getline(menuBeverage,beverage[i].name,':');
			menuBeverage>>beverage[i].price;
		
		}
	
	}
	menuCake.close();
	menuBeverage.close();
}



void orderMenu (Menu cake[], Menu beverage[], Menu orderC[], Menu orderB[],int &numC,int &numB )
{
	int drinkNo,foodNo ;
	char answer;
	
	cout<<"\tORDER FOR BEVERAGE"<<endl;
	cout<<"Do you want to order beverage? Y-yes N-no: ";
	cin>>answer;
	
	if(answer=='Y')
	{
	
		
		for (int i=0;answer=='Y';i++)
		{
			cout<<"Please select number of drinks:";
			cin>>drinkNo;
			cout<<"Quantity: ";
			cin>>orderB[i].qty;
			
			orderB[i].name=beverage[drinkNo-1].name;
			orderB[i].price=beverage[drinkNo-1].price;
			
			cout<<"\nAdd another order for beverage? Y-yes N-no: ";
			cin>>answer;
		
			numB++;
		}
	}
	
	
	
		cout<<"\n\tORDER FOR CAKE"<<endl;
		cout<<"Do you want to order cake? Y-yes N-no: ";
		cin>>answer;
	
		if(answer=='Y')
		{
			
			for (int i=0;answer=='Y';i++)
			{
				cout<<"Please select number of cake:";
				cin>>foodNo;
				cout<<"Quantity: ";
				cin>>orderC[i].qty;
			
				orderC[i].name=cake[foodNo-1].name;
				orderC[i].price=cake[foodNo-1].price;
	
				cout<<"\nAdd another order for cake? Y-yes N-no: ";
				cin>>answer;
		
				numC++;
			}
		}
	
}

void displayOrder(int numB,int numC, Menu orderC[], Menu orderB[])
{
	char edit;
	
	cout<<"\nORDER : ";
	
	if(numB!=0)
	{
		cout<<"\nYour order for Beverage: \n";
		for(int i=0;i<numB;i++)
		{
			cout<<i+1<<". ";
			cout<<orderB[i].name;
			cout<<" x"<<orderB[i].qty<<" RM "<<orderB[i].price*orderB[i].qty<<endl;
		}
	}
	
	if(numC!=0)
	{
		cout<<"\nYour order for Cake: \n";
		for(int i=0;i<numC;i++)
		{
			cout<<i+1<<". ";
			cout<<orderC[i].name;
			cout<<" x"<<orderC[i].qty<<" RM "<<orderC[i].price * orderC[i].qty<<endl;
		}
	}

	
	
}


void editOrder(Menu cake[], Menu beverage[], Menu orderC[], Menu orderB[], int &numC, int &numB)
{
	int option,addB,addC,removeB,removeC,again;
	char add,remove;
	
	do{
		cout << "Press 1 to add order \nPress 2 to remove order \nPress 3 to edit quantity\nYour option: ";
		cin >> option;
		cout<<endl;
		
		switch (option)
		{
			case 1:
			{
				cout << "Press B to add beverages, Press C to add cakes: ";
				cin >> add;
			
				if (add=='B')
				{
					cout << "Insert additional beverage order: ";
					cin>> addB;
					cout<<"Quantity: ";
					cin>>orderB[numB].qty;
			
					orderB[numB].name=beverage[addB-1].name;
					orderB[numB].price=beverage[addB-1].price;
					numB++;
					cout<<endl;
				
				}
				
				if (add=='C')
				{
					cout << "Insert additional cake order: ";
					cin>> addC;
					cout<<"Quantity: ";
					cin>>orderC[numC].qty;
					
					orderC[numC].name=cake[addC-1].name;
					orderC[numC].price=cake[addC-1].price;
					numC++;
					cout<<endl;
				}
			}break;
			
			case 2:
			{
				cout << "Press B to remove beverages, Press C to remove cakes: ";
				cin >> remove;
			
				if (remove== 'B')
				{
					cout << "Which beverage would you like to remove? " ;
					cin >> removeB;
					
					orderB[removeB-1].name='\0';
					orderB[removeB-1].price= 0;
				}
				
				if (remove=='C')
				{
					cout << "Which cake would you like to remove? ";
					cin>> removeC;
					
					orderC[removeC-1].name='\0';
					orderC[removeC-1].price=0;
				}
				cout<<endl;
				}
			}
	
		cout << "Do you want to edit again? 1-yes 0-no: ";
		cin >> again;
		cout<<endl;
	
	}while (again!=0);
	
}

























