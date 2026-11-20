#include "db.h"

// сохранение в файл
void save_db(struct Database *db, char *filename) {
    FILE *f = fopen(filename, "w");
    if (f == NULL) {
        printf("Ошибка открытия файла для записи\n");
        return;
    }

    for (int i = 0; i < db->count; i++) {
        fprintf(f, "%s;%s;%d;%f\n", 
                db->items[i].maker, db->items[i].model, 
                db->items[i].storage, db->items[i].price);
    }

    fclose(f);
    printf("База сохранена в файл %s\n", filename);
}

// загрузка из файла
void load_db(struct Database *db, char *filename) {
    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        printf("Файл не найден, начинаем с пустой базы\n");
        return;
    }

    struct Console temp;
    while (fscanf(f, "%[^;];%[^;];%d;%f\n", temp.maker, temp.model, &temp.storage, &temp.price) == 4) {
        
        // если массив заполнен, расширяем его
        if (db->count >= db->capacity) {
            if (db->capacity == 0) {
                db->capacity = 2;
            } else {
                db->capacity = db->capacity * 2;
            }
            db->items = realloc(db->items, db->capacity * sizeof(struct Console));
        }
        
        db->items[db->count] = temp;
        db->count++;
    }

    fclose(f);
    printf("Загружено %d записей из файла\n", db->count);
}