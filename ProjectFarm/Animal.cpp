#include "pch.h"
#include "Animal.h"
#include <time.h>


Animal::Animal(int cost, const char* name, double reproduction, int amount)
{
	this->cost = cost;
	copy(this->name, name);
	this->reproduction = reproduction;
	this->amount = amount;
}

Animal::Animal(const Animal &a)
{
	this->cost = a.cost;
	copy(this->name, a.name);
	this->reproduction = a.reproduction;
	this->amount = a.amount;
}
Animal &Animal:: operator = (const Animal & a)
{
	if (this->name)
		delete[]this->name;
	this->cost = a.cost;
	copy(this->name, a.name);
	this->reproduction = a.reproduction;
	this->amount = a.amount;
	return *this;
}

Animal::~Animal()
{
	if(name)
		delete[]name;
}

//Setters
void Animal::set_name(const char*n) 
{ 
	copy(name, n);
};



//Printers
void Animal::print()
{
	cout << "Animal: " << name << endl;
	cout << "Cost: " << cost << "USD" << endl;
	cout << "Amount: " << amount << endl;
	cout << "Reproduction rate: ";
	if (reproduction < 0.5)
		cout << "Awful" << endl;
	else if (reproduction < 1)
		cout << "Bad" << endl;
	else if (reproduction < 1.5)
		cout << "Normal" << endl;
	else if (reproduction < 1.8)
		cout << "Good" << endl;
	else
		cout << "Super" << endl;
	return;
}

//Simulation
void Animal::reproduce()
{
	int temp = (int)(amount * reproduction);
	cout << "Animal " << name << " increased by " << (temp - amount) << endl;
	amount = temp;
}

bool Animal::eat(Crop c)
{
	srand(static_cast<unsigned int>(time(NULL)));
	int temp = amount * (rand() % 10 + 1);
	if (temp >= c.Amount())
		return 0;
	else
	{
		c.set_amount(c.Amount() - temp);
		return 1;
	}
}