#pragma once
class Worker
{
private:
	int salary;
	char* name;
	char* surname;
	double productivity;
	long id;
public:
	Worker(int salary, long id, const char* name, const char* surname, double productivity);
	Worker(const Worker &W);
	Worker &operator=(const Worker &W);
	~Worker();

	//Setters
	void set_name(const char*n);
	void set_surname(const char*n);
	void set_salary(int s) { salary = s; };
	void set_id(long i) { id = i; };
	void set_productivity(double p) { productivity = p; };

	//Getters
	const char* Name() { return name; };
	const char* Surname() { return surname; };
	int Salary() { return salary; };
	long Id() { return id; };
	double Productivity() { return productivity; };

	//Printers
	void print();
	void print_market();
	
	//Simulation
	void grow_crops(Crop CElement);//Workers starts growing crops and based on his productrivity he may increase or decrease amount of crops in crops class
};

