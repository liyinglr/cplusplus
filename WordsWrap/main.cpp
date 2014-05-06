#include <iostream>
#include <iomanip>
using namespace std;

#include "StringWordWrap.h"


// Driver program to test above functions
int main()
{
    StringWordWrap sww("The result would be the observed gradual change in fibril orientation!Gradual change is preferable to sudden,large");

    string txt;
    sww.StartWrap(20,txt);

    cout<<txt;
    return 0;
}

