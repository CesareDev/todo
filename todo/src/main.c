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
    FILE *reminder_file = fopen(REMINDERS_FILE, "r");
    int index = atoi(reminder_id);
    if (index == 0) {
        printf("Error: %s not a valid index\n", reminder_id);
        fclose(reminder_file);
        return 1;
    }
    
    fseek(reminder_file, 0, SEEK_END);
    long file_size = ftell(reminder_file);
    char *buffer = (char *)calloc(file_size, 1);
    rewind(reminder_file);
    fread(buffer, 1, file_size, reminder_file);
    fclose(reminder_file);

    FILE *reminder_file_new = fopen(REMINDERS_FILE, "w");
    
    char *line = strtok(buffer, "\n");
    int current_index = 1;
    while (line != NULL) {
        if (current_index != index) {
            fprintf(reminder_file_new, "%s\n", line);
        }
        line = strtok(NULL, "\n");
        current_index++;
    }

    fclose(reminder_file_new);
    free(buffer);
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

int help_page(char* executable_name) {
    printf("USAGE:\n");
    printf("  %s [OPTIONS] [ARGS]\n\n", executable_name);
    printf("OPTIONS:\n");
    printf("  -a <reminders>\n");
    printf("     Add <reminder> to the list of the reminders. The reminder must be at most 256 character\n");
    printf("  -d <index>\n");
    printf("     Remove the <index>-th reminder from the list\n");
    printf("  -l\n");
    printf("     List all the reminders\n");
    printf("  -c\n");
    printf("     Clear all the reminders\n");
    return 0;
}

int main(int argc, char* argv[]) {

    if (argc == 1) {
        printf("Type: %s -h for the help page\n", argv[0]);
        return 1;
    }

    set_reminders_file_path();

    int opt;
    while ((opt = getopt(argc, argv, "ha:d:lc")) != -1)
    {
        switch (opt) {
            case 'h': return help_page(argv[0]);
            case 'a': return add_reminder(optarg);
            case 'd': return delete_reminder(optarg);
            case 'l': return list_reminders();
            case 'c': return clear_reminders();
            default: printf("Type: %s -h for the help page\n", argv[0]); return 1;
        }
    }
    return 0;
}
