#include <iostream>

using namespace std;

class ToDo{

   friend ostream& operator<<(ostream &os, const ToDo &td);

   protected:
      static int nextId = 1;
      string name;
      const int getPosProject(string name);
      const int getPosProject(int id);
   
   public:
      ToDo(string name);

      const string getName();

      bool setName(string name);
      void addProject(Project * project);
      void deleteProject(int id = 0);
      void setProjectDescription(string name,string description);
      void ProjectMenu(int id = 0);
};

