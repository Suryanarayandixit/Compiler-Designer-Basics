#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

// List of keywords
const char *keywords[] = {"int", "float", "if", "else", "while", "return", "for", "char", "void"};
int keywordCount = 9;

// Check if the given word is a keyword
int isKeyword(char *word) {
    for (int i = 0; i < keywordCount; i++) {
        if (strcmp(word, keywords[i]) == 0)
            return 1;
    }
    return 0;
}

// Main lexical analyzer
void lexicalAnalyzer(FILE *fp) {
    char ch, buffer[50];
    int i = 0;

    while ((ch = fgetc(fp)) != EOF) {
        // If character is alphabet or underscore (start of identifier/keyword)
        if (isalpha(ch) || ch == '_') {
            buffer[i++] = ch;
            while (isalnum(ch = fgetc(fp)) || ch == '_') {
                buffer[i++] = ch;
            }
            buffer[i] = '\0';
            i = 0;
            if (isKeyword(buffer))
                printf("<KEYWORD, %s>\n", buffer);
            else
                printf("<IDENTIFIER, %s>\n", buffer);
            ungetc(ch, fp); // Put back the last read character
        }
        // If character is an operator
        else if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '=' ||
                 ch == '<' || ch == '>' || ch == '!' || ch == '&' || ch == '|') {
            printf("<OPERATOR, %c>\n", ch);
        }
        // If character is a number
        else if (isdigit(ch)) {
            buffer[i++] = ch;
            while (isdigit(ch = fgetc(fp))) {
                buffer[i++] = ch;
            }
            buffer[i] = '\0';
            i = 0;
            printf("<NUMBER, %s>\n", buffer);
            ungetc(ch, fp);
        }
    }
}

int main() {
    FILE *fp;
    char filename[50];

    printf("Enter the input file name: ");
    scanf("%s", filename);

    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error: Cannot open file %s\n", filename);
        exit(0);
    }

    printf("Lexical Analysis Output:\n");
    lexicalAnalyzer(fp);

    fclose(fp);
    return 0;
}

