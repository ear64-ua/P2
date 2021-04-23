#ifndef _PROJECT_H_
#define _PROJECT_H_

#include <iostream>
#include "List.h"
using namespace std;

class Project{

   friend ostream& operator<<(ostream &os, const Project &p);
   
   protected: 
      int id;
      string name;
      string description;
      vector<List> lists;
      int getPosList(string name) const;
   
   public:
      Project(string name,string description="");
      ~Project();
      int getId() const {return name;}
      string getName() const {return name;}
      string getDescription() const {return description;}

      bool setId(int id);
      bool setName(string name);
      void setDescription(string description);
      void edit(string name = "", string description = "");
      void addList(string name = "");
      void deleteList(string name = "");
      void addTaskFromList(string name = "");
      void deleteTaskFromList(string name = "");
      void toggleTaskFromList(string name = "");
      void menu();

      string summary() const;
};

#endif