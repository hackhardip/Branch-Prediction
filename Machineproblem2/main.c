#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

int main( int argc, char * argv[] )  {
    char * model;
    int m2;
    int ts;
    int miss_predict = 0;
    char * file;
    char tb;
    unsigned long long address=0,index = 0 ,sample = 0;
    
    char predict;
    
    int total = 0;
    
    
   if( argc == 4 ) {
       model = argv[1];
       ts = atoi(argv[2]);
       m2 = pow(2,ts);
       file = argv[3];
       int array[m2];
       int i;
       for(i=0; i<m2; i++){
           array[i] = 4;
       }

       FILE * hp;
       hp = fopen(file,"r");
       if(hp == NULL){
           printf("Error opening the file");
           return(1);
       }
       
       while(fscanf(hp,"%llx %c",&address,&tb))
       {
           
           
           if(feof(hp))
           {
               break;
           }
        
      
           
           total ++;
           sample = address>>2;
        
           index = ~(~0 << ts) & sample;
         
           
           if(array[index] >= 4){
               predict = 't';
        
           }
           else{
               predict = 'n';
           }
          /* if(predict != tb ){
               miss_predict ++;
               printf("%d", miss_predict);
           }
           if(tb == 't' && array[index] < 7){
               array[index] ++;
           }
           else if(array[index]>0){
               array[index] --;
           } */
           if(predict == tb){
               if(tb == 't' && array[index] <7 ){
                   array[index] ++;
               }
               else if (tb == 'n' && array[index] >0){
                   array[index] --;
               }
               
           }
           else{
               miss_predict++;
               if(tb == 't' && array[index] <7 ){
                                 array[index] ++;
                }
                else if (tb == 'n' && array[index] >0){
                                 array[index] --;
                }
               
           }
           
           
           
   
           
       }
   
       
       
       printf("OUTPUT \n");
             printf("number of predictions: %d \n",total);
             printf("number of mispredictions: %d \n",miss_predict);
         
             printf("number of mispredictions: %.2f%c \n",(double) miss_predict / (double)total * 100,'%') ;
          
              
          printf("FINAL BIMODAL CONTENTS\n");
          for(i=0; i<m2; i++){
              printf("%d      %d\n", i,array[i]);
                }
       
   
       
       
   }

    
       
    
   
    
   
   
   }

