#include <iostream>
#include <fstream>

using namespace std;

int index_letter(int letter, char alphabet[])
{
    for (int i = 0; *(alphabet + i); i++)
        if (letter == *(alphabet + i)) return i;
    return -1;
}

int isFinal(int row, int finish[], int n)
{
    for (int i = 0; i < n; i++) if (finish[i] == row) return 1;
    return 0;

}

int main() {
    int k = 3;
    char alphabet[] = "abcdefghijklmnopqrstuvwxyz";
    string path = "D:/lab2.txt";
    ifstream file;
    file.open(path);
    if (!file.is_open()) {
        cerr << "Cannot open file massive.txt" << endl;
        return 1;
    }

    int numLetters, numStates, initialState, finalStatesAmount;
    file >> numLetters >> numStates >> initialState >> finalStatesAmount;
    int* finalStates = new int[finalStatesAmount];

    for (int i = 0; i < finalStatesAmount; ++i) {
        file >> finalStates[i];
    }

    char* abc = new char[numLetters];
    for (int i = 0; i < numLetters; ++i) {
        abc[i] = alphabet[i];
    }

    int** sigma = new int* [numStates];
    for (int i = 0; i < numStates; ++i) {
        sigma[i] = new int[numLetters];
        for (int j = 0; j < numLetters; ++j) {
            sigma[i][j] = 0;
        }
    }

    int stateOut, stateIn, letterIndex;
    char letter;
    while (file >> stateOut >> letter >> stateIn) {
        letterIndex = index_letter(letter, abc);
        sigma[stateOut][letterIndex] = stateIn;
    }
    file.close();

    cout << "Alphabet = {";
    for (int i = 0; i < numLetters; ++i) {
        if (i == numLetters - 1) cout << abc[i];
        else cout << abc[i] << ", ";
    }
    cout << "}" << endl;

    int* states = new int [numStates];
    for (int i = 0; i < numStates; ++i) {
        states[i] = i;
    }
    cout << "States = {";
    for (int i = 0; i < numStates; ++i) {
        if (i == numStates - 1) cout << states[i];
        else cout << states[i] << ", ";
    }
    cout << "}" << endl;

    cout << "Final states = {";
    for (int i = 0; i < finalStatesAmount; ++i) {
        if (i == finalStatesAmount - 1) cout << finalStates[i];
        else cout << finalStates[i] << ", ";
    }
    cout << "}" << endl;

    for (int i = 0; i < numStates; ++i) {
        for (int j = 0; j < numLetters; ++j) {
            cout << sigma[i][j] << ' ';
        }
        cout << endl;
    }

    char* currentWord = new char[k + 1];

    for (int i = 0; i < k; i++) {
        currentWord[i] = abc[0];
    }
    currentWord[k] = '\0';
    bool exit = false;
    while (true) {
        int row = 0;
        int column = 0;
        for (int j = 0; j < k; ++j) {
            column = index_letter(currentWord[j], abc);
            row = sigma[row][column];
            if (row == 0) { exit = true; break; }
        }
        if (exit) break;
        if (isFinal(row, finalStates, finalStatesAmount) == 0) { exit = true; break; }
        int index = k - 1;
        while (index >= 0 && currentWord[index] == abc[numLetters - 1]) {
            index--;
        }

        if (index == -1) {
            break;
        }

        int currentIndex = strchr(abc, currentWord[index]) - abc;
        currentWord[index] = abc[currentIndex + 1];
        for (int i = index + 1; i < k; i++) {
            currentWord[i] = abc[0];
        }
    }
    if (exit) cout << "Automaton does not allow all words of length " << k << " from given alphabet" << endl;
    else cout << "Automaton allows all words of length " << k << " from given alphabet" << endl;

    delete[] currentWord;
    delete[] abc;
    delete[] states;
    delete[] finalStates;
    for (int i = 0; i < numStates; ++i) {
        delete[] sigma[i];
    }
    delete[] sigma;

    return 0;
}
