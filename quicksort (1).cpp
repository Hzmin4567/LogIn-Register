#include <iostream>
#include <string>
#include <stdexcept>//it can be thrown to indicate invalid arguments passed to a function. like std::invalid_argument
#include <limits>//It is included here for using numeric_limits<streamsize>::max() to clear the input buffer in case of invalid input.
#include <sstream> // Include the <sstream> header for stringstream
using namespace std;

const int MAX_SIZE = 100;

struct Data {
    int number;
    string str;
};

int partition(Data arr[], int low, int high) {
    int pivotIndex = low;
    string pivotStr = arr[low].str;
    int pivotNum = arr[low].number;
    int i = low + 1;
    int j = high;

    while (true) {
        while (i <= j && (arr[i].str < pivotStr || (arr[i].str == pivotStr && arr[i].number < pivotNum)))
            i++;
        while (i <= j && (arr[j].str > pivotStr || (arr[j].str == pivotStr && arr[j].number > pivotNum)))
            j--;
        if (i > j)
            break;

        swap(arr[i], arr[j]);
    }

    swap(arr[low], arr[j]);

    cout << "Partition Step: Pivot = " << arr[j].number << " (" << arr[j].str << "), Elements less than or equal to pivot: " <<endl;
    for (int k = low; k <= j; k++) {
        cout << arr[k].number << " (" << arr[k].str << ") " <<endl;
    }
    cout << "| Elements greater than pivot: " << endl;
    for (int k = j + 1; k <= high; k++) {
        cout << arr[k].number << " (" << arr[k].str << ") " <<endl;
    }
    cout << endl;

    return j;
}
void quickSort(Data arr[], int low, int high) {
    if (low < high) {
        int pivotIndex = partition(arr, low, high);

        cout << "Repeat the process recursively on the two sub-arrays formed by the partitioning step." << endl;

        quickSort(arr, low, pivotIndex - 1);
        quickSort(arr, pivotIndex + 1, high);
    }
}


int stringToInt(const string& input) {
    int result = 0;
    int sign = 1;
    int i = 0;

    if (input[i] == '-' || input[i] == '+') {
        sign = (input[i] == '-') ? -1 : 1;
        i++;
    }

    while (i < input.length()) {
        if (input[i] >= '0' && input[i] <= '9') {
            result = result * 10 + (input[i] - '0');
            i++;
        } else {
            throw invalid_argument("Invalid input: " + input);
        }
    }

    return result * sign;
}

void inputData(Data arr[], int& count) {
    int numSets;
    cout << "Enter the size of data to input: ";
    while (!(cin >> numSets)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter a valid number: ";
    }

    for (int i = 0; i < numSets; i++) {
        if (count >= MAX_SIZE) {
            cout << "Maximum data limit reached. Cannot add more data.\n";
            break;
        }

        cout << "Enter data (" << i + 1 << "): ";
        string input;
        cin >> input;

        try {
            arr[count].number = stringToInt(input);
            arr[count].str = "";
        } catch (const invalid_argument& e) {
            arr[count].number = 0;
            arr[count].str = input;
        }

        count++;
    }

    cout << "Data added successfully.\n";
}


void removeData(Data arr[], int& size) {
    if (size == 0) {
        cout << "No data to remove.\n";
        return;
    }

    string dataToRemove;
    cout << "Enter the data to remove: ";
    cin >> dataToRemove;

    bool found = false;
    for (int i = 0; i < size; i++) {
        stringstream ss;
        ss << arr[i].number;  // Convert the integer to string using stringstream
        if (arr[i].str == dataToRemove || ss.str() == dataToRemove) {
            // Data found, remove it by shifting elements
            for (int j = i; j < size - 1; j++) {
                arr[j] = arr[j + 1];
            }
            size--;
            found = true;
            break;
        }
    }

    if (found) {
        cout << "Data removed successfully.\n";
    } else {
        cout << "Data not found.\n";
    }
}


void truncateData(Data arr[], int& size) {
    if (size == 0) {
        cout << "No data to truncate.\n";
        return;
    }

    char confirmation;
    cout << "Are you sure you want to remove all the data? (y/n): ";
    cin >> confirmation;

    if (confirmation == 'y' || confirmation == 'Y') {
        size = 0;
        cout << "All data removed successfully.\n";
    } else {
        cout << "Truncate operation canceled.\n";
    }
}

void displayData(Data arr[], int size) {
    if (size == 0) {
        cout << "No data to display.\n";
        return;
    }

    cout << "Sorted Data:\n";
    for (int i = 0; i < size; i++) {
        if (arr[i].str.empty()) {
            cout << arr[i].number;
        } else {
            cout << arr[i].str;
        }
        cout << endl;
    }
}


void sortAscending(Data arr[], int size) {
    if (size == 0) {
cout << "No data to sort.\n";
        return;
    }

    quickSort(arr, 0, size - 1);

    cout << "Data sorted in ascending order.\n";
    displayData(arr, size);

    
}

void sortDescending(Data arr[], int size) {
    if (size == 0) {
        cout << "No data to sort.\n";
        return;
    }

    quickSort(arr, 0, size - 1);

    for (int i = 0; i < size / 2; i++) {
        swap(arr[i], arr[size - i - 1]);
    }

    cout << "Data sorted in descending order.\n";
    displayData(arr, size);

}


int main() {
    Data arr[MAX_SIZE];
    int size = 0;
    int choice;
     	cout << "\033[34m      QUICK SORT\033[0m" <<endl;

    do {
        
        cout << "\n----------------------------------------"<<endl;
    cout << "1. Add Data"<<endl;
    cout << "2. Remove Data"<<endl;
    cout << "3.Sort in Ascending Order"<<endl;
    cout << "4.Sort in Descending Order"<<endl;
    cout << "5.Truncate Data"<<endl;
    cout << "6.Exit"<<endl;
    cout << "----------------------------------------"<<endl;
    cout << "Enter your choice: ";
        while (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a valid number: ";
        }

        switch (choice) {
            case 1:
                inputData(arr, size);
                break;
            case 2:
                removeData(arr, size);
                break;
            case 3:
                 sortAscending(arr, size);
                break;
            case 4:
            	sortDescending(arr, size);
                break;
            case 5:
            	truncateData(arr, size);
                break; 
            case 6:
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid choice. Please enter a number from 1 to 7.\n";
        }
    } while (choice != 6);

    return 0;
}
