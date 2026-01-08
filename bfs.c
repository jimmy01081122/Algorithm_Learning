// bfs_viz.c
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

typedef struct {
    int r, c;
} Node;

static const char *base_map[] = {
    "###########",
    "#S..#....G#",
    "#.#.#.##..#",
    "#.#...#...#",
    "#.###.#.#.#",
    "#.....#...#",
    "###########",
};

void print_grid(int rows, int cols, char grid[rows][cols + 1], int step, const char *msg) {
    printf("\033[H\033[J");  // ANSI clear
    printf("Step %d - %s\n", step, msg);
    for (int r = 0; r < rows; ++r) {
        puts(grid[r]);
    }
    fflush(stdout);
}

int main(void) {
    const int rows = (int)(sizeof(base_map) / sizeof(base_map[0]));
    const int cols = (int)strlen(base_map[0]);

    char grid[rows][cols + 1];
    bool visited[rows][cols];
    Node parent[rows][cols];
    Node queue[rows * cols];
    int head = 0, tail = 0, step = 0;

    Node start = { -1, -1 }, goal = { -1, -1 };

    for (int r = 0; r < rows; ++r) {
        if ((int)strlen(base_map[r]) != cols) {
            fprintf(stderr, "Row %d width mismatch\n", r);
            return 1;
        }
        memcpy(grid[r], base_map[r], cols + 1);
        for (int c = 0; c < cols; ++c) {
            visited[r][c] = false;
            parent[r][c] = (Node){ -1, -1 };
            if (grid[r][c] == 'S') start = (Node){ r, c };
            if (grid[r][c] == 'G') goal = (Node){ r, c };
        }
    }

    if (start.r == -1 || goal.r == -1) {
        fprintf(stderr, "Start or goal not found\n");
        return 1;
    }

    queue[tail++] = start;
    visited[start.r][start.c] = true;

    print_grid(rows, cols, grid, step++, "初始地圖");
    usleep(200000000);

    const int dr[4] = { -1, 0, 1, 0 };
    const int dc[4] = { 0, 1, 0, -1 };
    bool found = false;

    while (head < tail) {
        Node cur = queue[head++];

        if (grid[cur.r][cur.c] != 'S' && grid[cur.r][cur.c] != 'G') {
            grid[cur.r][cur.c] = '.';
        }

        if (cur.r == goal.r && cur.c == goal.c) {
            found = true;
            break;
        }

        for (int k = 0; k < 4; ++k) {
            int nr = cur.r + dr[k], nc = cur.c + dc[k];
            if (nr < 0 || nr >= rows || nc < 0 || nc >= cols) continue;
            if (grid[nr][nc] == '#' || visited[nr][nc]) continue;

            visited[nr][nc] = true;
            parent[nr][nc] = cur;
            queue[tail++] = (Node){ nr, nc };

            if (grid[nr][nc] != 'G') grid[nr][nc] = '*';
        }

        print_grid(rows, cols, grid, step++, "擴展中");
        usleep(120000);
    }

    if (!found) {
        print_grid(rows, cols, grid, step, "找不到路徑");
        return 0;
    }

    // 清掉剩餘 frontier
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            if (grid[r][c] == '*') grid[r][c] = '.';
        }
    }

    // 回溯並標示最終路徑
    for (Node p = goal; p.r != -1 && p.c != -1; p = parent[p.r][p.c]) {
        if (grid[p.r][p.c] != 'S' && grid[p.r][p.c] != 'G') {
            grid[p.r][p.c] = '@';
        }
        if (p.r == start.r && p.c == start.c) break;
    }

    print_grid(rows, cols, grid, step, "最終路徑");
    return 0;
}
