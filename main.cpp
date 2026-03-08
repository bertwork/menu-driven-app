#include <iostream>
#include <string>
#include <stdexcept>
#include <iomanip>

using namespace std;

const int MAX_MENU_OPTIONS = 9; // maximum number of menu options
const int MAX_ARRAY_SIZE = 200; // maximum size of the array

int numbersArr[MAX_ARRAY_SIZE] = { 0 }; // array to hold numbers, initialized to 0

// Enum for header types
enum HeaderType {
  MAIN_MENU,
  SUB_MENU
};


// UI functions prototypes
void displayMenu(int arraySize);
void displayHeader(const string& title, HeaderType type);
void pauseScreen();


// Utility function prototypes
void validateInput(const string& input, int& number, int minValue, int maxValue); // function to validate input and convert to int
string trim(const string& str); // function to trim whitespace from input
string toLower(const string& str); // function to convert string to lowercase


// Array function prototypes
void inputArray(int& arraySize); // function to handle array size input and data from user
void displayArray(int arraySize); // function to handle array display
void findSum(int arraySize, int& sum); // function to handle finding the sum of array elements
void findAverage(int arraySize, int& sum); // function to handle finding the average of array elements
void findMinMax(int arraySize); // function to handle finding the minimum and maximum of array elements
void reverseArray(int arraySize); // function to handle reversing the array
void sortArray(int arraySize); // function to handle sorting the array
void searchArray(int arraySize); // function to handle searching for an element in the array


int main() {
  int menuChoice = 0, arraySize = 0, sum = 0;
  string menuInput; // string version of menuChoice for input validation

  do {
    displayMenu(arraySize); // display menu options

    // Menu input loop with validation
    while (true) {

      cout << "Enter your choice (1-" << MAX_MENU_OPTIONS << "): ";
      getline(cin, menuInput);
      menuInput = trim(menuInput); // trim whitespace from input

      try {
        // check empty input first
        if (menuInput.empty()) {
          throw invalid_argument("Invalid Input.");
        }

        // validate input and convert to int
        validateInput(menuInput, menuChoice, 1, MAX_MENU_OPTIONS);

        break; // valid input
      }
      catch (invalid_argument&) { // catch invalid argument exceptions
        cerr << "❌ Invalid Input. Please enter a number (1-" << MAX_MENU_OPTIONS << ").\n\n";
      }
      catch (out_of_range&) { // catch out of range exceptions
        cerr << "❌ Choice out of range. Please enter a number (1-" << MAX_MENU_OPTIONS << ").\n\n";
      }
    }


    switch (menuChoice) {
    case 1:
      displayHeader(" Insert Data to Array Selected ", SUB_MENU);
      inputArray(arraySize);
      pauseScreen();
      break;

    case 2:
      displayHeader(" Display Array Selected ", SUB_MENU);
      if (arraySize == 0) {
        cerr << "❌ No array data! Please insert data first (Option 1).\n";
      }
      else {
        displayArray(arraySize);
      }
      pauseScreen();
      break;

    case 3:
      displayHeader(" Find Sum of Array Elements Selected ", SUB_MENU);
      if (arraySize == 0) {
        cerr << "❌ No array data! Please insert data first (Option 1).\n";
      }
      else {
        findSum(arraySize, sum);
      }
      pauseScreen();
      break;

    case 4:
      displayHeader(" Find Average of Array Elements Selected ", SUB_MENU);
      if (arraySize == 0) {
        cerr << "❌ No array data! Please insert data first (Option 1).\n";
      }
      else {
        findAverage(arraySize, sum);
      }
      pauseScreen();
      break;

    case 5:
      displayHeader(" Find Min & Max of Array Elements Selected ", SUB_MENU);
      if (arraySize == 0) {
        cerr << "❌ No array data! Please insert data first (Option 1).\n";
      }
      else {
        findMinMax(arraySize);
      }
      pauseScreen();
      break;

    case 6:
      displayHeader(" Reverse Array Selected ", SUB_MENU);
      if (arraySize == 0) {
        cerr << "❌ No array data! Please insert data first (Option 1).\n";
      }
      else {
        reverseArray(arraySize);
      }
      pauseScreen();
      break;

    case 7:
      displayHeader(" Sort Array Selected ", SUB_MENU);
      if (arraySize == 0) {
        cerr << "❌ No array data! Please insert data first (Option 1).\n";
      }
      else {
        sortArray(arraySize);
      }
      pauseScreen();
      break;

    case 8:
      displayHeader(" Search for an Element Selected ", SUB_MENU);
      if (arraySize == 0) {
        cerr << "❌ No array data! Please insert data first (Option 1).\n";
      }
      else {
        searchArray(arraySize);
      }
      pauseScreen();
      break;

    case 9:
      cout << "\nExiting the program... Goodbye!\n" << endl;
      break;

    default:
      cout << "Invalid choice. Please try again." << endl;
      break;
    }

  } while (menuChoice != MAX_MENU_OPTIONS);


  return 0;
}

// Handle the display of the menu
void displayMenu(int arraySize) {
  displayHeader(" Main Menu ", MAIN_MENU);

  // show array status
  if (arraySize == 0) {
    cout << "Array Status: Empty ❌\n\n";
  }
  else {
    cout << "Array Status: " << arraySize << " elements loaded ✅\n\n";
  }

  cout << "[1] Insert Data to Array\n"
    << "[2] Display Array\n"
    << "[3] Find Sum of Array Elements\n"
    << "[4] Find Average of Array Elements\n"
    << "[5] Find Min & Max of Array Elements\n"
    << "[6] Reverse Array\n"
    << "[7] Sort Array\n"
    << "[8] Search for an Element in Array\n"
    << "[9] Exit\n";
}

// Handle the display of the header
void displayHeader(const string& title, HeaderType type) {
  if (type == MAIN_MENU) {
    cout << "\n" << string(15, '=') << title << string(15, '=') << "\n";
  }
  else {
    cout << "\n" << string(15, '*') << title << string(15, '*') << "\n";
  }
}

// Pause screen until user presses Enter
void pauseScreen() {
  cout << "\nPress Enter to continue...";
  cin.ignore();
}

// Function to validate input and convert to int
void validateInput(const string& input, int& number, int minValue, int maxValue) {
  size_t pos; // position of first non-numeric character
  number = stoi(input, &pos); // convert string to int

  // check for non-numeric input
  if (pos != input.length()) {
    throw invalid_argument("Invalid Input.");
  }

  // check for out of range input
  if (number < minValue || number > maxValue) {
    throw out_of_range("Choice out of range.");
  }
}

// Function to trim whitespace from input
string trim(const string& str) {
  // find first and last non-whitespace characters
  size_t first = str.find_first_not_of(" \t\n\r");
  size_t last = str.find_last_not_of(" \t\n\r");

  if (first == string::npos) return "";

  return str.substr(first, last - first + 1);
}

// Function to convert string to lowercase
string toLower(const string& str) {
  string result = str;
  for (char& c : result) {
    c = tolower(c);
  }
  return result;
}

// Function to handle array size input and data from user
void inputArray(int& arraySize) {
  string sizeInput, elemInput;

  // confirm overwrite if array already has data
  if (arraySize > 0) {
    string confirm;
    cout << "⚠️  Array already has " << arraySize << " elements. Overwrite? (y/n): ";
    getline(cin, confirm);
    confirm = toLower(trim(confirm));

    if (confirm != "y" && confirm != "yes") {
      cout << "❌ Operation cancelled.\n";
      return;
    }
  }

  // Array size input loop with validation
  while (true) {
    cout << "Enter array size (1-" << MAX_ARRAY_SIZE << "): ";
    getline(cin, sizeInput);
    sizeInput = trim(sizeInput); // trim whitespace from input

    try {
      // check empty input first
      if (sizeInput.empty()) {
        throw invalid_argument("Invalid Input.");
      }

      validateInput(sizeInput, arraySize, 1, MAX_ARRAY_SIZE); // validate input and convert to int

      break; // valid size
    }
    catch (invalid_argument&) {
      cerr << "❌ Invalid Input. Please enter a number (1-" << MAX_ARRAY_SIZE << ").\n";
    }
    catch (out_of_range&) {
      cerr << "❌ Array size out of range. Please enter a number (1-" << MAX_ARRAY_SIZE << ").\n";
    }
  }

  // Element input loop with validation
  for (int i = 0; i < arraySize; i++) {
    while (true) {
      cout << "Enter element " << i + 1 << ": ";
      getline(cin, elemInput);
      elemInput = trim(elemInput); // trim whitespace from input

      try {
        // check empty input first
        if (elemInput.empty()) {
          throw invalid_argument("Invalid Input.");
        }

        validateInput(elemInput, numbersArr[i], 0, 1000000); // validate input and convert to int
        break; // valid element
      }
      catch (invalid_argument&) { // catch invalid argument exceptions
        cerr << "❌ Invalid Input. Please enter a number between 0 and 1,000,000.\n";
      }
      catch (out_of_range&) {
        cerr << "❌ Invalid Input. Please enter a number between 0 and 1,000,000.\n";
      }
    }
  }
}

// Function to handle array display
void displayArray(int arraySize) {
  cout << "Array Contents:\n";
  for (int i = 0; i < arraySize; i++) {
    cout << "Element " << i + 1 << ": " << numbersArr[i] << endl;
  }
}

// Function to handle finding the sum of array elements
void findSum(int arraySize, int& sum) {
  displayArray(arraySize); // display array contents
  sum = 0; // reset sum before calculation

  // calculate sum of array elements
  for (int i = 0; i < arraySize; i++) {
    sum += numbersArr[i]; // add each element to sum
  }
  cout << "Sum of array elements: " << sum << "\n";
}

// Function to handle finding the average of array elements
void findAverage(int arraySize, int& sum) {
  findSum(arraySize, sum); // always recalculate fresh sum
  double average = static_cast<double>(sum) / arraySize; // cast sum to double for accurate average calculation
  cout << fixed << setprecision(2) << "Average of array elements: " << average << "\n"; // display average with 2 decimal places
}

// Function to handle finding the minimum and maximum of array elements
void findMinMax(int arraySize) {
  displayArray(arraySize); // display array contents

  // initialize min and max to first element
  int min = numbersArr[0];
  int max = numbersArr[0];

  // find min and max in array
  for (int i = 1; i < arraySize; i++) {
    if (numbersArr[i] < min) {
      min = numbersArr[i]; // update min if smaller element found
    }
    if (numbersArr[i] > max) {
      max = numbersArr[i]; // update max if larger element found
    }
  }

  cout << "Minimum element: " << min << "\n";
  cout << "Maximum element: " << max << "\n";
}

// Function to handle reversing the array
void reverseArray(int arraySize) {
  displayArray(arraySize); // show original array

  // reverse the array in place
  for (int i = 0; i < arraySize / 2; i++) {
    swap(numbersArr[i], numbersArr[arraySize - 1 - i]); // swap elements from start and end
  }

  cout << "\nArray reversed successfully! ✅\n";
  displayArray(arraySize); // show reversed array
}

// Function to handle sorting the array
void sortArray(int arraySize) {
  displayArray(arraySize); // show original array

  // ask user for sort order
  string orderInput;
  int order;

  cout << "\n[1] Ascending\n[2] Descending\n";

  while (true) {
    cout << "Enter sort order (1-2): ";
    getline(cin, orderInput);
    orderInput = trim(orderInput);

    try {
      if (orderInput.empty()) throw invalid_argument("Invalid Input.");
      validateInput(orderInput, order, 1, 2);
      break;
    }
    catch (invalid_argument&) {
      cerr << "❌ Invalid Input. Please enter 1 or 2.\n";
    }
    catch (out_of_range&) {
      cerr << "❌ Choice out of range. Please enter 1 or 2.\n";
    }
  }

  // bubble sort
  for (int i = 0; i < arraySize - 1; i++) {
    for (int j = 0; j < arraySize - i - 1; j++) {
      bool shouldSwap = (order == 1)
        ? numbersArr[j] > numbersArr[j + 1]   // ascending
        : numbersArr[j] < numbersArr[j + 1];  // descending

      if (shouldSwap) {
        swap(numbersArr[j], numbersArr[j + 1]);
      }
    }
  }

  cout << "\nArray sorted successfully! ✅\n";
  displayArray(arraySize); // show sorted array
}

// Function to handle searching for an element in the array
void searchArray(int arraySize) {
  displayArray(arraySize); // display array contents

  string searchInput;
  int target;

  // input loop with validation
  while (true) {
    cout << "Enter element to search: ";
    getline(cin, searchInput);
    searchInput = trim(searchInput);

    try {
      if (searchInput.empty()) throw invalid_argument("Invalid Input.");
      validateInput(searchInput, target, 0, 1000000);
      break;
    }
    catch (invalid_argument&) {
      cerr << "❌ Invalid Input. Please enter a number between 0 and 1,000,000.\n";
    }
    catch (out_of_range&) {
      cerr << "❌ Invalid Input. Please enter a number between 0 and 1,000,000.\n";
    }
  }

  // search for target element in array
  bool found = false;
  for (int i = 0; i < arraySize; i++) {
    if (numbersArr[i] == target) {
      cout << "✅ Element " << target << " found at index " << i + 1 << "!\n";
      found = true;
    }
  }

  if (!found) {
    cout << "❌ Element " << target << " not found in the array.\n";
  }
}