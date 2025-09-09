#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_TAG_LEN 64
#define MAX_STACK   128

typedef struct {
    char tags[MAX_STACK][MAX_TAG_LEN];
    int top;
} TagStack;

void init_stack(TagStack *s) {
    s->top = -1;
}

int push(TagStack *s, const char *tag) {
    if (s->top >= MAX_STACK - 1) return -1;
    s->top++;
    strncpy(s->tags[s->top], tag, MAX_TAG_LEN - 1);
    s->tags[s->top][MAX_TAG_LEN - 1] = '\0';
    return 0;
}

int pop(TagStack *s) {
    if (s->top < 0) return -1;
    s->top--;
    return 0;
}

const char *current_tag(TagStack *s) {
    if (s->top < 0) return "default";
    return s->tags[s->top];
}

//this should be replaced with xattr read
int file_has_tag(const char *filename, const char *tag) {
    if (strcmp(filename, "report.docx") == 0 && strcmp(tag, "work") == 0) return 1;
    if (strcmp(filename, "notes.txt") == 0 && strcmp(tag, "study") == 0) return 1;
    return 0;
}

void check_access(const char *filename, TagStack *s) {
    const char *tag = current_tag(s);
    if (file_has_tag(filename, tag)) {
        printf("Access to %s: ALLOWED under tag [%s]\n", filename, tag);
    } else {
        printf("Access to %s: DENIED under tag [%s]\n", filename, tag);
    }
}

int main() {
    TagStack s;
    init_stack(&s);

    printf("starting tag: %s\n", current_tag(&s));
    push(&s, "work");
    printf("current tag: %s\n", current_tag(&s));
    check_access("report.docx", &s);
    check_access("notes.txt", &s);

    push(&s, "study");
    printf("Current tag: %s\n", current_tag(&s));
    check_access("notes.txt", &s);

    pop(&s);
    printf("After pop, current tag: %s\n", current_tag(&s));
    check_access("research.pdf", &s);

    return 0;
}
