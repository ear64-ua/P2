#include <iostream>

using namespace std;

class ToDo{

   friend ostream& operator<<(ostream &os, const ToDo &td);

   protected:
      int nextId = 1;
      string name;
   
   public:
      ToDo(string name);

      const string getName();
      static const int getPosProject(string name);
      static const int getPosProject(int id);

      bool setName(string name);
      void addProject(Project * project);
      void deleteProject(int id = 0);
      void setProjectDescription(string name,string description);
      void ProjectMenu(int id = 0);
};

