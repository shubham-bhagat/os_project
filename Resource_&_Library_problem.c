#include <pthread.h> 
#include <semaphore.h> 
#include <stdio.h> 
#include<sys/types.h>
#include<stdlib.h>
#include<unistd.h>
#define size 10

// functions for student 1 :-
 void *student1(void *result);

// function for student 2 :-
void *student2(void *result);

// function for student 3 :--
void *student3(void *result);


//declaring mutex variable
pthread_mutex_t m; 			
int shared=1;
struct resource
{
	int pen;
	int paper;
	int ques_paper;
};
int turn=0;

//

//defining function for student and teacher

void deletion_student();
void deletion_teacher();
void studenteacher_insert(int);
void teacher_insert(int);

// Queue for student and teacher
int student_queue[size], teacher_queue[size];
int front_student=-1,rear_student=-1,front_teacher=-1,rear_teacher=-1;

int preemption;

// 

//

void studenteacher_insert(int val_of_student)
{
	if((front_student==0 && rear_student==size-1) || front_student==rear_student+1)
 	 {
  		printf("student queue is full:insertion not possible"); 
 	 }
 	 
	else
	{
		if(front_student==-1 && rear_student==-1)
		{
  		front_student=0;
  		rear_student=0;
  		}
  		
  		else if(rear_student==size-1)
  		{
  		rear_student=0;	
		}
		else
		rear_student=rear_student+1;
		
		student_queue[rear_student]=val_of_student;
		printf("\nStudent %d is inserted",val_of_student);
	}
}


//

void teacher_insert(int val_of_teacher)
{
	if(front_teacher==0 && rear_teacher==size-1 || front_teacher==rear_teacher+1)
 	 {
  		printf("teacher queue is full:insertion not possible"); 
 	 }
 	 
	else
	{
		if(front_teacher==-1 && rear_teacher==-1)
		{
  		front_teacher=0;
  		rear_teacher=0;
  		}
  		
  		else if(rear_teacher==size-1)
  		{
  		rear_teacher=0;	
		}
		else
		rear_teacher=rear_teacher+1;
		
		teacher_queue[rear_teacher]=val_of_teacher;
		printf("\nteacher %d is inserted",val_of_teacher);
	}
}

//

void deletion_student()
{
	if(front_student==-1 && rear_student==-1)
	{
	printf("\nno student in queue to process!");
	return;
	}
	
	if(front_student==rear_student)
	{
	printf("\nProcessed student: %d\n", student_queue[front_student]);
	front_student=-1;
	rear_student=-1;
	}
	else if(front_student==size-1)
	{
	printf("\nProcessed student: %d\n", student_queue[front_student]);
	front_student=0;
	}
	
	else
	{
	printf("\nProcessed student: %d\n", student_queue[front_student]);
	front_student++;
	}
	
	
}

//

void deletion_teacher()
{
	if(front_teacher==-1 && rear_teacher==-1)
	{
	printf("\nno teacher in queue to process!");
	return;
	}
	
	if(front_teacher==rear_teacher)
	{
	printf("\nProcessed teacher: %d", teacher_queue[front_teacher]);
	front_teacher=-1;
	rear_teacher=-1;
	}
	else if(front_teacher==size-1)
	{
	printf("\nProcessed teacher: %d", teacher_queue[front_teacher]);
	front_teacher=0;
	}
	
	else
	{
	printf("\nProcessed teacher: %d", teacher_queue[front_teacher]);
	front_teacher++;
	}
	
}

//


void process(){
	int ch;
   if(rear_teacher == -1)
   {
   	
      printf("\nno teacher in queue to process!");
   
  	 if(rear_student==-1)
  	 printf("\nno student to process!");
   while(front_student!=-1)
	{
    
    deletion_student();
    if(1)
    {
    printf("\nIs there any more teacher to insert  ?\n1.Yes\n2.No\n");
      scanf("%d",&ch);
      if(ch ==1)
      {
      	preemption=1;
      	return;
	  }
	}
    sleep(1);
	}
   }
   else{
      
      while(front_teacher!=-1)
	{  
      deletion_teacher();
      sleep(1);
	}
	if(rear_student==-1)
	
   	printf("\nno student to process!");
   	
	while(front_student!=-1)
	{
      deletion_student();
      if(1){
      printf("\nIs there any more taecher to insert  ?\n1.Yes\n2.No\n");
	  scanf("%d",&ch);
      if(ch==1)
      {
      	preemption=1;
      	return;
	  }
	  sleep(1);
	}
	}
   }
}
//

//



int main()
{
	printf("\n\n\n\t\t\t Resource sharing problem \n\n\n");
	printf("First Student  has pen\n");
	printf("Second Student  has paper\n");
	printf("Third Student  has question paper\n");
	
	//initializing mutex locks
	pthread_mutex_init(&m, NULL); 

	pthread_t first_student, second_student,third_student;	
	struct resource given;					//declaring object of resource
	while(turn<3)
	{
	   	if(turn==0)
		{
			given.paper=1;
			given.ques_paper=1;
			turn++;
		}
			if(turn==1)
		{
			given.pen=1;
			given.ques_paper=1;
			turn++;
	}
		if(turn==2)
	{
		given.paper=1;
		given.pen=1;
		turn++;
	}
	pthread_create(&first_student, NULL, student1, &given); 
	pthread_create(&second_student, NULL, student2, &given);
	pthread_create(&third_student, NULL, student3, &given);
	pthread_join(first_student, NULL);
	pthread_join(second_student, NULL);				
	pthread_join(third_student,NULL);
printf(" \n\n \n\n\n\t\t   *************************************\n");
printf(" \t\t\t   Library problem \n\n");
	}


//

int d,n,i;
	preemption=0;
	while(1)
	{
	if(preemption==1)
	{
	d=2;
	goto k;
	}
	printf("\n\nenter your choice :-");
	printf("\n 1. Insert number of students");
	printf("\n 2. Insert number of  teachers");
	printf("\n 3. Simulation of  student and teacher on library counter.\n");
	printf("\n- ");
	scanf("%d",&d);
	k:
	switch(d)
	{
		case 0:
			exit(0);
			
		case 1:
			printf("\nenter no. of students-");
			scanf("%d",&n);
			for(i=1;i<=n;i++)
			{
				studenteacher_insert(i);
				sleep(1);
			}
			break;
		
		case 2:
			printf("\nenter no. of teachers-");
			scanf("%d",&n);
			for(i=1;i<=n;i++)
			{
				teacher_insert(i);
				sleep(1);
			}
			preemption=0;
			break; 
			
		case 3:
			process();
			break;
	
		default:
			printf("invalid choice");
			break;
	}
	}

//	
}


void *student1(void *result)
{
    int x;
    int pen=1;
    struct resource *check=(struct resource *)result;
   	if((check->paper==1)&&(check->ques_paper==1))
    {
		//locking variable l
	    pthread_mutex_lock(&m);			
	    x=shared;
	    x++; 
	    printf("Teacher has given paper and question paper and student  have pen\n");
	    sleep(5); 
	    shared=x; 
	    printf("student 1 completed assignment\n");
	    //unlocking variable
	    pthread_mutex_unlock(&m);
							
   
  	}
}


// function for student 2 :-

void *student2(void *result)
{
    int x;
    int paper =2;
    struct resource *check=(struct resource *)result;
  	 if((check->pen==1)&&(check->ques_paper==1))
   {
	    pthread_mutex_lock(&m);
	    x=shared;
	    x++;  
	    printf("Teacher has given pen and question paper and student have paper\n");
	    sleep(5); 				
	    shared=x; 
	    printf("student 2 completed assignment\n");
	    pthread_mutex_unlock(&m);
	}
     
}


// function for student 3 :--
void *student3(void *result)

{
    int x;
    int q_paper=3;
    struct resource *check=(struct resource *)result;
   	if((check->paper==1)&&(check->pen==1))
   	{
	    pthread_mutex_lock(&m);
	    x=shared;
	    x++;  
	    printf("Teacher has given pen and paper and I have question paper\n");
	    sleep(5); 
	    shared=x; 
	    printf("student 3 completed assignment\n");
	    pthread_mutex_unlock(&m);
	}	




    
}
