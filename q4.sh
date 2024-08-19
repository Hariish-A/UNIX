#!/bin/bash

# Function to create backup
backup_directory() {
    src_dir=$1
    backup_dir=$2

    # Check if source directory exists
    if [ ! -d "$src_dir" ]; then
        echo "Source directory does not exist."
        exit 1
    fi

    # Create backup directory if it doesn't exist
    mkdir -p "$backup_dir"

    # Copy contents of source directory to backup directory
    cp -r "$src_dir/"* "$backup_dir"

    # Navigate to backup directory
    cd "$backup_dir" || exit

    # Create folders for each extension and move files
    for file in .; do
        if [ -f "$file" ]; then
            ext="${file##*.}"
            # Create folder with extension name if it doesn't exist
            mkdir -p "$ext"
            # Move file to the respective folder
            mv "$file" "$ext/"
        fi
    done

    echo "Backup completed successfully."
}

# Check if correct number of arguments are provided
if [ "$#" -ne 2 ]; then
    echo "Usage: $0 <source_directory> <backup_directory>"
    exit 1
fi

# Call the function with provided arguments
backup_directory "$1" "$2"
