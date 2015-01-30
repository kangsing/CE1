//Assuming the user input would be of the correct type.

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

string filename= "";

void createFile(string filename);
void performCommand();


int main(int argc, char* argv[]){
	cout << "c:>";
	if(argc==2){	
		filename = argv[1];
		createFile(filename);
	}
	return 0;
}

void createFile(string filename){
	ofstream writeFile(filename);
		writeFile.close();
	performCommand();
}

void performCommand(){
	vector <string> file;
	cout << "Welcome to TextBuddy. "<< filename <<" is ready for use" << endl;
	cout << "command: ";
	string command;
	cin >> command;

	while(command != "exit"){

		if(command == "add"){

			string inputline;
			getline(cin,inputline);
				//removing the extra whitespace infront
				inputline = inputline.substr(1,inputline.length()); 
			cout << "added to " << filename << ": " << '"' << inputline << '"' << endl;

			string data;
			
			ifstream in(filename);
			while(getline(in,data)){
				file.push_back(data);
			}

			in.close();
			
			file.push_back(inputline);
			ofstream add(filename);
			
			int i=0;
			int size=file.size();

			while(size > 0){
				add << file[i] << endl;
				i++; size--;
			}
			add.close();
		}

		if(command == "display"){
			string data;
			ifstream readFile(filename);
			while (getline(readFile,data)){
				file.push_back(data);
			}

			int counter=1;
			for(int i=0 ; i!=file.size() ; i++){
				cout << counter << ". ";
				cout << file[i] << endl;
				counter++;
			}
			if(file.empty())
				cout << filename << " is empty"<< endl;
		}

		if(command == "delete"){
			int number=0;
			cin >> number;

			string data;
			ifstream readFile(filename);

			while (getline(readFile,data)){
				file.push_back(data);
			}

			if(file.empty()){
				cout << "Error: File is empty, nothing to delete.";
				break;
			}

			if(number > file.size()){
				cout << "Error: Invalid item number to be deleted.";
				break;
			}

			string deletestring;
			deletestring = file[number-1];
			file.erase(file.begin()+number-1);
			cout<< "deleted from " << filename << ": " << '"' << deletestring << '"' << endl;

			ofstream add(filename);
			
			int i=0;
			int size=file.size();

			while(size > 0){
				add << file[i] << endl;
				i++; size--;
			}
			add.close();
		}

		if(command == "clear"){
			file.clear();
			ofstream add(filename);
			int i=0, size=file.size();

			while(size > 0){
				add << file[i] << endl;
				i++; size--;
			}

			add.close();
			cout<< "all content deleted from " << filename << endl;
		}

		while(!file.empty()){
				file.pop_back();
		}
			cout<< "command: ";
			cin >> command;
	}
}

