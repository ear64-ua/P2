#include <iostream>
#include <vector>
#include <cstdlib>
#include <sstream> 
#include <fstream>

using namespace std;

struct Date{
  int day;
  int month;
  int year;
};

struct Task{
  string name;
  Date deadline;
  bool isDone;
  int time;
};

struct List{
  string name;
  vector<Task> tasks;
};

struct Project{
  int id;
  string name;
  string description;
  vector<List> lists;
};

struct ToDo{
  int nextId;
  string name;
  vector<Project> projects;
};

void eraseFirstElement(string &s){
   
   s.replace(0,1,"");
}

void assign(string &s, Project &toDoList){

	Project newList;
	bool newproject;

	size_t p_name = s.find("#");
	size_t p_desc = s.find("*");

   // proyecto
	if (p_name != string::npos){
		eraseFirstElement(s);
		newList.name = s;
		newproject = true;
	}

	if (p_desc != string::npos && newproject == true){

		newList.description = s;
	}

	cout << "p name" << newList.name << "p desc" << newList.description << "list name" << endl;


}

int main(){

   bool newproject;
   Project toDoList;
	
	ifstream fichero("miFichero.txt");

	if(fichero.is_open()){
		string s;
		while(getline(fichero,s)){
			size_t posi = s.find("<");
			size_t posf = s.find(">");

			// encuentra el < y asume que empieza un proyecto
			if (posi != string::npos)
				newproject=true;
			// ejcuta el proyecto
			if (posf == string::npos && newproject == true)
				assign(s, toDoList);
            // termina el proyecto
            if (posf != string::npos)
                   	  newproject = false; 
			
		}
		fichero.close();
	}
	
	else{
	    cout << "Error al abrir el fichero" << endl;
	}

	return 0;
}