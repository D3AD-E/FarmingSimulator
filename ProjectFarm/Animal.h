#pragma once
class Animal
{
private:
	long cost;
	char* name;
	double reproduction;
	int amount;
public:
	Animal(int cost, const char* name, double reproduction, int amount);
	Animal(const Animal &a);
	Animal &operator=(const Animal &a);
	~Animal();

	//Setters
	void set_name(const char*n);
	void set_cost(int c) { cost = c; };
	void set_amount(int a) { amount = a; };
	void set_reproduction(double r) { reproduction = r; };

	//Getters
	const char* Name() { return name; };
	const int Cost() { return cost; };
	const int Amount() { return amount; };
	const double Reproduction() { return  reproduction; };

	//Printers; print data of the node
	void print();

	//Simulation
	void reproduce(); //Increases by amount*reproduction
	bool eat(Crop c); //Simulates eating of a crop and decreases its amount returns 0 if  amount of plants is less than (amount*(rand()%10+1))
};

