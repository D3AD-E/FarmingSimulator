#pragma once
#include <vector>
class Farm
{
private:
	long money;
	char* name;
	int week_num = 0;
	std::vector<Worker> WList;
	std::vector<Animal> AList;
	std::vector<Crop> CList;
	struct _Market_available
	{
		bool W = true;
		bool C = true;
		bool A = true;
	}Market_available;
	void no_dupl(int i); //1 - animal, 2 - crop
	void set_Market_available_true();
public:
	//Constructors
	Farm();
	Farm(long money, const char *name);

	//Destructor
	~Farm();

	//Setters
	void set_name(const char*n);
	void set_money(long m) { money = m; };


	//Getters
	const char* Name() {return name;};
	long Money() { return money; };
	unsigned int WListsize() { return WList.size(); };
	unsigned int AListsize() { return AList.size(); };
	unsigned int CListsize() { return CList.size(); };

	//Adders: add a *type* to a list
	bool add_worker(Worker w, long id);
	bool add_worker(Worker w);
	void add_crop(Crop c);
	void add_animal(Animal a);

	//Removers; remove a *type* from a  list
	void rem_worker(long id);
	void rem_crop(unsigned int i);
	void rem_animal(unsigned int i);
	void clear_crops();
	void clear_workers();
	void clear_animals();

	//Printers
	void print_workers();
	void print_worker_names();
	void print_animals();
	void print_crops();
	void print_other();

	//Finders: returns pointer to an element of a list
	bool exist_id(long id);
	Worker& find_worker(long id);//finds a worker by his id
	Crop& find_crop(int place);
	Animal& find_animal(int place);

	//Simulation skip *time* in a simulation
	//With each function exept skip week workers get payed, enimals eat crops (decresing amount of crops), crops grow(increasing their amount), 
	//workers grow crops based on workers productivity
	void skip_week(); //Small chance of changes in economy, but changes in marketplace if you call this function 4 times skip_month is called
	bool skip_month(); //Salary cost deduces from finances, grops have a chance to grow and animals have a chance to reproduce; animals eat plants
	void skip_year(); //Big changes to crops and great loss in money due to salary payments, but may be effective if you do not want to waste time

	//Simulation payments
	bool pay_worker(Worker w); //Pays a worker his salary; returns 0 if you do not have enough money
	bool buy_crop(Crop c, int amount); //Buys a crop (adds it to the list) ; returns 0 if you do not have enough money
	bool buy_animal(Animal a, int amount); //Buys an animal (adds it to the list); returns 0 if you do not have enough money
	
	void sell_crop(); //Sells a crop(decreases its amount by a given value if you sell all available amount 
	//then removes it from the list), increases your available funds
	void sell_animal();//Sells an animal (decreases its amount by a given value if you sell all available amount 
	//then removes it from the list), increases your available funds

	/*Market of workers; */
	void WMarket();
	/*Market of crops; */
	void CMarket();
	/*Market of animals;*/
	void AMarket();

};

