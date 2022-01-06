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
void copyArray(char word1[] , char word2[])
{
    int i=0;
    while (word1[i-1]!='$'){
        word2[i]=word1[i];
        i++;
    }

}
class SuffixArray{
private:
    Element* array;
    int n;
    char word[];
public:
    SuffixArray(char word[] )
    {
        copyArray(word , this->word);
        n=findLen(word);
        array = new Element[n];
    }


    void ConstructUsingPrefixDoubling() {

    }

    void Print() {
        for(int i=0 ; i<n ; i++)
        {
            cout<< array[i].index;
        }
    }
};
int main()
{
    SuffixArray t("ACGACTACGATAAC$");

    t.ConstructUsingPrefixDoubling();

    t.Print(); // Prints:  14 11 12  0  6  3  9 13  1  7  4  2  8 10  5

    return 0;
}
