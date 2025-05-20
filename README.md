## Idea for response splitting

``` cpp
char response[] = "abcde 01 02";

char* preamble = strtok(response, " ");  // trennt beim ersten Leerzeichen
char* high     = strtok(NULL, " ");      // trennt beim zweiten Leerzeichen
char* low      = strtok(NULL, " ");      // trennt beim dritten Leerzeichen
```
