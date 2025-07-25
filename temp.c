#include <math.h>
#include <stdio.h>  // For printf
#include <stdlib.h> // For rand() and srand()
#include <time.h>   // For time() (used to seed the random number generator)

void generateDate(float arr[], int n, int min, int max) {
  for (int i = 0; i < n; i++) {
    arr[i] = min + ((float)rand() / RAND_MAX) * (max - min);
  }
}

int findMin(float arr[], int n) {
  // float min = arr[1];
  int minIndex = 1;
  for (int i = 1; i < n; i++) {
    if (arr[i] < arr[minIndex]) {
      minIndex = i;
    }
  }
  return minIndex;
}

int findMinQuadratic(float arr[], int n) {
  for (int i = 0; i < n; i++) {
    int isMin = 1;
    for (int j = 0; j < n; j++) {
      if (arr[j] < arr[i]) {
        isMin = 0;
        break;
      }
    }
    if (isMin) {
      return i;
    }
  }
  return 0;
}

float findMaxQuadratic(float arr[], int n) {
  for (int i = 0; i < n; i++) {
    int isMax = 1;
    for (int j = 0; j < n; j++) {
      if (arr[j] > arr[i]) {
        isMax = 0;
        break;
      }
    }
    if (isMax) {
      return i;
    }
  }
  return 0;
}
int linearSearch(float arr[], int n, int target) {
  for (int i = 0; i < n; i++) {
    if (arr[i] >= target) {
      return i;
    }
  }
  return -1;
}

void sort(float arr[], int len) {
  for (int i = 0; i < len; i++) {
    float largest = arr[i];
    int largestIndex = i;
    for (int j = i; j < len; j++) {
      if (arr[j] < largest) {
        largest = arr[j];
        largestIndex = j;
      }
    }
    arr[largestIndex] = arr[i];
    arr[i] = largest;
  }
}

int compare_floats(const void *a, const void *b) {
  float fa = *(const float *)a;
  float fb = *(const float *)b;
  return (fa > fb) - (fa < fb);
}
int findWithBinary(float arr[], int len, float target) {
  qsort(arr, len, sizeof(float), compare_floats);
  int low = 0, high = len - 1;

  while (low <= high) {
    int mid = (low + high) / 2;
    if (arr[mid] >= target) {
      if (mid == 0) {
        return mid;
      }
      if (arr[mid - 1] < target) {
        return mid;
      } else {
        high = mid - 1;
      }
    } else {
      low = mid + 1;
    }
  }
  return -1;
}

int findMax(float arr[], int n) {
  int maxIndex = 1;
  for (int i = 1; i < n; i++) {
    if (arr[i] > arr[maxIndex]) {
      maxIndex = i;
    }
  }

  return maxIndex;
}
int main(int argc, char const *argv[]) {
  int n = 1000000;
  // clock_t start, end;
  // double duration;
  //
  float pressureArr[n];
  generateDate(pressureArr, n, 950, 1050);

  int minIndx;
  int maxIndx;
  double duration;
  clock_t start, end; // start = clock(); // returns processor clock time
                      // since the program is started
  start = clock();
  maxIndx = findMax(pressureArr, n);
  minIndx = findMin(pressureArr, n);
  // printf("max is %d \n", maxIndx);
  end = clock();
  duration = (((double)(end - start)) /
              CLOCKS_PER_SEC); // no. of clock ticks per second

  printf("For the array size %d, Time required to find minimum and maximum in "
         "the temperature array using "
         "linear Search "
         "= %f seconds, the minimum value = %f and the maximum value = %f\n ",
         n, duration, pressureArr[minIndx], pressureArr[maxIndx]);

  start = clock();
  maxIndx = findMaxQuadratic(pressureArr, n);
  minIndx = findMinQuadratic(pressureArr, n);
  end = clock();
  duration = (((double)(end - start)) /
              CLOCKS_PER_SEC); // no. of clock ticks per second

  printf(
      "\nFor the array size %d, Time required to find minimum and maximum in "
      "the pressure array using "
      "quadratic Search "
      "= %f seconds, the minimum value = %f and the maximum value = %f\n \n",
      n, duration, pressureArr[minIndx], pressureArr[maxIndx]);

  float temperatureArr[n];
  int firstAppreance;

  generateDate(temperatureArr, n, 20, 50);
  start = clock();
  firstAppreance = linearSearch(temperatureArr, n, 30);
  end = clock();
  duration = (((double)(end - start)) / CLOCKS_PER_SEC);
  printf("first apperence index with linear %d, duration = %f, length of array"
         "= %d \n \n",
         firstAppreance, duration, n);

  start = clock();

  firstAppreance = findWithBinary(temperatureArr, n, 30);
  end = clock();
  duration = (((double)(end - start)) / CLOCKS_PER_SEC);
  printf(
      "first apperence with binary %d, duration = %f, length of array = %d \n",
      firstAppreance, duration, n);

  return 1;
}
