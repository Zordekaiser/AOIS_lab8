#include <iostream>
#include <array>
#include <random>
#include <string>
#include <time.h>
#include <vector>
using namespace std;


array<array<bool, 16>, 16> filler() {
    array<array<bool, 16>, 16> result;
    srand(time_t(NULL));
    for (int first_iterator = 0; first_iterator < 16; first_iterator++) {
        for (int second_iterator = 0; second_iterator < 16; second_iterator++) {
            result[first_iterator][second_iterator] = rand() % 2;
        }
    }
    return result;
}
array<bool, 16> getColumn(array<array<bool, 16>, 16> data, int index)
{
    array<bool, 16> result;

    for ( int i = 0; i < 16; i++)
    {
        result[i] = data[i][index];
    }
    return result;
}

bool myConjunction(bool data1, bool data2)
{
    if(data1 == data2 == true)
    {
        return true;
    }
    return false;
}

bool myDisjunction(bool data1, bool data2)
{
    if (data1 == true or data2 == true)
    {
        return true;
    }
    return false;
}

bool negative(bool data1)
{
    if(data1)
    {
        return false;
    }
    return true;
}

array<bool, 16> function4(array<array<bool, 16>, 16> data1, int index1, int index2)
{
    array<bool, 16> result, col1 = getColumn(data1, index1), col2 = getColumn(data1, index2);

    for (int i = 0; i < 16; i++)
    {
        result[i] = myConjunction(negative(col1[i]), col2[i]);
    }

    return result;
}

array<bool, 16> function6(array<array<bool, 16>, 16> data1, int index1, int index2)
{
    array<bool, 16> result, col1 = getColumn(data1, index1), col2 = getColumn(data1, index2);

    for (int i = 0; i < 16; i++)
    {
        result[i] = myDisjunction(myConjunction(negative(col1[i]), col2[i]), myConjunction(negative(col2[i]), col1[i]));
    }

    return result;
}

array<bool, 16> function9(array<array<bool, 16>, 16> data1, int index1, int index2)
{
    array<bool, 16> result, col1 = getColumn(data1, index1), col2 = getColumn(data1, index2);

    for (int i = 0; i < 16; i++)
    {
        result[i] = myDisjunction(myConjunction(col1[i], col2[i]), myConjunction(negative(col2[i]), negative(col1[i])));
    }

    return result;
}

array<bool, 16> function11(array<array<bool, 16>, 16> data1, int index1, int index2)
{
    array<bool, 16> result, col1 = getColumn(data1, index1), col2 = getColumn(data1, index2);

    for (int i = 0; i < 16; i++)
    {
        result[i] = myDisjunction(col1[i], negative(col2[i]));
    }

    return result;
}

array<array<bool, 16>, 16> sdvig(array<array<bool, 16>, 16> data)
{
    array<array<bool, 16>, 16> result;
    for (int i = 0; i < 16; i++)
    {
        for(int j = i; j < 16; j++)
        {
            result[j - i][i] = data[j][i];
        }
        for (int j = 0; j < i; j++)
        {
            result[16 - i + j][i] = data[j][i];
        }
    }
    return result;
}

vector<int> find(array<array<bool, 16>, 16> data, array<bool, 3> v)
{
    vector<int> result;
    for (int i = 0; i < 16; i++)
    {
        bool flag1 = false, flag2 = false;
        for(int j = 0; j < 3; j++)
        {
            if(j == 0 and v[j] == data[j][i])
            {
                flag1 = true;
            }
            if(j == 1 and v[j] == data[j][i] and flag1)
            {
                flag2 = true;
            }
            if(j == 2 and v[j] == data[j][i] and flag1 and flag2)
            {
                result.push_back(i);
                flag1 = false;
                flag2 = false;
            }
        }
    }
    return result;
}
array<bool, 16> summ(array<bool, 16> data)
{
    bool povish = false;
    for (int i = 0; i < 4; i++)
    {
        if(data[6 - i] == true and data[10 - i] == true)
        {
            if(povish == true)
            {
                data[15 - i] = true;
            }
            else
            {
                data[15 - i] = false;
            }
            povish = true;
        }
        if ((data[6 - i] == false and data[10 - i] == true) or (data[6 - i] == true and data[10 - i] == false))
        {
            if (povish == true)
            {
                data[15 - i] = false;
                povish = true;
            }
            else
            {
                data[15 - i] = true;
                povish = false;
            }
        }
        if(data[6 - i] == false and data[10 - i] == false)
        {
            if (povish == true)
            {
                data[15 - i] = true;
            }
            else
            {
                data[15 - i] = false;
            }
            povish = false;
        }
    }
    if(povish)
    {
        data[11] = true;
    }
    return data;
}

void viewArray(array<bool, 16> data)
{
    for (int sign = 0; sign < 16; sign++) {
        cout << data[sign] << " ";
    }
    cout << endl;
}

int main()
{
    string user_input;
    int key, input1, input2, input3;
    array<array<bool, 16>, 16> full_table = filler(), sdvig_table = sdvig(full_table);
    for (int variation = 0; variation < full_table.size(); variation++) {
        viewArray(full_table[variation]);
    }
    cout << "-------------------------------\n";
    for (int variation = 0; variation < full_table.size(); variation++) {
        viewArray(sdvig_table[variation]);
    }
    cout << "-------------------------------\n";
    cout << "1 - f4\n2 - f6\n3 - f9\n4 - f11\n5 - input V and view summ: ";
    cin >> key;
    switch (key)
    {
    case 1:
        cout << "input index of first col: ";
        cin >> input1;
        cout << "input index of second col: ";
        cin >> input2;
        viewArray(function4(sdvig_table, input1, input2));
        break;
    case 2:
        cout << "input index of first col: ";
        cin >> input1;
        cout << "input index of second col: ";
        cin >> input2;
        viewArray(function6(sdvig_table, input1, input2));
        break;
    case 3:
        cout << "input index of first col: ";
        cin >> input1;
        cout << "input index of second col: ";
        cin >> input2;
        viewArray(function9(sdvig_table, input1, input2));
        break;
    case 4:
        cout << "input index of first col: ";
        cin >> input1;
        cout << "input index of second col: ";
        cin >> input2;
        viewArray(function11(sdvig_table, input1, input2));
        break;
    case 5:
        cout << "input 1 bool: ";
        cin >> input1;
        cout << "input 2 bool: ";
        cin >> input2;
        cout << "input 3 bool: ";
        cin >> input3;
        array<bool, 3> input = { (bool)input1, (bool)input2, (bool)input3 };
        vector<int> bufferVecor = find(sdvig_table, input);
        for (int i = 0; i < bufferVecor.size(); i++)
        {
            cout << "     |       |       |\n";
            viewArray(getColumn(sdvig_table, bufferVecor.at(i)));
            cout << " |\n(!)\n";
            viewArray(summ(getColumn(sdvig_table, bufferVecor.at(i))));
            cout << "-------------------------------\n";
        }
        break;
    }
}

