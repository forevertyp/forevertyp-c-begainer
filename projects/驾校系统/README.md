V 3.0
---

# 🚗 C语言驾校管理系统

一个基于 **C 语言 + 链表数据结构** 的命令行驾校学员管理系统，实现学员信息的增删改查、数据持久化和成绩分析。

---

## 📌 项目概述

本系统采用 **模块化设计**，以链表作为核心数据结构，将程序拆分为多个功能独立的文件模块。系统通过从文件读取数据和保存数据实现持久化管理，支持：

* 学员信息的添加、删除、修改、查询
* 文件读写与数据持久化
* 成绩统计与排序分析

系统的特色在于：

* 基于链表的动态数据管理
* 通过冒泡排序实现成绩排名
* 模块清晰，便于维护和扩展

---

## 🧱 项目结构

```
main.c（程序入口）
│
├── 初始化阶段
│   ├── create_linkList()      # 创建链表头节点
│   └── load_from_file()       # 从文件加载数据
│
├── 核心循环（menu）
│   │
│   ├── 添加模块（record_add.c）
│   │   └── batch_add_node()
│   │       ├── tail_add_node()
│   │       ├── assignment_node()
│   │       ├── get_uid()
│   │       └── 显示添加结果
│   │
│   ├── 删除模块（record_delete.c）
│   │   └── batch_delete_node()
│   │       ├── 选择删除方式
│   │       ├── tail_delete_node()
│   │       ├── head_delete_node()
│   │       └── uid_delete_node()
│   │
│   ├── 修改模块（record_modify.c）
│   │   ├── process_subject_progress()
│   │   │   └── process_node()
│   │   └── update_subject_node()
│   │       └── update_node()
│   │
│   ├── 查询模块
│   │   ├── show_all_progress()
│   │   │   └── show_student_progress()
│   │   ├── inquire_by_uid()
│   │   └── input_range()
│   │       └── input_score_range()
│   │
│   ├── 文件操作（record_file.c）
│   │   ├── load_from_file()
│   │   └── save_to_file()
│   │
│   ├── 数据分析（record_statistic.c）
│   │   ├── statistic_analysis()
│   │   └── bubble_sort_score()
│   │       └── swap_node_info()
│   │
│   └── 基础工具函数（record_base.c）
│       ├── safe_input_int()
│       ├── empty()
│       ├── get_linkList_len()
│       ├── get_uid()
│       └── free_linkList()
│
└── 清理阶段
    ├── save_to_file()         # 保存数据
    └── free_linkList()        # 释放内存
```

---

## 🧠 系统设计说明

### 1. 系统架构核心思想

#### 数据组织

* 使用 **带头节点的链表** 实现动态数据存储
* 使用宏定义和枚举常量管理系统状态
* 字符串数组 + 枚举下标提高可读性

#### 功能划分

系统按功能拆分为多个模块：

* 增加
* 删除
* 查询
* 修改
* 文件操作
* 数据分析

每个模块职责单一，降低耦合度。

---

### 2. 数据持久化机制

#### 文件格式

* 使用文本文件进行格式化存储
* 支持标准化读写

#### 读写时机

* 程序启动时自动读取文件
* 程序退出时自动保存数据
* 用户可手动触发读写操作

---

### 3. 用户交互模式

* 菜单驱动的命令行界面
* 系统提示引导用户输入
* 用户选择功能后执行对应操作

---

### 4. 关键数据结构

```c
typedef struct Record {
    int uid;
    char name[20];
    int score[SUBJECT_COUNT];
    int status[STATUS_COUNT];
    struct Record *next;
} Record;
```

特点：

* 使用带头节点链表
* 简化删除与清空操作
* 避免特殊处理首节点

---

### 5. 数据安全保障

* 输入验证（检查 scanf 返回值）
* 防止野指针和 NULL 解引用
* 基础错误处理机制

---

## ⚙️ 编译与运行

```bash
gcc main.c record_*.c -o driving_school
./driving_school
```

---

## 📊 系统工作流程简述

系统启动后从文件读取学员数据并构建链表结构。用户通过菜单进行操作（增删改查与数据分析），所有修改实时作用于链表。程序退出时将链表数据保存到文件，实现持久化管理。

数据分析模块通过遍历链表统计成绩，并使用基于节点信息交换的冒泡排序实现成绩排名。

---


