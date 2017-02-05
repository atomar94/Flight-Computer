//Valve.cpp

#include "Valve.h"
#include <string>

using namespace std;

Valve::Valve(string name, bool norm_open)
{
    m_name = name;
    normal_open = norm_open;
}

bool Valve::is_actuated()
{
    return false;
}

bool Valve::actuate()
{
    return false;
}

bool Valve::is_normal_open()
{
    return normal_open;
}

string Valve::name()
{ 
    return m_name;
}
