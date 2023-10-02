#include<iostream>
#include<algorithm>
#include<cstring>
#include<vector>
 
#define NAME_MAXLEN 6
#define PATH_MAXLEN 1999
#define FOLDER_MAX 50000
#define CHILD_MAX 30
 
using namespace std;
 
struct Folder {
    char name[NAME_MAXLEN + 1];
    Folder* parent;
    vector<Folder*> child;
    int count;
 
    void init(char _name[], Folder* _parent, int _count) {
        strcpy(name, _name);
        parent = _parent;
        child.clear();
        count = _count;
    }
 
} Folders[FOLDER_MAX];
int folder_cnt;
 
Folder* root;
 
Folder* new_folder(char name[], Folder* parent, int count) {
    Folder* folder = &Folders[folder_cnt++];
 
    folder->init(name, parent, count);
    parent->child.emplace_back(folder);
 
    return folder;
}
 
void init(int n) {
    folder_cnt = 0;
 
    char name[2] = { '/', 0 };
    root = &Folders[folder_cnt++];
    root->init(name, nullptr, 0);
}
 
int mycmp(char *a, char *b) {
    int i = 0;
 
    while ((a[i] == b[i++])) {
        if ((a[i] == 0 || a[i] == '/') && (b[i] == 0)) return i;
    }
    return -1;
}
 
Folder* get_dir(Folder* folder, char* path) {
    while (folder) {
        if (*path == 0) return folder;
 
        for (auto c: folder->child) {
            int len = mycmp(path, c->name);
            if (len > 0) {
                folder = c;
                path += len + 1;
                break;
;           }
        }
    }
    return nullptr;
}
 
Folder* get_path(char path[]) {
    if (path[1] == 0) {
        return root;
    }
    return get_dir(root, path + 1);
}
 
void update(Folder* folder, int amount) {
    while (folder) {
        folder->count += amount;
        folder = folder->parent;
    }
}
 
void cmd_mkdir(char path[PATH_MAXLEN + 1], char name[NAME_MAXLEN + 1]) {
    Folder* parent = get_path(path);
    new_folder(name, parent, 0);
 
    update(parent, 1);
}
 
Folder* rm;
void cmd_rm(char path[PATH_MAXLEN + 1]) {
    Folder* folder = get_path(path);
    Folder* parent = folder->parent;
 
    auto f = find(parent->child.begin(), parent->child.end(), folder);
    parent->child.erase(f);
 
    update(parent, -(folder->count+1));
     
    rm = folder;
}
 
 
void cmd_cp_mkdir(Folder* srcFolder, Folder* dstFolder) {
    Folder* new_fold = new_folder(srcFolder->name, dstFolder, srcFolder->count);
 
    for (Folder* f: srcFolder->child) {
        cmd_cp_mkdir(f, new_fold);
    }
}
 
void cmd_cp(char srcPath[PATH_MAXLEN + 1], char dstPath[PATH_MAXLEN + 1]) {
    Folder* srcFolder = get_path(srcPath);
    Folder* dstFolder = get_path(dstPath);
    cmd_cp_mkdir(srcFolder, dstFolder);
 
    update(dstFolder, srcFolder->count + 1);
}
 
void cmd_mv(char srcPath[PATH_MAXLEN + 1], char dstPath[PATH_MAXLEN + 1]) {
    cmd_rm(srcPath);
 
    Folder* dstFolder = get_path(dstPath);
    rm->parent = dstFolder;
    dstFolder->child.emplace_back(rm);
 
    update(dstFolder, rm->count + 1);
}
 
int cmd_find(char path[PATH_MAXLEN + 1]) {
    Folder* folder = get_path(path);
 
    return folder->count;
}