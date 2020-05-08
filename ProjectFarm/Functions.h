#pragma once

/*s1-destination s2-origin*/
void copy(char*&s1, const char *s2);

void menu_main(); //Starting menu

void menu_data(Farm *Farm_main);//Menu where you can choose different types of functions

void finances(Farm *Farm_main);//*type* functions are available in this menu

void workers(Farm *Farm_main);//*type* functions are available in this menu

void crops(Farm *Farm_main);//*type* functions are available in this menu

void animals(Farm *Farm_main);//*type* functions are available in this menu

void printing(Farm *Farm_main);//*type* functions are available in this menu

void skiptime(Farm *Farm_main);//*type* functions are available in this menu

void menu_data_start();//Setting up the farm class

void print_logo();//Pringts logo of a program

void test();//Just testing !!!to be removed!!!

/*checks if the data is int and is in range (a,b)*/
bool check_dataRT(int a,int b, int &choice);
