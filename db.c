#include "db.h"

// инициализация базы
void init_db(struct Database *db) {
    db->items = NULL;
    db->count = 0;
    db->capacity = 0;
}

// очистка памяти
void free_db(struct Database *db) {
    if (db->items != NULL) {
        free(db->items);
    }
    db->items = NULL;
    db->count = 0;
    db->capacity = 0;
}

// функция для очистки буфера ввода (чтобы scanf не зависал)
void clear_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// добавление новой консоли
void add_console(struct Database *db) {
    // если места нет, увеличиваем массив
    if (db->count >= db->capacity) {
        if (db->capacity == 0) {
            db->capacity = 2;
        } else {
            db->capacity = db->capacity * 2;
        }
        db->items = realloc(db->items, db->capacity * sizeof(struct Console));
        if (db->items == NULL) {
            printf("Ошибка выделения памяти!\n");
            return;
        }
    }

    struct Console new_console;
    printf("\n[Добавление консоли]\n");
    
    printf("Производитель (одно слово): ");
    scanf("%s", new_console.maker);
    
    printf("Модель (одно слово): ");
    scanf("%s", new_console.model);
    
    printf("Память (ГБ): ");
    scanf("%d", &new_console.storage);
    
    printf("Цена (руб): ");
    scanf("%f", &new_console.price);
    
    clear_buffer(); // чистим enter после ввода

    // добавляем в массив
    db->items[db->count] = new_console;
    db->count++;
    printf("Консоль успешно добавлена!\n");
}

// вывод всей базы
void print_db(struct Database *db) {
    if (db->count == 0) {
        printf("\nБаза данных пуста.\n");
        return;
    }

    printf("\n[Список консолей]\n");
    
    for (int i = 0; i < db->count; i++) {
        printf("[№%d] Производитель: %s, Модель: %s, Память: %d ГБ, Цена: %f руб.\n", 
               i+1, 
               db->items[i].maker, 
               db->items[i].model, 
               db->items[i].storage, 
               db->items[i].price);
    }
}

// удаление консоли по номеру
void delete_console(struct Database *db) {
    if (db->count == 0) {
        printf("База пуста!\n");
        return;
    }

    print_db(db);
    int num;
    printf("Введите номер консоли для удаления: ");
    scanf("%d", &num);
    clear_buffer();

    if (num < 1 || num > db->count) {
        printf("Неверный номер\n");
        return;
    }

    // сдвигаем все элементы влево, чтобы затереть удаленный
    for (int i = num-1; i < db->count-1; i++) {
        db->items[i] = db->items[i+1];
    }
    db->count--;
    printf("Консоль удалена\n");
}

// редактирование консоли
void edit_console(struct Database *db) {
    if (db->count == 0) {
        printf("База пуста\n");
        return;
    }

    print_db(db);
    int num;
    printf("Введите номер консоли для редактирования: ");
    scanf("%d", &num);
    clear_buffer();

    if (num < 1 || num > db->count) {
        printf("Неверный номер\n");
        return;
    }

    int index = num - 1;
    printf("\n[Редактируем консоль #%d]\n", num);
    
    printf("Новый производитель (текущий %s): ", db->items[index].maker);
    scanf("%s", db->items[index].maker);
    
    printf("Новая модель (текущая %s): ", db->items[index].model);
    scanf("%s", db->items[index].model);
    
    printf("Новая память (текущая %d): ", db->items[index].storage);
    scanf("%d", &db->items[index].storage);
    
    printf("Новая цена (текущая %f): ", db->items[index].price);
    scanf("%f", &db->items[index].price);
    
    clear_buffer();
    printf("Данные обновлены!\n");
}

// поиск по производителю
void search_brand(struct Database *db) {
    if (db->count == 0) {
        printf("База пуста\n");
        return;
    }

    char search_str[50];
    printf("Введите производителя для поиска: ");
    scanf("%s", search_str);
    clear_buffer();

    printf("\nРезультаты поиска:\n");
    int found = 0;
    for (int i = 0; i < db->count; i++) {
        // strstr ищет подстроку, если производитель содержит введенное слово - выводим
        if (strstr(db->items[i].maker, search_str) != NULL) {
            printf("[№%d] Производитель: %s, Модель: %s, Память: %d ГБ, Цена: %f руб.\n", 
                   i+1, db->items[i].maker, db->items[i].model, 
                   db->items[i].storage, db->items[i].price);
            found++;
        }
    }
    
    if (found == 0) {
        printf("Ничего не найдено\n");
    } else {
        printf("Найдено записей: %d\n", found);
    }
}

// поиск по цене
void search_price(struct Database *db) {
    if (db->count == 0) {
        printf("База пуста\n");
        return;
    }

    float max_price;
    printf("Введите максимальную цену: ");
    scanf("%f", &max_price);
    clear_buffer();

    printf("\nКонсоли дешевле %f руб:\n", max_price);
    int found = 0;
    for (int i = 0; i < db->count; i++) {
        if (db->items[i].price <= max_price) {
            printf("[№%d] Производитель: %s, Модель: %s, Память: %d ГБ, Цена: %f руб.\n", 
                   i + 1, db->items[i].maker, db->items[i].model, 
                   db->items[i].storage, db->items[i].price);
            found++;
        }
    }
    
    if (found == 0){
        printf("Ничего не найдено\n");
    }    
}