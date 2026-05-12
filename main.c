/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunlee <hyunlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 14:42:48 by hyunlee           #+#    #+#             */
/*   Updated: 2026/05/12 16:55:06 by hyunlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include "get_next_line.h"

int main(void)
{
    int     fd;
    char    *line;

    // 1. test.txt 파일을 읽기 전용(O_RDONLY)으로 엽니다.
    fd = open("test.txt", O_RDONLY);
    if (fd == -1)
    {
        printf("Error: test.txt 파일을 열 수 없습니다.\n");
        return (1);
    }

    // 2. 파일의 끝(NULL)에 도달할 때까지 계속해서 한 줄씩 뽑아옵니다.
    while (1)
    {
        line = get_next_line(fd);
        
        // GNL이 NULL을 반환하면 다 읽었거나 에러가 났다는 뜻이므로 루프를 탈출합니다.
        if (line == NULL)
            break;
        
        // 3. 뽑아온 한 줄을 출력합니다.
        // (GNL이 자체적으로 '\n'을 포함해서 주므로 printf 안에 따로 \n을 넣지 않습니다.)
        printf("%s", line);
        
        // 4. 아주 중요! GNL이 malloc으로 할당해 준 메모리이므로, 
        // 출력이 끝났다면 잊지 말고 꼭 free를 해줍니다.
        free(line);
    }

    // 5. 다 읽은 파일은 예의 바르게 닫아줍니다.
    close(fd);
    
    return (0);
}