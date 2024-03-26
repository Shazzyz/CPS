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

/**
 * Question 3 Begins
 */
void question3() {
  int tempCounts[12];
  double tempSums[12];

  // initialize all to 0
  for (int i = 0; i < 12; i++) {
    tempCounts[i] = 0;
    tempSums[i] = 0;
  }

  for (int row = 1; row < rowsCount(); row++) {
    char date[10];
    getColumnValue(row, DATE_COL, date);
    int year = getYear(date);
    if(year < 1900 || year > 2015) { 
      continue;
    }

    int month = getMonth(date);
    
    char avgTemp[100];
    getColumnValue(row, AVG_TEMP_COL, avgTemp);
    double temp = 0;
    if (strlen(avgTemp) > 0) {
      // only if temp is available
      temp = atof(avgTemp);
      
      tempCounts[month - 1]++;
      tempSums[month - 1] = tempSums[month - 1] + temp;
    }
  }

  printf("\n\n       Question 3\n");
  printf("=============================\n");
  for (int i = 0; i < 12; i++) {
    char * monthName;
    switch(i) {
      case 0: monthName = "January"; break;
      case 1: monthName = "February"; break;
      case 2: monthName = "March"; break;
      case 3: monthName = "April"; break;
      case 4: monthName = "May"; break;
      case 5: monthName = "June"; break;
      case 6: monthName = "July"; break;
      case 7: monthName = "August"; break;
      case 8: monthName = "September"; break;
      case 9: monthName = "October"; break;
      case 10: monthName = "November"; break;
      case 11: monthName = "December"; break;

    }
    printf("For %s: Avg. Temp=%.2lf\n", monthName, tempSums[i] / tempCounts[i]);
  }
  printf("=============================\n");
}

/**
* Main
 */
int main(void) {

  question2();
  question3();
  return 0;
}
