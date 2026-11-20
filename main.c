#include "db.h"
#include "storage.h"

#define FILENAME "consoles.txt"

int main() {
    struct Database db;
    init_db(&db);
    
    // Пытаемся загрузить данные при старте
    load_db(&db, FILENAME);

    int choice;
    while (1) {
        printf("\nМЕНЮ (Всего консолей: %d)\n", db.count);
        printf("1. Вывести все консоли\n");
        printf("2. Добавить консоль\n");
        printf("3. Редактировать консоль\n");
        printf("4. Удалить консоль\n");
        printf("5. Поиск по производителю\n");
        printf("6. Поиск по цене\n");
        printf("7. Сохранить в файл\n");
        printf("0. Выход\n");
        printf("Ваш выбор: ");

        if (scanf("%d", &choice) != 1) {
            printf("Ошибка ввода\n");
            clear_buffer();
            continue;
        }
        clear_buffer();

        switch (choice) {
            case 1: print_db(&db); break;
            case 2: add_console(&db); break;
            case 3: edit_console(&db); break;
            case 4: delete_console(&db); break;
            case 5: search_brand(&db); break;
            case 6: search_price(&db); break;
            case 7: save_db(&db, FILENAME); break;
            case 0: 
                save_db(&db, FILENAME); // сохраняем перед выходом
                free_db(&db);           // освобождаем память
                return 0;
            default:
                printf("Неверный пункт меню.\n");
        }
    }
    return 0;
}