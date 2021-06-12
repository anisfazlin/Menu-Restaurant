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

void displayMenu (Menu [], Menu []);
void orderMenu(Menu [], Menu[], Menu [], Menu [], int&,int &);
void displayOrder(int ,int, Menu[], Menu[] );
void editOrder(Menu [], Menu[], Menu [], Menu [], int &, int &);
void paymentMethod(int ) ;
double calcPrice(int ,int ,Menu [], Menu []);


int main ()
{
	Menu cake[CAKE_ROWS];
	Menu beverage[BEV_ROWS];
	Menu orderCake[10];
	Menu orderBeverage[10];
	
	void read_menu(Menu [], Menu[],ifstream& , ifstream&);
	ifstream menuCake, menuBeverage;
	
	int numC=0,numB=0, payMethod;
	char edit;
	
	read_menu(cake,beverage,  menuBeverage, menuCake);
	cout<<fixed<<showpoint<<setprecision(2);
	
	cout << endl << "********************************************************************************" << endl;
  	cout << "\n\t Welcome to the Lass County Cafe! \t\n\n";
	
	displayMenu (cake, beverage);
	orderMenu(cake, beverage, orderCake, orderBeverage, numC, numB);
	displayOrder(numB,numC,orderCake, orderBeverage);
	cout<<endl;
		
	cout<< "do you want to edit your order? Y-yes N-no: ";
	cin >> edit;
	cout<<endl;
	
	if (edit=='Y')
		editOrder(cake, beverage, orderCake, orderBeverage, numC, numB);

	//displayOrder(numB,numC,orderCake,orderBeverage);
	double amount = calcPrice(numB,numC, orderCake, orderBeverage);
    displayOrder(numB,numC,orderCake,orderBeverage);
    
    cout<<"\nThe amount that you need to pay including tax(6%) is RM"<<amount;
    
	do{
		
   		cout << "\nEnter preferrable payment method:\n";
  	  	cout << "1-Cash, 2-Card: ";
  	  	cin >> payMethod;

   	 	paymentMethod(payMethod);
    
  	}while(payMethod != 1 && payMethod != 2);
    

    
    cout << "\n  ===>THANK YOU<===\n";
  	cout << "  Item Ordered Successfully ! \n\n";
    
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
			menuCake.ignore(1000,'\n');
		}
	
		for (int i=0;i<BEV_ROWS;i++)
		{
		
			getline(menuBeverage,beverage[i].name,':');
			menuBeverage>>beverage[i].price;
			menuBeverage.ignore(1000,'\n');
		
		}
	
	}
	menuCake.close();
	menuBeverage.close();
}

void displayMenu (Menu cake[], Menu beverage[])
{
	cout<<left<<setw(25)<<"CAKE"<<setw(6)<<"PRICE"<<endl;
	cout<<"------------------------------------"<<endl;
	for(int i=0;i<CAKE_ROWS;i++)
		cout<<left<<setw(3)<<i+1<<setw(25)<<cake[i].name<<setw(6)<<cake[i].price<<endl;
		cout<<endl;
		
	cout<<left<<setw(25)<<"BEVERAGE"<<setw(6)<<"PRICE"<<endl;
	cout<<"-----------------------------------"<<endl;
	for(int i=0;i<CAKE_ROWS;i++)
		cout<<left<<setw(3)<<i+1<<setw(25)<<beverage[i].name<<setw(6)<<beverage[i].price<<endl;
		cout<<endl;
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
			cout<<i+1<<". "<<orderB[i].name;
			cout<<" x"<<orderB[i].qty<<" RM "<<orderB[i].price*orderB[i].qty<<endl;
		}
	}
	
	if(numC!=0)
	{
		cout<<"\nYour order for Cake: \n";
		for(int i=0;i<numC;i++)
		{
			cout<<i+1<<". "<<orderC[i].name;
			cout<<" x"<<orderC[i].qty<<" RM "<<orderC[i].price * orderC[i].qty<<endl;
		}
	}
}


void editOrder(Menu cake[], Menu beverage[], Menu orderC[], Menu orderB[], int &numC, int &numB)
{
	int option,addB,addC,removeB,removeC,again;
	char add,remove;
	
	do{
		cout << "Press 1 to add order \nPress 2 to remove order \nYour option: ";
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
					cout << "Which beverage would you like to remove? (insert number): " ;
					cin >> removeB;
		
					for(int i=removeB;i<numB;i++)
					{
					orderB[i-1].name = orderB[i].name;
					orderB[i-1].price = orderB[i].price;
					}
					numB--;
				}
				
				if (remove=='C')
				{
					cout << "Which cake would you like to remove? (insert number): ";
					cin>> removeC;
		
					for(int i=removeC;i<numC;i++)
					{
					orderC[i-1].name = orderC[i].name;
					orderC[i-1].price = orderC[i].price;
					}
					numC--;
				}
				cout<<endl;
				}
			}
	
		cout << "Do you want to edit again? 1-yes 0-no: ";
		cin >> again;
		cout<<endl;
	
	}while (again!=0);
	
}

void paymentMethod(int payment) 
{

	int i=0, pin;
	int cardNo[100];
	double chargedMoney[100];
	double tp, totalMoney=0;
	
  	//Cash payment option
  	if (payment == 1) 
	{

   		totalMoney += tp ;
  		
  	}
  	
  	///Credit/Debit Card Option
  	else if (payment == 2) 
	{
   	 	int card_number[100];
    		++i;
    
		cout << "Enter Your Card No : ";
		cin >> card_number[i];

		cardNo[i] = card_number[i];

		cout << "Enter Your Card Pin [we would never save your pin]  : ";
		cin >> pin;
		fflush(stdin);

		totalMoney += tp ;
		chargedMoney[i] += tp;

	}
}

double calcPrice(int numB,int numC, Menu orderC[], Menu orderB[])
{
	const double TAX=0.06;
	double totalPrice_excTax=0;
	double totalPrice,totalPriceBeverage=0,totalPriceCake=0;

	for(int i=0;i<(numB+numC);i++)
	{
		
		totalPriceBeverage+=(orderB[i].price*orderB[i].qty);
		totalPriceCake+=(orderC[i].price*orderC[i].qty);
		
		totalPrice_excTax=(totalPriceBeverage+totalPriceCake)*TAX;
		totalPrice=totalPriceBeverage+totalPriceCake+totalPrice_excTax;
	}
	
	return totalPrice;
}
