#include <algorithm>

#include <iostream>

#include <vector>

#include <cmath>

#include <numeric>

 

int max_analog_dta = 300;  // max analog data

int min_analog_dta = 100;  // min analog data

int static_analog_dta = 0; // static analog data

std::vector<int> nList;

std::vector<int> sList;

 

double getAverage(std::vector<int> v)

{

    if (v.empty())

    {

        return 0;

    }

    return std::accumulate(v.begin(), v.end(), 0.0) / v.size();

}

 

bool isMonotonicIncreasing(std::vector<int> &numberList)

{

    for (int i = 1; i < numberList.size(); ++i)

    {

        if (numberList[i] < numberList[i - 1])

        {

            return false;

        }

    }

    return true;

}

 

bool isMonotonicDecreasing(std::vector<int> &numberList)

{

    for (int i = 1; i < numberList.size(); ++i)

    {

        if (numberList[i] > numberList[i - 1])

        {

            return false;

        }

    }

    return true;

}

 

bool isMonotonic(std::vector<int> &numberList)

{

    return isMonotonicIncreasing(numberList) || isMonotonicDecreasing(numberList);

}

 

int checkIfSmooth(std::vector<int> &numberList, int length)

{

    if (numberList.size() < length)

        return 0;

    int max = *std::max_element(numberList.begin(), numberList.end());

    int min = *std::min_element(numberList.begin(), numberList.end());

 

    if (isMonotonic(numberList))

        return 0;

 

    return max - min;

}

 

// get analog value

int getAnalog(int pin)

{

    long sum = 0;

 

    for (int i = 0; i < 32; i++)

    {

        sum += analogRead(pin);

    }

 

    int dta = sum >> 5;

 

    max_analog_dta = dta > max_analog_dta ? dta : max_analog_dta; // if max data

    min_analog_dta = min_analog_dta > dta ? dta : min_analog_dta; // if min data

 

    return sum >> 5;

}

 

void setup()

{

    Serial.begin(9600);

    while (!Serial)

        ;

}

 

int level = 0;

 

void loop()

{

    // std::vector<int> nList;

    int val = getAnalog(A0); // get Analog value

 

    nList.push_back(val);

    sList.push_back(checkIfSmooth(nList, 5));

 

    if (nList.size() > 5)

        nList.erase(std::next(nList.begin()));

 

    if (sList.size() > 5)

        sList.erase(std::next(sList.begin()));

 

    level += (getAverage(sList) * 100 - level) * 0.1f;

 

    Serial.print(analogRead(A0));

    Serial.print(", ");

    Serial.print(val);

    Serial.print(", ");

    Serial.println(level);

 

    delay(10);

}
