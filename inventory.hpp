#include <bits/stdc++.h>

class Stack
{
    public:
    int type;
    int amount;
    Stack(int x, int y)
    {
        type = x;
        amount = y;
    }
};

class Item
{
    public:
    std::string name;
    int icon;
    std::string description;
    Item(std::string x, int y, std::string z)
    {
        name = x;
        icon = y;
        description = z;
    }
};

Item itemDatabase[1] = 
{
    Item("item",1,"just a test")
};