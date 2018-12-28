#include <iostream>
#include <cstdlib>
#include<ctime>
# define quan 6
# define cpu 16
# define minn 0
# define maxx cpu
using namespace std;

class linklist
{
    struct node
    {
    int data;
    int pid;
    node *link;
    }*start,*rear;
public:

    linklist()
    {
        start=NULL;
        rear=NULL;
       cout<<"time quantum :"<<quan<<endl<<"cpu time :"<<cpu<<endl;
    }


 void insert_end()
 { static int i=1;

     node *n1=new node;
     n1->data=(rand()%(maxx-minn+1))+minn;
     n1->pid=i;
     cout<<"p"<<i<<"  "<<"burst time :"<<n1->data<<endl;
     i++;
     if(start==NULL)
     {
         n1->link=n1;
         start=n1;
         rear=n1;
     }
     else
        {
        rear->link=n1;
        rear=n1;
        n1->link=start;
        }
 }

 void display()
 {

     while(start!=NULL)
     {
         cout<<start->data<<" "<<start->pid<<endl;
     }
 }

 void delete_beg()
 {
     node *temp;
     temp=start;
     start=temp->link;
     delete(temp);
     rear->link=start;
 }

 int* make_schedule(int *ts1,int *j1)
 {
   int j=0,ts=0,timeused=0;
   int *arr=new int[100];
   srand(time(0));
   insert_end();
   while(start!=NULL && timeused<=cpu)
   {
       if(start->data>quan)
       {
           timeused=timeused+quan;
           start->data=start->data-quan;
           arr[j]=start->pid;
           j++;
    /*     start=start->link;
           rear=t;
           rear->link=start;*/
           start=start->link;
       }
       else
       {
           timeused=timeused+start->data;
           arr[j]=start->pid;
           j++;
           ts=ts+(quan-start->data);
           delete_beg();
       }
       insert_end();
   }
   *ts1=ts;
   *j1=j;
   cout<<"Time used :"<<timeused<<endl;
   return arr;
 }

};

int main()
{
  linklist l1;
  int ts,j,i;
  int *x=l1.make_schedule(&ts,&j);
  for(i=0;i<j;i++)
  {
      cout<<"P"<<x[i]<<" ";
  }
  cout<<endl<<"Time Saved="<<ts;
}
