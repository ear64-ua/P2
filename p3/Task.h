#include <iostream>

using namespace std;

struct Date{
  int day;
  int month;
  int year;
};

class Task{

   friend ostream& operator<<(ostream &os, const Task &t);

   protected:
      string name;
      Date deadline;
      bool isDone;
      int time;

   public:
      Task(string name);
      
      const string getName();
      const Date getDeadline();
      const bool getIsDone();
      const ont getTime();

      void setName(string name);
      bool setDeadline(string deadline);
      bool setTime(int time);
      void toggle();
};