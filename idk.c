void shorten_last_line_by_one_char(t_map *destination)
{
    if (destination->height > 0)
    {
        char *last_line = destination->map[destination->height - 1];
        
        size_t currentLength = strlen(last_line);
        
        // Ensure that the current length is greater than 0 before shortening
        if (currentLength > 0)
        {
            last_line[currentLength - 1] = '\0'; // Shorten the line by one character
        }
    }
}
	void	copy_game(t_map *source, t_map *destination)
	{
		size_t	i;
		size_t	current_width;
		size_t	padding_size = 0;

		source->width = get_longest_line_width(source);
		destination->height = source->height;
		destination->width = source->width;
		destination->player_y = source->player_y;
		destination->player_x = source->player_x;
		destination->player_char = source->player_char;
		destination->map = (char **)malloc(sizeof(char *) * destination->height);
		if (destination->map == NULL)	
			exit(1);
		for (i = 0; i < destination->height; i++)
		{
			current_width = strlen(source->map[i]);
			if (current_width < destination->width)
			{
				// Add '0' characters to the beginning of the line
				padding_size = destination->width - current_width;
				destination->map[i] = (char *)malloc(sizeof(char)
						* (destination->width + 1));
				if (destination->map[i] == NULL)
				{
					fprintf(stderr, "Memory allocation failed\n");
					exit(1);
				}
				memset(destination->map[i], '0', padding_size);
				strcpy(destination->map[i] + padding_size, source->map[i]);
				if(destination->map[destination->height])
				{
				destination->width -=1;
				memset(destination->map[i], '0', padding_size -1);
				strcpy(destination->map[i] + padding_size, source->map[i]);
				}
				destination->map[i][destination->width] = '\0';
					// Null-terminate the string
			}
			else
			{
				destination->map[i] = (char *)malloc(sizeof(char) * (current_width
							+ 1));
				if (destination->map[i] == NULL)
				{
					fprintf(stderr, "Memory allocation failed\n");
					exit(1);
				}
				strcpy(destination->map[i], source->map[i]);
			}
			// Replace spaces and tabs with '0' characters in the line
			for (size_t j = 0; j < destination->width; j++)
			{
				if (destination->map[i][j] == ' ' || destination->map[i][j] == '\t')
					destination->map[i][j] = '0';
			}
		}
		shorten_last_line_by_one_char(destination);
	}
