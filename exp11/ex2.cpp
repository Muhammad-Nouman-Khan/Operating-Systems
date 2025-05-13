#include <iostream>
#include <cstring>
using namespace std;

struct fileTable {
    char name[20];
    int nob;
    int* blocks;
} ft[30];

int main() {
    int n;
    cout << "Enter number of files: ";
    cin >> n;

    for (int i = 0; i < n; i++) {
        cout << "\nEnter name for file " << i + 1 << ": ";
        cin >> ft[i].name;

        cout << "Enter number of blocks for file " << ft[i].name << ": ";
        cin >> ft[i].nob;

        ft[i].blocks = new int[ft[i].nob];

        cout << "Enter " << ft[i].nob << " block numbers:\n";
        for (int j = 0; j < ft[i].nob; j++) {
            cout << "  Block " << j + 1 << ": ";
            cin >> ft[i].blocks[j];
        }
    }

    cout << "\nFILE NAME\tNO OF BLOCKS\tBLOCKS OCCUPIED\n";
    for (int i = 0; i < n; i++) {
        cout << ft[i].name << "\t\t" << ft[i].nob << "\t\t";

        for (int j = 0; j < ft[i].nob; j++) {
            cout << ft[i].blocks[j];
            if (j < ft[i].nob - 1)
                cout << ",";
        }
        cout << endl;
    }

    for (int i = 0; i < n; i++) {
        delete[] ft[i].blocks;
    }

    return 0;
}
