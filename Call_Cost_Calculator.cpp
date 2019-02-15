/****SAMPLE PROGRAM HEADER*******************************************************
Robert Bowen      Total Points:  100
Due Date:  09/05/2017
Course:  C0P3014
Assignment:  Assignment 1
Professor: Dr. Lofton Bullard

Description: Creating a program that will provide the calculations for the
net cost of a call, tax on a call, and total cost of the call. It will
determine these results by taking information from the user and those things
being, a cell phone number, the number of relay stations, and the length
in minutes of the call.
*************************************************************/
#include <iostream> //standard library for i/o
#include <string>
#include <iomanip>

using namespace std;

int main()
{
	//list of variables that will be used
	long long cell_num;
	int relays;
	int call_length;
	double tax_rate;
	double net_cost;
	double call_tax;
	double total_cost;

	string user_response = "y";

	while (user_response == "y" || user_response == "Y")
	{
		//The code to get the user's input
		cout << "Enter a cell phone number with no hyphens" << endl;
		cin >> cell_num;
		cout << "Enter the number of relay stations" << endl;
		cin >> relays;
		cout << "Finally enter how long the call was in minutes" << endl;
		cin >> call_length;

		//Calculations can be found here
		if ((relays >= 1) && (relays <= 5))
		{
			tax_rate = .01;
		}
		else if ((relays >= 6) && (relays <= 11))
		{
			tax_rate = .03;
		}
		else if ((relays >= 12) && (relays <= 20))
		{
			tax_rate = .05;
		}
		else if ((relays >= 21) && (relays <= 50))
		{
			tax_rate = .08;
		}
		else
		{
			tax_rate = .12;
		}

		net_cost = (relays / 50.0 * .40 * call_length);
		
		call_tax = net_cost * tax_rate;

		total_cost = net_cost + call_tax;

		// the results to the screen should go here.  
		cout << "\nField                      Format" << endl;
		cout << "==========================================" << endl;
		cout << "Cell Phone                 " << cell_num << endl;
		cout << "Number of Relay Stations   " << relays << endl;
		cout << "Minutes Used               " << call_length << endl;
		cout << "Net Cost                   " << fixed << setprecision(2) <<net_cost << endl;
		cout << "Call Tax                   " << fixed << call_tax << setprecision(2) << endl;
		cout << "Total Cost of Call         " << fixed << total_cost << setprecision(2) << endl;

		cout << "\nWould you like to do another calculation (Y or N): " << endl;
		cin >> user_response;
	}



	return  0;
}





