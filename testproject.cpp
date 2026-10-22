
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <iomanip>
#include <cctype>
using namespace std;

// Class 1: Customer
class Customer
{
private:
    string name;
    string phone;

public:
    void inputDetails();
    void displayDetails();
};

// Class 2: Destination

class Destination
{
private:
    string destinationName;
    double pricePerPerson;

public:
    Destination()
    {
        destinationName = "";
        pricePerPerson = 0;
    }

    Destination(string name, double price)
    {
        destinationName = name;
        pricePerPerson = price;
    }

    void displayDestinations()
    {
        cout << "\nAvailable Destinations:\n";
        cout << "1. Goa    - Rs. 5000 per person\n";
        cout << "2. Manali - Rs. 8000 per person\n";
        cout << "3. Jaipur - Rs. 4000 per person\n";
    }

    double getPrice()
    {
        return pricePerPerson;
    }

    string getName()
    {
        return destinationName;
    }
};


// Class 3: Booking

class Booking
{
private:
    string customerName;
    string phone;
    string destinationName;
    int numberOfTravelers;
    double pricePerPerson;
    double totalCost;

public:


void saveToFile()
{
    ofstream file("bookings.txt", ios::app);

    if (!file.is_open())
    {
        cout << "Unable to open bookings.txt\n";
        return;
    }

    file << customerName << "|"
         << phone << "|"
         << destinationName << "|"
         << numberOfTravelers << "|"
         << totalCost << '\n';

    file.close();

    cout << "Booking saved successfully!\n";
}


    bool createBooking()
    {
        int choice;

        cout << "\nEnter customer name: ";
        cin.ignore();
        getline(cin, customerName);

        cout << "Enter phone number: ";
        getline(cin, phone);
        if (phone.length() != 10)
{
    cout << "Phone number must contain exactly 10 digits.\n";
    return false;
}

for (char digit : phone)
{
    if (!isdigit(digit))
    {
        cout << "Phone number must contain digits only.\n";
        return false;
    }
}

        cout << "\nSelect Destination:\n";
        cout << "1. Goa - Rs. 5000\n";
        cout << "2. Manali - Rs. 8000\n";
        cout << "3. Jaipur - Rs. 4000\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                destinationName = "Goa";
                pricePerPerson = 5000;
                break;

            case 2:
                destinationName = "Manali";
                pricePerPerson = 8000;
                break;

            case 3:
                destinationName = "Jaipur";
                pricePerPerson = 4000;
                break;

            default:
                cout << "Invalid destination!\n";
                return false;
        }


cout << "Enter number of travelers: ";
cin >> numberOfTravelers;

if (cin.fail())
{
    cin.clear();
    cin.ignore(10000, '\n');
    cout << "Invalid input! Please enter a number.\n";
    return false;
}

if (numberOfTravelers <= 0)
{
    cout << "Number of travelers must be greater than zero.\n";
    return false;
}

totalCost = pricePerPerson * numberOfTravelers;


        cout << "\n===== BOOKING CONFIRMED =====\n";
        displayBooking();
        return true;
    }

    void displayBooking()
    {
        cout << "Customer: " << customerName << endl;
        cout << "Phone: " << phone << endl;
        cout << "Destination: " << destinationName << endl;
        cout << "Travelers: " << numberOfTravelers << endl;
        cout << "Price per person: Rs. "
             << pricePerPerson << endl;
        cout << "Total cost: Rs. " << totalCost << endl;
    }


void viewSavedBookings()
{
    ifstream file("bookings.txt");

    if (!file.is_open())
    {
        cout << "\nNo saved bookings found.\n";
        return;
    }

    string line;
    int count = 0;

    cout << "\n===== ALL SAVED BOOKINGS =====\n";

    while (getline(file, line))
    {
        stringstream ss(line);

        string name, phone, destination;
        string travelersText, costText;

        if (getline(ss, name, '|') &&
            getline(ss, phone, '|') &&
            getline(ss, destination, '|') &&
            getline(ss, travelersText, '|') &&
            getline(ss, costText))
        {
            cout << "\n-----------------------------\n";
            cout << "Booking Number : " << ++count << endl;
            cout << "Customer Name  : " << name << endl;
            cout << "Phone Number   : " << phone << endl;
            cout << "Destination    : " << destination << endl;
            cout << "Travelers      : " << travelersText << endl;
            cout << "Total Cost     : Rs. " << costText << endl;
            cout << "-----------------------------\n";
        }
    }

    if (count == 0)
    {
        cout << "No valid bookings available.\n";
    }

    file.close();
}
};


// Class 4: Trip Management System
class TripManagementSystem
{
private:
    Destination destination;
    Booking booking;
    vector<Booking> bookings;

public:
    void displayMenu();
    void run();
    void viewBookings();
    void viewSavedBookings();
};
void TripManagementSystem::viewBookings()
{
    if (bookings.empty())
    {
        cout << "\nNo bookings available.\n";
        return;
    }

    cout << "\n===== ALL BOOKINGS =====\n";

    for (size_t i = 0; i < bookings.size(); i++)
    {
        cout << "\nBooking " << i + 1 << ":\n";
        bookings[i].displayBooking();
    }
}

void TripManagementSystem::displayMenu()
{
    cout << "\n===== TRIP MANAGEMENT SYSTEM =====\n";
    cout << "1. View Destinations\n";
    cout << "2. Book a Trip\n";
    cout << "3. View Bookings\n";
    cout << "4. Exit\n";
    cout << "Enter your choice: ";
}
void TripManagementSystem::viewSavedBookings()
{
    Booking savedBooking;
    savedBooking.viewSavedBookings();
}

void TripManagementSystem::run()
{
    int choice;

    do
    {
        displayMenu();
        cin >> choice;

        switch (choice)
        {
            case 1:
    destination.displayDestinations();
    break;

case 2:
{
    Booking newBooking;

    if (newBooking.createBooking())
    {
        bookings.push_back(newBooking);
        newBooking.saveToFile();
    }

    break;
}


            case 3:
    viewSavedBookings();
    break;

            case 4:
                cout << "Exiting program. Goodbye!\n";
                break;

            default:
                cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 4);
}

int main()
{
    TripManagementSystem system;
    system.run();

    return 0;
}
