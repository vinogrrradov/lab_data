#ifndef STORAGE_H
#define STORAGE_H

// функции базы данных по работе с файлами
void save_db(struct Database *db, char *filename);
void load_db(struct Database *db, char *filename);

#endif