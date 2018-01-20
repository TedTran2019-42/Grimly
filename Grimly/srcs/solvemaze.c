/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solvemaze.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttran <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 18:10:33 by ttran             #+#    #+#             */
/*   Updated: 2018/01/19 18:10:34 by ttran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "grimly.h"

static int isQueueEmpty(t_queue *queue)
{
    if (queue == NULL)
        return (1);
    else
        return (0);
}

/* This means popping from the FRONT of the queue. */
static t_bfs   *popQueue(t_queue **queue)
{
    t_queue *head;
    t_queue *FUCKHEAD;

    FUCKHEAD = NULL;
    head = *queue;
    while (head->next != NULL)
    {
        FUCKHEAD = head;
        head = head->next;
    }
    if (FUCKHEAD != NULL)
        FUCKHEAD->next = NULL;
    else
        *queue = NULL;
    return (head->node);
}

/* This is putting to the end of the queue. */
static void    pushQueue(t_bfs *node, t_queue **queue)
{
    t_queue *newTail;

    if (*queue == NULL)
    {    
        *queue = malloc(sizeof(t_queue));
        (*queue)->next = NULL;
        (*queue)->node = node;
    }
    else
    {
        newTail = malloc(sizeof(t_queue));
        newTail->next = *queue;
        newTail->node = node;
        *queue = newTail;
    }    
}

t_bfs   *genNorth(t_queue **queue, t_key *key, t_bfs *item)
{
    t_bfs *FUCKYEAH;

    if (item->y > 0)
    {
        if (key->arr[item->y - 1][item->x] == key->key[4])
        {
            FUCKYEAH = malloc(sizeof(t_bfs));
            FUCKYEAH->parent = item;
            FUCKYEAH->y = item->y - 1;
            FUCKYEAH->x = item->x;
            return (FUCKYEAH);
        }
        else if (key->arr[item->y - 1][item->x] == key->key[1])
        {
            FUCKYEAH = malloc(sizeof(t_bfs));
            FUCKYEAH->parent = item;
            FUCKYEAH->y = item->y - 1;
            FUCKYEAH->x = item->x;
            pushQueue(FUCKYEAH, queue);
        }
    }
    return (NULL);
}

t_bfs   *genWest(t_queue **queue, t_key *key, t_bfs *item)
{
    t_bfs *FUCKYEAH;

    if (item->x > 0)
    {
        if (key->arr[item->y][item->x - 1] == key->key[4])
        {
            FUCKYEAH = malloc(sizeof(t_bfs));
            FUCKYEAH->parent = item;
            FUCKYEAH->y = item->y;
            FUCKYEAH->x = item->x - 1;
            return (FUCKYEAH);
        }
        else if (key->arr[item->y][item->x - 1] == key->key[1])
        {
            FUCKYEAH = malloc(sizeof(t_bfs));
            FUCKYEAH->parent = item;
            FUCKYEAH->y = item->y;
            FUCKYEAH->x = item->x - 1;
            pushQueue(FUCKYEAH, queue);
        }
    }
    return (NULL);
}

t_bfs   *genEast(t_queue **queue, t_key *key, t_bfs *item)
{
    t_bfs *FUCKYEAH;

    if (item->x < key->column - 1)
    {
        if (key->arr[item->y][item->x + 1] == key->key[4])
        {
            FUCKYEAH = malloc(sizeof(t_bfs));
            FUCKYEAH->parent = item;
            FUCKYEAH->y = item->y;
            FUCKYEAH->x = item->x + 1;
            return (FUCKYEAH);
        }
        else if (key->arr[item->y][item->x + 1] == key->key[1])
        {
            FUCKYEAH = malloc(sizeof(t_bfs));
            FUCKYEAH->parent = item;
            FUCKYEAH->y = item->y;
            FUCKYEAH->x = item->x + 1;
            pushQueue(FUCKYEAH, queue);
        }
    }
    return (NULL);
}

t_bfs   *genSouth(t_queue **queue, t_key *key, t_bfs *item)
{
    t_bfs *FUCKYEAH;

    if (item->y < key->row - 1)
    {
        if (key->arr[item->y + 1][item->x] == key->key[4])
        {
            FUCKYEAH = malloc(sizeof(t_bfs));
            FUCKYEAH->parent = item;
            FUCKYEAH->y = item->y + 1;
            FUCKYEAH->x = item->x;
            return (FUCKYEAH);
        }
        else if (key->arr[item->y + 1][item->x] == key->key[1])
        {
            FUCKYEAH = malloc(sizeof(t_bfs));
            FUCKYEAH->parent = item;
            FUCKYEAH->y = item->y + 1;
            FUCKYEAH->x = item->x;
            pushQueue(FUCKYEAH, queue);
        }
    }
    return (NULL);
}

/* 0 is up, 1 is left, 2 is right, 3 is down. */
t_bfs *genSuccessor(t_queue **queue, int direction, t_key *key, t_bfs *item)
{
    t_bfs *done;

    if (direction == 0)
    {
        if ((done = genNorth(queue, key, item)) != NULL)
            return (done);
    }
    else if (direction == 1)
    {
        if ((done = genWest(queue, key, item)) != NULL)
            return (done);
    }
    else if (direction == 2)
    {
        if ((done = genEast(queue, key, item)) != NULL)
            return (done);
    }
    else
    { 
        if ((done = genSouth(queue, key, item)) != NULL)
            return (done);
    }
    return (NULL);
}

t_bfs   *bfs(t_bfs *entrance, t_key *key)
{
    t_queue *queue;
    t_bfs *item;
    int i;
    t_bfs *done;

    queue = NULL;
    pushQueue(entrance, &queue);
    while (isQueueEmpty(queue) != 1)
    {
        item = popQueue(&queue);
        key->arr[item->y][item->x] = 0;
        while (i < 4)
        {
            if ((done = genSuccessor(&queue, i, key, item)) != NULL)
                return (done); 
            i++;
        }
        i = 0;
    }
    return (NULL);
}

/* initQ for initialize queue */
int solvemaze(t_key *key)
{
    t_bfs *entrance;
    
    entrance = malloc(sizeof(t_bfs));
    entrance->x = key->startx;
    entrance->y = key->starty;
    entrance->parent = NULL;
    if (bfs(entrance, key) == NULL)
        return (-1);
    return (0);
}