#include <iostream>
#include <string>
#include <cassert>
using namespace std;

int appendToAll(string a[], int n, string value);
int lookup(const string a[], int n, string target);
int positionOfMax(const string a[], int n);
int rotateLeft(string a[], int n, int pos);
int countRuns(const string a[], int n);
int flip(string a[], int n);
int differ(const string a1[], int n1, const string a2[], int n2);
int subsequence(const string a1[], int n1, const string a2[], int n2);
int lookupAny(const string a1[], int n1, const string a2[], int n2);
int separate(string a[], int n, string separator);

int main()
{
    string h[7] = { "mick", "marie", "fiona", "rudy", "", "gordon", "lindsey" };
    assert(lookup(h, 7, "gordon") == 5);
    assert(lookup(h, 7, "fiona") == 2);
    assert(lookup(h, 2, "fiona") == -1);
    assert(positionOfMax(h, 7) == 3);

    string g[4] = { "mick", "marie", "lindsey", "nancy" };
    assert(differ(h, 4, g, 4) == 2);
    assert(appendToAll(g, 4, "?") == 4 && g[0] == "mick?" && g[3] == "nancy?");
    assert(rotateLeft(g, 4, 1) == 1 && g[1] == "lindsey?" && g[3] == "marie?");

    string e[4] = { "fiona", "rudy", "", "gordon" };
    assert(subsequence(h, 7, e, 4) == 2);

    string d[5] = { "marie", "marie", "marie", "rudy", "rudy" };
    assert(countRuns(d, 5) == 2);

    string f[3] = { "lindsey", "fiona", "mike" };
    assert(lookupAny(h, 7, f, 3) == 2);
    assert(flip(f, 3) == 3 && f[0] == "mike" && f[2] == "lindsey");

    assert(separate(h, 7, "lindsey") == 3);

    cout << "All tests succeeded" << endl;
}

int appendToAll(string a[], int n, string value)
{
    if (n < 0) // check n < 0
        return -1;
    for (int i = 0; i < n; i++) // Go through the loop and add the value to end of each string
    {
        a[i] += value;
    }
    return n;
}

int lookup(const string a[], int n, string target)
{
    if (n < 0) // check n < 0
        return -1;
    for (int i = 0; i < n; i++) // Go through the loop to check whether one of the element match the target and return the position
    {
        if (a[i] == target)
            return i;
    }
    return -1; // if no match
}

int positionOfMax(const string a[], int n)
{
    if (n < 0) // check n < 0
        return -1;
    if (n == 0) //check n = 0 (no match)
        return -1;
    int maxPosition = 0; // assume the current biggest string is at 0
    for (int i = 0; i < n; i++)
    {
        if (a[i] > a[maxPosition]) // Go through the loop, if one of the string is larger than the former max, record the new position
            maxPosition = i;
    }
    return maxPosition;
}

int rotateLeft(string a[], int n, int pos)
{
    if (n < 0 || pos < 0 || pos >= n) // if n < 0, position out of the bound (<0 or >n) return false
        return -1;
    string temp = a[pos]; // record the string to be removed
    for (int i = 0; i < n - pos -1; i++)
    {
        a[i + pos] = a[i+ pos +1]; // all string go left one position
    }
    a[n-1] = temp; // appendix last position for the string to be removed
    return pos;
}

int countRuns(const string a[], int n)
{
    if (n < 0) // check n < 0
        return -1;
    if (n == 0)
        return 0;
    int count = 1;
    for (int i = 1; i < n; i++)
    {
        if (a[i] != a[i-1]) // when a different element is met, it means the end of one consecutive strings. count plus 1
            count++;
    }
    return count;
}

int flip(string a[], int n)
{
    if (n < 0) // check n < 0
        return -1;
    for (int i = 0; i < n/2; i++)
    {
        string temp = a[i]; // create a temp string for swap
        a[i] = a[n-i-1]; // swap the elements one by one and approach the center
        a[n-i-1] = temp;
    }
    return n;
}

int differ(const string a1[], int n1, const string a2[], int n2)
{
    if (n1 < 0 || n2 < 0) // check either of n < 0
        return -1;
    if (n1 == 0 || n2 == 0) // if both n1 and n2 is 0, the difference is at zero position
        return 0;
    int positiond = 0;
    if (n1 <= n2) // choose a smaller velue for the sub string
        positiond = n1;
    else
        positiond = n2;
    
    for (int i = 0; i < positiond; i++) // when the difference is met, return the position
        if (a1[i] != a2[i])
                return i;
    return positiond;
}

int subsequence(const string a1[], int n1, const string a2[], int n2)
{
    int pos = 0;
    bool match = false; // assume it does not match
    if (n1 < 0 || n2 < 0) // check either of n < 0
        return -1;
    if (n2 == 0)
        return 0;
    for (int k1 = 0; k1 < n1; k1++) // go through each element in the n1
    {
        
        if (a1[k1] == a2[0]) // check if any element in n1 match the first element in n2
        {
            pos = k1; // if so, record the position
            for (int k2 = 0; k2 < n2; k2++ ) // check the following element
            {
                if (a1[k1+k2] == a2[k2] && (k2 +1 == n2))
                    match = true; // if all of the element matches, return true
                if (a1[k1+k2] != a2[k2])
                    break; // if one of the element does not match, go back to the loop
            }
            
        }
    }
    if (not match)
        return -1;
    else
        return pos;
}

int lookupAny(const string a1[], int n1, const string a2[], int n2)
{
    if (n1 < 0 || n2 < 0) // check either of n < 0
    return -1;
    
    for (int k1 = 0; k1 < n1; k1++) // go through the n1 loop
        for (int k2 = 0; k2 < n2; k2++) // go through each element in n2
        {
            if (a1[k1] == a2[k2]) // the first element met is the foremost one
                return k1;
        }
    return -1;
}

int separate(string a[], int n, string separator)
{
    if (n < 0) // check n < 0
        return -1;
    
    for (int i = 0; i < n; i++)
    {
        string tempsmall = a[i]; // go through each element, assume the first string is the smallest
        for (int i1 = i + 1; i1 < n; i1++) // find each element an position after
        {
            if (tempsmall > a[i1]) // if an even smaller element is met
            {
                tempsmall = a[i1];
                a[i1] = a[i];
                a[i] = tempsmall; // swap the string position
            }
        }
    }
    for (int i = 0; i < n; i++)
    {
        if (a[i] >= separator) // find the string that is >= seperator and return the position
            return i;
    }
    return n;
}
