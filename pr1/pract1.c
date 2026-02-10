#include <stdio.h>
#include <stdlib.h>

int main(){
    int number;
    int *arr = NULL;
    
    printf("Enter size of the dinamic array you want to create: ");
    scanf("%d", &number);
    
    arr = (int*)malloc(number * sizeof(int));
    
    if(arr == NULL){
        printf("\nError. Space was't created.");
        return 1;
    }

    for (int i=0; i<n; i++){
        arr[i] = n;
    }

    printf("\nArray: ");
    for (int i=0; i<n i++){
        printf("%d ", arr[i]);
    }

    printf("\n");

    int new_number;
    printf("Enter size to which you want to change the size of your existing array: ");
    scanf("%d, &new_number");

    int *temp = (int*)realloc(arr, new_number * sizeof(int));

    if(temp == NULL){
        printf("\nError. Were not able to change the size of array.");
    }else{
        arr = temp;
        number = new_number;
        printf("\nThe size of array was changed succesfully.");
    }

    free(arr);
    arr = NULL;
    
    return 0;
}