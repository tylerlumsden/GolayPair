#include<stdio.h>
#include<stdlib.h>

int logbase2(unsigned long x);

long unsigned power(int base, int x);

void printbinary(unsigned long x, int totalbits);

int main(int argc, char * argv[]) {
    if(argc != 4) {
        return 0;
    }

    int ptable = atoi(argv[1]);
    int memaddr = atoi(argv[2]);
    int psize = atoi(argv[3]);

    if(ptable != 1 && ptable != 2) {
        printf("error: ptable incorrect value\n");
        return 0;
    } 

    if(memaddr > 63 || memaddr < 8) {
        printf("error: memaddr incorrect value\n");
        return 0;
    }

    if(psize != 1 && psize != 2 && psize != 4 && psize != 8 && psize != 16 && psize != 32 && psize != 64 && psize != 128 && psize != 256 && psize != 512) {
        printf("error: psize incorrect value\n");
        return 0;
    }

    //check if args are consistent
    int exponent = logbase2(psize) + 10;

    if(memaddr < exponent) {
        printf("Error: Page Size cannot be larger than total memory.\n");
        return 0;
    }

    if(memaddr < 10) {
        printf("Memory Size: %d Bytes\n", 1 << memaddr % 10);
        printf("Error: Memory Size cannot be less than 1KB.\n");
        return 0;
    } else if(memaddr < 20) {
        printf("Memory Size:                             %dKB\n", 1 << memaddr % 10);
    } else if(memaddr < 30) {
        printf("Memory Size:                             %dMB\n", 1 << memaddr % 10);
    } else {
        printf("Memory Size:                             %dGB\n", 1 << memaddr % 10);
    }

    int totalpage = power(2, memaddr - exponent);
    int ptablesize = totalpage * 4; 
    int pbytesize = power(2,exponent);
    int pagetableentries = pbytesize / 4;

    if(ptable == 1) {
    printf("Total number of pages:                   %d\n", totalpage);
    printf("Total Number of Page Table Entries:      %d\n", totalpage);
    printf("Size of Page Table:                      %d\n", ptablesize);
    printf("Number of bits for VPN:                  %d\n", memaddr - exponent);
    printf("Number of bits for page offset:          %d\n", exponent);

        while(1) {
            unsigned long vaddr;
            printf("\ndecimal virtual address: ");
            scanf("%lu", &vaddr);

            if(logbase2(vaddr) > memaddr) {
                printf("%lu", vaddr);
                printf("Error: vaddr is too large for memory space.\n");
                continue;
            }

            int vpndigits = logbase2(totalpage);
            unsigned long vpn = vaddr;
            vpn = vpn >> memaddr - vpndigits;

            int pdindex = vaddr >> memaddr - logbase2(ptablesize / pbytesize);

            int poffset = vaddr - (vpn << memaddr - vpndigits);
            
            printf("VPN of the address in decimal:           %d\n", vpn);
            printf("page offset of the address in decimal:   %d\n", poffset);

            int ptindex = vaddr >> (memaddr - (logbase2(ptablesize / pbytesize) + logbase2(pagetableentries)));
            
            int removebits = ptindex >> logbase2(pagetableentries);
            removebits = removebits << logbase2(pagetableentries);

            ptindex = ptindex - removebits;

            printf("the input address in binary:             ");
            printbinary(vaddr, memaddr);
            printf("VPN of the address in binary:            ");
            printbinary(vpn, memaddr - exponent);
            printf("page offset of the address in binary:    ");
            printbinary(poffset, exponent);
        }
    }

    if(ptable == 2) {
        printf("Total number of pages:                   %d\n", totalpage);
        printf("Total Number of Page Table Entries:      %d\n", totalpage);
        printf("Size of Page Table:                      %d\n", ptablesize);
        printf("Number of bits for VPN:                  %d\n", memaddr - exponent);
        printf("Number of bits for page offset:          %d\n", exponent);
        printf("Number of PTE in a page of page table:   %d\n", pagetableentries);
        printf("Number of pages in a page table:         %d\n", ptablesize / pbytesize);
        printf("Number of bits for page directory index: %d\n", logbase2(ptablesize) - logbase2(pbytesize));
        printf("Number of bits for page table index:     %d\n", logbase2(pagetableentries));
        while(1) {
            unsigned long vaddr;
            printf("\ndecimal virtual address: ");
            scanf("%lu", &vaddr);
            printf("\n");

            if(logbase2(vaddr) > memaddr) {
                printf("%lu", vaddr);
                printf("Error: vaddr is too large for memory space.\n");
                continue;
            }

            int vpndigits = logbase2(totalpage);
            unsigned long vpn = vaddr;
            vpn = vpn >> memaddr - vpndigits;

            int pdindex = vaddr >> memaddr - logbase2(ptablesize / pbytesize);

            int poffset = vaddr - (vpn << memaddr - vpndigits);
            
            printf("VPN of the address in decimal:           %d\n", vpn);
            printf("page offset of the address in decimal:   %d\n", poffset);
            
            printf("page directory index in decimal:         %d\n", pdindex);

            int ptindex = vaddr >> (memaddr - (logbase2(ptablesize / pbytesize) + logbase2(pagetableentries)));
            
            int removebits = ptindex >> logbase2(pagetableentries);
            removebits = removebits << logbase2(pagetableentries);

            ptindex = ptindex - removebits;

            printf("page table index in decimal:             %d\n", ptindex);

            printf("the input address in binary:             ");
            printbinary(vaddr, memaddr);
            printf("VPN of the address in binary:            ");
            printbinary(vpn, memaddr - exponent);
            printf("page offset of the address in binary:    ");
            printbinary(poffset, exponent);
            printf("page directory index in binary:          ");
            printbinary(pdindex, logbase2(ptablesize / pbytesize));
            printf("page table index in binary:              ");
            printbinary(ptindex, logbase2(pagetableentries));
        }
    }


}

void printbinary(unsigned long x, int totalbits) {
    char buf[100000];
    itoa(x, buf, 2);
    int i;
    for(i = 0; buf[i] != 0; i++); 

    int leading = totalbits - i;

    for(int j = 0; j < leading; j++) {
        printf("0");
    }

    printf("%s\n", buf);
}

int logbase2(unsigned long x) {
    int exponent = 0;

    while(x != 1) {
         x /= 2;
         exponent++;
    }

    return exponent;
}

long unsigned power(int base, int x) {
    int basetemp = base;
    for(int i = 1; i < x; i++) {
        base *= basetemp;
    }

    return base;
}