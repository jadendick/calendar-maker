#ifndef ENTRY_H
#define ENTRY_H

#include <iostream>
#include <fstream>

class Entry
{
private:
	int month;	// 0=January
	int day;
	int weekday;	// Day of week, 0 is Sunday
	std::string message;	// User added events for the day
public:
	Entry() { month=0; day=1; weekday=0; message="";}
	Entry(int m, int d, int wd, std::string msg) { month=m; day=d; weekday=wd; message=msg; }

	void setDay(int wd) { weekday=wd; }
	void setMessage(std::string msg) { message=msg; }
	void setData(int wd, std::string msg) { weekday=wd; message=msg; }
	int getDay() { return weekday; }
	std::string getMessage() { return message; }

	void operator+(std::string msg) { message+=msg; }	// Append message with string
	bool operator==(std::string date) { return (std::stoi(date.substr(0,date.find('/')))==month+1 && std::stoi(date.substr(date.find('/')+1))==day); }
	friend std::ofstream& operator<<(std::ofstream&, Entry&);	// Print a Day's data to an output stream
};

#endif
