/***************************************
* Author: Lamba, Vishek *
* Email: vishek12@my.yorku.ca*

****************************************/

#include <stdio.h>
#include <ctype.h>  // for tolower()
#include <string.h>
#include <stdlib.h>

#define SIZE 48
#define fieldLength 258

struct db_type
{
   char name[fieldLength];
   int age;
   int height;   // cm
   float bmi;
   char status[fieldLength]; //This is the weight type that they are 
};

 
char prompt_menu(void);
void enterNew(struct db_type * pArr[]);  
void init_list(struct db_type * pArr[]); 
void displayDB(struct db_type * pArr[]);   
void sortDB(struct db_type * pArr[]);
void updateRecord(struct db_type * pArr[]); 
void removeRecord(struct db_type * pArr[]);
void clearDB(struct db_type * pArr[]);

//Helper functions for sorting
void sortByName(struct db_type*pArr[]); 
void sortByBMI(struct db_type*pArr[]);
void updateBMI(struct db_type* current, float weight);
void updateStatus(struct db_type* current); 


int main(int argc, char *argv[])
{
    
    struct db_type * db_pArr[SIZE];  // main db storage

    init_list(db_pArr);  // set to NULL
    
    char choice;
    int i; 
    //We can only have a finite amount of entries 
    for(i = 0; i<SIZE; i++){
      choice = prompt_menu();
      switch (choice)
      {
         case 'n': enterNew(db_pArr); break;
         case 'd': displayDB(db_pArr); break;
        
         case 's': sortDB(db_pArr); break;
	   
         case 'c': clearDB(db_pArr); break;  
        
         case 'u': updateRecord(db_pArr); break;
         case 'r': removeRecord(db_pArr);break;
         
         case 'q': exit(1); // terminate the whole program
       }
	
     }
     return 0;
}


char prompt_menu(void){
  char s[80];
  while(1){
    printf("\n-----------------------------------------------------------------\n");
    printf("|    %-20s","(N)ew record");
    printf("%-20s","(R)emove record");
    printf("(U)pdate record\t|\n");
    printf("|    %-20s","(S)ort database");
    printf("%-20s","(C)lear database");
    printf("(D)isplay database\t|\n");
  
    printf("|    %-20s","(Q)uit");
    printf("*Case Insensitive*\t\t\t|\n");
    printf("-----------------------------------------------------------------\n");
    printf("choose one: ");
  
    fgets(s,50, stdin); // \n added
    //scanf("%s", s);  
    if (strlen(s) == 2 && strchr("edlsuqrcwnvpr", tolower(*s))) 
       return tolower(*s); // s[0], return the first character of s  
    //else
    printf("not a valid input!\n");
	 
 }
}

/*This method initializes the list setting all entries to NULL*/
void init_list(struct db_type * pArr[]){
  int t;
  for (t=0; t<SIZE; t++)
  { 
     pArr[t]= NULL;
  }
}

// /* delete all the records in the database */
void clearDB(struct db_type * pArr[]){
   char yn[3];
   printf("are you sure to clear database? (y) or (n)? ");
    
   fgets(yn,3,stdin);
   
   // complete the function by calling init_list();
   if(strchr(yn, 'y')){
      init_list(pArr); 
   } 
   
}


/* input items into the database */
/* hint: need malloc */
void enterNew(struct db_type * pArr[SIZE]){

//Create a new structure Pointer 
struct db_type*newPerson = (struct db_type*)malloc(sizeof(struct db_type*)); 
float weight; 
printf("name: "); 
fgets(newPerson->name, fieldLength, stdin); //
//set the last character to null
newPerson->name[strlen(newPerson->name)-1] = '\0'; 

printf("age: "); 
scanf("%d", &newPerson->age); 
getchar(); 

printf("height (cm): "); 
scanf("%d", &newPerson->height); 
getchar(); 

printf("weight (kg): "); 
scanf("%f", &weight); 
getchar(); 


//Calculate the bmi 
newPerson->bmi = (weight)/(( (newPerson->height) *0.01)*( (newPerson->height)*0.01));


//Figure out thr status 
if(newPerson->bmi < 18.5){
   strcpy(newPerson->status, "Underweight"); 

}else if(newPerson->bmi>=18.5 && newPerson->bmi<=24.999){

   strcpy(newPerson->status, "Normal"); 

}else if(newPerson->bmi >=25.0 && newPerson->bmi <=29.999){

   strcpy(newPerson->status, "Overweight"); 

}else if(newPerson->bmi>=30.0 &&  newPerson->bmi<=34.999){

   strcpy(newPerson->status, "Obese I"); 

}else if(newPerson->bmi >= 35.0 && newPerson->bmi<=39.999){
   
   strcpy(newPerson->status, "Obese II"); 

}else if(newPerson->bmi >=40){

   strcpy(newPerson->status, "Obese III"); 

}

int i; 
//Add the entry 
for(i = 0; i<SIZE; i++){

   if(pArr[i] == NULL){

         pArr[i] = newPerson; //add the entry 
         break; 

   }

}
   
}


/* remove an existing item from the database */
void removeRecord (struct db_type * pArr[])	{
  
char nameToRemove[fieldLength];//The name that must be removed 


//Get the user input and edit the input 
printf("enter full name to remove: ");
fgets(nameToRemove, fieldLength, stdin); 
nameToRemove[strlen(nameToRemove)-1] = '\0'; 

int index = -1; //default keep the value of index -1 

//Search for the index of that contains the name to be removed
int i; 
for(i = 0; pArr[i] != NULL; i++){
   if(strcmp(nameToRemove, pArr[i]->name)==0){
      index = i;
      pArr[index] = NULL; //Nullify the index 
   }
}

//If there was no index found 
if(index < 0){
   printf("record not found.\n"); 

//If there was an index found 
}else{

for(i = index; i<SIZE-1; i++){
   pArr[i] = pArr[i+1]; 
}

printf("record [%s] removed successfully.\n", nameToRemove); 
}

}










/* display all the records in the database. Generate output with the same formaing as the sample output 
 use \t to align well
*/
void displayDB(struct db_type * pArr[]){
  int numberOfRecords = 0; 
  int t;
  
  
  if(pArr[0] == NULL){
   printf("===============================\n");
   printf("========== %d records ==========\n", numberOfRecords);
  }else{
    printf("===============================\n\n");
     for (t=0; t <SIZE ; t++)
  {
     if( pArr[t] != NULL)
     {   
         numberOfRecords++; 
        printf("name:\t%s",   pArr[t]->name);
        printf("\nage:\t%d\n", pArr[t]->age); 
        printf("height:\t%d\n", pArr[t]->height); 
        printf("BMI:\t%.1f\n", pArr[t]->bmi); 
        printf("status:\t%s\n\n", pArr[t]->status);
        

     } 

  }
  printf("========== %d records ==========\n", numberOfRecords);


  }
 
}


 /* modify (update weight of) an existing member */
void updateRecord (struct db_type * pArr[])	{ 
 
 //Get the name to update
char nameToUpdate[fieldLength]; 
printf("enter full name to search: "); 
fgets(nameToUpdate, fieldLength, stdin); 
nameToUpdate[strlen(nameToUpdate)-1] = '\0'; //Enter the null  

int flag = 0; 
int i; 
for(i= 0; i<SIZE; i++){

   //Only checking non-null elements 
   if(pArr[i] != NULL){

      if(strcmp(nameToUpdate, pArr[i]->name)==0){
      float weight; 
      printf("record found, enter new weight (kg): "); 
      scanf("%f", &weight); 
      getchar(); 
      flag = 1;
      updateBMI(pArr[i], weight);
      updateStatus(pArr[i]);
      printf("record [%s] updated successfully\n", nameToUpdate);
      break;
      }
   }
  
}
//The case that they aren't in the list
if(flag == 0){
   printf("Record not found!\n");
}
  
}

 
// sort the records, either by name or BMI. Prompt user for choice
void sortDB(struct db_type * pArr[])
{
   char response; 
   //Ask what to sort by
  printf("sort by name (n) or BMI (b)? ");
  scanf("%c", &response); 
  getchar(); 

  if(response == 'n'){
   sortByName(pArr); 

  
  }else if(response == 'b'){
   sortByBMI(pArr); 
  }

  
}

void sortByBMI(struct db_type* pArr[]){
int i; 
int j;


int n = 0; 

//find the length of array 
for(i = 0; pArr[i] != NULL; i++){
   n++; 
}


  for (i=0; i<n; i++)
   {
      for (j=0; j<n-1-i; j++)
      {
        
            if (pArr[j]->bmi > pArr[j+1]->bmi)
            {
               struct db_type*tmp = (struct db_type*)malloc(sizeof(struct db_type*));
               tmp = pArr[j]; 
               pArr[j] = pArr[j+1];
               pArr[j+1] = tmp;
            }
         
      }
   }
   



}




  



void sortByName(struct db_type* pArr[]){

int n = 0; 
int i; 
int j; 

//find the length of array 
for(i = 0; pArr[i] != NULL; i++){
   n++; 
}


  for (i=0; i<n; i++)
   {
      for (j=0; j<n-1-i; j++)
      {
            if (strcmp(pArr[j]->name, pArr[j+1]->name)>0)
            {  //Swap them 
               struct db_type*tmp = (struct db_type*)malloc(sizeof(struct db_type*));
               tmp = pArr[j]; 
               pArr[j] = pArr[j+1];
               pArr[j+1] = tmp;
            }
      }
   }

}

//Helper function that updates the BMI 
void updateBMI(struct db_type* current, float weight){
current->age = current->age;
current->bmi = weight/((current->height*0.01)*(current->height*0.01));

}
//This method updates the status 
void updateStatus(struct db_type* current){

//Figure out thr status 
if (current->bmi < 18.5){
   strcat(current->status, " -> Underweight");

}else if(current->bmi>=18.5 && current->bmi<=24.999){

   strcat(current->status, " -> Normal");

}else if(current->bmi >=25.0 && current->bmi <=29.999){

   strcat(current->status, " -> Overweight"); 

}else if(current->bmi>=30.0 &&  current->bmi<=34.999){

   strcat(current->status, " -> Obese I");

}else if(current->bmi >= 35.0 && current->bmi<=39.999){
   
  strcat(current->status, " -> Obese II");

}else if(current->bmi >=40){

 strcat(current->status, " -> Obese III");

}

}




