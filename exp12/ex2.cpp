#include <iostream>
#include <cstring>
using namespace std;

#define MAX_FILES 10
#define MAX_DIRS 10

struct Directory {
    char name[30];
    char files[MAX_FILES][30];
    int fileCount;

    Directory* subDirs[MAX_DIRS];
    int dirCount;

    Directory* parent;  
};

Directory* createDirectory(const char* name, Directory* parent = NULL) {
    Directory* newDir = new Directory;
    strcpy(newDir->name, name);
    newDir->fileCount = 0;
    newDir->dirCount = 0;
    newDir->parent = parent;
    return newDir;
}

void createFile(Directory* current) {
    if (current->fileCount >= MAX_FILES) {
        cout << "Cannot create more files in this directory.\n";
        return;
    }
    char fname[30];
    cout << "Enter file name: ";
    cin >> fname;
    strcpy(current->files[current->fileCount], fname);
    current->fileCount++;
    cout << "File '" << fname << "' created in " << current->name << endl;
}

void createSubDirectory(Directory* current) {
    if (current->dirCount >= MAX_DIRS) {
        cout << "Cannot create more subdirectories.\n";
        return;
    }
    char dname[30];
    cout << "Enter subdirectory name: ";
    cin >> dname;
    Directory* newDir = createDirectory(dname, current);
    current->subDirs[current->dirCount++] = newDir;
    cout << "Subdirectory '" << dname << "' created under " << current->name << endl;
}

void display(Directory* dir, int depth = 0) {
    for (int i = 0; i < depth; i++) cout << "  ";
    cout << "[DIR] " << dir->name << endl;

    for (int i = 0; i < dir->fileCount; i++) {
        for (int j = 0; j < depth + 1; j++) cout << "  ";
        cout << "- " << dir->files[i] << endl;
    }

    for (int i = 0; i < dir->dirCount; i++) {
        display(dir->subDirs[i], depth + 1);
    }
}

Directory* navigate(Directory* current) {
    char name[30];
    cout << "Enter subdirectory name to navigate (.. to go back): ";
    cin >> name;

    if (strcmp(name, "..") == 0) {
        if (current->parent != NULL) {
            return current->parent;
        } else {
            cout << "Already at root directory.\n";
            return current;
        }
    }

    for (int i = 0; i < current->dirCount; i++) {
        if (strcmp(current->subDirs[i]->name, name) == 0) {
            return current->subDirs[i];
        }
    }

    cout << "Subdirectory not found.\n";
    return current;
}

int main() {
    Directory* root = createDirectory("root");
    Directory* current = root;

    int choice;

    while (true) {
        cout << "\nCurrent Directory: " << current->name;
        cout << "\n1. Create Subdirectory \t 2. Create File \t 3. Display Directory Structure \t 4. Navigate \t 5. Exit";
        cout << "\nEnter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: createSubDirectory(current); break;
            case 2: createFile(current); break;
            case 3: display(root); break;
            case 4: current = navigate(current); break;
            case 5: return 0;
            default: cout << "Invalid choice.\n";
        }
    }

    return 0;
}

