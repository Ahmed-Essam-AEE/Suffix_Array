#include <iostream>
#include <algorithm>
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

        sort(array , array+n , compare);    ///////////
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

            sort(array , array+n , compare);

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
