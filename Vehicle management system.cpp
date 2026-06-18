#include <iostream>
#include <fstream>
#include <conio.h>
using namespace std;

class Vehicle {
public:
    int id;
    char name[20];
    char category[20];
    char color[10];
    int model;
    float cost;

    Vehicle() {
        id = 0;
        model = 0;
        cost = 0;
    }

    void add(int vid) {
        id = vid;
        cout << "\n Enter Vehicle Name: ";
        cin >> name;
        cout << "\n Enter Category: ";
        cin >> category;
        cout << "\n Enter Color: ";
        cin >> color;
        cout << "\n Enter Model Year: ";
        cin >> model;
        cout << "\n Enter Cost: ";
        cin >> cost;

        ofstream("vehicle.txt", ios::app) << id << ' ' << name << ' ' << category << ' ' << color << ' ' << model << ' ' << cost << endl;
    }

    void displayFromFile() {
        ifstream file("vehicle.txt");
        int tid, tmodel;
        float tcost;
        char tname[20], tcat[20], tcolor[10];

        if (!file) {
            cout << "No vehicles saved yet.\n";
            return;
        }

        cout << "\n--- Vehicle Data from File ---\n";
        while (file >> tid >> tname >> tcat >> tcolor >> tmodel >> tcost) {
            cout << "ID: " << tid << ", Name: " << tname << ", Category: " << tcat
                 << ", Color: " << tcolor << ", Model: " << tmodel << ", Cost: " << tcost << endl;
        }

        file.close();
    }

    void updateVehicle() {
        int vid;
        cout << "\nEnter Vehicle ID to update: ";
        cin >> vid;

        ifstream in("vehicle.txt");
        ofstream temp("temp.txt");

        int tid, tmodel;
        float tcost;
        char tname[20], tcat[20], tcolor[10];
        bool found = false;

        while (in >> tid >> tname >> tcat >> tcolor >> tmodel >> tcost) {
            if (tid == vid) {
                found = true;
                cout << "Enter new Category: ";
                cin >> tcat;
                cout << "Enter new Cost: ";
                cin >> tcost;
            }
            temp << tid << ' ' << tname << ' ' << tcat << ' ' << tcolor << ' ' << tmodel << ' ' << tcost << endl;
        }

        in.close();
        temp.close();
        remove("vehicle.txt");
        rename("temp.txt", "vehicle.txt");

        if (found)
            cout << "Vehicle updated.\n";
        else
            cout << "Vehicle ID not found.\n";
    }

    void deleteVehicle() {
        int vid;
        char confirm;
        cout << "\nEnter Vehicle ID to delete: ";
        cin >> vid;

        ifstream in("vehicle.txt");
        ofstream temp("temp.txt");

        int tid, tmodel;
        float tcost;
        char tname[20], tcat[20], tcolor[10];
        bool found = false;

        while (in >> tid >> tname >> tcat >> tcolor >> tmodel >> tcost) {
            if (tid == vid) {
                found = true;
                cout << "Vehicle Found: " << tname << " - Confirm delete (Y/N)? ";
                cin >> confirm;
                if (confirm == 'Y' || confirm == 'y') {
                    continue;
                }
            }
            temp << tid << ' ' << tname << ' ' << tcat << ' ' << tcolor << ' ' << tmodel << ' ' << tcost << endl;
        }

        in.close();
        temp.close();
        remove("vehicle.txt");
        rename("temp.txt", "vehicle.txt");

        if (found)
            cout << "Vehicle deleted.\n";
        else
            cout << "Vehicle ID not found.\n";
    }

    void searchVehicle() {
        char key[20];
        cout << "\nEnter keyword to search (name/category/color): ";
        cin >> key;

        ifstream in("vehicle.txt");
        int tid, tmodel;
        float tcost;
        char tname[20], tcat[20], tcolor[10];
        bool found = false;

        while (in >> tid >> tname >> tcat >> tcolor >> tmodel >> tcost) {
            if (
                compareStr(key, tname) ||
                compareStr(key, tcat) ||
                compareStr(key, tcolor)
            ) {
                found = true;
                cout << "ID: " << tid << ", Name: " << tname << ", Category: " << tcat
                     << ", Color: " << tcolor << ", Model: " << tmodel << ", Cost: " << tcost << endl;
            }
        }

        in.close();
        if (!found)
            cout << "No matching vehicle found.\n";
    }

    void buyVehicle() {
        int vid;
        cout << "\nEnter Vehicle ID to buy: ";
        cin >> vid;

        ifstream in("vehicle.txt");
        ofstream temp("temp.txt");

        int tid, tmodel;
        float tcost;
        char tname[20], tcat[20], tcolor[10];
        bool found = false;

        while (in >> tid >> tname >> tcat >> tcolor >> tmodel >> tcost) {
            if (tid == vid && !found) {
                found = true;
                cout << "You bought vehicle: " << tname << endl;
                cout << "Cost is: " << tcost << endl;
                continue; // Skip writing this vehicle (sold)
            }
            temp << tid << ' ' << tname << ' ' << tcat << ' ' << tcolor << ' ' << tmodel << ' ' << tcost << endl;
        }

        in.close();
        temp.close();
        remove("vehicle.txt");
        rename("temp.txt", "vehicle.txt");

        if (!found)
            cout << "Vehicle ID not found or already sold.\n";
    }

    bool compareStr(const char* a, const char* b) {
        int i = 0;
        while (a[i] != '\0' && b[i] != '\0') {
            if (a[i] != b[i])
                return false;
            i++;
        }
        return (a[i] == '\0' && b[i] == '\0');
    }
};

char login() {
    char userType;
    cout << "Are you a User (U) or Admin (A)? ";
    cin >> userType;

    char uname[10], entered[10];
    int i = 0;
    char ch;

    cout << "Enter Username: ";
    cin >> uname;

    cout << "Enter Password: ";
    while ((ch = getch()) != 13) {
        if (i < 9) {
            entered[i++] = ch;
            cout << '*';
        }
    }
    entered[i] = '\0';
    cout << endl;

    char correctU[10], correctP[10];

    if (userType == 'A' || userType == 'a') {
        char tempU[] = "admin";
        char tempP[] = "1234";
        for (int j = 0; j <= 5; j++) correctU[j] = tempU[j];
        for (int j = 0; j <= 5; j++) correctP[j] = tempP[j];
    } else {
        char tempU[] = "user";
        char tempP[] = "0000";
        for (int j = 0; j <= 5; j++) correctU[j] = tempU[j];
        for (int j = 0; j <= 5; j++) correctP[j] = tempP[j];
    }

    bool nameMatch = true, passMatch = true;
    for (int j = 0; uname[j] != '\0' || correctU[j] != '\0'; j++) {
        if (uname[j] != correctU[j]) {
            nameMatch = false;
            break;
        }
    }

    for (int j = 0; entered[j] != '\0' || correctP[j] != '\0'; j++) {
        if (entered[j] != correctP[j]) {
            passMatch = false;
            break;
        }
    }

    if (nameMatch && passMatch) {
        cout << "Login successful.\n";
        return (userType == 'A' || userType == 'a') ? 'A' : 'U';
    } else {
        cout << "Access Denied.\n";
        return 'N';
    }
}

int main() {
    cout << "\n========== VEHICLE MANAGEMENT SYSTEM ==========\n";

    Vehicle v;
    int ch, id = 101;
    char role = login();

    if (role == 'N') return 0;

    do {
        cout << "\n--- Vehicle Menu (" << (role == 'A' ? "Admin" : "User") << ") ---\n";
        cout << "1. View Vehicles from File\n";
        cout << "2. Search Vehicle\n";
        if (role == 'A') {
            cout << "3. Add Vehicle\n";
            cout << "4. Update Vehicle\n";
            cout << "5. Delete Vehicle\n";
            cout << "6. Exit\n";
        } else {
            cout << "3. Buy Vehicle\n";
            cout << "4. Exit\n";
        }

        cout << "Enter choice: ";
        cin >> ch;

        if (role == 'A') {
            switch (ch) {
                case 1: v.displayFromFile(); break;
                case 2: v.searchVehicle(); break;
                case 3: v.add(id++); break;
                case 4: v.updateVehicle(); break;
                case 5: v.deleteVehicle(); break;
                case 6: cout << "Exiting...\n"; break;
                default: cout << "Invalid choice.\n";
            }
        } else {
            switch (ch) {
                case 1: v.displayFromFile(); break;
                case 2: v.searchVehicle(); break;
                case 3: v.buyVehicle(); break;
                case 4: cout << "Exiting...\n"; break;
                default: cout << "Invalid choice.\n";
            }
            if (ch == 4) break;
        }

    } while ((role == 'A' && ch != 6) || (role == 'U' && ch != 4));

    return 0;
}


