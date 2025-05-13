#include <iostream>
#include <cstring>
using namespace std;

struct block {
    int bno;
    block* next;
};

struct fileTable {
    char name[20];
    int nob;
    block* sb;
} ft[30];

int main() {
    int n;
    cout << "Enter number of files: ";
    cin >> n;

    for (int i = 0; i < n; i++) {
        cout << "\nEnter name for file " << i + 1 << ": ";
        cin >> ft[i].name;

        cout << "Enter number of blocks for " << ft[i].name << ": ";
        cin >> ft[i].nob;

        ft[i].sb = NULL;
        block* temp = NULL;

        cout << "Enter block numbers:\n";
        for (int j = 0; j < ft[i].nob; j++) {
            int bno;
            cout << "  Block " << j + 1 << ": ";
            cin >> bno;

            block* newBlock = new block();
            newBlock->bno = bno;
            newBlock->next = NULL;

            if (ft[i].sb == NULL) {
                ft[i].sb = newBlock;
                temp = newBlock;
            } else {
                temp->next = newBlock;
                temp = newBlock;
            }
        }
    }


    cout << "\nFILE NAME\tNO OF BLOCKS\tBLOCKS OCCUPIED\n";
    for (int i = 0; i < n; i++) {
        cout << ft[i].name << "\t\t" << ft[i].nob << "\t\t";

        block* temp = ft[i].sb;
        while (temp != NULL) {
            cout << temp->bno;
            if (temp->next != NULL)
                cout << " → ";
            temp = temp->next;
        }
        cout << endl;
    }

    return 0;
}
