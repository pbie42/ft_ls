/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_swap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbie <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/18 15:16:39 by pbie              #+#    #+#             */
/*   Updated: 2017/06/18 15:19:09 by pbie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_files*						get_prevnd(t_files* head, t_files* a)
{
    if(head == a){
        // node[a] is first node 
        return NULL;
    }
    t_files* temp = head; // temp is current node
    t_files* pre_a = NULL; 

    while(temp && temp!=a){ //search while not reach to end or the node
        pre_a = temp;          // find previous node   
        temp = temp->next;
    }
    if(temp!=a){// node[a] not present in list
        fprintf(stderr, "\n error: node not found!\n");
        exit(EXIT_FAILURE); // bad technique to exit()
    }
    return pre_a;
}

void							ft_list_swap(t_files **head, t_files **a, t_files **b)
{
  // first check if a agrgument is null                 
  if( (*head) == NULL ||               // Empty list         
        (*a) == NULL || (*b) == NULL){     // one node is null  
       // Nothing to swap, just return 
        printf("\n Nothing to swap, just return \n");
        return;
  }     

  // find previos nodes
  t_files* pre_a = get_prevnd(*head, *a);
  t_files* pre_b = get_prevnd(*head, *b);

  //Now swap previous node's next
  if(pre_a) pre_a->next = (*b); // a's previous become b's previous, and 
  if(pre_b) pre_b->next = (*a); // b's previous become a's previous

  //Now swap next fiels of candidate nodes  
  t_files* temp = NULL;  
    temp = (*a)->next;
  (*a)->next = (*b)->next;
  (*b)->next = temp;

  //change head: if any node was a head 
  if((*head)==(*a)) 
     *head = *b;
  else 
     if((*head)==(*b))  
        *head = *a;
}