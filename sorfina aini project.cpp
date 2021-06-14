#include<iostream>
#include<iomanip>
#include<fstream>
#include<cstdlib>
#include<string>
#include<cctype>
using namespace std;

const int CAKE_ROWS=4;
const int BEV_ROWS=8;

// declare global type to store different types of data
struct Menu
{
	string name;
	double price;
	int qty;

};

void menuCafe(Menu*, Menu*,ifstream& , ifstream&);			 // function to open file for menu
void menuCafe (Menu *, Menu *);                                          // display welcome and list menu function
void orderMenu(Menu [], Menu[], Menu [], Menu [], int&,int &);		 // function to order from list menu
void displayOrder(int ,int, Menu*, Menu* );				 // function to display customer's order
void editOrder(Menu *, Menu*, Menu *, Menu*, int &, int &);              // function for customer that want to edit the order that they already decided
void paymentMethod(int, double ) ;                                       // function to determine payment method for customer's order
double calcPrice(int ,int ,Menu *, Menu *);                              // function to calculate the price from customer's order


int main ()
{
	Menu cake[CAKE_ROWS];
	Menu beverage[BEV_ROWS];  //declaration structure to array
	Menu orderCake[10];
	Menu orderBeverage[10];
	
	
	ifstream menuCake, menuBeverage;  
	
	int numC=0,numB=0, payMethod;		//numB is order for beverage, 
						//numC is the order for cake
	menuCafe(cake,beverage,  menuBeverage, menuCake);
	cout<<fixed<<showpoint<<setprecision(2);
		
	menuCafe (cake, beverage);
	orderMenu(cake, beverage, orderCake, orderBeverage, numC, numB);
	displayOrder(numB,numC,orderCake, orderBeverage);
	editOrder(cake, beverage, orderCake, orderBeverage, numC, numB);

	double amount = calcPrice(numB,numC, orderCake, orderBeverage);
    displayOrder(numB,numC,orderCake,orderBeverage);
    
    cout<<"\nThe amount that you need to pay including tax(6%) is RM"<<amount;
    
    paymentMethod(payMethod, amount);
    
    cout << "\n\n\t\t   ====>THANK YOU<====\n";
    cout << "\t\tItem Ordered Successfully ! \n\n";
    
	return 0;
}
// function to open file for Menu
void menuCafe (Menu *cake, Menu *beverage, ifstream &menuBeverage, ifstream &menuCake)
{
	
		menuCake.open("Cake Menu.txt"); //open the file with the 
		menuBeverage.open("Drink Menu.txt"); //external name Cake Menu.txt and Drink Menu.txt
	
	if (menuBeverage.fail()||menuCake.fail())    //chech for successful open
	{
		cout<<"\nCannot display the menu"<<endl;
		exit(1);
	}
	    
	else //assign the value to 1-d array using pointer notation
	{
		for (int i=0;i<CAKE_ROWS;i++)
		{
		
			getline(menuCake,(cake +i)->name,':');
			menuCake>>(cake +i)->price;
			menuCake.ignore(1000,'\n');
		}
	
		for (int i=0;i<BEV_ROWS;i++)
		{
		
			getline(menuBeverage,(beverage+i)->name,':');
			menuBeverage>>(beverage+i)->price;
			menuBeverage.ignore(1000,'\n');
		
		}
	
	}	// to close the file
		menuCake.close();
		menuBeverage.close();
}	
// function to display welcome and menu list function
void menuCafe (Menu *cake, Menu *beverage)     
{
	cout << endl << "**********************************************************************" << endl;
  	cout << "\n\t\tWelcome to the Lass County Cafe! \t\n";
  	cout << endl << "**********************************************************************" << endl<<endl;
	
	
	cout<<"\t"<<"\t"<<left<<setw(25)<<"CAKE"<<setw(6)<<"PRICE"<<endl; //display the list of cake's menu
	cout<<"\t\t------------------------------------"<<endl;
	for(int i=0;i<CAKE_ROWS;i++)
		cout<<"\t"<<"\t"<<left<<setw(3)<<i+1<<setw(25)<<(cake +i)->name<<setw(6)<<(cake +i)->price<<endl;
		cout<<endl;
		
		
	cout<<"\t"<<"\t"<<left<<setw(25)<<"BEVERAGE"<<setw(6)<<"PRICE"<<endl; //display the list of beverage's menu
	cout<<"\t\t-----------------------------------"<<endl;
	for(int i=0;i<BEV_ROWS;i++)
		cout<<"\t"<<"\t"<<left<<setw(3)<<i+1<<setw(25)<<(beverage +i)->name<<setw(6)<<(beverage +i)->price<<endl;
		cout<<endl<<endl;
		
}
// function to order from list menu
void orderMenu (Menu cake[], Menu beverage[], Menu orderC[], Menu orderB[],int &numC,int &numB )
{
	int drinkNo,foodNo, leave ;
	char answerB, answerC;
	
	
	do{
	
		cout<<"\n\t->ORDER FOR BEVERAGE<-"<<endl<<endl;
		cout<<"Do you want to order beverage? Y-yes N-no: "; 
		cin>>answerB;
	
		if(toupper(answerB) =='Y')
		{
		
			for (int i=0;toupper(answerB) =='Y';i++)
			{
				cout<<"Please select number of drinks:";
				cin>>drinkNo;
				cout<<"Quantity: ";
				cin>>orderB[i].qty;
			
				orderB[i].name=beverage[drinkNo-1].name;    //store the selected beverage's index to variable beverage's order
				orderB[i].price=beverage[drinkNo-1].price;
			
				cout<<"\nAdd another order for beverage? Y-yes N-no: ";
				cin>>answerB;
			
				if(toupper(answerB) =='N')
					answerB='A';
						
				numB++;
			}
		}
	
			cout<<"\n\n\t->ORDER FOR CAKE<-"<<endl<<endl;
			cout<<"Do you want to order cake? Y-yes N-no: ";
			cin>>answerC;
	
		if(toupper(answerC) =='Y')
		{
			
			for (int i=0;toupper(answerC) =='Y';i++)
			{
				cout<<"Please select number of cake:";
				cin>>foodNo;
				cout<<"Quantity: ";
				cin>>orderC[i].qty;
			
				orderC[i].name=cake[foodNo-1].name; //store the selected cake's index to variable beverage's order
				orderC[i].price=cake[foodNo-1].price;
	
				cout<<"\nAdd another order for cake? Y-yes N-no: ";
				cin>>answerC;
				
				if(toupper(answerC) =='N')
					answerC='A';
				
				numC++;
			}
		}

		if(toupper(answerC) =='N'&& toupper(answerB)=='N')
		{
			cout<<"Are comfirmed leave without leaving? (1- Yes 2- No): "; // if the customer choose 'N'-no for both option above, 
			cin>>leave;						 // ask them again whether they want to continue or exit the program
		
			if (leave==1)  // the customer decide to leave the program
			{
				cout<<"\n\n\tPlease come again next time!\n";
				exit(1);
			}
		}
		
	}while(leave==2&&answerB=='N'&&answerC=='N');
}
// function to display customer's order
void displayOrder(int numB,int numC, Menu *orderC, Menu *orderB)
{
	//display the list order that customer decide to buy
	
	cout<<"\nYOUR ORDER : ";
	
	if(numB!=0)
	{
		cout<<"\nYour order for Beverage: \n"; 
		for(int i=0;i<numB;i++)
		{
			cout<<i+1<<". "<<(orderB +i)->name;
			cout<<" x"<<(orderB +i)->qty<<" RM "<<(orderB +i)->price*(orderB +i)->qty<<endl;
		}
	}
	
	if(numC!=0)
	{
		cout<<"\nYour order for Cake: \n";
		for(int i=0;i<numC;i++)
		{
			cout<<i+1<<". "<<(orderC +i)->name;
			cout<<" x"<<(orderC +i)->qty<<" RM "<<(orderC +i)->price * (orderC +i)->qty<<endl;
		}
	}
}

// function for customer that want to edit the order that they already decided
void editOrder(Menu *cake, Menu *beverage, Menu *orderC, Menu *orderB, int &numC, int &numB)
{
	
	int option,addB,addC,removeB,removeC;
	char edit;
	
	cout<< "\nDo you want to edit your order? Y-yes N-no: ";
	cin >> edit;
	
		
	if (edit=='Y')
	{
	
		do{
			cout << "Press 1 to add order \nPress 2 to remove order \nYour option: "; // give two option if they want to add order or remove them
			cin >> option;
			cout<<endl;
		
			switch (option)
			{
				case 1:
				{
					cout << "Press B to add beverages, Press C to add cakes: ";
					cin >> edit;
			
					if (edit=='B')
					{
						cout << "Insert additional beverage order: ";
						cin>> addB;
						cout<<"Quantity: ";
						cin>>(orderB+numB)->qty;
			
						(orderB+numB)->name=(beverage+addB-1)->name;    
						(orderB+numB)->price=(beverage+addB-1)->price;
						numB++;
					
						cout<<endl;
				
					}
					
					if (edit=='C')
					{
						cout << "Insert additional cake order: ";
						cin>> addC;
						cout<<"Quantity: ";
						cin>>(orderC+numC)->qty;
					
						(orderC+numC)->name=(cake+addB-1)->name;
						(orderC+numC)->price=(cake+addB-1)->price;
						numC++;
					
						cout<<endl;
					}
				}break;
			
				case 2:
				{
					cout << "Press B to remove beverages, Press C to remove cakes: ";
					cin >> edit;
			
					if (edit== 'B')
					{
						cout << "Which beverage would you like to remove? (insert number): " ;
						cin >> removeB;
				
						for(int i=removeB;i<numB;i++)
						{
							(orderB +i -1)->name = (orderB +i)->name;
							(orderB +i -1)->price =(orderB +i)->price;
						}
						numB--;
					}
					
					if (edit=='C')
					{
						cout << "Which cake would you like to remove? (insert number): ";
						cin>> removeC;
		
						for(int i=removeC;i<numC;i++)
						{
							(orderC +i -1)->name = (orderC +i)->name;
							(orderC +i -1)->price =(orderC +i)->price;
						}
						numC--;
					}
					cout<<endl;
				}
			}
	
			cout << "Do you want to edit again? 1-yes 0-no: ";
			cin >> option;
			cout<<endl;
	
		}while (option!=0);
	}
	
}
// function to determine payment method
void paymentMethod(int payment, double totalPrice) 
{

	int i=0, pin;
	int cardNo[100];
	double chargedMoney[20];
	double totalMoney=0;
	
	do{
	
		cout << "\n\nEnter preferrable payment method:\n";
  		cout << "1-Cash, 2-Card: ";
  		cin >> payment;
  	
  		//cash payment option
  		if (payment == 1) 
		{
   			totalMoney += totalPrice ;  //store total money customer have to pay
  		}
  	
 	 	///debit//credit Card payment option
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

			totalMoney += totalPrice ;
			chargedMoney[i] += totalMoney;		// store money that has to be charged from the card

		}
	
	}while(payment != 1 && payment != 2);
}
// function to calculate the price from customer's order
double calcPrice(int numB,int numC, Menu *orderC, Menu *orderB)
{
	const double TAX=0.06;
	double totalPrice_excTax=0;
	double totalPrice,totalPriceBeverage=0,totalPriceCake=0;

	for(int i=0;i<(numB+numC);i++)
	{
		
		totalPriceBeverage+=((orderB +i)->price*(orderB +i)->qty);
		totalPriceCake+=((orderC +i)->price*(orderC +i)->qty); 
		
		totalPrice_excTax=(totalPriceBeverage+totalPriceCake)*TAX; // store price of tax
		totalPrice=totalPriceBeverage+totalPriceCake+totalPrice_excTax; //store total price including tax
	}
	
	return totalPrice;
}
