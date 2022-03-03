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
void copyArray(string word1 , char word2[])
{
    int i=0;
    while (word1[i-1]!='$'){
        word2[i]=word1[i];
        i++;
    }

}
void copyArray(char word1[] , char word2[])
{
    int i=0;
    while (word1[i-1]!='$'){
        word2[i]=word1[i];
        i++;
    }

}
int compare(Element a,Element b )
{
    if(a.r[0]==b.r[0])
    {
        if(a.r[1] < b.r[1]) return 1;
        else return 0;
    }
    else if (a.r[0] < b.r[0]) return 1;
    else return 0;
}

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
    char word[];
public:
    SuffixArray(string word )
    {
        copyArray(word , this->word);
        n=findLen(this->word);
        array = new Element[n];
    }



    void ConstructUsingPrefixDoubling() {
        for(int i=0 ; i<n ; i++)
        {
            array[i].index=i;
            array[i].r[0]=word[i]-'a';
            if(i+1 <n)
            {
                array[i].r[1]=word[i+1]-'a';
            }else array[i].r[1]=-1;
        }

        merge_sort(array , 0 , n-1);
        int indArr[n];

        for(int j=4 ; j<n*2 ; j*=2)
        {
            int pre =array[0].r[0], curr=0;
            array[0].r[0]=curr;
            indArr[array[0].index]=0;
            for(int i=1 ; i<n ; i++)
            {

                if(array[i].r[0] == pre  && array[i].r[1]==array[i-1].r[1])
                {
                    pre = array[i].r[0];
                    array[i].r[0]=curr;
                }else{
                    pre = array[i].r[0];
                    curr++;
                    array[i].r[0]=curr;
                }
                indArr[array[i].index]=i;

            }
            for(int i=0 ; i<n ; i++)
            {
                int next=array[i].index + j/2;
                if(next<n) array[i].r[1]=array[indArr[next]].r[0];
                else array[i].r[1]=-1;

            }
            merge_sort(array , 0 , n-1);

        }


    }

    void Print() {
        for(int i=0 ; i<n ; i++)
        {
            cout<< array[i].index<<" ";
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
