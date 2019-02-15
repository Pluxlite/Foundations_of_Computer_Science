/* 
****************************************************************************************************************************************************************************

Name: Robert Bowen                             Z#: 23207972
Course Foundations of Computer Science (COP3014)
Professor: Dr. Lofton Bullard
Due Date: 11/7/17                    Due Time: 11:59 P.M.
Total points: 100
Assignment 9: call_stats5.cpp

**************************************************************************************************************************************************************************
*/

//list of librarys used
#include <fstream>
#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

//class being used in the program
class call_record
{
public:
	string firstname;
	string lastname;
	string cell_number;
	int relays;
	int call_length;
	double net_cost;
	double tax_rate;
	double call_tax;
	double total_cost;
};

//Here is the prototypes that i have declared
void Initialize(call_record *& call_DB, int & count, int & size, ifstream & in);
bool Is_empty(const int count, call_record & call_DB); //inline implementation
bool Is_full(const int count, int size);//inline implementation
int Search(const call_record *call_DB, const int count, const string key);//returns location if item in listl; otherwise return -1
void Add(call_record * &call_DB, int & count, int & size, const string key); //adds item inorder to the list
void Remove(call_record *call_DB, int & count, const string key); //removes an item from the list
void Double_size(call_record * &call_DB, int & count, int & size);
void Process(call_record *call_DB, const int & count);
void Print(const call_record *call_DB, int & count); //prints all the elements in the list to the screen
void Destroy_call_DB(call_record * &call_DB); //de-allocates all memory allocate to call_DB by operator new.



/************************************************************************************************************************************/
//Name: Initialize
//Precondition: The file is opened and read into an array
//Postcondition: The information is properly placed into an array that is in a class
//Decription: Reads the data file of call information (cell number, relays and call length) into the dynamic array of call record, 
//call_DB. If the count because equal to the size the function double_size is called and the memory allocated to call_DB is doubled.
/************************************************************************************************************************************/
void Initialize(call_record * & call_DB, int & count, int & size, ifstream & in)
{
	//makes sure that all of the content is read from the file
	while (!in.eof())
	{

		//checks to make sure the array can hold all this information
		if (Is_full(count, size) == true)
		{
			Double_size(call_DB, count, size);
		}

		//storing the information into the array.
		in >> call_DB[count].firstname;
		in >> call_DB[count].lastname;
		in >> call_DB[count].cell_number;
		in >> call_DB[count].relays;
		in >> call_DB[count].call_length;

		//While dealing with the section of the array this function is placed to do the math ahead of time.
		Process(call_DB, count);

		//make sure to increment the count so if new information needs to be add it can be based off this number.
		count++;
	}
}

/***********************************************************************************************************************************/
//Name: Is_empty
//Precondition: used to check if an array is empty
//Postcondition: if the array is empty it returns 1 otherwise being 0
//Decription: returns true if call_DB is empty
/**********************************************************************************************************************************/

//ONE WAY TO MAKE A FUNCTION INLINE IS TO PUT THE KEYWORD "inline" in from of the 
//FUNCTION HEADER AS SHOWN BELOW:
inline bool Is_empty(const int count, call_record & call_DB)
{
	if (count == 0)
	{
		return 1;
	}
	return -1;
}

//ONE WAY TO MAKE A FUNCTION INLINE IS TO PUT THE KEYWORD "inline" in from of the 
//FUNCTION HEADER AS SHOWN BELOW:
/**********************************************************************************************************************************/
//Name: Is_full 
//Precondition: Checks if the arrays completed filled
//Postcondition: If count is the same number as size it will return 1 if not then it will return 0
//Decription: returns true if call_DB is full
/*********************************************************************************************************************************/
inline bool Is_full(const int count, int size)
{
	if (count == size)
	{
		return 1;
	}
	else
	{
		return 0;
	}
	return -1;
}

/**********************************************************************************************************************************/
//Name: search
//Precondition: Searches for key in the array to see if it matches anything
//Postcondition: Taking the string key checks each cell_number in the class and returns the location that it is in
//Decription: locates key in call_DB if it is there; otherwise -1 is returned
/*********************************************************************************************************************************/
int Search(const call_record *call_DB, const int count, const string key)
{
	for (int i = 0; i < count; i++)
	{
		//if the cell number matches one found in the array it returns the location of it.
		if (key == call_DB[i].cell_number)
		{
			return i;
		}
	}

	return 0;
}

/*********************************************************************************************************************************/
//Name: Add
//Precondition: Takes information from the user and adds it to the array
//Postcondition: Prompts the user for basic information needed for the array and inserts into the array
//Decription: add key to call_DB; if call_DB is full, double_size is called to increase the size of call_DB.
/********************************************************************************************************************************/
void Add(call_record * &call_DB, int & count, int & size, const string key)
{

	//basic step function to make sure the array is large enough.
	if (Is_full(count, size) == true)
	{
		Double_size(call_DB, count, size);
	}

	//prompts the user for basic information to store including cell number
	call_DB[count].cell_number = key;

	cout << "Enter a first name";
	cin >> call_DB[count].firstname;
	cout << "Enter a last name";
	cin >> call_DB[count].lastname;
	cout << "number of relays";
	cin >> call_DB[count].relays;
	cout << "How long is the call length";
	cin >> call_DB[count].call_length;

	count++;
}

/********************************************************************************************************************************/
//Name: Remove
//Precondition: Finds an array with the string in it and deletes it
//Postcondition: Searching the whole array it looks to find a matching string and if it matches it deletes any information relating to that number
//Decription: remove key from call_DB if it is there.
/*******************************************************************************************************************************/
void Remove(call_record *call_DB, int & count, const string key)
{

	for (int i = 0; i < count; i++)
	{
		//if the number is found it will delete all of its content
		if (key == call_DB[i].cell_number)
		{
			delete[] &call_DB[i];
		}
	}

}

/******************************************************************************************************************************/
//Name: Double_Size
//Precondition: increases the size of the array
//Postcondition: It creates a copy of call_DB into a temp array that has the info and the expanded size. Deleting the old array and copy its content back with 
//adjusted size
//Decription: doubles the size (capacity) of call_DB
/******************************************************************************************************************************/
void Double_size(call_record * &call_DB, int & count, int & size)
{
	//makes a new array with double the size
	size *= 2;
	call_record *temp = new call_record[size];


	//copies the content from call_DB into temp
	for (int i = 0; i < count; i++)
	{
		temp[i] = call_DB[i];
	}

	//deallocates the memory
	delete[] call_DB;

	//places the content back with an expanded array size
	call_DB = temp;

}


/******************************************************************************************************************************/
//Name: Process
//Precondition: Calculates extra information from existing data
//Postcondition: Based off the information given from the class it uses that info to form new values of data to be added.
//Decription: calculate the net cost, tax rate, call tax and total cost for every call record in call_DB.
/*****************************************************************************************************************************/
void Process(call_record *call_DB, const int & count)
{
	call_DB[count].net_cost = (call_DB[count].relays / 50.0 * .40 * call_DB[count].call_length);

	if ((call_DB[count].relays >= 1) && (call_DB[count].relays <= 5))
	{
		call_DB[count].tax_rate = .01;
		call_DB[count].call_tax = call_DB[count].net_cost * call_DB[count].tax_rate;
	}
	else if ((call_DB[count].relays >= 6) && (call_DB[count].relays <= 11))
	{
		call_DB[count].tax_rate = .03;
		call_DB[count].call_tax = call_DB[count].net_cost * call_DB[count].tax_rate;
	}
	else if ((call_DB[count].relays >= 12) && (call_DB[count].relays <= 20))
	{
		call_DB[count].tax_rate = .05;
		call_DB[count].call_tax = call_DB[count].net_cost * call_DB[count].tax_rate;
	}
	else if ((call_DB[count].relays >= 21) && (call_DB[count].relays <= 50))
	{
		call_DB[count].tax_rate = .08;
		call_DB[count].call_tax = call_DB[count].net_cost * call_DB[count].tax_rate;
	}
	else
	{
		call_DB[count].tax_rate = .12;
		call_DB[count].call_tax = call_DB[count].net_cost * call_DB[count].tax_rate;
	}

	call_DB[count].total_cost = call_DB[count].net_cost + call_DB[count].call_tax;
}


/****************************************************************************************************************************/
//Name: Print
//Precondition: prints out all the information gathered
//Postcondition: Using a loop to print the information in each location of the arrays
//Decription: prints every field of every call_record in call_DB formatted to the screen.
/***************************************************************************************************************************/
void Print(const call_record *call_DB, int & count)
{
	//basic loop used to cycle through the whole array
	for (int i = 0; i < count; i++)
	{
		cout << fixed << setw(3) << setprecision(2) << call_DB[i].firstname << "   ";
		cout << fixed << setw(3) << setprecision(2) << call_DB[i].lastname << "   ";
		cout << fixed << setw(3) << setprecision(2) << call_DB[i].cell_number << "   ";
		cout << fixed << setw(3) << setprecision(2) << call_DB[i].relays << "   ";
		cout << fixed << setw(3) << setprecision(2) << call_DB[i].call_length << "   ";
		cout << fixed << setw(3) << setprecision(2) << call_DB[i].net_cost << "   ";
		cout << fixed << setw(3) << setprecision(2) << call_DB[i].tax_rate << "   ";
		cout << fixed << setw(3) << setprecision(2) << call_DB[i].call_tax << "   ";
		cout << fixed << setw(3) << setprecision(2) << call_DB[i].total_cost << "   " << endl << endl;
	}
}

/****************************************************************************************************************************/
//Name: Destroy_call_DB
//Precondition: Simply delete call_DB
//Postcondition: The object call_DB has all its memory removed
//Decription: de-allocates all memory allocated to call_DB.  This should be the last function to be called before the program
//            is exited.
/***************************************************************************************************************************/
void Destroy_call_DB(call_record * &call_DB)
{
	delete [] call_DB;
}



int main()
{
	//simple important variables
	int size = 5; //total amount of memory (cells) allocated for the dynamic array of call records
	int count = 0;
	call_record *call_DB = new call_record[size];
	ifstream in;

	//put code here to test your funcitons
	in.open("callstats_data.txt");

	//Primary functions used to operate program
	Initialize(call_DB, count, size, in);
	Process(call_DB, count);
	Print( call_DB, count);

	//used to destroy the object call_DB
	Destroy_call_DB(call_DB);
	return 0;
}


