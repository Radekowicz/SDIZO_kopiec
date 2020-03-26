//--------------------------------------------------------------
//                       SDIZO ĆWICZENIA
//                           LISTA NR 2
//--------------------------------------------------------------
//                     RADOSŁAW ŁODZIŃSKI
//                           249455
//--------------------------------------------------------------


#include <iostream>
using namespace std;

//--------------------------------------------------------------
//                      ZADANIA Z KOPCA
//--------------------------------------------------------------

void printTab(int *tab, int size) {
    for (size_t i = 0; i < size; i++) {
        cout << tab[i] << ' ';
    }
    cout << "\n";
}

void repairDown(int *tab, int size, int parentIndex) {

    //definiowanie dzieci rodzica
    int leftChildIndex = 2 * parentIndex + 1;
    int rightChildIndex = 2 * parentIndex + 2;

    bool rightExists = rightChildIndex < size;

    if(rightExists) {
        if (tab[leftChildIndex] < tab[parentIndex] || tab[rightChildIndex] < tab[parentIndex]) {

            //ustalanie które dziecko jest mniejsze
            int smallerChildIndex;
            if (tab[rightChildIndex] < tab[leftChildIndex])
                smallerChildIndex = rightChildIndex;
            else if (tab[rightChildIndex] > tab[leftChildIndex])
                smallerChildIndex = leftChildIndex;

            //zamiana miejscami
            int tempParent = tab[parentIndex];
            tab[parentIndex] = tab[smallerChildIndex];
            tab[smallerChildIndex] = tempParent;


            //nowy rodzic i rekurencyjne wywołanie funkcji
            if (smallerChildIndex <= (size - 2) / 2)
                repairDown(tab, size, smallerChildIndex);
        }
    }
    else if (tab[leftChildIndex] < tab[parentIndex]){

        //zamiana miejscami
        int tempParent = tab[parentIndex];
        tab[parentIndex] = tab[leftChildIndex];
        tab[leftChildIndex] = tempParent;


        //nowy rodzic i rekurencyjne wywołanie funkcji
        if (leftChildIndex <= (size - 2) / 2)
            repairDown(tab, size, leftChildIndex);
    }
}


int main() {

//--------------------------------------------------------------
//                      ZADANIE 1B (z opisem stanów)
//--------------------------------------------------------------

    //tworzenie tablicy danej w zadaniu
    int tab[] = {7, 5, 9, 6, 7, 8, 10, 1, 11};
    size_t n = sizeof(tab)/sizeof(tab[0]);

    //wydrukowanie tablicy
    cout << endl << "Drzewo binarne" << endl;
    printTab(tab, n);
    cout << endl;

    cout << "Budowa kopca minimalnego metodą dokładania do kopca kolejnych elementów:" << endl << endl;

    //tworzenie tablicy, którą będziemy uzupełniać po kolei
    int heap[] = {0, 0, 0, 0, 0, 0, 0, 0, 0};

    //pierwszy element jest taki sam
    heap[0] = tab[0];
    cout << "Dodajemy " << heap[0] << ", rodzic: brak" << endl;
    cout << heap[0] << endl << endl << endl;

    //iterujemy po całej tablicy
    for(int i = 1; i < n; i++) {
        heap[i] = tab[i];
        int currentNumber = heap[i];
        int parent = heap[(i - 1) / 2];
        cout << "Dodajemy " << heap[i] << ", rodzic: " << parent << " (tab[" << (i - 1) / 2 << "])" << endl;
        printTab(heap, i+1);

        int index = i;

        while(currentNumber < parent){
            cout << endl << currentNumber << " nie spełnia warunku kopca" << endl;
            cout << "Zamiana " << currentNumber << " z " << parent << endl;

            //zamiana miejscami
            heap[index] = parent;
            heap[(index - 1) / 2] = currentNumber;

            printTab(heap, i+1);

            int j = (index-1)/2;
            currentNumber = heap[j];
            parent = heap[(j - 1) / 2];
            index = j;
        }
        cout << endl << endl;
    }

    //wydrukowanie tablicy
    cout << endl << "Kopiec minimalny zbudowany metodą dokładania do kopca kolejnych elementów" << endl;
    printTab(heap, n);




//--------------------------------------------------------------
//                      ZADANIE 2
//--------------------------------------------------------------

    //usuwanie korzenia
    //znalezienie ostatniego elementu i wstawienie go na miejsce korzenia
    heap[0] = heap[n - 1];
    heap[n - 1] = NULL;

    int N = n-1;

    cout << "\n";

    //naprawa kopca w dół
    repairDown(heap, N, 0);

    //wydrukowanie tablicy
    cout << endl << "Kopiec minimalny z zadania 1b z usuniętym korzeniem" << endl;
    printTab(heap, N);




//--------------------------------------------------------------
//                      ZADANIE 3B
//--------------------------------------------------------------

    int lastParentIndex = (n-2)/2;

    while(lastParentIndex >= 0) {

        //naprawa kopca w dół
        repairDown(tab, N, lastParentIndex);

        //nowy lastParent
        lastParentIndex--;

    }

    //wydrukowanie tablicy
    cout << endl << "Kopiec minimalny zbudowany metodą Floyda" << endl;
    printTab(tab, n);

    return 0;
}

