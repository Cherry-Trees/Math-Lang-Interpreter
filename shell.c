while (1) {
        putchar('>');
        char symbol = '\0';
        char buffer[128];
        short i = 0;
        while (symbol != ';') {
            symbol = getchar();
            buffer[i++] = symbol;
        }
        putchar('\n');
        printf("%s\n", buffer);
        memset(buffer, 0, sizeof(buffer));
    }