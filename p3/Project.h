#ifndef _PROJECT_H_
#define _PROJECT_H_

#include <iostream>
#include <vector>
#include "List.h"
using namespace std;

const string P_NAME = "Enter project name: " ;
const string P_DESC = "Enter project description: ";
const string P_ID = "Enter project id: ";
const string L_NAME = "Enter list name: " ;
const string DEADLINE = "Enter deadline: ";
const string EXP_TIME = "Enter expected time: ";
const string T_NAME = "Enter task name: " ;



class Project{

   friend ostream& operator<<(ostream &os, const Project &p);
   
   protected: 
      int id;
      string name;
      string description;
      vector<List> lists;
      int getPosList(string name) const;
      void showMenu();
      int askForListName(string name);
   
   public:
      Project(string name,string description="");
      int getId() const {return id;}
      string getName() const {return name;}
      string getDescription() const {return description;}

      bool setId(int id);
      bool setName(string name);
      void setDescription(string description);
      void edit(string name = "", string description = "");
      void addList(string name = "");
      void deleteList(string name = "");
      void addTaskToList(string name="");
      void deleteTaskFromList(string name = "");
      void toggleTaskFromList(string name = "");
      void menu();

      string summary() const;
};

#endif