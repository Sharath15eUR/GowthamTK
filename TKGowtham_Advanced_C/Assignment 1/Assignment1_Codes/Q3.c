#include <stdio.h>

int main() {
    int n, m;
    printf("Enter Size n & m: \n");
    scanf("%d %d",&n,&m);

    int arr[n][m];

    printf("Enter Values:  \n");
    for(int i = 0;i < n;i++){
        for(int j = 0; j < n; j++){
            printf("Enter arr[%d][%d]: ",i,j);
            scanf("%d",&arr[i][j]);
        }
    }

    printf("Enter Key: ");
    int key;
    scanf("%d",&key);

    int row = 0; int col = m - 1;
    int present = 0;
    while(row < m && col >= 0) {
        if(arr[row][col] == key) {
            printf("Key present at %d %d\n",row,col);
            present = 1;
            break;
        } else if (arr[row][col] > key ) {
            col--;
        } else {
            row++;
        }
    }

    if (present == 0) {
        printf("Key not present");
    } 
    return 0;
}