*This project has been created as part of the 42 curriculum by hyunlee.*

# get_next_line

## Result

<p align="center">
  <img src="./assets/score-100.png" alt="get_next_line 100 score" width="260">
</p>
<p align="center">
  <img src="./assets/tester-ok.png" alt="get_next_line tester OK result" width="100%">
</p>

## Description
get_next_line is a 42 curriculum project that implements a function for reading one line at a time from a file descriptor. The goal is to understand static variables, repeated `read` calls, and careful heap memory management across successive function calls.

The function returns the next available line, including the trailing newline when one is present. It keeps unread data in a static backup buffer so that later calls can continue from the exact same file position.

### Implementation Notes

Input is read in chunks controlled by `BUFFER_SIZE`. Each chunk is appended to the backup buffer until a newline or end-of-file is reached.

When a complete line is available, the line is extracted and returned to the caller. Any remaining bytes after the newline are stored back in the static backup buffer for the next call.

Allocated buffers are released on end-of-file and read errors so repeated calls do not keep stale memory alive.

## Instructions
Compile with a chosen `BUFFER_SIZE`:

```sh
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c
```

Include the header and call `get_next_line` with a valid file descriptor:

```c
#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("test.txt", O_RDONLY);
	line = get_next_line(fd);
	while (line != NULL)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}
```

## Resources
- Linux manual pages: `man 2 read`, `man 3 malloc`, `man 3 free`
- My Notion study notes: https://coconut-munchkin-952.notion.site/2026_42gs-79872d44d901462c8b583fa5b48e7f03

AI assistance was used during the learning and debugging process. Google's Gemini model was used to study static variables, discuss memory ownership, and analyze segmentation faults or leaks without generating or copy-pasting the implementation code.