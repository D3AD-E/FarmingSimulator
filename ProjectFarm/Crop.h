#pragma once
class Crop
{
private:
	int cost;
	char* species;
	double growth;
	int amount;
public:
	Crop(int cost, const char* species, double growth, int amount);
	Crop(const Crop &c);
	Crop & operator = (const Crop & c);
	~Crop();

	//Setters
	void set_species(const char*n);
	void set_cost(int c) { cost = c; };
	void set_amount(int a) { amount = a; };
	void set_growth(double g) { growth = g; };

	//Getters
	const char* Species() { return species; };
	int Cost() { return cost; };
	int Amount() { return amount; };
	double Growth() { return  growth; };

	//Printers; print data of the node
	void print();

	//Simulation
	void grow(); //Increases by amount*growth
};

