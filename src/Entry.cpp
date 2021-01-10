#include <fstream>
#include "Entry.h"

std::ofstream& operator<<(std::ofstream& o, Entry& e)	// Print a Day's data to an output stream
{
	bool printEveryDate = false;	// If true every line has the date, else only the start of the week has the date
	if(printEveryDate || e.weekday==1)	// Print date every day or on Mondays
		o <<'\n'<<e.month+1<<'/'<<e.day<<std::endl;

	o << e.message << std::endl;	// Print message

	return o;
}
