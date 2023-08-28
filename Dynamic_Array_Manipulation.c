#include<stdio.h>
#include<stdlib.h>
#include<string.h>


#define LIMIT 50 //macroconstant which is used throughout the program

typedef struct{
    char * fname; //first name
	char * lname; //last name
	char * show; //favorite show
}record_t;


//all function prototypes
record_t * createArray(int maxsize);
record_t * insert(record_t *myarray, int *maxsize, int *currentsize); 
void display(record_t *myarray, int currentsize);
record_t *doubleIt(record_t *arr, int size); 
int removeRecord(record_t *arr, int size, int index); 
void freeRecords(record_t *arr, int size); 

int main(void)
{
	int maxsize;

	printf("Enter a size for the dynamic array: ");
	scanf("%d", &maxsize);


	record_t *myarray = createArray(maxsize); //allocates memory in the heap which the pointer points to 
	
	int currentsize = 0; 
	int option = -1;

	while(option != 0)
    {
        printf("What would you like to do?\n");
        printf("1: Insert a record\n");
        printf("2: Display records\n");
        printf("3: Remove record\n");
        printf("4: Exit\n");
        printf("Enter an option: ");
        scanf("%d", &option);
        while(!(option >= 1 && option <= 4))
        {
            printf("Enter an option: ");
            scanf("%d", &option);
        }

        switch(option)
        {
            case 1:
                printf("Insert was selected...\n");
                myarray = insert(myarray, &maxsize, &currentsize); //function call 
                break;

            case 2:
                printf("Display was selected...\n");
                display(myarray, currentsize); //function call 
                break;

            case 3:
                printf("Remove was selected...\n");
                printf("Select an index of record to remove...\n");
                int index;
                scanf("%d", &index);
                while(!(index >= 0 && index < currentsize)) //while loop is used to check is the users input it valid or not. 
                {
                    printf("Select an index of record to remove...\n");
                    scanf("%d", &index);
                }
                currentsize = removeRecord(myarray,currentsize,index); //the currentsize changes after the removeRecord function is called. 
                break;

            case 4:
                printf("Exiting...\n");
                option = 0;
				break;

            default:
                printf("Invalid Selection...\n");


        }

    }
    
    freeRecords(myarray, currentsize); //all memory is the heap will be returned back 
    free(myarray); 
    myarray = NULL; //makes sure the pointer is not pointing to anything. 
	return 0;
}


//this function uses the malloc function to allocate memory equal to the size of the typedef struct declared.
record_t * createArray(int maxsize)
{
	record_t * arr = (record_t *) malloc(maxsize * sizeof(record_t));
	
	//if statement is used to make sure the pointer is pointing to something in the heap. 
    if(arr == NULL)
	{
		printf("malloc error in createArray...program exiting\n");
		exit(1);
	}
	
	return arr; 
}



//display function is used to display all of the elements on the array. 
void display(record_t *myarray, int currentsize)
{
	printf("---------------------------------\n");

	//if statement is used to see which address the pointer is pointing to. 
    if(myarray == NULL)
        printf("Hey this is null\n"); 
    
    //iterates through every index of the array to print out all of the eleements. 
    for(int x = 0; x < currentsize; ++x)
	{
	    printf("myarray[%d].fname = %s\n", x, myarray[x].fname); 
		printf("myarray[%d].lname = %s\n", x, myarray[x].lname); 
		printf("myarray[%d].show = %s\n", x,  myarray[x].show); 
	}

	printf("---------------------------------\n");
}


//main part of the program, it is used to add to *myarray, and add a record to the system
record_t * insert(record_t *myarray, int *maxsize, int *currentsize) 
{

        //if the currentsize is greater then the maxsize then the arrays total element count needs to be doubled by allocating more memory. 
        if(*currentsize >= *maxsize)
        {
            printf("Array is full...Need to doubleIt...\n"); 
            myarray = doubleIt(myarray, *currentsize); 
            *maxsize = *maxsize * 2; //maxsize is doubled because double the memory has been allocated into the heap. 
        }

        
        
        char FIRST[LIMIT]; 
        char LAST[LIMIT]; 
        char SHOW[LIMIT]; 
        char stdinINPUT; 

        printf("Enter the first name: "); 
        scanf(" %s", FIRST);

        printf("Enter the last name: "); 
        scanf(" %s", LAST);

        stdinINPUT = getc(stdin); //this is used because scanf adds a newline character in the buffer. getc reads the newline character.

        printf("Enter favorite show: ");
        fgets(SHOW, LIMIT, stdin); 

       


        //each pointer in the struct allocates memory so the pointer can point to memory in the heap. 
        myarray[*currentsize].fname = (char *) malloc(sizeof(char) * LIMIT); 
        myarray[*currentsize].lname = (char *) malloc(sizeof(char) * LIMIT); 
        myarray[*currentsize].show = (char *) malloc(sizeof(char) * LIMIT); 

        //checks if the pointer is pointing to an address or not. 
        if(myarray == NULL)
        {
            printf("The array is pointing to a null val\n"); 
        }

        //strcpy is used to copy the hardcoded strings into the dynamic array. 
        strcpy(myarray[*currentsize].fname, FIRST); 
        strcpy(myarray[*currentsize].lname, LAST); 
        strcpy(myarray[*currentsize].show, SHOW); 

        (*currentsize)++; //*currentsize = *currentsize + 1

 
    return myarray; 
}


//function removes a record in the system. 
int removeRecord(record_t *arr, int size, int index)
{
    
    //makes sure the index is valid. 
    if (index < 0 || index >= size) {
        printf("Invalid Index\n");
        return -1;
	}

    //because an index is being deleted, the memory needs to be returned back to the computer from the heap. 
    free(arr[index].fname); 
    free(arr[index].lname); 
    free(arr[index].show); 
    
    
    //loop goes through the array and performs a shift because an index will be deleted. 
    for(int i = 0; i < size-1; ++i)
    {
        if(i >= index)
        {
            arr[i] = arr[i + 1]; 
        }
    }

    (size) --; //size is decremented. 
    
    return size; 
}

record_t * doubleIt(record_t *arr, int size)
{
    record_t * new_arr = (record_t *) malloc(size * sizeof(record_t) * 2); //double the amount of memory is allocated into a new array
    
    //appends all of *arr to the new array. 
    for(int x = 0; x < size; ++x)
    {
        new_arr[x] = arr[x]; 
    }
    
    free(arr); //the previous array is being freed because a new array was created and memory was allocated to it.

    arr = NULL; 
    
    
    return new_arr; 
}


//this function iterates through array to free all of the memory in the heap
void freeRecords(record_t *arr, int currsize) 
{
	
    //frees all of the memory in the heap. 
    for(int i = 0; i < currsize; i++) 
    {
	free(arr[i].lname);
	free(arr[i].fname);
	free(arr[i].show);
    }
    
    //makes sure all of the pointers point to a NULL value. 
    for(int j = 0; j < currsize; j++)
    {
        arr[j].fname = NULL; 
        arr[j].lname = NULL; 
        arr[j].show = NULL;
    }
}
