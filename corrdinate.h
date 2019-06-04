#ifndef _corrdinate
#define _corrdinate

#include <string>
#include <iostream>
using namespace std;

class corrdinate
{
private:
	int row, column, play_value;

public:
	corrdinate();
	corrdinate(int r, int c);
	void set_corrdinate(int r, int c);
	void set_play_value(int p);
	int get_row();
	int get_column();
	int get_play_value();
};

#include "corrdinate.cpp"
#endif