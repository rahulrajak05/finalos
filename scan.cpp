
#include <stdio.h>

int main() {
    int integer_value;
    float float_value;
    char character_value;
    char string_value[50];

    printf("Enter an integer: ");
    scanf("%d", &integer_value);

    printf("Enter a float: ");
    scanf("%f", &float_value);

    printf("Enter a character: ");
    scanf(" %c", &character_value); // Note the space before %c to consume any leading whitespace

    printf("Enter a string: ");
    scanf("%s", string_value);

    printf("Integer: %d\n", integer_value);
    printf("Float: %f\n", float_value);
    printf("Character: %c\n", character_value);
    printf("String: %s\n", string_value);

    return 0;
}