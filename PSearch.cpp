#include <stdio.h>
#include <string>
#include <dirent.h>
#include <vector>
#include <stdlib.h>
#include <string.h>
using namespace std;

void ls(string const& name, bool recursive, vector<string>& ret) {
    printf("ls(%s)\n", name.c_str());
    DIR* dir = opendir(name.c_str());
    if (dir == nullptr) return;
    for (dirent* d = readdir(dir); d != nullptr; d = readdir(dir)) {
        printf("ls(%s): %s\n", name.c_str(), d->d_name);
        if (recursive && d->d_type == DT_DIR) {
            if (strcmp(d->d_name, ".") == 0) continue;
            if (strcmp(d->d_name, "..") == 0) continue;
            ls(name + string("/") + d->d_name, true, ret);
        }
        else {
            ret.push_back(d->d_name);
        }
    }
    closedir(dir);
}

int main(int argc, char** argv) {
    string dir = argc > 1 ? argv[1] : ".";
    vector<string> files;
    ls(dir, true, files);
    for (auto file : files) {
        printf("%s\n", file.c_str());
    }
}