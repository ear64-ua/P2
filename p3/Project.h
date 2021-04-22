#include <iostream>

using namespace std;

class Project{

   friend ostream& operator<<(ostream &os, const Project &p);
   
   protected: 
      int id;
      string name;
      string description
   
   public:
      Project(string name,string description="");
      
      const int getId();
      const string getName();
      const string getDescription();
      static const int getPosList(string name);

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

      const string summary();
};