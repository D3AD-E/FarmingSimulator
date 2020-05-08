#include "pch.h"
#include "Crop.h"
#include <iostream>


Crop::Crop(int cost, const char* species, double growth, int amount)
{
	this->cost = cost;
	copy(this->species, species);
	this->growth = growth;
	this->amount = amount;
}

Crop::Crop(const Crop &c)
{
	this->cost = c.cost;
	copy(this->species, c.species);
	this->growth = c.growth;
	this->amount = c.amount;
}
Crop &Crop:: operator = (const Crop & c)
{
	if (this->species)
		delete[]this->species;
	this->cost = c.cost;
	copy(this->species, c.species);
	this->growth = c.growth;
	this->amount = c.amount;
	return *this;
}
Crop::~Crop()
{
	if(species)
		delete[]species;
}

//Setters
void Crop::set_species(const char*n)
{
	copy(species, n);
}

//Printers
void Crop::print()
{
	cout << "Plant: " << species << endl;
	cout << "Cost: " << cost << "USD" << endl;
	cout << "Amount: " << amount << endl;
	cout << "Growth rate: ";
	if (growth < 0.5)
		cout << "Awful" << endl;
	else if (growth < 1)
		cout << "Bad" << endl;
	else if (growth < 1.5)
		cout << "Normal" << endl;
	else if (growth < 1.8)
		cout << "Good" << endl;
	else
		cout << "Super" << endl;
	return;
}

//Simulation
void Crop::grow()
{
	int temp = (int)(amount * growth);
	cout << "Crop " << species << " grew by " << (temp-amount) << endl;
	amount = temp;
}