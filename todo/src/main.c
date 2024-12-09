#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static char* REMINDERS_FILE;

void set_reminders_file_path() {
    char *home_directory = getenv("HOME");
    if (home_directory == NULL) {
        printf("Error: HOME environment variable is not set\n");
        exit(1);
    }

    char *reminders_path = strncat(home_directory, "/.todo", 7);

    REMINDERS_FILE = reminders_path;
}

int add_reminder(char* reminder) {
    return 0;
}

int delete_reminder(char* reminder_id) {
    return 0;
}

int help_page(char* executable_name) {
    printf("USAGE:\n");
    printf("  %s [OPTIONS] [ARGS]\n\n", executable_name);
    printf("OPTIONS:\n");
    printf("  -a <reminders>\n");
    printf("     Add <reminder> to the list of the reminders\n");
    printf("  -d <index> [Not implemented yet]\n");
    printf("     Remove the <index>-th reminder from the list\n");
    return 0;
}

int main(int argc, char* argv[]) {

    set_reminders_file_path();

    int opt;
    while ((opt = getopt(argc, argv, "ha:d:")) != -1)
    {
        switch (opt) {
            case 'h': return help_page(argv[0]);
            case 'a': return add_reminder(optarg);
            case 'd': return delete_reminder(optarg);
            default: printf("Type: %s -h for the help page\n", argv[0]); return 1;
        }
    }
    return 0;
}
