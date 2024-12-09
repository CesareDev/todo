#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[]) {

    int opt;
    while ((opt = getopt(argc, argv, "ha:c")) != -1)
    {
        switch (opt) {
            case 'h': printf("Usage: %s -a <argument>\n", argv[0]); return 0;
            case 'a': printf("Argument: %s\n", optarg); return 0;
            case 'c': printf("Option c\n"); return 0;
            default: printf("Type: %s -h for the help page\n", argv[0]); return 1;
        }
    }
    return 0;
}
