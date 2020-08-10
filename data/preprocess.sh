#!/bin/zsh

# Delete the header
for file in *.csv; do
   sed -i -e 1d $file
done

# Clean
rm *.csv-e
