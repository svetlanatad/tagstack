# TagStack

**TagStack** is a small prototype in C that demonstrates a **stack-based tag mechanism** for file access control.  
This idea comes from extending the concept of file tags (such as xattrs) with context switching based on a process-local stack of active tags.

## Why
Traditional tag-based systems allow checking whether a file’s tags match a process’s tags.  
This idea experiments with making the tag context dynamic and hierarchical, using a stack:

- A process starts with a base tag (e.g., `default`).
- New contexts can be pushed (e.g., `work`, `study`).
- When accessing a file, the current tag at the top of the stack is checked against the file’s allowed tags.
- When finished, the process can pop the context and return to the previous one.

This makes it possible to scope access by context without losing the history of previously valid tags.

## To bring an example 
```
Process starts with tag: default
Current tag: work
Access to report.docx: ALLOWED
Access to notes.txt: DENIED
Current tag: study
Access to notes.txt: ALLOWED
After pop, current tag: work
Access to research.pdf: DENIED
```

The code is a simple C program that:
- Implements a tag stack for processes.
- Associates files with lists of tags.
- Demonstrates push/pop and access decisions.

Of course it is not a kernel module; rather, it illustrates how stack-based tag contexts could simplify reasoning about access control in OS design.

This idea could be potentially integrated with Linux xattr for real file metadata, and it could implement tag enforcements in Linux kernel by LSM hooks.
