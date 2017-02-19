#include "VM.h"
#include "opcode.h"
#include <cassert>

char VM::interpret(char bytecode[], size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        Instruction opcode = static_cast<Instruction>(bytecode[i]);
        switch (opcode)
        {
        case OPCODE_NUM:
            push(bytecode[++i]);
            break;
        case OPCODE_ADD:
        {
            char a = pop();
            char b = pop();
            char value = a + b;
            push(value);
        }
            break;
        case OPCODE_SUB:
        {
            char a = pop();
            char b = pop();
            char value = a - b;
            push(value);
        }
            break;
        case OPCODE_DIV:
        {
            char a = pop();
            char b = pop();
            char value = a / b;
            push(value);
        }
            break;
        case OPCODE_MUL:
        {
            char a = pop();
            char b = pop();
            char value = a * b;
            push(value);
        }
            break;
        default:
            assert(false);
            break;
        }
    }

    return pop();
}

char VM::pop()
{
    if (StackIndex_ > 0)
    {
        return Stack_[--StackIndex_];
    }
    else if (0 == StackIndex_)
        return Stack_[0];

    assert(false);
    return 0;
}

void VM::push(char c)
{
    Stack_[StackIndex_++] = c;
}

int VM::add(int lhs, int rhs)
{
    return lhs + rhs;
}

int VM::sub(int lhs, int rhs)
{
    return lhs - rhs;
}

int VM::div(int lhs, int rhs)
{
    return lhs / rhs;
}

int VM::mul(int lhs, int rhs)
{
    return lhs * rhs;
}
