#!/bin/bash

while true; do
    echo "Menu:"
    echo "1. Print lines containing roll numbers"
    echo "2. Display all 7-letter words of the form b---da-"
    echo "3. Create a folder with the current date as its name"
    echo "4. Fetch and print user-names with their length"
    echo "5. Remove all permissions for groups and others in a directory"
    echo "6. Sort employee file and create an alias"
    echo "7. Print lines with two capital letters followed by a space and a capital letter"
    echo "8. Display file content from the 5th to the 8th line"
    echo "9. Exit"
    read -p "Choose an option: " option

    case $option in
        1)
            read -p "Enter filename: " filename
            grep -E '21P[CDTWR][0-9]{2}' "$filename"
            ;;
        2)
            read -p "Enter filename: " filename
            grep -E 'b[a-z]{3}da[a-z]' "$filename"
            ;;
        3)
            folder_name=$(date +"%Y-%m-%d")
            mkdir "$folder_name"
            echo "Folder '$folder_name' created."
            ;;
        4)
            cut -d: -f1 /etc/passwd | while read user; do
                echo "$user (${#user})"
            done
            ;;
        5)
            read -p "Enter directory name: " dirname
            chmod go-rwx "$dirname"/*
            echo "Permissions removed for groups and others."
            ;;
        6)
            read -p "Enter employee file: " empfile
            sort -k3,3 -k1,1 "$empfile"
            alias sort_empfile="sort -k3,3 -k1,1 $empfile"
            echo "Alias 'sort_empfile' created."
            ;;
        7)
            read -p "Enter filename: " filename
            grep -E '[A-Z]{2} [A-Z]' "$filename"
            ;;
        8)
            read -p "Enter filename: " filename
            #sed -n '5,8p' "$filename"
            cat "$filename" | head -8 | tail +5
	    ;;
        9)
            echo "Exiting..."
            break
            ;;
        *)
            echo "Invalid option. Please choose again."
            ;;
    esac
done
