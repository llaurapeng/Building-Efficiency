
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct buildinfo{
    char building[63];
    int sqft;
    float electricity;
    float energy;
    struct buildinfo* next;

};

struct buildinfo *fill(char building[63], float energy) {

    struct buildinfo* newE = (struct buildinfo*)malloc(sizeof(struct buildinfo));
    strcpy (newE->building, building);
    newE->energy = energy;
    return newE;

}

void swapFloat(float *a, float *b) {
    float temp = *a;

    *a = *b;
    *b = temp;

}

void swapString(char a[63], char b[63]) {
    char temp[63];
    strcpy (temp, a);
    //a = temp;
    strcpy (a, b);
    //a = b;
    //b = temp;

    strcpy (b, temp);

}


void sortList (struct buildinfo* rec, int n) {
    float maxE; 
    int maxdex = 0;
    float curr;


    for (int i = 0; i <n;i++) {
        maxE = (rec+i)->energy;
       
        for (int j = i+1;j<n;j++) {
            curr = (rec+j)->energy;

            if (curr == maxE) {

                int compare = strcmp ((rec+j)->building, (rec+i)->building);

                if (compare<0) {
                    maxE = curr;
                    maxdex = j;
                    swapFloat (&(rec+i)->energy, &(rec+maxdex)->energy);
                    swapString ((rec+i)->building,(rec+maxdex)->building);

                }


            }
            
            if (curr > maxE) {
                maxE = curr;
                maxdex = j;
                swapFloat (&(rec+i)->energy, &(rec+maxdex)->energy);
                swapString ((rec+i)->building,(rec+maxdex)->building);
            }


            
        }


    }


    for (int i = 0; i <n; i++) {
        printf ("%s %f\n", (rec+i)->building, (rec+i)->energy);

        
    }


}



int main(int argc, char* argv[]){

    FILE* file;
    file = fopen(argv[1],"r");

    char input[63];
    char building[63];
    int sqft;
    float elec;
    float energy;

    int count = 1;
    int dex = 0;


    struct buildinfo* curr = NULL;

    
    struct buildinfo* head = NULL;

    while (fscanf(file, "%s", input) == 1) {
      
        //checks if file is empty
        if (dex == 0 && strcmp (input, "DONE")==0) {
            printf ("BUILDING FILE IS EMPTY");
            return 0;
        }

        //stops loop if read done
        if (strcmp (input, "DONE")==0) {
            break;
        }


        if (count==1) {
            strcpy(building, input);
            count++;
        } else if (count==2) {
            //printf ("sqft: %d\n", sqft);
            sqft = atoi(input);
            count++;

        } else if (count==3) {
            elec = atoi(input);
            if (elec !=0) {
           
                energy = (float) elec/sqft;

            } 
            if (elec == 0){

                energy = 0.0;
            }

            if (sqft == 0) {
         
                energy = 0.0;
            }
            count++;

        }


        if (head == NULL && count == 4) {
            head = fill (building, energy);
            
            curr = head;
            dex++;
            count = 1;
        }
        
        if (head!=NULL && count ==4) {
            curr->next = fill (building, energy);
            curr = curr->next;
    
            count =1;
            dex++;


        }
        
    }

    
     struct buildinfo* helper = head;
    

     struct buildinfo* entireRec = (struct buildinfo*)malloc(dex*sizeof(struct buildinfo));


     for (int i = 0; i<dex; i++) {

        strcpy ((entireRec+i)->building,helper->building);
        (entireRec+i)->energy = helper->energy;    


       
        helper = helper->next;

        

     }
     

     sortList (entireRec, dex);
     
     fclose (file);

    struct buildinfo* tmp;
    for (int i = 0; i<dex; i++) {
        tmp = head;
        head = head->next;
        free (tmp);


    }

    

    free(entireRec);



    

     return 0;




}   
