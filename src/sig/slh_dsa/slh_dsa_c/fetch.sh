#!/bin/bash

# Commit hash and tarball URL
commit="ddbf57e92cb9864c3449e86ebcc1309a9843495b"
rel_url="https://github.com/pq-code-package/slhdsa-c/archive/$commit.tar.gz"
tar_name="$commit.tar.gz"
extracted_dir="slhdsa-c-$commit"

# Download and extract the tarball
wget "$rel_url" -O "$tar_name"
tar -xvzf "$tar_name"

# Copy all files from the commit into the current directory
cp -r "$extracted_dir/"* .

# Clean up
rm -rf "$tar_name" "$extracted_dir"

echo "✅ All files from commit $commit have been copied into the current directory."
