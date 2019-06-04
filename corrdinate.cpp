#include <iostream>
using namespace std;

corrdinate::corrdinate()
{
	row = 0;
	column = 0;
	play_value = 0;
}
corrdinate::corrdinate(int r, int c)
{
	row = r;
	column = c;
	play_value = 0;
}

void corrdinate::set_play_value(int p)
{
	play_value = p;
}
void corrdinate::set_corrdinate(int r, int c)
{
	row = r;
	column = c;
	play_value = 0;
}
int corrdinate::get_row()
{
	return row;
}
int corrdinate::get_column()
{
	return column;
}
int corrdinate::get_play_value()
{
	return play_value;
}
