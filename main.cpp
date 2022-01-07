#include <iostream>
using namespace std;

class Element{
public:
    int index;
    int r[2];
};

int findLen(char word[])
{
    int i=0;
    while (word[i]!='$'){
        i++;
    }
    return ++i;
}

bool compare(Element a,Element b )
{
    if(a.r[0]==b.r[0])
    {
        return a.r[1] < b.r[1];
    }
    else return a.r[0] < b.r[0];
}

// Function of Merge that merge two arrays together.
void Merge(Element arr[], int l, int mid, int r)
{
    int n1 = mid - l + 1, n2 = r - mid;

    Element L[n1], R[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];

    for (int i = 0; i < n2; i++)
        R[i] = arr[mid + 1 + i];

    int i = 0, j = 0, k = l;

    while(i < n1 && j < n2){
        if (compare(L[i], R[j]))
            arr[k] = L[i], i++;
        else
            arr[k] = R[j], j++;
        k++;
    }

    while(i < n1)
        arr[k] = L[i], k++, i++;

    while(j < n2)
        arr[k] = R[j], k++, j++;
}

// Function of Merge Sort.
void merge_sort(Element arr[], int l, int r)
{
    if (l < r)
    {
        int mid = (l + r) / 2;

        merge_sort(arr, l, mid);

        merge_sort(arr, mid + 1, r);

        Merge(arr, l, mid, r);
    }
}

class SuffixArray{
private:
    Element* array;
    int n;
    char *word;
public:
    SuffixArray(char arr[] )
    {
        n = findLen(arr);
        word = new char [n];
        for (int i = 0; i < n; i++)
            word[i] = arr[i];
        array = new Element[n];
    }

    void ConstructUsingPrefixDoubling() {

        // Suffix Array.
        Element suffix[n];

        // Making the first two iterations (2^0 = 1 and 2^1 = 2)
        for (int i = 0; i < n; i++)
        {
            suffix[i].index = i;
            suffix[i].r[0] = (word[i] - 'A');
            suffix[i].r[1] = (i + 1 < n ? (word[i + 1] - 'A') : 0);
        }

        // Sorting suffix array using merge sort (n log n).
        merge_sort(suffix, 0, n - 1);

        // Array which tells the index in suffix array from the original index.
        int next[n];

        // Now let's continue our log n iterations.
        int j = 4; // The third iteration: 2 ^ 2 = 4
        bool isFinished = false; // Boolean to check if we finished or not.
        while(!isFinished)
        {
            int rank = 0;
            int prev = suffix[0].r[0];
            suffix[0].r[0] = 0;
            next[suffix[0].index] = 0;
            for (int i = 1; i < n; i++)
            {
                if (suffix[i].r[0] == prev && suffix[i].r[1] == suffix[i - 1].r[1]){
                    prev = suffix[i].r[0];
                    suffix[i].r[0] = rank;
                }
                else{
                    prev = suffix[i].r[0];
                    suffix[i].r[0] = ++rank;
                }
                next[suffix[i].index] = i;
            }

            // Updating the r1 for each suffix.
            for (int i = 0; i < n; i++)
            {
                int idx = suffix[i].index + (j / 2);
                suffix[i].r[1] = (idx < n ? suffix[next[idx]].r[0] : 0);
            }

            // Sort again according to the first j characters.
            merge_sort(suffix, 0, n - 1);

            // A frequency array to check if all the indices are distinct or not.
            int freq[n];

            // Initializing frequency array with zeros.
            for (int i = 0; i < n; i++)
                freq[i] = 0;

            // Counting how many times did the index appear.
            for (int i = 0; i < n; i++){
               // cout << suffix[i].index << endl;
                freq[suffix[i].index]++;
            }

            isFinished = true;
            for (int i = 0; i < n; i++){
                // If the index appeared more than one time, we didn't finish yet.
                if (freq[i] > 1)
                    isFinished = false;
            }
            j *= 2;
        }

        array = new Element[n];
        for (int i = 0; i < n; i++)
            array[i] = suffix[i];
    }

    void Print() {
        for (int i = 0; i < n; i++)
        {
            cout << array[i].index << " ";
        }
        cout<<endl;
    }
};

int main()
{
    SuffixArray t("ACGACTACGATAAC$");

    t.ConstructUsingPrefixDoubling();

    t.Print(); // Prints:  14 11 12  0  6  3  9 13  1  7  4  2  8 10  5

    return 0;
}