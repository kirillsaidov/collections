#include <stdio.h>
#include <stdbool.h>
#include "../third_party/vita/vita.h"

#define ZHBK_PACKAGE_FILES (2 + 0)
#define ZHBK_PACKAGE_FOLDER "../assets/"
#define ZHBK_INSTALL_FOLDER "../imgs/"
// #define ZHBK_INSTALL_FOLDER "C:\\Users\\Public\\AppData\\ZHBK"
// #define ZHBK_LICENSE_FILE "C:\\Users\\Public\\AppData\\ZHBK\\zhbk.license"

#define LOG(...) printf("INSTALLER: " __VA_ARGS__)

int main(void) {
    // init global mallocator
    vt_mallocator_t *malloctr = vt_mallocator_create();

    // check if sotware already installed
    if (vt_path_exists(ZHBK_INSTALL_FOLDER)) {
        LOG("Software already installed. Reinstall? [y/N]: ");

        char ret = tolower(getchar());
        if (ret != 'y') {
            LOG("Cancel operation...\n");
            goto label_main_done;
        }

        LOG("Removing previous installation...\n");

        // delete install folder
        if (!vt_path_rmdir_recurse(ZHBK_INSTALL_FOLDER)) {
            LOG("System error...\n");
            goto label_main_done;
        }
    }

    LOG("Installing the software...\n");
    LOG("Checking package contents...\n");
    
    // check all files in install package
    vt_plist_t *dirlist = vt_plist_create(ZHBK_PACKAGE_FILES, malloctr);
    dirlist = vt_path_listdir(dirlist, ZHBK_PACKAGE_FOLDER, true);
    if (vt_plist_len(dirlist) != ZHBK_PACKAGE_FILES) {
        LOG("Broken package! Cancel operation...\n");
        goto label_main_done;
    }

    // remove the installer from dirlist
    VT_FOREACH(i, 0, vt_plist_len(dirlist)) {
        vt_str_t *s = (vt_str_t*)vt_plist_get(dirlist, i);
        if (vt_str_can_find(vt_str_z(s), "install")) {
            vt_plist_remove(dirlist, i, VT_REMOVE_STRATEGY_FAST);
            break;
        }
    }

    // create install folder
    if (!vt_path_exists(ZHBK_INSTALL_FOLDER) && !vt_path_mkdir(ZHBK_INSTALL_FOLDER)) {
        LOG("System error...\n");
        goto label_main_done;
    }

    LOG("Moving packages...\n");
    
    // move files to install folder
    VT_FOREACH(i, 0, vt_plist_len(dirlist)) {
        vt_str_t *s = (vt_str_t*)vt_plist_get(dirlist, i);
        vt_str_t *n = vt_str_dup(s);
        LOG("Found %s\n", vt_str_z(s));

        vt_str_insert(s, ZHBK_PACKAGE_FOLDER, 0);
        vt_str_insert(n, ZHBK_INSTALL_FOLDER, 0);

        LOG("Moving to: %s\n", vt_str_z(n));

        vt_path_rename(vt_str_z(s), vt_str_z(n));
    }

    // delete this executable
    vt_path_remove(vt_str_z(vt_path_get_this_exe_location(malloctr)));

label_main_done:
    LOG("Done.\n");
    vt_mallocator_print_stats(malloctr->stats);
    vt_mallocator_destroy(malloctr);
    return 0;
}

