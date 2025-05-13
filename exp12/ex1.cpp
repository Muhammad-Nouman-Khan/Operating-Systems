#include <iostream>
#include <cstring>
using namespace std;

struct UserDirectory {
    string userName;
    string files[10];
    int fileCount;
};

int main() {
    UserDirectory users[5];
    int userCount = 0;
    int choice, uIndex;
    string uname, fname;

    while (true) {
        cout << "\n\n1. Create User Directory \t 2. Create File \t 3. Delete File \t 4. Search File \t 5. Display Files \t 6. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                if (userCount >= 5) {
                    cout << "Maximum user limit reached.\n";
                    break;
                }
                cout << "Enter new user name: ";
                cin >> users[userCount].userName;
                users[userCount].fileCount = 0;
                userCount++;
                break;

            case 2:
                cout << "Enter user name: ";
                cin >> uname;
                for (uIndex = 0; uIndex < userCount; uIndex++) {
                    if (users[uIndex].userName == uname) break;
                }
                if (uIndex == userCount) {
                    cout << "User not found.\n";
                    break;
                }
                if (users[uIndex].fileCount >= 10) {
                    cout << "User's directory full.\n";
                    break;
                }
                cout << "Enter file name: ";
                cin >> users[uIndex].files[users[uIndex].fileCount];
                users[uIndex].fileCount++;
                break;

            case 3:
                cout << "Enter user name: ";
                cin >> uname;
                for (uIndex = 0; uIndex < userCount; uIndex++) {
                    if (users[uIndex].userName == uname) break;
                }
                if (uIndex == userCount) {
                    cout << "User not found.\n";
                    break;
                }
                cout << "Enter file name to delete: ";
                cin >> fname;
                {
                    int i;
                    for (i = 0; i < users[uIndex].fileCount; i++) {
                        if (users[uIndex].files[i] == fname) {
                            users[uIndex].files[i] = users[uIndex].files[users[uIndex].fileCount - 1];
                            users[uIndex].fileCount--;
                            cout << "File deleted.\n";
                            break;
                        }
                    }
                    if (i == users[uIndex].fileCount)
                        cout << "File not found.\n";
                }
                break;

            case 4:
                cout << "Enter user name: ";
                cin >> uname;
                for (uIndex = 0; uIndex < userCount; uIndex++) {
                    if (users[uIndex].userName == uname) break;
                }
                if (uIndex == userCount) {
                    cout << "User not found.\n";
                    break;
                }
                cout << "Enter file name to search: ";
                cin >> fname;
                {
                    int i;
                    for (i = 0; i < users[uIndex].fileCount; i++) {
                        if (users[uIndex].files[i] == fname) {
                            cout << "File found.\n";
                            break;
                        }
                    }
                    if (i == users[uIndex].fileCount)
                        cout << "File not found.\n";
                }
                break;

            case 5:
                cout << "Enter user name: ";
                cin >> uname;
                for (uIndex = 0; uIndex < userCount; uIndex++) {
                    if (users[uIndex].userName == uname) break;
                }
                if (uIndex == userCount) {
                    cout << "User not found.\n";
                    break;
                }
                cout << "Files in " << uname << "'s directory:\n";
                if (users[uIndex].fileCount == 0) {
                    cout << "No files.\n";
                } else {
                    for (int i = 0; i < users[uIndex].fileCount; i++) {
                        cout << "\t" << users[uIndex].files[i] << "\n";
                    }
                }
                break;

            case 6:
                return 0;

            default:
                cout << "Invalid choice.\n";
        }
    }

    return 0;
}
