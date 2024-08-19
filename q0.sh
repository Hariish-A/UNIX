x#!/bin/bash

while true; do
    echo "Choose an option:"
    echo "1. Print the list of files present in the current working directory, along with the count in one command."
    echo "2. List the names of directories that start with letter 'f'."
    echo "3. Print only the filenames and size of the two smallest sized files in your current working directory."
    echo "4. Create an alias called 'tclean' that would display the content of files from your current directory that starts with the letter 't'."
    echo "5. Display the number of files that start with letter 'f'."
    echo "6. Display only the lines common to two files."
    echo "7. List five recently used commands."
    echo "8. Copy the file 'temp1' from 'dir1' to 'dir2' and call it 'temp2'."
    echo "9. Copy the contents of 3 files to a new file using one command."
    echo "10. Display all the files in your home directory for which the group has write permissions."
    echo "11. Ensure that all files (directories need not be considered) created by users will have the default permission rw-rw-r--."
    echo "12. Display the name of all files in the current directory in uppercase."
    echo "13. Exit"
    read -p "Enter your choice (1-13): " choice

    case $choice in
        1)
            file_list=$(ls -1)
            file_count=$(echo "$file_list" | wc -l)
            echo "$file_list"
            echo "Total number of files: $file_count"
            ;;
        2)
            echo "Directories starting with 'f' in $(pwd):"
            find . -maxdepth 1 -type d -name 'f*'
            ;;
        3)
	    echo "Filenames and sizes of the two smallest files in $(pwd):"
	    ls -S -s
	    ;;
        4)
            alias tclean = "cat t*"
            echo "Created alias 'tclean' to display contents of files starting with 't'."
            ;;
        5)
            find . -maxdepth 1 -type f -name 'f*' | wc -l > q1.txt
	    echo "There are $(cat q1.txt) files that start with letter 'f'."
	    ;;
        6)
            read -p "Enter the first file: " file1
            read -p "Enter the second file: " file2
            comm -12 <(sort "$file1") <(sort "$file2")
            ;;
        7)
            history | tail -n 5
            ;;
        8)
            cp ~/dir1/temp1 ~/dir2/temp2
            echo "Copied 'temp1' from 'dir1' to 'dir2' and renamed it to 'temp2'."
            ;;
        9)
            read -p "Enter the first file: " file1
            read -p "Enter the second file: " file2
            read -p "Enter the third file: " file3
            cat "$file1" "$file2" "$file3" > combined_file
            echo "Contents of the three files have been copied to 'combined_file'."
            ;;
        10)
            echo "Files in your home directory with group write permissions:"
            find ~ -maxdepth 1 -type f -perm -g=w
            ;;
        11)
            echo "Setting default file permissions to rw-rw-r--..."
            umask 0027
            ;;
        12)
            echo "Files in $(pwd) in uppercase:"
            for file in *; do
                echo "${file^^}"
            done
            ;;
        13)
            echo "Exiting..."
            break
            ;;
        *)
            echo "Invalid choice. Please try again."
            ;;
    esac
done

