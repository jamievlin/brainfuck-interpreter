#include <vector>
#include <iostream>
#include <string>
#include <set>
#include <fstream>

using std::vector;
using std::cout;
using std::cin;

typedef vector<char> vchar;

vchar::iterator findInstrAfterClosingBrack(vchar& instructions, vchar::iterator const& ptr);
vchar::iterator findInstrAfterOpenBrack(vchar& instructions, vchar::iterator const& ptr);

int main(int argc, char* argv[])
{
    vchar data;
    data.push_back(0);
    vchar instructions;

    unsigned int data_addr = 0;

    std::ifstream bfFile(argv[1]);

    std::set<char> validCommands {'-', '+', '<', '>', '.', ',', '[', ']'};

    while(!bfFile.eof())
    {
        char inst;
        bfFile >> inst;

        if (validCommands.find(inst) != validCommands.end())
        {
            instructions.push_back(inst);
        }
    }
    bfFile.close();

    auto instr_ptr = instructions.begin();

    while (instr_ptr != instructions.end())
    {
        if (*instr_ptr == '>')
        {
            data_addr++;
            if (data.size() >= data_addr)
            {
                data.push_back(0);
            }
        }
        else if (*instr_ptr == '<')
        {
            data_addr--;
        }
        else if (*instr_ptr == '+')
        {
            data[data_addr]++;
        }
        else if (*instr_ptr == '-')
        {
            data[data_addr]--;
        }
        else if (*instr_ptr == '.')
        {
            std::cout << data[data_addr];
        }
        else if (*instr_ptr == ',')
        {
            // std::cout << "Input received.";
            std::cin >> data[data_addr];
        }
        else if (*instr_ptr == '[')
        {
            if (data[data_addr] == 0)
            {
                instr_ptr = findInstrAfterClosingBrack(instructions, instr_ptr);
                continue;
            }
        }
        else if (*instr_ptr == ']')
        {
            if (data[data_addr] != 0)
            {
                instr_ptr = findInstrAfterOpenBrack(instructions, instr_ptr);
                continue;
            }
        }

        instr_ptr++;
    }

    // std::cout << std::endl;
}

vchar::iterator findInstrAfterClosingBrack(vchar& instructions, vchar::iterator const& ptr)
{
    int depth = 1;
    auto curr_ptr = ptr + 1;

    if (*ptr != '[')
    {
        return instructions.end();
    }

    while (depth > 0 && curr_ptr != instructions.end())
    {
        if (*curr_ptr == '[')
        {
            depth++;
        }
        else if (*curr_ptr == ']')
        {
            depth--;
        }

        curr_ptr++;
    }

    if (depth != 0)
    {
        throw 1;
    }

    return curr_ptr;
}


vchar::iterator findInstrAfterOpenBrack(vchar& instructions, vchar::iterator const& ptr)
{
    int depth = 1;
    auto curr_ptr = ptr - 1;

    if (*ptr != ']')
    {
        return instructions.end();
    }

    auto ret_instruction = ptr + 1;

    while (depth > 0 && curr_ptr >= instructions.begin())
    {
        if (*curr_ptr == '[')
        {
            depth--;
            ret_instruction = curr_ptr + 1;
        }
        else if (*curr_ptr == ']')
        {
            depth++;
        }

        curr_ptr--;
    }

    if (depth != 0)
    {
        throw 1;
    }
    return ret_instruction;
}
