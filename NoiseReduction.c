#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

// To use a bool variable in C 
typedef enum { F, T } bool;

// Global variable to for addOneAtTheFirstIndex function
int count = 1;

// This function calculate the total of the noise in the array
int total(int * exhibit, int ** animals, int size) {

    // Declared the sum variable to store the total of the noise
    int sum = 0;

    // Loop through the exhibit array to find the total noise
    for (int i = 0; i < size; i++) {
        
        // For loop to calculate the noise of the animals of the left 2 affecting animals of the exhibit
        for(int j = i - 1; j >= 0 && j > i - 3; j--) {
            sum += animals[exhibit[i] - 1][exhibit[j] - 1]; 
        }

        // For loop to calculate the noise of the animals of the right 2 affecting animals of the exhibit
        for(int k = i + 1; k < size && k < i + 3; k++) {
            sum += animals[exhibit[i] - 1][exhibit[k] - 1];
        }

    }

    // Returns the total of the noise
    return sum;
}

// Finds the factorial of the specified number
int findFactorial(int n) {

    // If the number is greater than 0, then it will return the function findFactorial with number - 1, multiplied by the number
    if(n > 0) {
        return findFactorial(n - 1) * n;
    } else { // If the number is 0, then it will return 1
        return 1;
    }
}

// This function is used to swap the elements of the array
void swap(int * a, int * b) {
    // Declared a temporary variable to store the value of a
    int temp = *a;

    // Assign the value of b to a & vice versa
    *a = *b;
    *b = temp;
}

// This function is used to add one at the first index of the exhibit array until it reaches the last index
void addOneAtTheFirstIndex(int * array, int size, int LeftArrangments) {

    // If the count is greater than 1, then it will add one at the first index of the array
    if(count > 1) {

        // Add one at the first index of the array
        array[0]++;

        // Loop through the array to add the numbers from 1 to size
        for(int i = 1, j = 1; i < size + 1; i++) {

            // If the number is not equal to the first index of the array and the index value is less than size - 1, then it will add the number to the array
            if(i != array[0] && j <= size - 1) {
                array[j] = i;
                j++;
            }
        }
    } else { // If the count is 1, then it will increase the count by 1
        count++;
    }
}


// This function finds all the optimal arrangements of the exhibit array
void findingOptimalArrangements(int * array, int size, int LeftArrangements) {
    // It will only work if the number of arrangements is greater than 0
    if(LeftArrangements > 0) {

        // If the number of arrangements is odd, then it will find the optimal arrangement using addOneAtTheFirstIndex function
        if(LeftArrangements % findFactorial(size - 1) == 0) {

            // Calls the addOneAtTheFirstIndex function
            addOneAtTheFirstIndex(array, size, LeftArrangements);

        } else { // If the number of arrangements is even, then it will find the optimal arrangement using findingOptimalArrangements and swap function
            
            // For loop to find the optimal arrangement
            for(int currentCase = size - 2, index = 1; currentCase > 1; currentCase--, index++) {

                // If the number of arrangements is divisible by the factorial of the current case, then it will add one at the current index of the array
                if(LeftArrangements % findFactorial(currentCase) == 0) {
                    
                    // Add one at the current index of the array
                    for(int x = array[index] + 1; x < size + 1; x++) {

                        // This bool variable is used to check if the number is already in the array
                        bool isFound = F;

                        array[index] = x;

                        // Loop through the array to check if the number is already in the array
                        for(int y = 0; y < index; y++) {
                            if(array[index] == array[y]) {
                                isFound = T;
                                break;
                            }
                        }

                        // If the number is not found in the array, then it will break the loop
                        if(!isFound) {
                            break;
                        }
                    }

                    // Loop through the array to add the rest of the numbers from 1 to size
                    for(int i = 1, j = index + 1; i < size + 1; i++) {
                        
                        // This bool variable is used to check if the number is already in the array
                        bool isFound = F;

                        // For loop to check if the number is already in the array
                        for(int y = 0; y < index + 1; y++) {
                            if(i == array[y]) {
                                isFound = T;
                            }
                        }

                        // If the number is not found in the array, then it will add the number 'i' to the array
                        if(!isFound && j < size) {
                            array[j] = i;
                            j++;
                        }

                    }

                    break;

                }

            }
        }
    }
}

// This function is used to find the least amount of noise out of all the optimal arrangements
int leastNoiseSum(int * exhibit, int ** animal, int animalExhibit, int min, int current, int LeftArrangements) {
    
    if(animalExhibit == 1) { // If the number of animals in the exhibit is 1, then it will return the minimum noise
        min = total(exhibit, animal, animalExhibit);
    } else if(animalExhibit == 2) { // If the number of animals in the exhibit is 2, then it will return the minimum noise after one optimal arrangement change
        
        // Current variable is used to store the current noise
        current = total(exhibit, animal, animalExhibit);

        // If the current noise is less than the minimum noise, then it will assign the current noise to the minimum noise
        if(current < min) {
            min = current;
        }

        // Calls the addOneAtTheFirstIndex function to add all the elements by one at the first index of the array
        addOneAtTheFirstIndex(exhibit, animalExhibit, 2);

        // Current variable is used to store the current noise
        current = total(exhibit, animal, animalExhibit);

        // If the current noise is less than the minimum noise, then it will assign the current noise to the minimum noise
        if(current < min) {
            min = current;
        }
    } else if(animalExhibit < 9 && LeftArrangements > 0) { // If the number of animals in the exhibit is less than 9 and the number of arrangements left is greater than 0, then it will find the minimum noise after animalExhibit! times / 2
        
        // Calls the findingOptimalArrangements function to find the optimal arrangements
        findingOptimalArrangements(exhibit, animalExhibit, LeftArrangements);

        // Current variable is used to store the current noise
        current = total(exhibit, animal, animalExhibit);

        // If the current noise is less than the minimum noise, then it will assign the current noise to the minimum noise
        if(current < min) {
            min = current;
        }

        // Calls the swap function to swap the last two indexes of the array
        swap(&exhibit[animalExhibit - 2], &exhibit[animalExhibit - 1]);

        // Current variable is used to store the current noise
        current = total(exhibit, animal, animalExhibit);

        // If the current noise is less than the minimum noise, then it will assign the current noise to the minimum noise
        if(current < min) {
            min = current;
        }
        
        // Returns the lessNoiseSum function to search again for the minimum noise for the rest of optimal arrangements
        return leastNoiseSum(exhibit, animal, animalExhibit, min, current, LeftArrangements - 2);
    } else if(animalExhibit > 8) { // If the number of animals in the exhibit is greater than 8, then it will find the minimum noise differently

        // For loop to start from Highest possible optimal arrangements to the lowest possible optimal arrangements and find the minimum noise
        for(int Left = LeftArrangements; Left > 0; Left = Left - 2) {

            // Calls the findingOptimalArrangements function to find the optimal arrangements
            findingOptimalArrangements(exhibit, animalExhibit, Left);

            // Current variable is used to store the current noise
            current = total(exhibit, animal, animalExhibit);

            // If the current noise is less than the minimum noise, then it will assign the current noise to the minimum noise
            if(current < min) {
                min = current;
            }

            // Calls the swap function to swap the last two indexes of the array
            swap(&exhibit[animalExhibit - 2], &exhibit[animalExhibit - 1]);

            // Current variable is used to store the current noise
            current = total(exhibit, animal, animalExhibit);

            // If the current noise is less than the minimum noise, then it will assign the current noise to the minimum noise
            if(current < min) {
                min = current;
            }
        }
    }

    // Returns the minimum noise
    return min;
    
}

int main() {

    // Declaring variable for animalExhibit
    int animalExhibit = 11;
    // Taking input from user for animalExhibit to create n X n matrix
    scanf("%d", &animalExhibit);

    // Creating pointer array for animalExhibit using calloc
    int * exhibit = (int *)calloc(animalExhibit, sizeof(int));
    for(int i = 0; i < animalExhibit; i++) {
        exhibit[i] = i+1;
    }

    // Creating double pointer array for animalExhibit using calloc
    int **animals = (int **)calloc(animalExhibit, sizeof(int *));
    
    //Using for loop to create single pointer array for animalExhibit using calloc
    for (int i = 0; i < animalExhibit; i++) {
        animals[i] = (int *)calloc(animalExhibit, sizeof(int));
        // Taking input from user for animalExhibit
        for (int j = 0; j < animalExhibit; j++) {
            scanf("%d", &animals[i][j]);
        }
    }

    // Calling the leastNoiseSum function to find the least noise sum
    int lowestNoiseSum = leastNoiseSum(exhibit, animals, animalExhibit, INT_MAX, 0, findFactorial(animalExhibit));
    
    // Printing the lowest noise sum
    printf("%d\n", lowestNoiseSum);

    // Freeing the memory allocated for exhibit
    free(exhibit);
    // Freeing the memory allocated for animals individually
    for (int i = 0; i < animalExhibit; i++) {
        free(animals[i]);
    }
    // Freeing the memory allocated for animals
    free(animals);

    return 0;

}