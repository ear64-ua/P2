#include <iostream>

using namespace std;

class List{

  friend ostream& operator<<(ostream &os, const List &l);

   protected:
      string name;

   public:
      List(string name);
      
      const string getName();
      const vector<Task> getTasks();
      const unsigned getNumTasks();
      const unsigned getNumDone();
      const int getTimeTasks();
      const int getTimeDone();
      const int getPosTask(string name);

      bool setName(string name);
      void addTask(const Task& task);
      bool deleteTask(string name);
      bool toggleTask(string name);
};