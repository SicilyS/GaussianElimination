#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define EPSILON 1e-9

//2d array print
void arrPrint(int rowCount, double arr[][rowCount+ 1]){
  printf("\n");
  for (int i = 0; i < rowCount; i++) {
      for (int j = 0; j < (rowCount + 1); j++) {
          printf("%lf ", arr[i][j]);
      }
      printf("\n");
  }
}


int main() {

  printf("update compiled");

  //open text file

  char filename[100];
  FILE *g;
  printf("filename? ");
  scanf("%s", filename);

  g = fopen(filename, "r");
  if (g == NULL){
    printf("can't open file %s \n", filename);
    exit(1);
  }


  //inits from file
  int rowCount, x, i, j, k, n;
  double mult, initMult, sum;

  fscanf(g, "%d", &rowCount);

  //[row][collumn]
  double input[rowCount][rowCount + 1];

  //need to scan for array
  for(x = 0; x < rowCount; x++){
    for(i = 0; i <= rowCount; i++){
      fscanf(g, "%lf", &input[x][i]);
    }
  }

  fclose(g);


  //manual input: begin main here
  /*
  int rowCount, x, i, j, n, k;
  double mult, initMult, sum;

  rowCount = 3;
  double input[3][4] = {
        {3,  9, 27, 14},
        {1,  1,  1,  1},
        {2,  4,  8,  5}
  };
  */

  printf("Row Count Entered: %d \n", rowCount);
  printf("Input Array: \n");
  arrPrint(rowCount, input);
  printf("\n \n");


  for(x = 0; x < rowCount; x++){

    //sort col[x] high to low according to value input[j][x]
    //k passes
    for(k = 0; k < rowCount; k++){
      for(j = 0; j < (rowCount - 1); j++){
        //only sort rows where preceding values in row are 0
        for(n = 0; n < x ; n++){
          sum += input[j][n];
        }
        if(sum == 0){
          if(input[j][x] < input[j+1][x]){
            for(i = 0; i <= rowCount; i++){
              double temp;
              temp = input[j][i];
              input[j][i]= input[j+1][i];
              input[j+1][i] = temp;
            }
          }
        }
        sum = 0;
      }
    }
    //printf("sorted large to small: \n");
    //arrPrint(rowCount, input);


    //DEVIDING BY ZERO FIX + recognizing unsolvable eq
    //printf("%lf \n", input[x][x]);
    //it really didn't wanna recognize 0
    if(fabs(input[x][x]) < EPSILON){
      printf("no unique solution");
      exit(1);
    }


    //make row x lead with a 1
    initMult = 1 / input[x][x];
    if(initMult){
      for(k = 0; k <= rowCount; k++){
        input[x][k] = input[x][k] * initMult;
      }
    }else{
      printf("no unique solution");
      exit(1);
    }
    //arrPrint(rowCount, input);

    //subtract (row[x] * scaler) from other rows
    for(i = 0; i < rowCount; i++){
      if(i != x){
        mult = input[i][x];
        for(k = 0; k <= rowCount; k++){
          input[i][k] = input[i][k] - mult * input[x][k];
          //printf("%.2f \n", input[i][k]);
        }
      }
    }

    //arrPrint(rowCount, input);
    //printf("\n cycle complete \n \n");

  }

  printf("the roots are:");
  for(x = 0; x < rowCount; x++){
    printf("\n %.5f ", input[x][rowCount]);
  }

}
