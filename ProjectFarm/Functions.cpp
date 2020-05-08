#include "pch.h"
#include "Functions.h"
#include <string> 



void copy(char*&s1, const char *s2)
{
	s1 = new char[strlen(s2)+1];
	strcpy(s1, s2);
	return;
}

bool check_dataRT(int a, int b, int &choice)
{
	int temp;
	cin >> temp;
	while (1)
	{
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cin >> temp;
		}
		if (!cin.fail())
		{
			if (temp >= a && temp <= b)
			{
				choice = temp;
				return 1;
			}
			else
			{
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cin >> temp;
			}
		}
	}
}


void menu_main()
{
	int choice;
	cout << "	         _                                    " << endl;
	cout << " _ __ ___   __ _(_)_ __    _ __ ___   ___ _ __  _   _ " << endl;
	cout << "| '_ ` _ \\ / _` | | '_ \\  | '_ ` _ \\ / _ \\ '_ \\| | | |" << endl;
	cout << "| | | | | | (_| | | | | | | | | | | |  __/ | | | |_| |" << endl;
	cout << "|_| |_| |_|\\__,_|_|_| |_| |_| |_| |_|\\___|_| |_|\\__,_|" << endl;
	do
	{
		cout << "Start a program in:" << endl << "1. Database mode." << endl << "2. Exit" << endl;
	} while (!check_dataRT(1,2,choice));								
	if (choice == 1)
		menu_data_start();
	if (choice == 2)
		exit(0);
}

void menu_data_start()
{
	string name;
	long money;
	cout << "Enter name of your farm: ";
	getchar();
	getline(cin, name);
	char * n = new char[name.length() + 1];
	strcpy(n, name.c_str());
	cout << "Enter your balance: ";
	cin >> money;
	static Farm *Farm_main = new Farm(money, n);
	menu_data(Farm_main);
}

void menu_data(Farm *Farm_main)
{
	int choice;
	print_logo();
	while (1)
	{
		cout << "Functions of database/simulation:" << endl << "1. Editing finances" << endl << "2. Editing workers" << endl;
		cout << "3. Editing crops" << endl << "4. Editing animals" << endl;
		cout << "5. Printing functions" << endl << "6. Simulation functions" << endl;
		cout << "7. Exit the program" << endl;
		do
		{

		} while (!check_dataRT(1, 7, choice));

		if (choice == 1)
			finances(Farm_main);
		else if (choice == 2)
			workers(Farm_main);
		else if (choice == 3)
			crops(Farm_main);
		else if (choice == 4)
			animals(Farm_main);
		else if (choice == 5)
			printing(Farm_main);
		else if (choice == 6)
			skiptime(Farm_main);
		else if (choice == 7)
			exit(0);
	}
}

void finances(Farm *Farm_main)
{
	int choice;
	
	print_logo();
	while (1)
	{
		cout << "Finance functions:" << endl << "1. Change amount of funds" << endl << "2. Editing worker's salary" << endl;
		cout << "3. Back" << endl;
		do
		{

		} while (!check_dataRT(1, 3, choice));
		if (choice == 1)
		{
			cout << "Current balance is: " << Farm_main->Money() << endl;
			cout << "Change funds to: ";
			cin >> choice;
			Farm_main->set_money(choice);
		}
		else if (choice == 2)
		{
			if (Farm_main->WListsize() == 0)
			{
				cout << "No workers available" << endl;
			}
			else
			{
				Farm_main->print_worker_names();
				cout << "Input a worker id to edit his data" << endl;
				long choiceID;
				cin >> choiceID;
				if (!Farm_main->exist_id(choiceID))
				{
					cout << "No such id found" << endl;
				}
				else
				{
					Worker worker = Farm_main->find_worker(choiceID);
					long salary;
					cout << "New salary:";
					cin >> salary;
					worker.set_salary(salary);
				}
			}
		}
		else if (choice == 3)
		{
			print_logo();
			return;
		}
	}
}

void workers(Farm *Farm_main)
{
	int choice;

	print_logo();
	while (1)
	{
		cout << "List of workers editor" << endl << "1. Add a worker" << endl << "2. Edit worker's data" << endl;
		cout << "3. Remove a worker" << endl << "4. Clear worker's list" << endl;
		cout << "5. Print all workers data" << endl << "6. Back" << endl;
		do
		{

		} while (!check_dataRT(1, 6, choice));

		if (choice == 1)
		{
			string name;
			string sname;
			int salary;
			long id;
			cout << "Name: ";
			getchar();
			getline(cin, name);
			char * n1 = new char[name.length() + 1];
			strcpy(n1, name.c_str());

			cout << "Surname: ";
			getline(cin, sname);
			char * n2 = new char[sname.length() + 1];
			strcpy(n2, sname.c_str());

			cout << "Salary: ";
			cin >> salary;
			do
			{
				cout  << "Id: ";
				cin >> id;
			} while (Farm_main->exist_id(id));
			double productivity;
			cout << "Input productivity(from 0.0 (bad) to 2.0 (extremely good)): ";
			while (1)
			{
				cin >> productivity;
				if (productivity > 2.0 || productivity < 0.0)
					cout << "Wrong input" << endl;
				else
					break;
			}
			Worker worker(salary, id, n1, n2, productivity);
			Farm_main->add_worker(worker);
		}
		else if (choice == 2)
		{
			Farm_main->print_worker_names();
			cout << "Input a worker id to edit his data" << endl;
			long choiceID;
			cin >> choiceID;

			if (!Farm_main->exist_id(choiceID))
			{
				cout << "No such id found" << endl;
				workers(Farm_main);
			}

			Worker &worker = Farm_main->find_worker(choiceID);
			{
				cout << "Editing data of:" << endl;
				worker.print();
				string name;
				string sname;
				int salary;
				cout << "New name(write \"--\" to not to change): ";
				getchar();
				getline(cin, name);
				char * n1 = new char[name.length() + 1];
				strcpy(n1, name.c_str());
				if (n1 == "--")
				{
					delete[]n1;
					copy(n1, worker.Name());
				}
				cout << "New surname(write \"--\" to not to change): ";
				getline(cin, sname);
				char * n2 = new char[sname.length() + 1];
				strcpy(n2, sname.c_str());
				if (n2 == "--")
				{
					delete[]n2;
					copy(n2, worker.Surname());
				}
				cout << "Salary: ";
				cin >> salary;
				double productivity;
				cout << "Input productivity(from 0.0 (bad) to 2.0 (extremely good)): ";
				while (1)
				{
					cin >> productivity;
					if (productivity > 2.0 || productivity < 0.0)
						cout << "Wrong input" << endl;
					else
						break;
				}
				worker.set_productivity(productivity);
				worker.set_name(n1);
				worker.set_surname(n2);
				worker.set_salary(salary);
			}
		}
		else if (choice == 3)
		{
			Farm_main->print_worker_names();
			cout << "Input a worker id to remove him" << endl;
			long choiceW;
			cin >> choiceW;
			if (!Farm_main->exist_id(choiceW))
			{
				cout << "No such id found" << endl;
			}
			else
				Farm_main->rem_worker(choiceW);
		}
		else if (choice == 4)
		{
			Farm_main->clear_workers();
		}
		else if (choice == 5)
			Farm_main->print_workers();
		else if (choice == 6)
		{
			print_logo();
			return;
		}
	}
}

void crops(Farm *Farm_main)
{
	int choice;

	print_logo();
	while (1)
	{
		cout << "List of crops editor" << endl << "1. Add a crop" << endl << "2. Edit crops' data" << endl;
		cout << "3. Remove a crop" << endl << "4. Clear crops' list" << endl;
		cout << "5. Print all crops data" << endl << "6. Back" << endl;
		do
		{

		} while (!check_dataRT(1, 6, choice));

		if (choice == 1)
		{
			string name;
			int cost;
			int amount;
			cout << "Species: ";
			getchar();
			getline(cin, name);
			char * n1 = new char[name.length() + 1];
			strcpy(n1, name.c_str());
			cout << "Cost(for 1): ";
			cin >> cost;
			cout << "Amount: ";
			cin >> amount;
			double productivity;
			cout << "Input growth rate(from 0.0 (bad) to 2.0 (extremely good)): ";
			while (1)
			{
				cin >> productivity;
				if (productivity > 2.0 || productivity < 0.0)
					cout << "Wrong input" << endl;
				else
					break;
			}
			Crop crop(cost, n1, productivity, amount);
			Farm_main->add_crop(crop);
		}
		else if (choice == 2)
		{
			Farm_main->print_crops();
			cout << "Choose a crop to edit its data or write (0) to cancel" << endl;
			int choiceP;
			do
			{

			} while (!check_dataRT(0, Farm_main->CListsize(), choiceP));
			if (choiceP != 0)
			{
				cout << "Editing data of:" << endl;
				Crop& crop = Farm_main->find_crop(choiceP-1);
				crop.print();
				string name;
				int cost;
				int amount;
				cout << "New species(write \"--\" to not to change): ";
				getchar();
				getline(cin, name);
				char * n1 = new char[name.length() + 1];
				strcpy(n1, name.c_str());
				if (n1 == "--")
				{
					delete[]n1;
					copy(n1, crop.Species());
				}
				cout << "Cost(for 1): ";
				cin >> cost;
				cout << "Amount: ";
				cin >> amount;
				double productivity;
				cout << "Input growth rate(from 0.0 (bad) to 2.0 (extremely good)): ";
				while (1)
				{
					cin >> productivity;
					if (productivity > 2.0 || productivity < 0.0)
						cout << "Wrong input" << endl;
					else
						break;
				}
				crop.set_growth(productivity);
				crop.set_species(n1);
				crop.set_amount(amount);
				crop.set_cost(cost);
			}


		}
		else if (choice == 3)
		{
			Farm_main->print_crops();
			cout << "Choose a crop to remove it or write (0) to cancel" << endl;
			int choiceP;
			do
			{

			} while (!check_dataRT(0, Farm_main->CListsize(), choiceP));
			if (choiceP != 0)
			{
				Farm_main->rem_crop(choiceP-1);
			}
		}
		else if (choice == 4)
		{
			Farm_main->clear_crops();
		}
		else if (choice == 5)
			Farm_main->print_crops();
		else if (choice == 6)
		{
			print_logo();
			return;
		}
	}
}

void animals(Farm *Farm_main)
{
	
	int choice;

	print_logo();
	while (1)
	{
		cout << "List of animals editor" << endl << "1. Add a animal" << endl << "2. Edit animals' data" << endl;
		cout << "3. Remove a animal" << endl << "4. Clear animals' list" << endl;
		cout << "5. Print all animals data" << endl << "6. Back" << endl;
		do
		{

		} while (!check_dataRT(1, 6, choice));

		if (choice == 1)
		{
			string name;
			int cost;
			int amount;
			cout << "Name: ";
			getchar();
			getline(cin, name);
			char * n1 = new char[name.length() + 1];
			strcpy(n1, name.c_str());
			cout << "Cost(for 1): ";
			cin >> cost;
			cout << "Amount: ";
			cin >> amount;
			double productivity;
			cout << "Input reproduction rate(from 0.0 (bad) to 2.0 (extremely good)): ";
			while (1)
			{
				cin >> productivity;
				if (productivity > 2.0 || productivity < 0.0)
					cout << "Wrong input" << endl;
				else
					break;
			}
			Animal animal(cost, n1, productivity, amount);
			Farm_main->add_animal(animal);
		}
		else if (choice == 2)
		{
			Farm_main->print_animals();
			cout << "Choose a animal to edit its data or write (0) to cancel" << endl;
			int choiceA;
			do
			{

			} while (!check_dataRT(0, Farm_main->AListsize(), choiceA));
			if (choiceA != 0)
			{
				cout << "Editing data of:" << endl;
				Animal& animal = Farm_main->find_animal(choiceA - 1);
				animal.print();
				string name;
				int cost;
				int amount;
				cout << "New species(write \"--\" to not to change): ";
				getchar();
				getline(cin, name);
				char * n1 = new char[name.length() + 1];
				strcpy(n1, name.c_str());
				if (n1 == "--")
				{
					delete[]n1;
					copy(n1, animal.Name());
				}
				cout << "Cost(for 1): ";
				cin >> cost;
				cout << "Amount: ";
				cin >> amount;
				double productivity;
				cout << "Input reproduction rate(from 0.0 (bad) to 2.0 (extremely good)): ";
				while (1)
				{
					cin >> productivity;
					if (productivity > 2.0 || productivity < 0.0)
						cout << "Wrong input" << endl;
					else
						break;
				}
				animal.set_reproduction(productivity);
				animal.set_name(n1);
				animal.set_cost(cost);
				animal.set_amount(amount);
			}


		}
		else if (choice == 3)
		{
			Farm_main->print_animals();
			cout << "Choose a animal to remove it or write (0) to cancel" << endl;
			int choiceA;
			do
			{

			} while (!check_dataRT(0, Farm_main->AListsize(), choiceA));
			if (choiceA != 0)
			{
				Farm_main->rem_animal(choiceA - 1);
			}
		}
		else if (choice == 4)
		{
			Farm_main->clear_animals();
		}
		else if (choice == 5)
			Farm_main->print_animals();
		else if (choice == 6)
		{
			print_logo();
			return;
		}
	}
}

void printing(Farm *Farm_main)
{
	int choice;
	
	print_logo();

	while (1)
	{
		cout << "Printing functions:" << endl << "1. Print all available data" << endl << "2. Print all workers data" << endl;
		cout << "3. Print all crops data " << endl << "4. Print all animals data " << endl;
		cout << "5. Print all other data " << endl << "6. Back" << endl;
		do
		{

		} while (!check_dataRT(1, 6, choice));

		if (choice == 1)
		{
			Farm_main->print_workers();
			Farm_main->print_animals();
			Farm_main->print_crops();
			Farm_main->print_other();
		}
		else if (choice == 2)
			Farm_main->print_workers();
		else if (choice == 3)
			Farm_main->print_crops();
		else if (choice == 4)
			Farm_main->print_animals();
		else if (choice == 5)
			Farm_main->print_other();
		else if (choice == 6)
		{
			print_logo();
			return;
		}
	}
}

void skiptime(Farm *Farm_main)
{
	int choice;
	
	print_logo();
	while (1)
	{
		cout << "Simulation functions:" << endl << "1. Go to next week" << endl << "2. Go to next month" << endl;
		cout << "3. Go to next year " << endl << "4. Visit the workers' market " << endl <<"5. Visit the plants' market" << endl;
		cout << "6. Visit the animals' market" << endl<< "7. Sell crops " << endl << "8. Sell animals " << endl;
		cout << "9. Back" << endl;
		do
		{

		} while (!check_dataRT(1, 9, choice));

		if (choice == 1)
			Farm_main->skip_week();
		else if (choice == 2)
			Farm_main->skip_month();
		else if (choice == 3)
			Farm_main->skip_year();
		else if (choice == 4)
		{
			Farm_main->WMarket();
		}
		else if (choice == 5)
		{
			Farm_main->CMarket();
		}
		else if (choice == 6)
		{
			Farm_main->AMarket();
		}
		else if (choice == 7)
		{
			Farm_main->sell_crop();
		}
		else if (choice == 8)
		{
			Farm_main->sell_animal();
		}
		else if (choice == 9)
		{
			print_logo();
			return;
		}
	}
}

void print_logo()
{
	#ifdef _WIN32
		system("cls");
	#else
		system("clear");
	#endif
	cout << "+===============================================================================+"<<endl;
	cout << "|	  __                            _                 _       _             |" << endl;
	cout << "|	 / _| __ _ _ __ _ __ ___    ___(_)_ __ ___  _   _| | __ _| |_ ___  _ __	|" << endl;
	cout << "|	| |_ / _` | '__| '_ ` _ \\  / __| | '_ ` _ \\| | | | |/ _` | __/ _ \\| '__||" << endl;
	cout << "|	|  _| (_| | |  | | | | | | \\__ \\ | | | | | | |_| | | (_| | || (_) | |	|" << endl;
	cout << "|	|_|  \\__,_|_|  |_| |_| |_| |___/_|_| |_| |_|\\__,_|_|\\__,_|\\__\\___/|_|	|" << endl;
	cout << "+===============================================================================+" << endl;
	cout << endl;
}

void test()
{
	static Farm *Farm_main = new Farm(10000, "FARM");
	{
		Worker w(1000, 1200, "NAME", "SURNAME", 1.2);
		Crop c1(100, "CROP1", 1.5, 1000);
		Crop c2(200, "CROP2", 1.5, 1000);
		Animal a(100, "Animal", 1.8, 100);
		Farm_main->add_worker(w);
		Farm_main->add_crop(c1);
		Farm_main->add_crop(c2);
		Farm_main->add_animal(a);
		Farm_main->print_workers();
		Farm_main->print_animals();
		Farm_main->print_crops();
		Farm_main->print_other();
	}
	cout << "======================================" << endl;
	Farm_main->skip_month();
	cout << "=========================================" << endl;
	Farm_main->print_workers();
	Farm_main->print_animals();
	Farm_main->print_crops();
	Farm_main->print_other();
}