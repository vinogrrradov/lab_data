#ifndef DB_H
#define DB_H

#define _CRT_SECURE_NO_WARNINGS 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// структура одной приставки
struct Console {
    char maker[50]; // Производитель
    char model[50]; // Модель
    int storage;    // Объем памяти
    float price;    // Цена
};

// структура базы данных
struct Database {
    struct Console *items; 
    int count;    // сколько приставок сейчас в базе
    int capacity; // сколько влезает в выделенную память
};

void clear_buffer(void);
// функции для работы с базой данных
void init_db(struct Database *db);
void free_db(struct Database *db);
void add_console(struct Database *db);
void print_db(struct Database *db);
void edit_console(struct Database *db);
void delete_console(struct Database *db);
void search_brand(struct Database *db);
void search_price(struct Database *db);

#endif