#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *FILENAME = "GlobalTemperatures.csv";
const int DATE_COL = 0;
const int AVG_TEMP_COL = 1;
const int AVG_TEMP_UNC_COL = 2;

int datenumber(int year, int month) { return 12 * (year - 1750) + month; }

/**
 * Get month from date string
 */
int getMonth(char *date) {
  char tmp[strlen(date)];
  strcpy(tmp, date);
  char *yearStr = strtok(tmp, "-");
  char *monthStr = strtok(NULL, "-");
  int month = atoi(monthStr);
  return month;
}

/**
 * Get year from date string
 */
int getYear(char *date) {
  char tmp[strlen(date)];
  strcpy(tmp, date);
  char *yearStr = strtok(tmp, "-");
  int year = atoi(yearStr);
  return year;
}

/**
 * Get number of rows from CSV file
 */
int rowsCount() {
  FILE *data = fopen(FILENAME, "r");
  if (data == NULL) {
    printf("Error opening file.\n");
    exit(1);
  }
  int rows = 0;

  char line[1024];
  while (fgets(line, sizeof(line), data) != NULL) {
    rows++;
  }

  fclose(data);

  return rows;
}

void getColumnValue(int row, int col, char* result) {
  FILE *data;
  char wanted[1000];
  int ctr = 0;

  data = fopen(FILENAME, "r");
  if (data == NULL) {
    printf("Error opening file.\n");
    exit(1);
  }

  while (fgets(wanted, sizeof(wanted), data) != NULL) {
    if (ctr == row) {
      char *thing = strtok(wanted, ",");

      for (int i = 0; i < col; i++) {
        thing = strtok(NULL, ",");
      }

      if (thing != NULL) {
        strcpy(result, thing);
      } else {
        result[0] = '\0';
      }
      
      
      break;
    } else
      ctr++;
  }

  fclose(data);
}

/**
* Question 2 Begins
 */
void question2() {
  int tempCounts[4] ={0, 0, 0, 0};
  double tempSums[4] = {0, 0, 0, 0};
  
  for (int row = 1; row < rowsCount(); row++) {
    
    
    char date[10];
    getColumnValue(row, DATE_COL, date);
    char avgTemp[100];
    getColumnValue(row, AVG_TEMP_COL, avgTemp);
    double temp = 0;
    if(strlen(avgTemp) > 0) {
      // only if temp is available
      temp = atof(avgTemp);
      int year = getYear(date);
      int century = (int)year/100 + 1;
      
      int index = century - 18;
      tempCounts[index]++;
      tempSums[index] = tempSums[index] + temp;
    } 
  }

  printf("\n\n       Question 2\n");
  printf("=============================\n");
  for(int i=0; i<4; i++) {
    double avg = tempSums[i]/tempCounts[i];
    printf("Century %d:Avg. Temp=%.2lf\n", i+18,  avg);
  }
  printf("=============================\n");
}

void question3() {
  printf("\n\n       Question 3\n");
  printf("=============================\n");
  printf("=============================\n");
}

/**
* Main
 */
int main(void) {

  // question 2
  question2();
  question3();
  return 0;
}
