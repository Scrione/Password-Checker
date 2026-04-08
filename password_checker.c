#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEN 200
#define SPECIAL_CHARS "!@#$%^&*()-_=+[]{}|;:'\",.<>?/`~"

// Includes at least one uppercase
int has_upper(const char *s) {
    while (*s) {
        if (isupper((unsigned char)*s)) return 1;
        s++;
    }
    return 0;
}

// Includes at least one lowercase
int has_lower(const char *s) {
    while (*s) {
        if (islower((unsigned char)*s)) return 1;
        s++;
    }
    return 0;
}

// Includes at least one digit
int has_digit(const char *s) {
    while (*s) {
        if (isdigit((unsigned char)*s)) return 1;
        s++;
    }
    return 0;
}

// Includes at least one special character
int has_special(const char *s) {
    while (*s) {
        if (strchr(SPECIAL_CHARS, *s)) return 1;
        s++;
    }
    return 0;
}


int main() {
    // Some assistance from ChatGPT
    // Opens pw.txt in read mode
    FILE *fin = fopen("pw.txt", "r");
    // Opens and create report.txt in write mode
    FILE *fout = fopen("report.txt", "w");

    if (!fin) {
        printf("Error: unable to open pw.txt\n");
        return 1;
    }
    if (!fout) {
        printf("Error: could not create report.txt\n");
        fclose(fin);
        return 1;
    }


    char line[MAX_LEN];
    int strongCount = 0, weakCount = 0;

    while (fgets(line, sizeof(line), fin)) {
        // Remove newline
        line[strcspn(line, "\r\n")] = '\0';

        int length = strlen(line);
        int hasUpper = has_upper(line);
        int hasLower = has_lower(line);
        int hasDigit = has_digit(line);
        int hasSpecialChar = has_special(line);

        int isStrong = 1;
       
        // Identifies password that needs to meet the requirement
        if (length < 8) isStrong = 0;
        if (!hasUpper) isStrong = 0;
        if (!hasLower) isStrong = 0;
        if (!hasDigit) isStrong = 0;
        if (!hasSpecialChar) isStrong = 0;
        
        if (isStrong) {
            fprintf(fout, "Password: %s - STRONG\n", line);
            strongCount++; // Add a count to the amount of passwords that are Strong
        } else {
            fprintf(fout, "Password: %s - WEAK\n", line);
            if (length < 8)
                fprintf(fout, "Missing: Minimum Length\n");
            if (!hasUpper)
                fprintf(fout, "Missing: Uppercase Letter\n");
            if (!hasLower)
                fprintf(fout, "Missing: Lowercase Letter\n");
            if (!hasDigit)
                fprintf(fout, "Missing: Number\n");
            if (!hasSpecialChar)
                fprintf(fout, "Missing: Special Character\n");
            weakCount++; // Add a count to the amount of passwords that are Weak.
        }
    }

    fclose(fin);
    fclose(fout);

    // Print summary
    printf("Total Strong Passwords: %d\n", strongCount);
    printf("Total Weak Passwords: %d\n", weakCount);

    return 0;
}
