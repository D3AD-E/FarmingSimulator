#include "pch.h"
#include "Worker.h"



Worker::Worker(int salary,long id, const char* name, const char* surname, double productivity)
{
	this->salary = salary;
	copy(this->name, name);
	copy(this->surname, surname);
	this->productivity = productivity;
	this->id = id;
}

Worker::Worker(const Worker &W)
{
	this->salary = W.salary;
	copy(this->name, W.name);
	copy(this->surname, W.surname);
	this->productivity = W.productivity;
	this->id = W.id;
}

Worker &Worker:: operator=(const Worker &W)
{
	if (name)
		delete[]name;
	if (surname)
		delete[]surname;
	this->salary = W.salary;
	copy(this->name, W.name);
	copy(this->surname, W.surname);
	this->productivity = W.productivity;
	this->id = W.id;
	return *this;
}

Worker::~Worker()
{
	delete[]this->name;
	delete[]this->surname;
}

//Setters
void Worker::set_name(const char*n) 
{ copy(name, n); };
void Worker::set_surname(const char*n) 
{ copy(surname, n); };


//Printers
void Worker::print()
{
	cout << "Worker: " << name <<" "<< surname<< endl;
	cout << "Id: " << id << endl;
	cout << "Salary: " << salary << "USD" << endl;
	cout << "Skills in growing crops: ";
	if (productivity<0.5)
		cout << "Awful"  << endl;
	else if (productivity < 1)
		cout << "Bad"  << endl;
	else if (productivity < 1.5)
		cout << "Normal"  << endl;
	else if (productivity < 1.8)
		cout << "Good"  << endl;
	else 
		cout << "Expert"  << endl;
	cout << "-------------" << endl;
	return;
}

void Worker::print_market()
{
	cout << "Worker: " << name << " " << surname << endl;
	cout << "Expected salary: " << salary <<"USD" << endl;
	cout << "Skills in growing crops: ";
	if (productivity < 0.5)
		cout << "Awful"  << endl;
	else if (productivity < 1)
		cout << "Bad"  << endl;
	else if (productivity < 1.5)
		cout << "Normal"  << endl;
	else if (productivity < 1.8)
		cout << "Good"  << endl;
	else
		cout << "Expert"  << endl;
	cout << "-------------" << endl;
	return;
}

//Simulation
void Worker::grow_crops(Crop CElement)
{
	int amount = CElement.Amount();
	amount = (int)(amount * productivity);
	cout << "Woker " << name << " " << surname << " grew a crop " << CElement.Species() << " by " << (amount - CElement.Amount()) << endl;
	CElement.set_amount(amount);
}


