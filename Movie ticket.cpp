
#include<stdio.h>

int tot_row=5;
int tot_col=5;

int movie_seat[5][5];
char movie[][15]={"Teddy","Master","Telnet","Avengers"};

//Functions defined
FILE* open(int );
void initialize_seat(FILE *);
void display(int [][5]);
int check(int ,int [][2]);
void bill(char [],unsigned long long int ,int ,int ,int );


int main()
{
	int movie_choice,total_seat,checkval,i,j,age;
	unsigned long long int ph_no;
	FILE *fp;
    char name[40];
    
    printf("\tPLEASE FILL IN THE FOLLOWING DETAILS\n");
    printf("1.Name : ");
    gets(name);
    printf("\n2.Age : ");
    scanf("%d",&age);
    printf("\n3.Phone Number : ");
    scanf("%llu",&ph_no);
    printf("\n4.Enter your choice : \n\n");
	printf("1. Teddy -- 8:00 am\n2. Master -- 2:30 pm\n3. Telnet -- 11:30 am \n4. Avengers -- 7:00 pm\n");
	scanf("%d",&movie_choice);
	
	fp=open(movie_choice);
	
	initialize_seat(fp);
	
	//No of seat input
	do
	{
		printf("\n");
		display(movie_seat);
		
		printf("\nEnter the no of seats: ");
		scanf("%d",&total_seat);
		int seat[total_seat][2];
		printf("Enter the seat row then column: \n");
		for(i=0;i<total_seat;i++)
		{
			scanf("%d %d",&seat[i][0],&seat[i][1]);
		}
		
		checkval=check(total_seat,seat);
		
		if(checkval==0)
		{
			printf("The seat is not available please try again.\n");
		}
		
	}while(checkval==0);
	
	if(checkval==1)
	{
		rewind(fp);
		for(i=0;i<tot_row;i++)
		{
			for(j=0;j<tot_col;j++)
			{
				fprintf(fp,"%d ",movie_seat[i][j]);
			}
		}
	}
	
	bill(name,ph_no,age,total_seat,movie_choice);
	fclose(fp);
	return 0;
}

//Opening the file
FILE* open(int n)
{
	FILE *temp;
	switch(n)
	{
		case 1:
			{
				temp=fopen("Ta_m.txt","r+");
				break;
			}
		case 2:
			{
				temp=fopen("Ta_eve.txt","r+");
				break;
			}
		case 3:
			{
				temp=fopen("Eng_m.txt","r+");
				break;
			}
		case 4:
			{
				temp=fopen("Eng_eve.txt","r+");
				break;
			}
		default:
			{
				printf("Invalid Option\n");
				temp=NULL;
				break;
			}
	}
	return temp;
}

//Initializing movie seats in file 
void initialize_seat(FILE *fp)
{
	int i,j;
	fseek(fp,-1,SEEK_END);
	if(ftell(fp)==NULL)
	{
		for(i=0;i<tot_row*tot_col;i++)
		{
			fprintf(fp,"%d ",0);
		}
	}
	rewind(fp);
	for(i=0;i<tot_row;i++)
	{
		for(j=0;j<tot_col;j++)
		{
			fscanf(fp,"%d ",&movie_seat[i][j]);
		}
	}
}

//To display the available seats
void display(int movie_seat[][5])
{
	printf("   ");
	for(int i=0;i<tot_col;i++)
	{
		printf("%d\t",i+1);
	}
	for(int i=0;i<tot_row;i++)
	{
		printf("\n%d. ",i+1);
		for(int j=0;j<tot_col;j++)
		{
			if(movie_seat[i][j]==1)
			{
				printf("X\t");
			}
			else
			{
				printf("O\t");
			}
		}
	}
}

//To check availability of seats
int check(int total_seat,int seat[][2])
{
	int r,c,count=0;
	for(int i=0;i<total_seat;i++)
	{
		r=seat[i][0]-1;
		c=seat[i][1]-1;
		if(movie_seat[r][c]==0)
		{
			count++;
		}
	}
	if(count!=total_seat)
	{
		return 0;
	}
	for(int i=0;i<total_seat;i++)
	{
		r=seat[i][0]-1;
		c=seat[i][1]-1;
		movie_seat[r][c]=1;
	}
	return 1;
}

//Bill output
void bill(char name[],unsigned long long int ph_no,int age,int total_seat,int movie_choice)
{
	printf("\n__________________________________________\n\n");
	printf("\t\t\t\tBILL\n\n\n");
	printf("\t\tName : %s\n\n", name );
	printf("\t\tAge : %d\n\n", age );
	printf("\t\tPhone number : +91 %llu\n\n", ph_no );
	printf("\t\tMovie Name : %s\n\n", movie[movie_choice-1] );
	printf("\t\tNumber of seats booked : %d\n\n", total_seat);
	printf("\t\tTotal amount to be paid : %d\n\n", (total_seat*150) );
	printf("\t\t\t**Enjoy the movie :)**\n");
}


