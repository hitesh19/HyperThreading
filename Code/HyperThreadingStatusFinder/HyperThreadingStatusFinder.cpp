// HyperThreadingStatusFinder.cpp : Defines the entry point for the console application.
// Thanks to smswam for the same(https://github.com/smswam)

#include "stdafx.h"
#include <iostream>

using namespace std;

void cpuID(unsigned i, unsigned regs[4]) {
#ifdef _WIN32
	__cpuid((int *)regs, (int)i);

#else
	asm volatile
		("cpuid" : "=a" (regs[0]), "=b" (regs[1]), "=c" (regs[2]), "=d" (regs[3])
			: "a" (i), "c" (0));
	// ECX is set to zero for CPUID function 4
#endif
}

int main()
{
	unsigned regs[4];

	// Get vendor
	char vendor[12];
	cpuID(0, regs);
	((unsigned *)vendor)[0] = regs[1]; // EBX
	((unsigned *)vendor)[1] = regs[3]; // EDX
	((unsigned *)vendor)[2] = regs[2]; // ECX

	string cpuVendor = string(vendor, 12);
	// Get CPU features
	cpuID(1, regs);
	unsigned cpuFeatures = regs[3]; // EDX

	// Logical core count per CPU
	cpuID(1, regs);
	unsigned logical = (regs[1] >> 16) & 0xff; // EBX[23:16]
	
	unsigned cores = logical;

	if (cpuVendor == "GenuineIntel") {
		// Get DCP cache info
		cpuID(4, regs);
		cores = ((regs[0] >> 26) & 0x3f) + 1; // EAX[31:26] + 1
	}
	else if (cpuVendor == "AuthenticAMD") {
		// Get NC: Number of CPU cores - 1
		cpuID(0x80000008, regs);
		cores = ((unsigned)(regs[2] & 0xff)) + 1; // ECX[7:0] + 1
	}

	// Detect hyper-threads  
	bool hyperThreads = cpuFeatures & (1 << 28) && cores < logical;
	cout << "  hyper-threads : " << (hyperThreads ? "true" : "false") << endl;
	if (hyperThreads) {
		cores /= 2;
		logical /= 2;
	}
	cout << "  true cpu cores: " << cores << endl;
	cout << "  logical cores : " << logical;

	int a;
	cin >> a;
    return 0;
}

