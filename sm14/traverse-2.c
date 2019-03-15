#include <dirent.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct DirList
{
    char **p_dirs;
    size_t n_dirs;
    size_t capacity;
} DirList;

void free_dir_list(DirList *dir_list) {
    if (!dir_list->n_dirs) {
        return;
    }
    for (size_t i = 0; i != dir_list->n_dirs; ++i) {
        free(dir_list->p_dirs[i]);
    }
    free(dir_list->p_dirs);
    dir_list->p_dirs = NULL;
    dir_list->n_dirs = 0;
    dir_list->capacity = 0;
}

void ls(DIR *dir, DirList *dir_list) {
    struct dirent *entry;
    while ((entry = readdir(dir))) {
        if (!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, "..")) {
            continue;
        }
        if (entry->d_type != DT_DIR) {
            // Not a directory.
            continue;
        }
        size_t dir_size = strlen(entry->d_name) + 1;
        if (dir_size > PATH_MAX) {
            continue;
        }
        if (dir_list->n_dirs == dir_list->capacity) {
            if (dir_list->capacity) {
                dir_list->capacity *= 2;
            } else {
                dir_list->capacity = 1;
            }
            char **new_p_dirs = realloc(dir_list->p_dirs, dir_list->capacity * sizeof(char *));
            if (!new_p_dirs) {
                free_dir_list(dir_list);
                return;
            }
            dir_list->p_dirs = new_p_dirs;
        }
        dir_list->p_dirs[dir_list->n_dirs] = malloc(dir_size);
        if (!dir_list->p_dirs[dir_list->n_dirs]) {
            free_dir_list(dir_list);
            return;
        }
        memcpy(dir_list->p_dirs[dir_list->n_dirs], entry->d_name, dir_size);
        ++dir_list->n_dirs;
    }
}

int strcasecmp_(const void *lhs, const void *rhs) {
    char **lhs_ = (char **)lhs;
    char **rhs_ = (char **)rhs;
    return strcasecmp(*lhs_, *rhs_);
}

void get_full_path(
        char *dst,
        const char *dir_path, size_t dir_path_length,
        const char *dir_name) {
    strcpy(dst, dir_path);
    dst[dir_path_length] = '/';
    strcpy(dst + dir_path_length + 1, dir_name);
}

void traverse(const char *dir_path, size_t dir_path_length, const char *dir_name) {
    char full_path[PATH_MAX];
    get_full_path(
            full_path,
            dir_path, dir_path_length,
            dir_name);
    size_t full_path_length = strlen(full_path);
    DirList subdirs;
    DIR *dir = opendir(full_path);
    ls(dir, &subdirs);
    closedir(dir);

    if (subdirs.n_dirs > 1) {
        qsort(subdirs.p_dirs, subdirs.n_dirs, sizeof(char *), strcasecmp_);
    }

    for (size_t i = 0; i != subdirs.n_dirs; ++i) {
        if (full_path_length + strlen(subdirs.p_dirs[i]) > PATH_MAX - 1) {
            continue;
        }
        char full_subdir_path[PATH_MAX];
        get_full_path(
                full_subdir_path,
                full_path, full_path_length,
                subdirs.p_dirs[i]
                );
        DIR *dir = opendir(full_subdir_path);
        if (dir) {
            closedir(dir);
            printf("cd %s\n", subdirs.p_dirs[i]);
            traverse(full_path, full_path_length, subdirs.p_dirs[i]);
            printf("cd ..\n");
        }
    }
    free_dir_list(&subdirs);
}

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Not enough argv\n");
        return 0;
    }
    DIR *dir = opendir(argv[1]);
    if (dir) {
        closedir(dir);
        char empty_dir_name[1] = "\0";
        traverse(argv[1], strlen(argv[1]), empty_dir_name);
    }
    return 0;
}

