#include <iostream>
#include <ctime>
#include <fstream>
#include <vector>

#include "Entry.h"
using namespace std;

void addEvents(vector<Entry>&);
void createSchedule(string[], vector<Entry>&);
void printSchedule(vector<Entry>&);

int main()
{
	string scheduleTemplate[7] = {"Su - ", "M - ","T - ","W - ","Th - ","F - ", "S - "};	// Start of entry for each day
	vector<Entry> schedule;	// Hold an Entry object for each day on the schedule

	createSchedule(scheduleTemplate, schedule);
	addEvents(schedule);
	printSchedule(schedule);

	return 0;
}

void addEvents(vector<Entry>& schedule)
{
	while(true)
	{
		cout << "Enter date and message to add or nothing to exit. month/day message:\t" << endl;
		string input;
		cin.ignore(10000, '\n');
		getline(cin, input);

		if(input.empty())
			break;

		string date = input.substr(0,input.find(' '));
		string message = input.substr(input.find(' ')+1);

		for(size_t i = 0; i < schedule.size(); i++)	// Find correct entry and add message
			if(schedule.at(i) == date)
				schedule.at(i) + message;
	}
}

void createSchedule(string scheduleTemplate[7], vector<Entry>& schedule)
{
	cout << "Include weekends? 1/0:\t";
	bool includeWeekends;
	cin >> includeWeekends;

	cout << "What day does the schedule start? Format: month/day" << endl;
	string startDate;
	cin >> startDate;
	int startMonth = stoi(startDate.substr(0,startDate.find('/')));
	int startDay = stoi(startDate.substr(startDate.find('/')+1));

	cout << "What day does the schedule end? Format: month/day" << endl;
	string endDate;
	cin >> endDate;
	int endMonth = stoi(endDate.substr(0,endDate.find('/')));
	int endDay = stoi(endDate.substr(endDate.find('/')+1));

	time_t time = std::time(0);
	tm* lt = localtime(&time);

	while(lt->tm_mon+1 != startMonth || lt->tm_mday != startDay)	// Move time until it is equal to start date
		lt = localtime(&(time+=86400));


	while(lt->tm_mon+1 != endMonth || lt->tm_mday != endDay)
	{
		lt = localtime(&time);

		if(includeWeekends || (lt->tm_wday >= 1 && lt->tm_wday <= 5))	// Add days to schedule
			schedule.push_back(Entry(lt->tm_mon, lt->tm_mday, lt->tm_wday, scheduleTemplate[lt->tm_wday]));

		time += 86400;	// Go to next Entry
	}
}

void printSchedule(vector<Entry>& schedule)
{
	ofstream file("schedule.txt");
	for(Entry e : schedule)
		file << e;
	file.close();
}
