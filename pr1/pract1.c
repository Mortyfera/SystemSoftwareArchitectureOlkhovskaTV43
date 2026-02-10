#include <stdio.h>
#include <stdlib.h>

int * change_array_size(int *arr){
    int new_number;

    printf("Enter size to which you want to change the size of your existing array: ");
    scanf("%d", &new_number);

    int *temp = (int*)realloc(arr, new_number * sizeof(int));

    if(temp == NULL){
        printf("\nError. Were not able to change the size of array.");
        return arr;
    }else{
        printf("\nThe size of array was changed succesfully.");
        for (int i=0; i<new_number; i++){
            temp[i] = new_number;
        }
        printf("\nArray: ");
        for (int i=0; i<new_number; i++){
        printf("%d ", temp[i]);
    }
        return temp;
    }
}

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

    for (int i=0; i<number; i++){
        arr[i] = number;
    }

    printf("\nArray: ");
    for (int i=0; i<number; i++){
        printf("%d ", arr[i]);
    }

    printf("\n");

    char answer;

    printf("Do you want to change the size of the existing array(y/n): ");
    scanf("%c", &answer);

    while(answer == 'y' || answer == 'Y'){
         if(answer == 'y' || answer == 'Y'){
            arr = change_array_size(arr);
        }else if(answer == 'n' || answer == 'N'){
            free(arr);
            arr = NULL;
            return 0;
        }else{
            printf("Error. Do you want to change the size of the existing array(y/n): ");
            scanf("%c", &answer);
        }
        printf("Do you want to change the size of the existing array(y/n): ");
        scanf("%c", &answer);
    }
}