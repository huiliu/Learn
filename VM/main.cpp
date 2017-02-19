#include "opcode.h"
#include "VM.h"
#include <iostream>
#include <memory>

typedef std::shared_ptr<VM> VM_SP;

void
case01(VM_SP spVM)
{
    char bytecode[] = {
        OPCODE_NUM,
        10,
        OPCODE_NUM,
        1,
        OPCODE_ADD,
        OPCODE_NUM,
        4,
        OPCODE_ADD,
        OPCODE_NUM,
        4,
        OPCODE_MUL,
        OPCODE_NUM,
        120,
        OPCODE_DIV
    };

    int x = spVM->interpret(bytecode, sizeof(bytecode));
    std::cout << x << std::endl;
}

int main()
{
    VM_SP spVM(new VM());

    case01(spVM);
    return 0;
}

