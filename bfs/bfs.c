#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

# define Max 1024 // 迷宮最大尺寸 (unit = bytes)

typedef struct {
    int x;
    int y;
} Point;

int directions[4][2] = {
    {0, 1},  // 右
    {1, 0},  // 下
    {0, -1}, // 左
    {-1, 0}  // 上
};
// char*  -> 1D
// char** -> 2D
char** load_maze(const char*filename, int *rows , int *cols)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("無法開啟檔案");//print error message
        return NULL;
    }

    char **maze = NULL;    // 初始化一個「指標的指標」，這將會是一個動態的二維陣列（字串陣列）
    char buffer[Max];     // 暫存區，用來暫時存放從鍵盤或檔案讀進來的一行文字 但只有1024個字元
    int r = 0;             // 紀錄目前讀到了第幾行
    while (fgets(buffer, sizeof(buffer), file)) {
    //  fgets 會從 file 讀一行文字到 buffer 中，直到遇到換行符號或檔案結束
        // char *fgets(char *str, int n, FILE *stream(from file)/*stdin(from I/O);
        // 移除行尾的換行符號
        // strcspn 會回傳第一個出現 '\n' 或 '\r' 的位置
        buffer[strcspn(buffer, "\r\n")] = 0;
        
        // 動態配置記憶體給 maze 陣列，增加一行
        maze = realloc(maze, (r + 1) * sizeof(char*));
        maze[r] = malloc((strlen(buffer) + 1) * sizeof(char));
        strcpy(maze[r], buffer); // 複製讀進來的行到 maze 陣列中
        r++;
    }
}
bool **create_visited(int rows, int cols){
    bool **visited = malloc(rows * sizeof(bool*));
    for (int i = 0; i < rows; i++) {
        visited[i] = malloc(cols * sizeof(bool));
        for (int j = 0; j < cols; j++) {
            visited[i][j] = false; // 初始化為未訪問
        }
    }
    return visited;
}




#if 0
int main(){
    char buffer[2];
    printf("請輸入: ");
    if (fgets(buffer,sizeof(buffer),stdin)!=NULL){
        //成功讀到
        printf("你輸入的是: %s\n",buffer);

    }
    return 0;
}
#endif 