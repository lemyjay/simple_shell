#!/bin/bash

# Specify the target file where you want to copy the contents
target_file="all_codes.txt"

# Function to append four lines of space
append_spaces() {
	    for ((i=1; i<=4; i++)); do
		            echo "" >> "$target_file"
			        done
			}

		# Copy the contents of .h files
		for header_file in *.h; do
			    append_spaces
			        echo "// Start of $header_file" >> "$target_file"
				    cat "$header_file" >> "$target_file"
				        append_spaces
					    echo "// End of $header_file" >> "$target_file"
				    done

				    # Copy the contents of .c files
				    for source_file in *.c; do
					        if [ "$source_file" != "shell.c" ]; then
							        append_spaces
								        echo "// Start of $source_file" >> "$target_file"
									        cat "$source_file" >> "$target_file"
										        append_spaces
											        echo "// End of $source_file" >> "$target_file"
												    fi
											    done

											    # Copy the contents of shell.c as the last file
											    if [ -e shell.c ]; then
												        append_spaces
													    echo "// Start of shell.c" >> "$target_file"
													        cat "shell.c" >> "$target_file"
														    append_spaces
														        echo "// End of shell.c" >> "$target_file"
											    fi

											    echo "Contents of .h and .c files have been copied to $target_file"

