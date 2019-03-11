#include <dirent.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/stat.h>

int strcasecmp_cmp(const void *lhs, const void *rhs) {
    return strcasecmp((const char *)lhs, (const char *)rhs);
}

size_t get_data(DIR *dir, char **array, const char *parent_dir) {
    *array = NULL;
    size_t size = 0, capacity = 0;
    struct dirent *entry;
    char *pathname = malloc(PATH_MAX);
    if (!pathname) {
        free(array);
        array = NULL;
        return 0;
    }
    while ((entry = readdir(dir)) != NULL) {
        snprintf(pathname, PATH_MAX, "%s/%s", parent_dir, entry->d_name);
        struct stat stat_buf;
        if (stat(pathname, &stat_buf) < 0) {
            continue;
        }
        if (!S_ISDIR(stat_buf.st_mode)) {
            continue;
        }
        if (strcmp(".", entry->d_name) == 0 || strcmp("..", entry->d_name) == 0) {
            continue;
        }

        if (size == capacity) {
            if (capacity == 0) {
                capacity = 1;
            }
            if (size == capacity) {
                capacity *= 2;
            }
            char *new_array = realloc(*array, capacity * PATH_MAX);
            if (!new_array) {
                free(*array);
                free(pathname);
                return 0;
            }
            *array = new_array;
        }
        memcpy(*array + size * PATH_MAX, entry->d_name, PATH_MAX);
        ++size;
    }
    free(pathname);
    return size;
}

void traverse(DIR *dir, const char *parent_dir, const char *current_dir) {
    if (current_dir) {
        printf("cd %s\n", current_dir);
    }
    char *new_parent_dir = malloc(PATH_MAX);
    if (!new_parent_dir) {
        return;
    }
    if (current_dir) {
        snprintf(new_parent_dir, PATH_MAX, "%s/%s", parent_dir, current_dir);
    } else {
        snprintf(new_parent_dir, PATH_MAX, "%s", parent_dir);
    }
    char *subdirs;
    size_t num_subdirs = get_data(dir, &subdirs, new_parent_dir);
    if (num_subdirs > 1) {
        qsort((void *)subdirs, num_subdirs, PATH_MAX, strcasecmp_cmp);
    }
    for (size_t i = 0; i != num_subdirs; ++i) {
    }
    for (size_t i = 0; i != num_subdirs; ++i) {
        char *new_parent_dir = malloc(PATH_MAX);
        if (!new_parent_dir) {
            free(subdirs);
            return;
        }
        if (current_dir) {
            snprintf(new_parent_dir, PATH_MAX, "%s/%s", parent_dir, current_dir);
        } else {
            snprintf(new_parent_dir, PATH_MAX, "%s", parent_dir);
        }
        char *pathname = malloc(PATH_MAX);
        if (!pathname) {
            free(subdirs);
            return;
        }
        snprintf(pathname, PATH_MAX, "%s/%s", new_parent_dir, subdirs + i * PATH_MAX);
        DIR *subdir = opendir(pathname);
        if (subdir) {
            traverse(subdir, new_parent_dir, subdirs + i * PATH_MAX);
            closedir(subdir);
        }
        free(pathname);
    }
    free(subdirs);
    if (current_dir) {
        printf("cd ..\n");
    }
}

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Not enough argv\n");
        return 0;
    }
    DIR *dir = opendir(argv[1]);
    if (dir) {
        traverse(dir, argv[1], NULL);
        closedir(dir);
    }
    return 0;
}

