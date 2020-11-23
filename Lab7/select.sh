#! /usr/bin/bash

DIR="$1"

echo "Total # of regular files in current working directory: $(find "${DIR:-.}" -maxdepth 1 -type f -ls | wc -l)"

echo "Total # of directories in current working directory: $(find "${DIR:-.}" -type d -ls | wc -l)"

