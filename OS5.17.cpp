#include <windows.h>
#include <iostream>

void SpawnNode(int level) {
    if (level > 2) return;
    std::cout << "Process Tree Node at level: " << level << " PID: " << GetCurrentProcessId() << std::endl;
    Sleep(200);
}

int main() {
    std::cout << "Building Process Tree Root...\n";
    SpawnNode(0);
    SpawnNode(1);
    SpawnNode(2);
    std::cout << "Process tree execution completed.\n";
    return 0;
}