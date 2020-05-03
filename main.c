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
    int m;
    int n;
    int size;
    unsigned long long address=0,index = 0 ,sample = 0,sample3=0,sample1=0,sample2=0;
    
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
           if(tb == 't' && array[index] <7 ){
                   array[index] ++;
               }
           else if (tb == 'n' && array[index] >0){
                   array[index] --;
            }
               
           if(predict!=tb){
 
              miss_predict++; 
           }

           
       }
        
	printf("COMMAND \n");
	printf("./sim bimodal %d %s\n",ts,argv[3]);
	printf("OUTPUT\n");

  	printf("number of predictions:   %d\n", total);
  	printf("number of mispredictions:  %d\n", miss_predict);
  	printf("misprediction rate:   %.2f%c \n", (double) miss_predict / (double)total * 100,'%');
  	printf("FINAL BIMODAL CONTENTS\n");
  	for (int i = 0; i < m2; i++) {
      	printf("%d ", i);
      	printf("%d \n",array[i]);
  	}
      
   }
   else if(argc == 5){
       model = argv[1];
       m = atoi(argv[2]);
       n = atoi(argv[3]);
       file = argv[4];
       unsigned int regi = 0;
       unsigned int temp;
       unsigned int temp1;
       unsigned int final;
       size = pow(2,m);
       int array[size];
       int i;
       for(i =0 ;i<size;i++){
           array[i] = 4;
       }
       FILE * hp;
       hp = fopen(file,"r");
       if(hp == NULL){
           printf("Error opening the file");
           return(1);
       }
       while (fscanf(hp,"%llx %c",&address,&tb)) {
            if(feof(hp))
            {
                break;
            }
           total ++;
           sample = address >> 2;
           temp = ((1<<n)-1) & sample;
           temp = temp ^ regi;
           temp1 =((1<<m)-1) & sample;
           final = ((1<<(m-n))-1) & (address >> (2+n));
           index = (final << n) | temp;
           
          if(array[index] >= 4){
              predict = 't';
          }
          else{
              predict = 'n';
          }
       if(predict != tb){
           
          miss_predict++; 
       }
           
	if(tb == 't' && array[index] <7 ){
               array[index] ++;
           }
           else if (tb == 'n' && array[index] >0){
               array[index] --;
           }
       if(tb == 't'){
           regi = regi >>1;
           regi = (1 << (n-1)) | regi;
       }
       else{
           regi = regi >>1;
       }

   }

	printf("COMMAND \n");
	printf("./sim gshare %d %d %s\n",m,n,argv[4]);
	printf("OUTPUT\n");

  	printf("number of predictions:   %d\n", total);
  	printf("number of mispredictions:  %d\n", miss_predict);
  	printf("misprediction rate:   %.2f%c \n", (double) miss_predict / (double)total * 100,'%');
  	printf("FINAL GSHARE CONTENTS\n");
  	for (int i = 0; i < size; i++) {
      	printf("%d ", i);
      	printf("%d \n",array[i]);
  	}
       
}
    else{
    
        char predict1;
        char predict2;
        int miss_predict=0;
        int index1;
        int index2;
        int index3;
        int m1;
        unsigned int regi = 0;

        
        unsigned int temp2;
        unsigned int temp12;
        
        unsigned int final2;
        
    
        //hybrid selector
        int ts3 = atoi(argv[2]);;
        int m3 = pow(2,ts3);
        int array_3[m3];
        int i;
        for(i=0; i<m3; i++){
            array_3[i] = 1;
        }
        //hybrid selector end here
        
        //gshare
        int m2 = atoi(argv[3]);
        int n = atoi(argv[4]);
        int size2 = pow(2,m2);
        int array_2[size2];
        for(i =0 ;i<size2;i++){
            array_2[i] = 4;
        }
        
        //bimodal
        int ts1 = atoi(argv[5]);;
        m1 = pow(2,ts1);
        int array_1[m1];
        for(i=0; i<m1; i++){
            array_1[i] = 4;
        }
        
        //read the file
        file = argv[6];
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
            
            //hybrid
            total++;
            sample3 = address>>2;
            index3 = ~(~0 << ts3) & sample3;
            
            //gshare
            
                    sample2 = address >> 2;
                      temp2 = ((1<<n)-1) & sample2;
                      temp2 = temp2 ^ regi;
                      temp12 =((1<<m2)-1) & sample2;
                      final2 = ((1<<(m2-n))-1) & (address >> (2+n));
                      index2 = (final2 << n) | temp2;
            
            //gshare prediction
            if(array_2[index2] >= 4){
                predict2 = 't';
            }
            else{
                predict2 = 'n';
            }
            
            //bimodal
            sample1 = address>>2;
            index1 = ~(~0 << ts1) & sample1;
            
            //bimodal prediction
            if(array_1[index1] >= 4){
                   predict1 = 't';
            
            }
            else{
                predict1 = 'n';
            }
            
            if(array_3[index3]>=2){
                //gshare
               if(predict2 != tb){
			miss_predict++;
		}
                if(tb == 't' && array_2[index2] <7 ){
                    array_2[index2] ++;
                }
                else if (tb == 'n' && array_2[index2] >0){
                    array_2[index2] --;
                }
            }else{
                //bimodal
                if(predict1 != tb){
			miss_predict++;
		}
                   if(tb == 't' && array_1[index1] <7 ){
                       array_1[index1] ++;
                   }
                   else if (tb == 'n' && array_1[index1] >0){
                       array_1[index1] --;
                   }
                
            }
            //update global history table
            if(tb == 't'){
               regi = regi >>1;
               regi = (1 << (n-1)) | regi;
            }
            else{
               regi = regi >>1;
            }
            //update hybrid counter table
            if (predict2 == tb && predict1 != tb) {
                if (array_3[index3] < 3) {
                    array_3[index3]++;
                }
            } else if (predict2 != tb  && predict1 == tb) {
                if (array_3[index3] > 0) {
                    array_3[index3]--;
                }
            }
        }
	printf("COMMAND \n");
	printf("./sim hybrid %d %d %d %d %s\n",ts3,m2,n,ts1,argv[6]);
	printf("OUTPUT\n");

  	printf("number of predictions:   %d\n", total);
  	printf("number of mispredictions:  %d\n", miss_predict);
  	printf("misprediction rate:   %.2f%c \n", (double) miss_predict / (double)total * 100,'%');
  	printf("FINAL CHOOSER CONTENTS\n");
  	for (int i = 0; i < m3; i++) {
      	printf("%d ", i);
      	printf("%d \n",array_3[i]);
  	}
	printf("FINAL GSHARE CONTENTS\n");
	for (int i = 0; i < size2; i++) {
	  printf("%d", i);
	  printf(" %d\n", array_2[i]);
	}
	printf("FINAL BIMODAL CONTENTS\n");
	for (int i = 0; i < m1; i++) {
	  printf("%d", i);
	  printf(" %d\n", array_1[i]);
	}

    }
}
