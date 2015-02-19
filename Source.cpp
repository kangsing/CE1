// Author: Kang Sing
// Matric card: A0114411B
//
// **********ASSUMPTIONS AND FUNCTIONALITIES**********
// Assuming the user input would be all valid and lowercased.
// E.g. Typing a number after the command "delete".
// If user tries to delete items when the list is empty, programme will show error message.
// If user tries to delete items out of the list, programme will show error message.
// This is a project to create a text file based on user input 
// and take in and store sentences by updating the text file.
// Other functions include removing a data, displaying the remaining 
// data in the file and clear the file of all contents when called. 


#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

string fileName= "";

void createFile(string fileName);
vector<string> extractData(vector<string> file);
vector<string> updateFile(vector<string> file);
void commandAdd();
void commandDisplay();
void commandDelete();
void commandClear();
void commandSort();
void commandSearch();
void printMessageSuccessAdd (string inputline);
void printMessageSuccessDelete(string deleteString);
void printMessageSuccessSort();
void printMessageError(int errorNumber);
void printMessageClear();
void printMessageWelcome();
void printMessageCommand();
string readCommand();
void performCommand();

int main(int argc, char* argv[]){
	cout << "c:>";
	if(argc==2){	
		fileName = argv[1];
		createFile(fileName);
	}

	printMessageWelcome();
	printMessageCommand();
	performCommand();

	return 0;
}

void createFile(string fileName){
	ofstream writeFile(fileName);
		writeFile.close();
}

// This function extracts exisitng file's data into vector "file"
// and returns a vector of strings.
vector<string> extractData(vector<string> file){

	string data;
	ifstream extract(fileName);
	while(getline(extract,data)){
		file.push_back(data);
	}
	extract.close();

	return file;
}

// This function opens exisitng file and updates it with new information.
vector<string> updateFile(vector<string> file){
	ofstream add(fileName);	
	int i=0;
	int size=file.size();

	while(size > 0){
		add << file[i] << endl;
		i++; 
		size--;
	}

	add.close();
	file.clear();
	return file;
}

// This function adds a new piece of information to 
// the destination file. 
void commandAdd(){
	vector <string> file;
	string inputline;
	getline(cin,inputline);
		
	//Removing the extra whitespace infront
	inputline = inputline.substr(1,inputline.length()); 
	
	file = extractData(file);
	file.push_back(inputline);
	printMessageSuccessAdd(inputline);

	file = updateFile(file);
}

// This function displays all exisitng contents in the file.
void commandDisplay(){
	vector <string> file;
	file = extractData(file);
			
	//Printing the contents in the format of
	//1. <content #1>
	//2. <content #2>
	int counter=1;
	for(int i=0 ; i!=file.size() ; i++){
		cout << counter << ". ";
		cout << file[i] << endl;
		counter++;
	}

	//Error #3 tells user that file is empty.
	if(file.empty()){
		printMessageError(3); 
		}
	file.clear();
}

// This function deletes the specific information specify by the user input. 
// It returns error messages if there is nothing to be deleted
// or the number input to be deleted is invalid.
void commandDelete(){
	vector <string> file;

	int number=0;
	cin >> number;

	file = extractData(file);

	//Error #1 tells users that file is empty, there is
	//nothing to delete.
	if(file.empty()){
		printMessageError(1);
	}

		//Error #2 tells users that there is no such
		//data to be deleted - Invalid input.
		else 
			if(number > file.size()){
				printMessageError(2);
			}

				else{
					string deleteString;
					deleteString = file[number-1];
					file.erase(file.begin()+number-1);
					printMessageSuccessDelete(deleteString);
					file = updateFile(file);
				}
}

// This function prints the respective error messages.
void printMessageError(int errorNumber){
	switch (errorNumber){
		case(1):
			cout << "Error: File is empty, nothing to delete." <<endl;
			break;

		case(2):
			cout << "Error: Invalid item number to be deleted." << endl;
			break;

		case(3):
			cout << fileName << " is empty"<< endl;
			break;
		}
}

// This function clears all the contents in the file
// and returns with a success message. 
void commandClear(){
	ofstream add(fileName);
	add.close();
	printMessageClear();
}

// This function sorts the items in the file in ascending order
// Order: Numerical order first then in alphabetical order.
void commandSort(){
	vector <string> file;
	file = extractData(file);
	sort(file.begin(), file.end());
	file = updateFile(file);
	printMessageSuccessSort();
}

void commandSearch(){
	vector <string> file;
	file = extractData(file);

	string searchString;
	cin >> searchString;

	for(int i=0; i<file.size() ; i++){
		for(int j=0; j<searchString.length();j++){
			string extractString;
			extractString = file[i];

			if(extractString.find(searchString) != extractString.npos){
				cout << i+1 << ". " << extractString << endl; 
			}
		}
	}

}

void printMessageSuccessAdd (string inputline){
	cout << "added to " << fileName << ": " << '"' << inputline << '"' << endl;	
}

void printMessageSuccessDelete(string deleteString){
	cout<< "deleted from " << fileName << ": " << '"' << deleteString << '"' << endl;
}

void printMessageSuccessSort(){
	cout<< fileName << " has been sorted." << endl;
}

void printMessageClear(){
	cout<< "all content deleted from " << fileName << endl;
}

void printMessageWelcome(){
	cout << "Welcome to TextBuddy. "<< fileName <<" is ready for use" << endl;
}

void printMessageCommand(){
	cout << "command: ";
}

// This function reads in the command and transform it into proper format.
// For example transforming uppercase to lowercase.
string readCommand(){
	string command;
	cin>>command;
	transform(command.begin(),command.end(),command.begin(),tolower);
	return (command);
}

// This function sorts the command and calls the respective functions.
void performCommand(){
	string command = readCommand();

	while(command != "exit"){

		if(command == "add"){
			commandAdd();
		}

		else if(command == "display"){
			commandDisplay();
		}

		else if(command == "delete"){
			commandDelete();
		}

		else if(command == "clear"){
			commandClear();
		}
		
		else if(command == "sort"){
			commandSort();
		}

		else if(command == "search"){
			commandSearch();
		}

		printMessageCommand();
		command = readCommand();
	}
}

