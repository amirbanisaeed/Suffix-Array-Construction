#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <utility>

using std::cin;
using std::cout;
using std::endl;
using std::make_pair;
using std::pair;
using std::string;
using std::vector;
using namespace std;

// Build suffix array of the string text and
// return a vector result of the same length as the text
// such that the value result[i] is the index (0-based)
// in text where the i-th lexicographically smallest
// suffix of text starts.

vector<int> SortCharacters(const string& text)
{
    vector<int> order(text.length());
    vector<int> count(5);
    for (int i = 0; i < count.size(); i++)
    {
        count[i] = 0;
    }

    for (int i = 0; i < text.length(); i++)
    {
        switch (text[i])
        {
        case '$':
            count[0]++;
            break;
        case 'A':
            count[1]++;
            break;
        case 'C':
            count[2]++;
            break;
        case 'G':
            count[3]++;
            break;
        case 'T':
            count[4]++;
            break;
        default:
            break;
        }
    }

    for (int i = 0; i < count.size(); i++)
    {
        // cout << "Sort Char: "<<count[i] << endl;
    }

    for (int i = 1; i < count.size(); i++)
    {
        count[i] = count[i] + count[i - 1];
    }

    for (int i = 0; i < count.size(); i++)
    {
        //cout << "SUM Sort Char: " << count[i] << endl;
    }

    for (int i = text.size() - 1; i >= 0; i--)
    {
        switch (text[i])
        {
        case '$':
            count[0] = count[0] - 1;
            order[count[0]] = i;
            break;
        case 'A':
            count[1] = count[1] - 1;
            order[count[1]] = i;
            break;
        case 'C':
            count[2] = count[2] - 1;
            order[count[2]] = i;
            break;
        case 'G':
            count[3] = count[3] - 1;
            order[count[3]] = i;
            break;
        case 'T':
            count[4] = count[4] - 1;
            order[count[4]] = i;
            break;
        default:
            break;
        }
    }

    for (int i = 0; i < order.size(); i++)
    {
        //cout << "Order: Sort Char: " << order[i] << endl;
    }

    return order;

}


vector<int> ComputeCharClasses(const string& text, vector<int>& order)
{
    vector<int> class_text(text.size());
    class_text[order[0]] = 0;

    for (int i = 1; i < text.length(); i++)
    {
        if (text[order[i]] != text[order[i - 1]])
        {
            class_text[order[i]] = class_text[order[i - 1]] + 1;

        }
        else
        {
            class_text[order[i]] = class_text[order[i - 1]];
        }

    }

    for (int i = 0; i < class_text.size(); i++)
    {
        //cout << "Class " << class_text[i] << endl;
    }


    return class_text;
}

vector<int> SortDoubled(const string& text, int L, vector<int>& order, vector<int>& class_text)
{

    //cout << "Enter SortDoubled" << endl;

    vector<int> new_order(text.length());
    vector<int> count(text.length());
    for (int i = 0; i < count.size(); i++)
    {
        count[i] = 0;
    }

    for (int i = 0; i < text.length(); i++)
    {
        count[class_text[i]] = count[class_text[i]] + 1;
    }


    for (int i = 1; i < text.length(); i++)
    {
        count[i] = count[i] + count[i - 1];
    }

    for (int i = 0; i < text.length(); i++)
    {
        //cout << "SSortDouble " << i  << "Count " << count[i] << endl;
    }

    int start;
    int cl;
    for (int i = text.length() - 1; i >= 0; i--)
    {

        start = (order[i] - L + text.length()) % text.length();
        //cout << "Start " << start << endl;
        cl = class_text[start];
        //cout << "cl: " << cl << endl;
        count[cl] = count[cl] - 1;
        new_order[count[cl]] = start;

        //cout << "i: " << i <<"Count: " << count[cl] << "  new_order[count[cl]]" << new_order[count[cl]] << endl;

    }

    for (int i = 0; i < new_order.size(); i++)
    {
        //cout << "SortDoubledd " << new_order[i] << endl;
    }

    return new_order;
}

vector<int> UpdateClasses(vector<int>& new_Order, vector<int>& Class_Text, int L)
{
    //cout << "Enter Update" << endl;
    int n = new_Order.size();
    vector<int> new_Class(n);
    new_Class[new_Order[0]] = 0;
    int cur = 0, prev = 0, mid = 0, midprev = 0;
    for (int i = 1; i < n; i++)
    {
        cur = new_Order[i];
        prev = new_Order[i - 1];
        mid = cur + L;
        midprev = (prev + L) % n;

        if (Class_Text[cur] != Class_Text[prev] || Class_Text[mid] != Class_Text[midprev])
        {
            new_Class[cur] = new_Class[prev] + 1;
        }
        else
        {
            new_Class[cur] = new_Class[prev];
        }


    }

    for (int i = 0; i < new_Class.size(); i++)
    {
        //cout << new_Class[i] << endl;
    }


    return new_Class;
}

vector<int> BuildSuffixArray(const string& text) {
    vector<int> result;
    vector<int> Order;
    vector<int> Text_Class;

    Order = SortCharacters(text);
    Text_Class = ComputeCharClasses(text, Order);
    int L = 1;

    while (L < text.length())
    {
        Order = SortDoubled(text, L, Order, Text_Class);
        Text_Class = UpdateClasses(Order, Text_Class, L);

        L = 2 * L;
    }

    // Implement this function yourself
    return Order;
}

int main() {
    string text;
    cin >> text;
    vector<int> suffix_array = BuildSuffixArray(text);
    for (int i = 0; i < suffix_array.size(); ++i) {
        cout << suffix_array[i] << ' ';
    }
    cout << endl;
    return 0;
}
