#include <stdio.h>
#include <stdbool.h>

#define MAX 10 // 最大節點數


/* ******************************************** 
   BFS 其實像是Level Order Traversal(Tree）
   將節點用步數做區分，每一層的節點都會被依序處理
   因此需要一個FIFO的結構來存放節點
   以下是BFS的基礎實作
*********************************************** */


// 定義佇列結構 FIFO
int queue[MAX];
// head position
int front = 0;
// tail position
int rear = -1;

void enqueue(int item) {
    queue[++rear] = item;
}

int dequeue() {
    return queue[front++];
}

bool isQueueEmpty() {
    return front > rear;
}

int parent[MAX]; // 紀錄每個節點的父親

void bfs_with_tree(int adj[MAX][MAX], int startNode, int n) {
    bool visited[MAX] = {false};
    for(int i = 0; i < n; i++) parent[i] = -1; // 初始化，-1 表示沒有父親

    visited[startNode] = true;
    enqueue(startNode);

    while (!isQueueEmpty()) {
        int u = dequeue();

        for (int v = 0; v < n; v++) {
            // 如果 u 與 v 相連，且 v 還沒被去過
            if (adj[u][v] == 1 && !visited[v]) {
                visited[v] = true;
                parent[v] = u; // 關鍵：標記 v 的上層節點是 u
                enqueue(v);
                
                // 視覺化表示：u (上層) -> v (下層)
                printf("發現樹枝: 節點 %d -> 節點 %d\n", u, v);
            }
        }
    }
}

// Trace back and print path from startNode to target
void printPath(int target) {
    if (target == -1) return;
    printPath(parent[target]); // 遞迴找父節點
    printf("%d ", target);
}

int main() {
    // 定義一個鄰接矩陣 (0:無連接, 1:有連接)
    int n = 5;
    int adj[MAX][MAX] = {
        {0, 1, 1, 0, 0}, // 0 連接到 1, 2
        {1, 0, 0, 1, 0}, // 1 連接到 0, 3
        {1, 0, 0, 1, 1}, // 2 連接到 0, 3, 4
        {0, 1, 1, 0, 1}, // 3 連接到 1, 2, 4
        {0, 0, 1, 1, 0}  // 4 連接到 2, 3
    };

    bfs_with_tree(adj, 0, n);
    printf("從節點 0 到節點 4 的路徑: ");
    printPath(4);
    printf("\n");
    return 0;
}
/** 
 ** 測試用code
 **/
#if 0
int main (){
    // 測試 a ++ , ++ a 
    printf("rear : %d\n", rear);
    // 先加再用
    printf ("++ rear %d\n", ++rear);
    // 先用再加
    printf("rear ++ : %d\n", rear++);
    return 0;
}
#endif