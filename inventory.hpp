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
    Item(std::string x, int y)
    {
        name = x;
        icon = y;
    }
};

class Inventory
{
    public:
    Stack stacks[18] = 
    {
        Stack(-1,0),Stack(-1,0),Stack(-1,0),Stack(-1,0),Stack(-1,0),Stack(-1,0),
        Stack(-1,0),Stack(-1,0),Stack(-1,0),Stack(-1,0),Stack(-1,0),Stack(-1,0),
        Stack(-1,0),Stack(-1,0),Stack(-1,0),Stack(-1,0),Stack(-1,0),Stack(-1,0)
    };
    
    void AddItem(int type, int amount)
    {
        bool done = false;
        for(int i = 0; i < sizeof(stacks)/sizeof(stacks[0]); i++)
        {
            if (stacks[i].type == type && !done)
            {
                int fits = 9 - stacks[i].amount;
                stacks[i].amount = std::clamp(amount + stacks[i].amount,0,9);
                amount -= fits;
                done = amount < 1;
            }
        }

        if(!done)
        {
            done = false;
            for(int i = 0; i < sizeof(stacks)/sizeof(stacks[0]); i++)
            {
                if (stacks[i].type == -1 && !done)
                {
                    stacks[i].type = type;
                stacks[i].amount = std::clamp(amount + stacks[i].amount,0,9);
                amount -= 9;
                done = amount < 1;
                }
            }
        }
    }

};

Item itemDatabase[4] = 
{
    Item("Poppy seed",0),
    Item("Blueberries",1),
    Item("Bay leaf",2),
    Item("Agrimony",3),
};