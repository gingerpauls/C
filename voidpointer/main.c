#include "stdio.h"
#include "time.h"

typedef struct {
    int x, y, z;
} Coordinate;

typedef struct {
    Coordinate coordinate_list[16];
} Map;

void change(int *num1, char *letter1, Coordinate *coordinate);
void change_with_void_ptr(void *object1, void *object2, void *object3);
void randomize_map(void* object);

int main(void) {
    srand((unsigned)time(0));

    Map map1;

    int num1 = 1;
    char letter1 = 'c';
    Coordinate coordinate1;
    coordinate1.x = 0;
    coordinate1.y = 0;
    coordinate1.z = 0;

    change(&num1, &letter1, &coordinate1);
    printf( "num1: %d\nletter1: %c\ncoordinate.x: %d"
            "\ncoordinate.y: %d \ncoordinate.z: %d\n\n",
            num1, letter1, coordinate1.x, coordinate1.y, coordinate1.z);

    change_with_void_ptr(&num1, &letter1, &coordinate1);
    printf( "num1: %d\nletter1: %c\ncoordinate.x: %d"
            "\ncoordinate.y: %d \ncoordinate.z: %d\n\n",
            num1, letter1, coordinate1.x, coordinate1.y, coordinate1.z);

    for (int i = 0; i < (sizeof(map1) / sizeof(map1.coordinate_list[i])); i++) {
        printf("map1.coordinate[%d].x: %d\n", i, map1.coordinate_list[i].x);
        printf("map1.coordinate[%d].y: %d\n", i, map1.coordinate_list[i].y);
        printf("map1.coordinate[%d].z: %d\n", i, map1.coordinate_list[i].z);
    }

    return 0;
}

void randomize_map(void* object) {
    for (int i = 0; i < (sizeof(object) / sizeof(object.coordinate_list[i])); i++) {
        object.coordinate_list[i].x = rand();
        object.coordinate_list[i].y = rand();
        object.coordinate_list[i].z = rand();
    }
}

void change_with_void_ptr(void *object1, void *object2, void *object3) {
    *(int*)object1 = 10;
    *(char*)object2 = 'F';
    (*(Coordinate*)object3).x = 100;
    (*(Coordinate*)object3).y = 200;
    (*(Coordinate*)object3).z = -300;
}

void change(int* num1, char* letter1, Coordinate* coordinate) {
    *num1 += *num1;
    *letter1 = 'd';
    coordinate->x = 1;
    coordinate->y = 2;
    coordinate->z = 3;
}