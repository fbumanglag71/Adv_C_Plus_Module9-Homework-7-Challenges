//Francisco Bumanglag
//Date: August 29, 2024
//Module9 Assignments -- CMPR121 Chapter 9 Pointer


#include <iostream>
#include <cstdlib> //for srand() and rand()
#include <ctime>   //for time()
#include <algorithm> //for sort 
#include "input.h" //codde from professor

using namespace std;

//function prototypes
void challenge3();
void challenge6(); 
void challenge7();
void challenge9();
void challenge10(); 
void challenge11();
void challenge12();


//function for challenges 
void arrSelectSort(int* [], int);  //shared by challenge 6 and 7
void arrSelectDescend(int* [], int);  //only for challenge 7 descending 
void showArray(const int[], int);  //shared by challenge 6 and 7
void showArrPtr(int* [], int);  //shared by challenge 6 and 7
void calculatedMedian(int* numArray, int arraySize, double* median); //challenge 9
void reverseArray(const int originalArray[], int arraySize, int* reversedArray); // challenge 10
void expandedArray(const int*, int, int*&); // Challenge 11  
void elementShifter(const int*, int, int*&);  //challenge 12
void showArray12(const int[], int);  //shared by challenge 11 & 12


int main()
{
    do
    {
        system("cls");
        cout << "\n\tCMPR121: Chapter 9 Pointer - assignments by Francisco Bumanglag";
        cout << "\n\t" << string(80, char(205));
        cout << "\n\t 3. Drop the Lowest Score";
        cout << "\n\t 6. Case Study Modification #1";
        cout << "\n\t 7. Case Study Modification #2";
        cout << "\n\t 9. Median Function";
        cout << "\n\t10. Reverse Array";
        cout << "\n\t11. Array Expander";
        cout << "\n\t12. Element Shifter";

        cout << "\n\t" << string(80, char(196));
        cout << "\n\t 0. Exit";
        cout << "\n\t" << string(80, char(205));
        cout << "\n";
        switch (inputInteger("\tOption: ", 0, 12))
        {
        case 0: exit(0);
        case 3: challenge3(); break;
        case 6: challenge6(); break;
        case 7: challenge7(); break;
        case 9: challenge9(); break;
        case 10: challenge10(); break;
        case 11: challenge11(); break;
        case 12: challenge12(); break;

        default: cout << "\n\tERROR: Invalid option.\n";
        }

        system("pause");
    } while (true);

    return 0;
}

//===============CHALLENGE 3============
//challenge 3: Drop the Lowest Score
void challenge3()
{
    int size = inputInteger("\n\tEnter the size of the dynamic array: ", true);
    srand(time(0));
    double* scores = new double[size];

    //get user input for scores
    for (int i = 0; i < size; i++)
    {
        // *(scores + i) = inputDouble("\nEnter score #" + to_string(i + 1) + ": ", 0.0, 100.0);
        *(scores + i) = rand() % 100 + 1;
        cout << *(scores + i) << '\n';
    }
    //sort the array 
    sort(scores, scores + size);

    //calculate the new average of the array excluding the lowest score
    double sum = 0.0;
    for (int i = 1; i < size; i++) //start from 1 to exclude the lowest score
    {
        sum += scores[i];
    }
    double average = sum / (size - 1); //calculate average excluding one element

    //display the sorted scores and the calculated average
    cout << "\nSorted Scores: ";
    for (int i = 0; i < size; i++)
    {
        cout << scores[i] << " ";
    }
    cout << "\nAverage (excluding the lowest score): " << average << endl;

    //destroy/clean up dynamically allocated memory
    delete[] scores;

}
//===============CHALLENGE 6============
//Case Study Modification #1--donations ascending order

void challenge6()
{
    int numDonations = inputInteger("Enter the number of donations: ", true); //ensure valid integer input

    //dynamically allocate an array to hold the donation amounts
    int* donations = new int[numDonations];

    //get the donation amounts
    for (int i = 0; i < numDonations; i++)
    {
        donations[i] = inputInteger("Enter donation #" + to_string(i + 1) + ": ");
    }

    //dynamically allocate an array of int pointer
    int** arrPtr = new int* [numDonations];

    //make each element of arrPtr point to an element in the donations array
    for (int count = 0; count < numDonations; count++)
        arrPtr[count] = &donations[count];

    //sort the elements of the pointer array
    arrSelectSort(arrPtr, numDonations);

    //display the donations 
    cout << "The donations, sorted in ascending order, are: \n";
    showArrPtr(arrPtr, numDonations);

    //destory dynamically allocated memory
    delete[] donations;
    delete[] arrPtr;
}


//challenge 6 functions
void arrSelectSort(int* arr[], int size)
{
    int startScan, minIndex;
    int* minElem;

    for (startScan = 0; startScan < (size - 1); startScan++)
    {
        minIndex = startScan;
        minElem = arr[startScan];

        for (int index = startScan + 1; index < size; index++)
        {
            if (*(arr[index]) < *minElem)
            {
                minElem = arr[index];
                minIndex = index;
            }
        }
        arr[minIndex] = arr[startScan];
        arr[startScan] = minElem;
    }
}
void showArray(const int arr[], int size)
{
    for (int count = 0; count < size; count++)
        cout << arr[count] << " ";
    cout << endl;
}


void showArrPtr(int* arr[], int size)
{
    for (int count = 0; count < size; count++)
        cout << *(arr[count]) << " ";
    cout << endl;
}

//===============challenge 7============
//challenge 7 case study modification #1 -- donations descending

void challenge7()   //descending order
{
    int numDonations = inputInteger("Enter the number of donations: ", true); //ensure positive integer

    //dynamically allocate an array to hold the donation amounts
    int* donations = new int[numDonations];

    //get the donation amounts
    for (int i = 0; i < numDonations; i++)
    {
        donations[i] = inputInteger("Enter donation #" + to_string(i + 1) + ": ", true); //ensure positive integer
    }

    //dynamically allocate an array of pointers to int
    int** arrPtr = new int* [numDonations];

    //make each element of arrPtr point to an element in the donations array
    for (int count = 0; count < numDonations; count++)
        arrPtr[count] = &donations[count];

    //sort the elements of the array of pointers
    arrSelectDescend(arrPtr, numDonations);

    //display the donations using the array of pointers
    cout << "The donations, sorted in descending order, are: \n";
    showArrPtr(arrPtr, numDonations);

    //cleanup dynamically allocated memory
    delete[] arrPtr;
    delete[] donations;
}

//challenge 7 function
void arrSelectDescend(int* arr[], int size)
{
    int startScan, maxIndex;
    int* maxElem;

    for (startScan = 0; startScan < (size - 1); startScan++)
    {
        maxIndex = startScan;
        maxElem = arr[startScan];

        for (int index = startScan + 1; index < size; index++)
        {
            if (*(arr[index]) > *maxElem)
            {
                maxElem = arr[index];
                maxIndex = index;
            }
        }
        arr[maxIndex] = arr[startScan];
        arr[startScan] = maxElem;
    }
}

//===============CHALLENGE 9============
//challenge 9 -- Median Function 

void calculatedMedian(int* numArray, int arraySize, double* median) {
    //check if the number of elements is even 
    if (arraySize % 2 == 0) {
        //calculate the average of the two middle elements
        *median = (*(numArray + (arraySize / 2 - 1)) + *(numArray + (arraySize / 2))) / 2.0;
    }
    else {
        //store the middle element
        *median = *(numArray + (arraySize / 2));
    }
}

//challenge 9 function
void challenge9() {
    //arrays with different number and sorted
    int numbersArray1[] = { 2, 4, 6, 8, 10, 12 }; //even number of even elements
    int numbersArray2[] = { 1, 3, 5, 7, 9 };      //odd number of odd elements

    int sizeOfArray1 = sizeof(numbersArray1) / sizeof(numbersArray1[0]);
    int sizeOfArray2 = sizeof(numbersArray2) / sizeof(numbersArray2[0]);

    double median1 = 0.0; // variable to store the median of the first array
    double median2 = 0.0; // variable to store the median of the second array

    //updated function with an additional parameter for the median
    calculatedMedian(numbersArray1, sizeOfArray1, &median1);
    calculatedMedian(numbersArray2, sizeOfArray2, &median2);

    //display the values
    cout << "The median for the even numbers (2, 4, 6, 8, 10, 12) in Array#1 is: " << median1 << endl;
    cout << "The median for the odd numbers (1, 3, 5, 7, 9) in Array#2 is: " << median2 << endl;
}


//===============CHALLENGE 10============
//challenge 10 -- Reverse Array

void reverseArray(const int originalArray[], int arraySize, int* reversedArray) {
    //copy the elements from the original array to the reversed array
    for (int i = 0; i < arraySize; i++) {
        reversedArray[i] = originalArray[arraySize - 1 - i];
    }
}
//challenge 10 function
void challenge10() {
    int originalArray[] = { 1, 2, 3, 4, 5 }; //sorted
    int arraySize = sizeof(originalArray) / sizeof(originalArray[0]);

    //allocate memory for the reversed array
    int* reversedArray = new int[arraySize];

    //call the updated reverseArray function
    reverseArray(originalArray, arraySize, reversedArray);

    //display the arrays -- original and reversed
    cout << "Original Array Sorted: ";
    for (int i = 0; i < arraySize; i++) {
        cout << originalArray[i] << " ";
    }
    cout << endl;

    cout << "Reversed Array Descending: ";
    for (int i = 0; i < arraySize; i++) {
        cout << reversedArray[i] << " ";
    }
    cout << endl;

    //deallocate the memory used by reversedArray
    delete[] reversedArray;
    //reversedArray = nullptr  --INSERT THIS CODE FOR EACH CHALLENGE
}

    //===============CHALLENGE 11============
   //challenge 11 function -- Array Expander

    void challenge11() {
      
        //user enters the number of elements
        int numberElements = inputInteger("Enter the number of elements in the array: ", true); //ensure positive integer


        //dynamic allocation memory -- original array
        int* originalArray = new int[numberElements];

        //user input -- original array
        for (int i = 0; i < numberElements; ++i) {
            originalArray[i] = inputInteger("Enter element #" + to_string(i + 1) + ": ", true); //enter positive integer only 
        }

        //display original array
        cout << "Original array: ";
        showArray12(originalArray, numberElements);

        //create the expanded array from the function
        int* newExpandedArray = nullptr; //initialize pointer to nullptr
        expandedArray(originalArray, numberElements, newExpandedArray);

        //display the expanded array
        cout << "\nThe new expanded array set are:\n";
        for (int i = 0; i < numberElements * 2; ++i) {
            cout << newExpandedArray[i];
            if (i < numberElements * 2 - 1) cout << ", ";
        }
        cout << endl;

        //destroy the dynamically allocated memory
        delete[] originalArray;
        delete[] newExpandedArray;
    }

    //function to create expanded array
    void expandedArray(const int* oldArray, int size, int*& newArray) {
        //allocate the memory
        newArray = new int[size * 2];

        //copy the elements from original to expanded array
        for (int i = 0; i < size; ++i) {
            newArray[i] = oldArray[i];
        }

        //initialize remaining elements for new array
        for (int i = size; i < size * 2; ++i) {
            newArray[i] = 0;
        }
    }

   

    //===============CHALLENGE 12============
    //challenge 12 -- Element Shifter

    //function to create a new array with shifted elements
      void elementShifter(const int* oldArray, int size, int*& newArray) {
      // create a new array one element larger
      newArray = new int[size + 1];

      //set the first element of the new array to 0
      newArray[0] = 0;

      //copy elements from old array to new array, shifted by one
            for (int i = 0; i < size; i++) {
                newArray[i + 1] = oldArray[i];
            }
        }

      //function to display an array -- side by side
        void showArray12(const int arr[], int size) {
            for (int i = 0; i < size; i++) {
                cout << arr[i];
                if (i < size - 1) {
                    cout << ", ";
                }
            }
         cout << endl;
        }

     //function for challenge 12
        void challenge12() {
         

      //get the number of elements from the user
       int numberElements = numberElements = inputInteger("Enter the number of elements in the array: ", true); //only positive integers


       //allocate memory for the original array
        int* originalArray = new int[numberElements];

       //get elements of the array from the user
        cout << "Enter the elements of the array:\n";
        for (int i = 0; i < numberElements; i++) {
            originalArray[i] = inputInteger("Enter element #" + to_string(i + 1) + ": ", true); //allow positive integers
        }
        //display the original array
           cout << "The array set, in their original order are: ";
            showArray12(originalArray, numberElements);

       //create the shifted array
            int* newShiftedArray = nullptr;
            elementShifter(originalArray, numberElements, newShiftedArray);

       //display the new shifted array
           cout << "The new one-larger and shifted array set are: ";
           showArray12(newShiftedArray, numberElements + 1);

       //clean up dynamically allocated memory
           delete[] originalArray;
           delete[] newShiftedArray;
        }



