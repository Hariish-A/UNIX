#!/bin/bash

echo "Type of files Count"

regular_files=$(find . -maxdepth 1 -type f | wc -l)
echo "Regular files $regular_files"

directories=$(find . -maxdepth 1 -type d | wc -l)
echo "Directories $directories"

soft_links=$(find . -maxdepth 1 -type l | wc -l)
echo "Softlinks $soft_links"

#to create softlink (ln -s original.txt softlink.txt)
#to create hardlink (ln original.txt hardlink.txt)
