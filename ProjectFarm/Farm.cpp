#include "pch.h"
#include "Farm.h"
#include <time.h> 


//Constructors
Farm::Farm()
{
	this->money = 0;
	this->name = NULL;
}

Farm::Farm(long money, const char *name)
{
	this->money = money;
	copy(this->name, name);
}

//Destructors
Farm::~Farm()
{
}

void Farm::no_dupl(int i)
{
	if (i == 1)
	{
		for (unsigned int j1 = 0; j1 < AList.size(); j1++)
		{
			for (unsigned int j2 = j1+1; j2 < AList.size(); j2++)
			{
				if (strcmp(AList[j1].Name(), AList[j2].Name())==0)
				{
					AList[j1].set_amount(AList[j1].Amount() + AList[j2].Amount());
					AList[j1].set_reproduction((AList[j1].Reproduction() + AList[j2].Reproduction()) / 2);
					rem_animal(j2);
				}
			}
		}
	}
	else if (i == 2)
	{
		for (unsigned int j1 = 0; j1 < CList.size(); j1++)
		{
			for (unsigned int j2 = j1+1; j2 < CList.size(); j2++)
			{
				if (strcmp(CList[j1].Species(), CList[j2].Species())==0)
				{
					CList[j1].set_amount(CList[j1].Amount() + CList[j2].Amount());
					CList[j1].set_growth((CList[j1].Growth() + CList[j2].Growth()) / 2);
					rem_crop(j2);
				}
			}
		}
	}
}

//Setters
void Farm::set_name(const char*n)
{ copy(name, n);};

void  Farm::set_Market_available_true()
{
	Market_available.A = true;
	Market_available.W = true;
	Market_available.C = true;
}
//Adders
bool Farm::add_worker(Worker w, long id)
{
	for (unsigned int i = 0; i < WList.size(); i++)
	{
		if (WList[i].Id() == id)
		{
			cout << "ID already exists. Choose a new one." << endl;
			return 0;
		}
	}
	WList.push_back(w);
	return 1;
}

bool Farm::add_worker(Worker w)
{
	for (unsigned int i = 0; i < WList.size(); i++)
	{
		if (WList[i].Id() == w.Id())
		{
			cout << "ID already exists. Choose a new one." << endl;
			return 0;
		}
	}
	WList.push_back(w);
	return 1;
}
void Farm::add_crop(Crop c)
{
	CList.push_back(c);
	no_dupl(2);
	return ;
}
void Farm::add_animal(Animal a)
{
	AList.push_back(a);
	no_dupl(1);
	return;
}

//Removers
void Farm::rem_worker(long id)
{
	vector<Worker>::iterator el = WList.begin();
	for (unsigned int i = 0; i < WList.size(); i++)
	{
		if (el->Id() == id)
		{
			WList.erase(WList.begin()+i);
			return;
		}
		el++;
	}
	return;
}
void Farm::rem_crop(unsigned int i)
{
	CList.erase(CList.begin() + i);
	return;
}
void Farm::rem_animal(unsigned int i)
{
	AList.erase(AList.begin() + i);
	return;
}
void  Farm::clear_workers()
{
	WList.clear();
	cout << "Cleared the workers list"<<endl;
}
void  Farm::clear_crops()
{
	CList.clear();
	cout << "Cleared the crops list" << endl;
}
void  Farm::clear_animals()
{
	AList.clear();
	cout << "Cleared the animals list" << endl;
}


//Printers
void Farm::print_workers()
{
	if (WList.size()==0)
	{
		cout << "You have no workers" << endl;
		return;
	}
	cout << "Printing all your employees" << endl;
	vector<Worker>::iterator el = WList.begin();
	for (unsigned int i = 0; i < WList.size(); i++)
	{
		el->print();
		el++;
	}
	return;
}
void Farm::print_worker_names()
{
	if (WList.size() == 0)
	{
		cout << "You have no workers" << endl;
		return;
	}
	cout << "Printing all your employees" << endl;
	vector<Worker>::iterator el = WList.begin();
	for (unsigned int i = 0; i < WList.size(); i++)
	{
		cout << i << ". " << el->Name() << " " << el->Surname() << " ID: " << el->Id() << endl;
		el++;
	}
	return;

}
void Farm::print_animals()
{
	if (AList.size() == 0)
	{
		cout << "You have no animals" << endl;
		return;
	}
	cout << "Printing all animals" << endl;
	for (unsigned int i = 0; i < AList.size(); i++)
	{
		cout << "==============" << i + 1 << "==============" << endl;
		AList[i].print();
	}
	return;
}
void Farm::print_crops()
{
	if (CList.size() == 0)
	{
		cout << "You have no crops" << endl;
		return;
	}
	cout << "Printing all crops" << endl;
	for (unsigned int i = 0; i < CList.size(); i++)
	{
		cout << "==============" << i+1 << "==============" << endl;
		CList[i].print();
	}
	return;
}
void Farm::print_other()
{
	cout << "-------------" << endl;
	cout << "Farm name: " << name << endl;
	cout << "Balance: " << money << endl;
	cout << "You have " << WList.size()<<" workers " << endl;
	cout << "You have " << CList.size() << " crops "<<  endl;
	cout << "You have " << AList.size() << " animals " << endl;
	cout << "-------------" << endl;
	return;
}

//Finders
Worker& Farm::find_worker(long id)
{
	for (unsigned int i = 0; i < WList.size(); i++)
	{
		if (WList[i].Id() == id)
			return WList[i];
	}
	return WList[0];
}

Crop& Farm::find_crop(int place)
{
	return CList[place];
}

Animal& Farm::find_animal(int place)
{
	return AList[place];
}

bool Farm::exist_id(long id)
{
	for (unsigned int i = 0; i < WList.size(); i++)
	{
		if (WList[i].Id() == id)
			return 1 ;
	}
	return 0;
}

//Simulation
bool Farm::pay_worker(Worker w)
{
	long temp = money;
	if ((temp - w.Salary()) < 0)
	{
		cout << "You do not have enough money to pay " << w.Name() << " " << w.Surname() << endl;
		return 0;
	}
	else
	{
		money = temp - w.Salary();
		return 1;
	}
}

bool Farm::buy_crop(Crop c, int amount)
{
	if ((money - (c.Cost()*amount)) < 0)
	{
		cout << "You do not have enough money to buy " << c.Species() << endl;
		return 0;
	}
	else
	{
		money = money - c.Cost()*amount;
		return 1;
	}
}

bool Farm::buy_animal(Animal a, int amount)
{
	if ((money - (a.Cost()*amount)) < 0)
	{
		cout << "You do not have enough money to buy " << a.Name() << endl;
		return 0;
	}
	else
	{
		money = money - a.Cost()*amount;
		return 1;
	}
}



//Simulation skip *time* in a simulation
void Farm::skip_week()
{
	set_Market_available_true();
	if (week_num > 3)
	{
		cout << "You already skipped a week 3 times so now you skip a month"<<endl;
		skip_month();
		week_num = 0;
	}
	cout << "Welcome to the next week" << endl;
	srand( static_cast<unsigned int>(time(NULL)));
	for(unsigned int i =0;i<WList.size();i++)
	{
		if (CList.size() == 0)
		{
			cout << "No crops to grow" << endl;
			break;
		}
		int random;
		random = rand() % 10;
		if (random==0)
		{
			random = rand() % CList.size();
			Crop randomcrop = CList[random];
			WList[i].grow_crops(randomcrop);
		}
	}

	
	for (unsigned int i = 0; i < CList.size(); i++)
	{
		int random = rand() % 100;
		if (random <= 10)
		{
			CList[i].grow();
		}
	}

	for (unsigned int i = 0; i < CList.size(); i++)
	{
		for (unsigned int j = 0; j < AList.size(); j++)
		{
			int random = rand() % 100;
			if (random <= 40)
			{
				if (!AList[j].eat(CList[i]))
					break;
			}
		}
	}

	for (unsigned int j = 0; j < AList.size(); j++)
	{
		int random = rand() % 100;
		if (random <= 70)
		{
			AList[j].reproduce();
		}
	}
	week_num++;
}

bool Farm::skip_month()
{
	set_Market_available_true();
	cout << "Welcome to the next month" << endl;
	for (unsigned int i = 0; i < WList.size(); i++)
	{
		if (!this->pay_worker(WList[i]))
		{
			cout << "The worker " << WList[i].Name() << " decided to leave" << endl;
			this->rem_worker(WList[i].Id());
			break;
		}
	}

	if (WList.size() == 0 || (WList.size() == 0 && CList.size() == 0))
	{
		cout << "Nothing to grow, or you have 0 workers" << endl;
		return 0;
	}

	//Workers growing crops
	srand( static_cast<unsigned int>(time(NULL)));
	for (unsigned int i = 0; i < WList.size(); i++)
	{
		if (CList.size() == 0)
		{
			cout << "No crops to grow for workers" << endl;
			break;
		}
		int random;
		random = rand() % 2;
		if (random)
		{
			random = rand() % CList.size();
			Crop randomcrop = CList[random];
			WList[i].grow_crops(randomcrop);
		}
	}
	//Crops growing by themselves
	for (unsigned int i = 0; i < CList.size(); i++)
	{
		int random = rand() % 100;
		if (random <= 80)
		{
			CList[i].grow();
		}
	}
	//animals eating crops
	for (unsigned int i = 0; i < CList.size(); i++)
	{
		for (unsigned int j = 0; j < AList.size(); j++)
		{
			int random = rand() % 100;
			if (random <= 80)
			{
				if (!AList[j].eat(CList[i]))
				{
					cout << "Animal " << AList[j].Name() << " ate all of the " << CList[i].Species() << endl;;
					rem_crop(i);
					break;
				}
			}
		}
	}
	//Animals reproducing
	if (CList.size() == 0)
	{
		cout << "No crops for animals to eat" << endl;
		for (unsigned int j = 0; j < AList.size(); j++)
		{
			int a;
			a = AList[j].Amount() / 3;
			cout << "Animal " << AList[j].Name() << " decreased by " << AList[j].Amount() - a << endl;
			AList[j].set_amount(a);
		}
	}
	else
	{
		for (unsigned int j = 0; j < AList.size(); j++)
		{
			AList[j].reproduce();
		}
	}
	return 1;
}

void Farm::skip_year()
{
	cout << "Changes by month:" << endl;
	for (unsigned int i = 0; i < 12; i++)
	{
		if (skip_month() == 0)
			break;
	}
}

void Farm:: WMarket()
{
	if (Market_available.W == false)
	{
		cout << "You have already visited this market, come next week!" << endl;
		return;
	}
	char answ;
	int temps;
	int tempi;
	double tempp;
	srand((unsigned int)time(NULL));
	const char *name_list[] = { "Noah","Xander","Adil","Bradley","Nicholas","Damien","Ted","Dominic",
		"Oscar","Francis","John","Ivan","Muhammed","Harris","Dexter","Tomos","Chad","Willard"
		,"Nathaniel","Kane","Haider","Jonathan","Myles","Adam","Ashley","Jerry",
		"Henry","Andrew","Peter","Osian","Jean",
		"Kieron","Julian","Floyd","Saul","Spencer",
		"Lara","Erica","Sana","Nathan","Yahya","Omar",
		"Imran","Charlie","Eugene","Dean",
		"Kenneth","Ebony","Jenson","Nikita" };
	const char *surname_list[] = { "Mccarthy","Cunningham","Townsend","Donnelly","Bush","Crawford",
		"Walters","Potter","Cox","Farmer","Wolf","Whelan","Morgan","Stevenson","Richardson","Steele",
		"Spence","Jensen","Garner","Smith","Adams","Reese","Barnett","Thompson","Zhang","Jenkins","Mathis",
		"Allen","Conner","Thomas","Jackson","Moore","Mendoza","Daniels","Ford","Carroll","Barker","Kay","Lewis",
		"Torres","Baker","Hodges","Osborne","Reyes","Leon","Chapman","Griffin","Cameron","Schevchenko","Gordon" };

	tempi = rand() % 10 + 2;
	for (int i = 0; i <= tempi; i++)
	{
		tempp = ((double)rand() / (double)(RAND_MAX)) * 2.0 + 0.2;
		if (tempp < 0.5)
			temps = rand() % 100 + 200;
		else if (tempp < 1)
			temps = rand() % 200 + 300;
		else if (tempp < 1.5)
			temps = rand() % 1000 + 500;
		else if (tempp < 1.8)
			temps = rand() % 500 + 1600;
		else
			temps = rand() % 500 + 2200;

		Worker temp(temps, 0, name_list[rand() % 49 + 1], surname_list[rand() % 49 + 1], tempp);
		temp.print_market();
		cout << "Do you accept this worker's offer? (y/n)";
		cin >> answ;
		if (answ == 'y')
		{
			long id;
			cout << "Set worker's id: ";
			while(1)
			{
				cin >> id;
				if (!exist_id(id))
				{
					temp.set_id(id);
					break;
				}
				else
					cout << "Such id already exist, try another one" << endl;
			}
			add_worker(temp);
			Market_available.W = false;
			return;
		}
	}
	cout << "There are no more unemploued workers right now, come back later" << endl;
	cout << "You did not choose any worker" << endl;
	Market_available.W = false;
	return;
}

void Farm::AMarket()
{
	if (Market_available.A == false)
	{
		cout << "You have already visited this market, come next week!" << endl;
		return;
	}
	char answ;
	int temps;
	int tempa;
	int tempi;
	double tempp;
	srand( static_cast<unsigned int>(time(NULL)));
	const char *name_list[] = { "Meleagris Gallopavo / Tukey","Bos indicus / Bull",
		"Capra Hircus / Goat","Equus Caballus / Horse","Ovis Aries / Sheep",
		"Gallus Gallus Domesticus / Chicken","Bos Tarus / Cow","Sus Scrofa / Pig" };

	tempi = rand() % 5 + 2;
	for (int i = 0; i <= tempi; i++)
	{
		tempp = ((double)rand() / (double)(RAND_MAX)) * 2.0 + 0.2;
		temps = rand() % 100 + 50;
		tempa = rand() % 500 + 100;
		Animal temp (temps, name_list[rand() % 8], tempp, tempa);
		temp.print();
		cout << "Do you want to buy this animal? (y/n)";
		cin >> answ;
		if (answ == 'y')
		{
			do
			{
				do
				{
					cout << "Amount:";
					cin >> tempi;
				} while (tempi > tempa);
			} while (!buy_animal(temp, tempi));
			temp.set_amount(tempi);
			add_animal(temp);
			Market_available.A = false;
			return;
		}
	}
	cout << "There are no more animals right now, come back later" << endl;
	cout << "You did not choose any animal" << endl;
	Market_available.A = false;
	return;
}

void Farm::CMarket()
{
	if (Market_available.C == false)
	{
		cout << "You have already visited this market, come next week!" << endl;
		return;
	}
	char answ;
	int temps;
	int tempa;
	int tempi;
	double tempp;
	srand( static_cast<unsigned int>(time(NULL)));
	const char *name_list[] = { "Triticum aestivum / Wheat",
		"Hordeum vulgare / Barley","Avena sativa / Oat","Secale cereale / Rye","Triticosecale spp. / Triticale",
		"Zea mays / Corn","Glycine spp. / Soybean",
		"Arachis hypogaea / Peanut","Brassica spp. / Mustard","Helianthus spp. / Sunflower",
		"Carthamus spp. / Safflower","Fagopyrum esculentum / Buckwheat","Nicotiana tabacum / Tobacco",
		"Beta vulgaris var.altissima / Sugar Beet" };

	tempi = rand() % 5 + 2;
	for (int i = 0; i <= tempi; i++)
	{
		tempp = ((double)rand() / (double)(RAND_MAX)) * 2.0 + 0.2;
		temps = rand() % 10 + 2;
		tempa = rand() % 1000 + 100;
		Crop temp (temps, name_list[rand() % 13 + 1], tempp, tempa);
		temp.print();
		cout << "Do you want to buy this crop? (y/n)";
		cin >> answ;
		if (answ == 'y')
		{
			do
			{
				do
				{
					cout << "Amount:";
					cin >> tempi;
				} while (tempi > tempa);
			} while (!buy_crop(temp, tempi));
			temp.set_amount(tempi);
			add_crop(temp);
			Market_available.C = false;
			return;
		}
	}
	cout << "There are no more crops right now, come back later" << endl;
	cout << "You did not choose any crop" << endl;
	Market_available.C = false;
	return;
}


void Farm::sell_crop()
{
	print_crops();
	int choice;
	unsigned int a = CList.size();
	do
	{
		cout << "A crop to sell (type 0 to go back): ";
	} while (!check_dataRT(0, a, choice));
	if (choice != 0)
	{
		int amount;
		do
		{
			cout << "Amount: ";
		} while (!check_dataRT(1, CList[choice-1].Amount(), amount));

		if (amount == CList[choice - 1].Amount())
		{
			money += amount * CList[choice - 1].Cost() / 3;
			rem_crop(choice - 1);
			return;
		}
		else
		{
			money += amount * CList[choice - 1].Cost() / 3;
			CList[choice - 1].set_amount(CList[choice - 1].Amount() - amount);
			return;
		}
	}
	else
	{
		cout << "You decided not to sell a crop" << endl;
		return;
	}
}

void Farm::sell_animal()
{
	print_animals();
	int choice;
	unsigned int a = AList.size();
	do
	{
		cout << "An animal to sell (type 0 to go back): ";
	} while (!check_dataRT(0, a, choice));
	if (choice != 0)
	{
		int amount;
		do
		{
			cout << "Amount: ";
		} while (!check_dataRT(1, AList[choice - 1].Amount(), amount));

		if (amount == AList[choice - 1].Amount())
		{
			money += amount * AList[choice - 1].Cost() / 2;
			rem_animal(choice - 1);
			return;
		}
		else
		{
			money += amount * AList[choice - 1].Cost() / 3;
			AList[choice - 1].set_amount(AList[choice - 1].Amount() - amount);
			return;
		}
	}
	else
	{
		cout << "You decided not to sell a crop" << endl;
		return;
	}
}