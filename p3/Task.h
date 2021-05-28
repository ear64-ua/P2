// NIE X9853366M ABMA ROMERO, ENRIQUE
#ifndef _TASK_H_
#define _TASK_H_

#include <iostream>

using namespace std;

struct Date
{
  int day;
  int month;
  int year;
};

class Task
{
   friend ostream& operator<<(ostream &os, const Task &task);

   protected:
      string name;
      Date deadline;
      bool isDone;
      int time;

   public:
      Task(string name);
      string getName() const {return name;}
      Date getDeadline() const {return deadline;}
      bool getIsDone() const {return isDone;}
      int getTime() const {return time;}

      void setName(string name);
      bool setDeadline(string deadline);
      bool setTime(int time);
      void toggle();
};

#endif
