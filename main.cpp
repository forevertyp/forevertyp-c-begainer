//数据结构大二上课设
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include <SDL2/SDL.h>

/************************* 常量定义 *************************/
// 方向：上、下、左、右（行、列偏移）
#define DIR_NUM 4
int dirs[DIR_NUM][2] = {{-2, 0}, {2, 0}, {0, -2}, {0, 2}};
// 迷宫难度（顶点度数阈值）
#define EASY_DEGREE 3
#define NORMAL_DEGREE 2
#define HARD_DEGREE 1
// 图形化配置
#define CELL_SIZE 30    // 每个迷宫格子的像素大小
#define WINDOW_PADDING 50 // 窗口内边距
// 颜色定义
#define COLOR_WALL     {50, 50, 50, 255}    // 墙壁：深灰色
#define COLOR_PATH     {255, 255, 255, 255} // 通路：白色
#define COLOR_PLAYER   {255, 0, 0, 255}     // 玩家：红色
#define COLOR_OPT_PATH {255, 255, 0, 255}    // 最优路径：黄色
#define COLOR_START    {0, 255, 0, 255}     // 起点：绿色
#define COLOR_END      {0, 0, 255, 255}     // 终点：蓝色

/************************* 数据结构定义 *************************/
// 坐标结构体
typedef struct {
    int x, y;  // 行、列（迷宫网格坐标）
} Point;

// 栈（DFS生成迷宫）
typedef struct StackNode {
    Point p;
    struct StackNode* next;
} StackNode;
typedef struct {
    StackNode* top;
} Stack;

// 链表（轨迹/最优路径）
typedef struct ListNode {
    Point p;
    struct ListNode* next;
} ListNode;
typedef struct {
    ListNode* head;
    ListNode* tail;
    int len;
} List;

// A*算法优先队列节点
typedef struct AStarNode {
    Point p;
    int g, h, f;
    struct AStarNode* parent;
} AStarNode;
typedef struct {
    AStarNode* nodes;
    int size;
    int capacity;
} PriorityQueue;

// 迷宫核心结构体
typedef struct {
    int** grid;
    int rows, cols;
    int degree;
    Point start;
    Point end;
    Point player;
    List player_path;
    List opt_path;
    // SDL相关
    SDL_Window* window;
    SDL_Renderer* renderer;
    int window_width;  // 窗口宽度
    int window_height; // 窗口高度
} Maze;

/************************* 栈操作函数 *************************/
void stack_init(Stack* s) { s->top = NULL; }
bool stack_is_empty(Stack* s) { return s->top == NULL; }
void stack_push(Stack* s, Point p) {
    StackNode* node = (StackNode*)malloc(sizeof(StackNode));
    node->p = p;
    node->next = s->top;
    s->top = node;
}
Point stack_pop(Stack* s) {
    if (stack_is_empty(s)) { Point p = {-1, -1}; return p; }
    StackNode* temp = s->top;
    Point p = temp->p;
    s->top = temp->next;
    free(temp);
    return p;
}
void stack_destroy(Stack* s) { while (!stack_is_empty(s)) stack_pop(s); }

/************************* 链表操作函数 *************************/
void list_init(List* list) { list->head = list->tail = NULL; list->len = 0; }
void list_add(List* list, Point p) {
    ListNode* node = (ListNode*)malloc(sizeof(ListNode));
    node->p = p;
    node->next = NULL;
    if (list->tail == NULL) {
        list->head = list->tail = node;
    } else {
        list->tail->next = node;
        list->tail = node;
    }
    list->len++;
}
bool list_remove_last(List* list) {
    if (list->len <= 1) return false;
    ListNode* cur = list->head;
    while (cur->next != list->tail) cur = cur->next;
    free(list->tail);
    list->tail = cur;
    cur->next = NULL;
    list->len--;
    return true;
}
void list_clear(List* list) {
    ListNode* cur = list->head;
    while (cur != NULL) {
        ListNode* temp = cur;
        cur = cur->next;
        free(temp);
    }
    list_init(list);
}
Point list_get_last(List* list) {
    Point p = {-1, -1};
    if (list->tail != NULL) p = list->tail->p;
    return p;
}

/************************* 优先队列操作（A*） *************************/
void pq_init(PriorityQueue* pq, int capacity) {
    pq->nodes = (AStarNode*)malloc(sizeof(AStarNode) * capacity);
    pq->size = 0;
    pq->capacity = capacity;
}
void pq_swap(AStarNode* a, AStarNode* b) {
    AStarNode temp = *a; *a = *b; *b = temp;
}
void pq_push(PriorityQueue* pq, AStarNode node) {
    if (pq->size >= pq->capacity) return;
    pq->nodes[pq->size++] = node;
    int i = pq->size - 1;
    while (i > 0) {
        int parent = (i - 1) / 2;
        if (pq->nodes[i].f >= pq->nodes[parent].f) break;
        pq_swap(&pq->nodes[i], &pq->nodes[parent]);
        i = parent;
    }
}
AStarNode pq_pop(PriorityQueue* pq) {
    if (pq->size == 0) { AStarNode empty = {{-1, -1}, -1, -1, -1, NULL}; return empty; }
    AStarNode min = pq->nodes[0];
    pq->nodes[0] = pq->nodes[--pq->size];
    int i = 0;
    while (true) {
        int left = 2 * i + 1, right = 2 * i + 2, smallest = i;
        if (left < pq->size && pq->nodes[left].f < pq->nodes[smallest].f) smallest = left;
        if (right < pq->size && pq->nodes[right].f < pq->nodes[smallest].f) smallest = right;
        if (smallest == i) break;
        pq_swap(&pq->nodes[i], &pq->nodes[smallest]);
        i = smallest;
    }
    return min;
}
void pq_destroy(PriorityQueue* pq) { free(pq->nodes); }

/************************* 迷宫核心函数 *************************/
// 初始化迷宫（含SDL窗口）
void maze_init(Maze* maze, int rows, int cols, int degree) {
    // 确保迷宫尺寸为奇数
    maze->rows = (rows % 2 == 0) ? rows + 1 : rows;
    maze->cols = (cols % 2 == 0) ? cols + 1 : cols;
    maze->degree = degree;

    // 计算窗口大小
    maze->window_width = maze->cols * CELL_SIZE + 2 * WINDOW_PADDING;
    maze->window_height = maze->rows * CELL_SIZE + 2 * WINDOW_PADDING + 50; // 预留文字区域

    // 初始化SDL窗口和渲染器
    SDL_Init(SDL_INIT_VIDEO);
    maze->window = SDL_CreateWindow(
        "迷宫生成与路径规划游戏",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        maze->window_width, maze->window_height,
        SDL_WINDOW_SHOWN
    );
    maze->renderer = SDL_CreateRenderer(maze->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    // 分配迷宫网格内存
    maze->grid = (int**)malloc(sizeof(int*) * maze->rows);
    for (int i = 0; i < maze->rows; i++) {
        maze->grid[i] = (int*)malloc(sizeof(int) * maze->cols);
        for (int j = 0; j < maze->cols; j++) maze->grid[i][j] = 1;
    }

    // 设置起点、终点、玩家位置
    maze->start = (Point){1, 1};
    maze->end = (Point){maze->rows - 2, maze->cols - 2};
    maze->player = maze->start;
    list_init(&maze->player_path);
    list_add(&maze->player_path, maze->player);
    list_init(&maze->opt_path);
}

// 网格坐标转窗口像素坐标
SDL_Point grid_to_pixel(Point p) {
    SDL_Point pixel;
    pixel.x = WINDOW_PADDING + p.y * CELL_SIZE;
    pixel.y = WINDOW_PADDING + p.x * CELL_SIZE;
    return pixel;
}

// 检查坐标合法性
bool is_valid(Point p, int rows, int cols) {
    return p.x >= 0 && p.x < rows && p.y >= 0 && p.y < cols;
}

// 计算顶点度数
int calc_degree(Maze* maze, Point p) {
    int degree = 0;
    for (int i = 0; i < DIR_NUM; i++) {
        Point np = {p.x + dirs[i][0]/2, p.y + dirs[i][1]/2};
        if (is_valid(np, maze->rows, maze->cols) && maze->grid[np.x][np.y] == 0) degree++;
    }
    return degree;
}

// DFS生成迷宫
void maze_generate(Maze* maze) {
    srand((unsigned int)time(NULL));
    Stack stack;
    stack_init(&stack);
    Point start = maze->start;
    maze->grid[start.x][start.y] = 0;
    stack_push(&stack, start);

    while (!stack_is_empty(&stack)) {
        Point cur = stack_pop(&stack);
        // 随机打乱方向
        for (int i = 0; i < DIR_NUM; i++) {
            int r = rand() % DIR_NUM;
            int temp[2] = {dirs[i][0], dirs[i][1]};
            dirs[i][0] = dirs[r][0];
            dirs[i][1] = dirs[r][1];
            dirs[r][0] = temp[0];
            dirs[r][1] = temp[1];
        }

        int dir_count = 0;
        for (int i = 0; i < DIR_NUM; i++) {
            Point np = {cur.x + dirs[i][0], cur.y + dirs[i][1]};
            Point wall = {cur.x + dirs[i][0]/2, cur.y + dirs[i][1]/2};
            if (is_valid(np, maze->rows, maze->cols) && maze->grid[np.x][np.y] == 1) {
                maze->grid[wall.x][wall.y] = 0;
                maze->grid[np.x][np.y] = 0;
                if (calc_degree(maze, cur) < maze->degree) stack_push(&stack, cur);
                stack_push(&stack, np);
                dir_count++;
                if (dir_count >= maze->degree) break;
            }
        }
    }
    stack_destroy(&stack);
}

// A*算法查找最优路径
void maze_find_opt_path(Maze* maze) {
    list_clear(&maze->opt_path);
    int rows = maze->rows, cols = maze->cols;
    bool** visited = (bool**)malloc(sizeof(bool*) * rows);
    int** g_val = (int**)malloc(sizeof(int*) * rows);
    Point** parent = (Point**)malloc(sizeof(Point*) * rows);
    for (int i = 0; i < rows; i++) {
        visited[i] = (bool*)calloc(cols, sizeof(bool));
        g_val[i] = (int*)malloc(sizeof(int) * cols);
        parent[i] = (Point*)malloc(sizeof(Point) * cols);
        for (int j = 0; j < cols; j++) {
            g_val[i][j] = -1;
            parent[i][j] = (Point){-1, -1};
        }
    }

    PriorityQueue pq;
    pq_init(&pq, rows * cols);
    AStarNode start_node = {maze->start, 0,
        abs(maze->start.x - maze->end.x) + abs(maze->start.y - maze->end.y),
        0, NULL};
    start_node.f = start_node.g + start_node.h;
    g_val[maze->start.x][maze->start.y] = 0;
    pq_push(&pq, start_node);

    bool found = false;
    while (pq.size > 0) {
        AStarNode cur = pq_pop(&pq);
        Point cur_p = cur.p;
        if (visited[cur_p.x][cur_p.y]) continue;
        visited[cur_p.x][cur_p.y] = true;

        if (cur_p.x == maze->end.x && cur_p.y == maze->end.y) {
            found = true;
            break;
        }

        for (int i = 0; i < DIR_NUM; i++) {
            Point np = {cur_p.x + dirs[i][0]/2, cur_p.y + dirs[i][1]/2};
            if (is_valid(np, rows, cols) && maze->grid[np.x][np.y] == 0 && !visited[np.x][np.y]) {
                int new_g = cur.g + 1;
                if (g_val[np.x][np.y] == -1 || new_g < g_val[np.x][np.y]) {
                    g_val[np.x][np.y] = new_g;
                    int h = abs(np.x - maze->end.x) + abs(np.y - maze->end.y);
                    AStarNode new_node = {np, new_g, h, new_g + h, &cur};
                    pq_push(&pq, new_node);
                    parent[np.x][np.y] = cur_p;
                }
            }
        }
    }

    // 回溯生成最优路径
    if (found) {
        Point p = maze->end;
        while (p.x != -1 && p.y != -1) {
            list_add(&maze->opt_path, p);
            p = parent[p.x][p.y];
        }
        // 反转链表
        ListNode *prev = NULL, *cur = maze->opt_path.head, *next;
        while (cur != NULL) {
            next = cur->next;
            cur->next = prev;
            prev = cur;
            cur = next;
        }
        maze->opt_path.tail = maze->opt_path.head;
        maze->opt_path.head = prev;
    }

    // 释放内存
    pq_destroy(&pq);
    for (int i = 0; i < rows; i++) {
        free(visited[i]);
        free(g_val[i]);
        free(parent[i]);
    }
    free(visited); free(g_val); free(parent);
}

// 玩家移动
bool player_move(Maze* maze, char dir) {
    Point cur = maze->player;
    Point next = cur;
    switch (dir) {
        case 'w': case 'W': next.x -= 1; break;
        case 's': case 'S': next.x += 1; break;
        case 'a': case 'A': next.y -= 1; break;
        case 'd': case 'D': next.y += 1; break;
        default: return false;
    }
    if (is_valid(next, maze->rows, maze->cols) && maze->grid[next.x][next.y] == 0) {
        maze->player = next;
        list_add(&maze->player_path, next);
        return true;
    }
    return false;
}

// 玩家回溯
bool player_back(Maze* maze) {
    if (maze->player_path.len <= 1) return false;
    list_remove_last(&maze->player_path);
    maze->player = list_get_last(&maze->player_path);
    return true;
}

// 绘制迷宫（核心图形化函数）
void maze_render(Maze* maze) {
    // 清空渲染器
    SDL_SetRenderDrawColor(maze->renderer, 20, 20, 20, 255); // 背景色：浅黑色
    SDL_RenderClear(maze->renderer);

    // 绘制迷宫网格
    for (int i = 0; i < maze->rows; i++) {
        for (int j = 0; j < maze->cols; j++) {
            Point p = {i, j};
            SDL_Point pixel = grid_to_pixel(p);
            SDL_Rect rect = {pixel.x, pixel.y, CELL_SIZE, CELL_SIZE};

            // 绘制墙壁/通路
            if (maze->grid[i][j] == 1) {
                SDL_SetRenderDrawColor(maze->renderer, COLOR_WALL);
                SDL_RenderFillRect(maze->renderer, &rect);
            } else {
                SDL_SetRenderDrawColor(maze->renderer, COLOR_PATH);
                SDL_RenderFillRect(maze->renderer, &rect);
                // 绘制格子边框（增强视觉效果）
                SDL_SetRenderDrawColor(maze->renderer, 200, 200, 200, 255);
                SDL_RenderDrawRect(maze->renderer, &rect);
            }

            // 标记起点
            if (i == maze->start.x && j == maze->start.y) {
                SDL_SetRenderDrawColor(maze->renderer, COLOR_START);
                SDL_RenderFillRect(maze->renderer, &rect);
            }
            // 标记终点
            if (i == maze->end.x && j == maze->end.y) {
                SDL_SetRenderDrawColor(maze->renderer, COLOR_END);
                SDL_RenderFillRect(maze->renderer, &rect);
            }
        }
    }

    // 绘制最优路径
    if (maze->opt_path.len > 0) {
        SDL_SetRenderDrawColor(maze->renderer, COLOR_OPT_PATH);
        ListNode* cur = maze->opt_path.head;
        while (cur != NULL && cur->next != NULL) {
            SDL_Point p1 = grid_to_pixel(cur->p);
            SDL_Point p2 = grid_to_pixel(cur->next->p);
            // 路径线居中
            p1.x += CELL_SIZE / 2; p1.y += CELL_SIZE / 2;
            p2.x += CELL_SIZE / 2; p2.y += CELL_SIZE / 2;
            SDL_RenderDrawLine(maze->renderer, p1.x, p1.y, p2.x, p2.y);
            cur = cur->next;
        }
    }

    // 绘制玩家（圆形）
    SDL_Point player_pixel = grid_to_pixel(maze->player);
    int player_radius = CELL_SIZE / 3;
    int center_x = player_pixel.x + CELL_SIZE / 2;
    int center_y = player_pixel.y + CELL_SIZE / 2;
    SDL_SetRenderDrawColor(maze->renderer, COLOR_PLAYER);
    // 绘制实心圆（SDL无直接画圆函数，用矩形模拟）
    for (int r = 0; r < player_radius; r++) {
        for (int angle = 0; angle < 360; angle += 5) {
            float rad = angle * M_PI / 180;
            int x = center_x + r * cos(rad);
            int y = center_y + r * sin(rad);
            SDL_RenderDrawPoint(maze->renderer, x, y);
        }
    }

    // 绘制提示文字（简化版，如需完整文字渲染可加SDL_ttf）
    char info[256];
    sprintf(info, "W/S/A/D:移动 | B:回溯 | F:寻路 | Q:退出 | 步数:%d | 最优路径:%d",
            maze->player_path.len - 1, maze->opt_path.len - 1);
    SDL_SetRenderDrawColor(maze->renderer, 255, 255, 255, 255);
    // 文字区域（简化为背景条）
    SDL_Rect text_bg = {WINDOW_PADDING/2, maze->window_height - 40, maze->window_width - WINDOW_PADDING, 30};
    SDL_SetRenderDrawColor(maze->renderer, 30, 30, 30, 255);
    SDL_RenderFillRect(maze->renderer, &text_bg);

    // 更新画面
    SDL_RenderPresent(maze->renderer);
}

// 销毁迷宫（释放所有资源）
void maze_destroy(Maze* maze) {
    // 释放迷宫网格
    for (int i = 0; i < maze->rows; i++) free(maze->grid[i]);
    free(maze->grid);
    // 释放链表
    list_clear(&maze->player_path);
    list_clear(&maze->opt_path);
    // 释放SDL资源
    SDL_DestroyRenderer(maze->renderer);
    SDL_DestroyWindow(maze->window);
    SDL_Quit();
}

/************************* 主函数 *************************/
int main() {
    Maze maze;
    int rows, cols, difficulty;

    // 初始化配置
    printf("===== 图形化迷宫游戏 =====\n");
    printf("请输入迷宫尺寸（如10 10，建议5-20）：");
    scanf("%d %d", &rows, &cols);
    printf("请选择难度（1=简单 2=普通 3=困难）：");
    scanf("%d", &difficulty);
    int degree = EASY_DEGREE;
    if (difficulty == 2) degree = NORMAL_DEGREE;
    else if (difficulty == 3) degree = HARD_DEGREE;

    // 初始化迷宫和SDL
    maze_init(&maze, rows, cols, degree);
    printf("正在生成迷宫...\n");
    maze_generate(&maze);

    // 游戏主循环
    bool running = true;
    SDL_Event event;
    while (running) {
        // 渲染迷宫
        maze_render(&maze);

        // 检查是否到达终点
        if (maze.player.x == maze.end.x && maze.player.y == maze.end.y) {
            printf("?? 恭喜！到达终点！\n");
            running = false;
            break;
        }

        // 处理SDL事件
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
            // 键盘按键事件
            if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_w: case SDLK_W:
                    case SDLK_s: case SDLK_S:
                    case SDLK_a: case SDLK_A:
                    case SDLK_d: case SDLK_D:
                        player_move(&maze, SDL_GetKeyName(event.key.keysym.sym)[0]);
                        break;
                    case SDLK_b: case SDLK_B:
                        player_back(&maze);
                        break;
                    case SDLK_f: case SDLK_F:
                        maze_find_opt_path(&maze);
                        break;
                    case SDLK_q: case SDLK_Q:
                        running = false;
                        break;
                }
            }
        }
        SDL_Delay(16); // 控制帧率（约60FPS）
    }

    // 销毁资源
    maze_destroy(&maze);
    printf("?? 游戏退出！\n");
    return 0;
}

