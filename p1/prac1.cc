// Code by:	 Enrique Abma Romero
// NIE :	 X9853366M


#include <iostream>
#include <vector>
#include <cstdlib>
#include <sstream> 

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

bool checkDate(int , int , int);

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
  bool repeated = false;

  do{
    cout << "Enter list name: ";
    getline(cin,nameList.name);

    if (nameList.name.length() == 0){
      e = ERR_EMPTY;
      error(e);
    }
    
    else{

      for (int i = 0; i < toDoList.lists.size(); i++)
      {

        if (toDoList.lists[i].name == nameList.name){
          repeated = true;
        }
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

    List nameList;
    Error e;
    int i, j;
    bool encontrado = true;

    do{
    cout << "Enter list name: ";
    getline(cin,nameList.name);

    if (nameList.name.length() == 0){
      e = ERR_EMPTY;
      error(e);
    }
    
    else {
      
      for (i = 0 ; i < toDoList.lists.size(); i++){

        if ( toDoList.lists[i].name == nameList.name){
          j = i--;
          toDoList.lists.erase(toDoList.lists.begin()+j);
          encontrado = true;
        }

        else
        	encontrado = false;
      }

      if (!encontrado){
        e = ERR_LIST_NAME;
        error(e);
      }
    }

  }while(nameList.name.length() == 0); 
}

void addTask(Project &toDoList){

	Task vecTask;
	List nameList;
  	Error e;
  	string date, aux;
  	bool found = false;
  	int i, j , day, month, year;
  	int k = 0;

	do{
	    cout << "Enter list name: ";
	    
	    getline(cin,nameList.name);

	    if (nameList.name.length() == 0){
	      e = ERR_EMPTY;
	      error(e);
	    }
	    
	    else{

	      	for (i = 0; i < toDoList.lists.size(); i++)
	      	{

		        if (toDoList.lists[i].name == nameList.name){
		          	j = i;
		          	found = true;
		        }
		     }

		    if (!found){
		      e = ERR_LIST_NAME;
		      error(e);
		    }

		    else{

		      	cout << "Enter task name: " ;
		      	getline(cin,vecTask.name);

		      	cout << "Enter deadline: ";
		   
				getline(cin,date);

				stringstream ss(date); 
			  
			    while (getline(ss, aux, '/')) { 
			        k++;

			       if (k==1){
			       	day = stoi(aux);
			        }

			       if (k==2){
			       	month = stoi(aux);
			        }

			       if (k==3){
					year = stoi(aux);
			        }
			    }

		      	if (checkDate(day, month, year)){
		      		vecTask.deadline.day = day;
		      		vecTask.deadline.month = month;
		      		vecTask.deadline.year = year; 

		      		cout << "Enter expected time: ";
		      		cin >> vecTask.time;
		      		vecTask.isDone = false;

		      		toDoList.lists[j].tasks.push_back(vecTask);
		        }

		        else if (!checkDate(day, month, year)){
		        	e = ERR_DATE;
		        	error(e);
		        }
			}
		}
	}while(nameList.name.length() == 0); 
}
void deleteTask(Project &toDoList){
}

void toggleTask(Project &toDoList){
}
void report(const Project &toDoList){

	int timeLeft = 0, timeDone = 0;

	cout << "Name: "<< toDoList.name << endl;
	cout << "Description: "<< toDoList.description << endl;

	for (int i = 0 ; i < toDoList.lists.size(); i++){

		cout << toDoList.lists[i].name << " " << endl;

		for (int j = 0 ; j < toDoList.lists[i].tasks.size(); j++){

			cout << "[";

			if (toDoList.lists[i].tasks[j].isDone){
				cout << "X";
				timeDone = timeDone + toDoList.lists[i].tasks[j].time;
			}
			else{
				cout << " ";
				timeLeft = timeLeft + toDoList.lists[i].tasks[j].time;
			}
			cout << "] ";

			cout << "(" << toDoList.lists[i].tasks[j].time << ") ";



			cout << toDoList.lists[i].tasks[j].deadline.day << "-";
			cout << toDoList.lists[i].tasks[j].deadline.month << "-";
			cout << toDoList.lists[i].tasks[j].deadline.year;

			cout << " : " << toDoList.lists[i].tasks[j].name << endl;

		}

	}

	cout << "Total left: " << timeLeft << endl;
	cout << "Total done: " << timeDone << endl;
	cout << endl;
}

bool checkDate(int day, int month, int year){

	bool bisiesto = false;
	bool valido = false;

	if((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
		bisiesto = true;

	if (year > 1999 && year < 2101){
		if (month > 0 && month < 13){
			if (bisiesto && month == 2 && day > 0 && day <= 29)
				valido = true;

			else if (!bisiesto && month == 2 && day > 0 && day <= 28)
				valido = true;
		
			else if ((month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12 ) && day > 0 && day <= 31)
				valido = true;
	
			else if ((month == 4 || month == 6 || month == 9 || month == 11 ) && day > 0 && day <= 30)
				valido = true;
		}
	}
	else
		valido = false;

	return valido;
}

int main(){
  Project toDoList;
  toDoList.id=1;
  char option;
  
  do{
    showMainMenu();
    cin >> option;
    cin.get();
    cout << endl;
    
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
