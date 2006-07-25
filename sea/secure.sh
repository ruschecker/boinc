#! /bin/sh

# Make a BOINC installation "secure"
# Create groups and users, set file/dir ownership and protection
#
# Execute this as root in the BOINC directory
# You must have already run the installer script
# that creates the switcher/ and locale/ directories, and their contents

# In addition, you should add boinc_master and boinc_projects
# to the supplementary group list of users who will administer BOINC.
# e.g.:
# usermod -G boinc_master,boinc_projects -a mary

function make_boinc_users() {
    groupadd boinc_master
    groupadd boinc_projects
    useradd boinc_master -g boinc_master
    useradd boinc_projects -g boinc_projects
}

function check_login() {
    if [ `whoami` != 'root' ]
    then
        echo 'This script must be run as root'
        exit
    fi
}

# set_perm path user group perm
#   set a file or directory to the given ownership/permissions
function set_perm() {
    chown $2:$3 $1
    chmod $4 $1
}

# same, but apply to all subdirs and files
#
function set_perm_recursive() {
    chown -R $2:$3 $1
    chmod -R $4 $1
}

# same, but apply to items in the given dir
#
function set_perm_dir() {
    for file in $(ls $1)
    do
        path=$1/$file
        set_perm $path $2 $3 $4
    done
}

check_login

echo "Changing file ownership to user $user and group $group - OK? (y/n)"
read line
if [ "$line" != "y" ]
then
    exit
fi

make_boinc_users

set_perm_recursive . boinc_master boinc_master u+rw,g+rw,o+r-w
set_perm . boinc_master boinc_master 0775
if [-f gui_rpc_auth.cfg] then
    set_perm gui_rpc_auth.cfg boinc_master boinc_master 0660
fi

if [-d projects] then
    set_perm_recursive projects boinc_master boinc_project u+rw,g+rw,o+r-w
    set_perm projects boinc_master boinc_master 0775
fi

if [-d slots] then
    set_perm_recursive slots boinc_master boinc_project u+rw,g+rw,o+r-w
    set_perm slots boinc_master boinc_master 0775
fi

set_perm switcher/switcher boinc_project boinc_project 6551
set_perm switcher/setprojectgrp boinc_master boinc_project 2500
set_perm switcher boinc_master boinc_master 0550

set_perm_recursive locale boinc_master boinc_master u+r-w,g+r-w,o-rwx

set_perm boinc_client boinc_master boinc_master 6555
set_perm boinc_manager boinc_master boinc_master 2555
