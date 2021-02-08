// Code by:	 Enrique Abma Romero
// NIE :	 X9853366M


#include <iostream>
#include <vector>
#include <cstdlib>

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

enum Error{
  ERR_OPTION,
  ERR_EMPTY,
  ERR_LIST_NAME,
  ERR_TASK_NAME,
  ERR_DATE,
  ERR_TIME
};

void error(Error e){
  switch(e){
    case ERR_OPTION:
      cout << "ERROR: wrong menu option" << endl;
      break;
    case ERR_EMPTY:
      cout << "ERROR: empty string" << endl;
      break;
    case ERR_LIST_NAME:
      cout << "ERROR: wrong list name" << endl;
      break;
    case ERR_TASK_NAME:
      cout << "ERROR: wrong task name" << endl;
      break;
    case ERR_DATE:
      cout << "ERROR: wrong date" << endl;
      break;
    case ERR_TIME:
      cout << "ERROR: wrong expected time" << endl;
  }
}

void showMainMenu(){
  cout << "1- Edit project" << endl
       << "2- Add list" << endl
       << "3- Delete list" << endl 
       << "4- Add task" << endl
       << "5- Delete task" << endl
       << "6- Toggle task" << endl
       << "7- Report" << endl
       << "q- Quit" << endl
       << "Option: ";
}


void editProject(Project &toDoList){

	Error e;

	do{
		cout << "Enter proyect name: ";
		getline(cin,toDoList.name);

		if (toDoList.name.length() == 0){
			e = ERR_EMPTY;
			error(e);
		}
	}while(toDoList.name.length() == 0);
	cout << "Enter proyect description: ";
	getline(cin,toDoList.description);

}

void addList(Project &toDoList){

  List nameList;
  Error e;
  bool repeated;

  do{
    cout << "Enter list name: " << endl;
    getline(cin,nameList.name);

    if (nameList.name.length() == 0){
      e = ERR_EMPTY;
      error(e);
    }
    
    else{

      for (int i = 0; i < toDoList.lists.size(); i++)
      {
        if ( toDoList.lists[i].name == nameList.name)
          repeated = false;
        else 
          repeated = true;
        
      }

      if (repeated){
        e = ERR_LIST_NAME;
        error(e);
        }

      else{
        toDoList.lists.push_back(nameList);
        }
    }

  } while(nameList.name.length() == 0);
}

void deleteList(Project &toDoList){
}

void addTask(Project &toDoList){
}

void deleteTask(Project &toDoList){
}

void toggleTask(Project &toDoList){
}

void report(const Project &toDoList){
}

int main(){
  Project toDoList;
  toDoList.id=1;
  char option;
  
  do{
    showMainMenu();
    cin >> option;
    cin.get();
    
    switch(option){
      case '1': editProject(toDoList);
                break;
      case '2': addList(toDoList);
                break;
      case '3': deleteList(toDoList);
                break;
      case '4': addTask(toDoList);
                break;
      case '5': deleteTask(toDoList);
                break;
      case '6': toggleTask(toDoList);
                break;
      case '7': report(toDoList);
                break;
      case 'q': break;
      default: error(ERR_OPTION);
    }
  }while(option!='q');
  
  return 0;    
}
