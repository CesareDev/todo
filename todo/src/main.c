#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_REMINDER_LENGTH 255

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
    FILE *reminder_file = fopen(REMINDERS_FILE, "a");
    if (strnlen(reminder, MAX_REMINDER_LENGTH) >= MAX_REMINDER_LENGTH) {
        printf("Error: The reminder must be at most 255 characters\n");
        fclose(reminder_file);
        return 1;
    }
    fprintf(reminder_file, "%s\n", reminder);
    fclose(reminder_file);
    return 0;
}

int delete_reminder(char* reminder_id) {
    FILE *reminder_file = fopen(REMINDERS_FILE, "a");
    unsigned long index = atoi(reminder_id);
    if (index == 0) {
        printf("Error: %s not a valid index\n", reminder_id);
        fclose(reminder_file);
        return 1;
    }
    fclose(reminder_file);
    return 0;
}

int list_reminders() {
    FILE *reminder_file = fopen(REMINDERS_FILE, "r");
    char reminder[MAX_REMINDER_LENGTH] = { 0 };
    unsigned long index = 1;
    while (fgets(reminder, MAX_REMINDER_LENGTH, reminder_file) != NULL) {
        printf("%lu: %s", index, reminder);
        index++;
    }
    fclose(reminder_file);
    return 0;
}

int clear_reminders() {
    FILE *reminder_file = fopen(REMINDERS_FILE, "w");
    fclose(reminder_file);
    return 0;
}

int help_page(FILE* reminder_file, char* executable_name) {
    printf("USAGE:\n");
    printf("  %s [OPTIONS] [ARGS]\n\n", executable_name);
    printf("OPTIONS:\n");
    printf("  -a <reminders>\n");
    printf("     Add <reminder> to the list of the reminders. The reminder must be at most 256 character\n");
    printf("  -d <index> [Not implemented yet]\n");
    printf("     Remove the <index>-th reminder from the list\n");
    printf("  -l\n");
    printf("     List all the reminders\n");
    printf("  -c\n");
    printf("     Clear all the reminders\n");
    fclose(reminder_file);
    return 0;
}

int main(int argc, char* argv[]) {

    if (argc == 1) {
        printf("Type: %s -h for the help page\n", argv[0]);
        return 1;
    }

    set_reminders_file_path();

    FILE *reminders_file = fopen(REMINDERS_FILE, "a");
    if (reminders_file == NULL) {
        printf("Error: Could not open or create the reminders file\n");
        return 1;
    }

    int opt;
    while ((opt = getopt(argc, argv, "ha:d:lc")) != -1)
    {
        switch (opt) {
            case 'h': return help_page(reminders_file, argv[0]);
            case 'a': return add_reminder(optarg);
            case 'd': return delete_reminder(optarg);
            case 'l': return list_reminders();
            case 'c': return clear_reminders();
            default: printf("Type: %s -h for the help page\n", argv[0]); return 1;
        }
    }
    return 0;
}
