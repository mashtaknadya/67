/*Напишите псевдокод (или код на C) функции my_copy(src_path, dst_path), которая копирует содержимое из одного файла в другой.
Условия:
Новый файл должен создаваться с правами 0644.
Если файл назначения уже существует, он должен быть перезаписан.
Используйте только системные вызовы: open, read, write, close.
Размер буфера для чтения/записи — 4096 байт.8 */

#include <fcntl.h>
#include <unistd.h>

int my_copy(const char *src_path, const char *dst_path) {
    int src_fd, dst_fd;
    ssize_t bytes_read, bytes_written, total_written;
    char buffer[4096];

    // открытие файла
    src_fd = open(src_path, O_RDONLY);
    if (src_fd < 0) {
        return -1;
    }

    dst_fd = open(dst_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dst_fd < 0) {
        close(src_fd);
        return -1;
    }

    // копируем содержимое
    while ((bytes_read = read(src_fd, buffer, sizeof(buffer))) > 0) {
        total_written = 0;
        while (total_written < bytes_read) {
            bytes_written = write(dst_fd, buffer + total_written, bytes_read - total_written);
            if (bytes_written < 0) {
                close(src_fd);
                close(dst_fd);
                return -1;
            }
            total_written += bytes_written;
        }
    }

    // проверка на ошибку чтения файла
    if (bytes_read < 0) {
        close(src_fd);
        close(dst_fd);
        return -1;
    }

    // и зрываем файлы
    close(src_fd);
    close(dst_fd);

    return 0;
}
