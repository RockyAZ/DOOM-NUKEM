/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BSP.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaporoz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/28 13:09:11 by azaporoz          #+#    #+#             */
/*   Updated: 2018/08/28 13:09:11 by azaporoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#define POLYGON
#define BSPNode

struct BSPNode
{
    POLYGON *splitter;
    BSPNode *FrontChild;
    BSPNode *BackChild;
};

void RenderBSP (NODE * CurrentNode)
{
    int Result;
    Result = ClassifyPoint(CameraPosition, CurrentNode->Polygon);
    if (Result==Front)
    {
        if (CurrentNode->BackChild!=NULL)
            RenderBSP (CurrentNode->BackChild);
        DrawPolygon(CurrentNode->Polygon);
        if (CurrentNode->FrontChild!=NULL)
            RenderBSP (CurrentNode->FrontChild);
    }
    else
    {
        if (CurrentNode->FrontChild!=NULL)
            RenderBSP (CurrentNode->FrontChild);
        DrawPolygon(CurrentNode->Polygon);
        if (CurrentNode->BackChild!=NULL)
            RenderBSP (CurrentNode->BackChild);
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
void WalkBspTree(NODE *Node,D3DVECTOR *pos)
{
POLYGON *shared;
int result=ClassifyPoint(pos,Node-> Splitter);

if (result==CP_FRONT)
{
    shared=Node-> Splitter->SameFacingShared;
    if (Node-> Back!=NULL)
        WalkBspTree(Node-> Back,pos);
    lpDevice-> DrawIndexedPrimitive(D3DPT_TRIANGLELIST,D3DFVF_LVERTEX,&Node-> Splitter-> VertexList[0],Node-> Splitter-> NumberOfVertices,&Node-> Splitter->Indices[0],Node-> Splitter-> NumberOfIndices,NULL);

    while (shared!=NULL)
    {
        lpDevice-> DrawIndexedPrimitive(D3DPT_TRIANGLELIST,D3DFVF_LVERTEX,&shared-> VertexList[0],shared-> NumberOfVertices,&shared-> Indices[0],shared-> NumberOfIndices,NULL);
        shared=shared-> SameFacingShared;
    }

    if (Node->Front!=NULL)
        WalkBspTree(Node->Front,pos);
    return ;
}

// this means we are at back of node 
    shared=Node->Splitter->OppositeFacingShared;
    if (Node->Front!=NULL)
        WalkBspTree(Node->Front,pos);

    while (shared!=NULL)
    {
        lpDevice-> DrawIndexedPrimitive(D3DPT_TRIANGLELIST,D3DFVF_LVERTEX,&shared-> VertexList[0],shared-> NumberOfVertices,&shared-> Indices[0],shared-> NumberOfIndices,NULL);
        shared=shared-> OppositeFacingShared;
    }
    if (Node-> Back!=NULL) WalkBspTree(Node->Back,pos);
        return;
}



////////////////////////////////////////////////////////////////////////////////////////////////////////
other site::
////////////////////////////////////////////////////////////////////////////////////////////////////////
Some example pseudo code for a simple back-to-front renderer would therefore be:

function render(node)
{
  if this node is a leaf
    {
      draw this node to the screen
    }
  else
    {
      determine which side of the dividing line the viewpoint is
      
      if it is on the left side
        {
          render(right subnode)
          render(left subnode)
        }
      else
        {
          render(left subnode)
          render(right subnode)
        }
    }
}



////////////////////////////////////////////////////////////////////////////////////////////////////////
other site::
////////////////////////////////////////////////////////////////////////////////////////////////////////
void    Build_BSP_Tree (BSP_tree *tree, list polygons)
{
   polygon   *root = polygons.Get_From_List ();
   tree->partition = root->Get_Plane ();
   tree->polygons.Add_To_List (root);
   list      front_list,
             back_list;
   polygon   *poly;
   while ((poly = polygons.Get_From_List ()) != 0)
   {
      int   result = tree->partition.Classify_Polygon (poly);
      switch (result)
      {
         case COINCIDENT:
            tree->polygons.Add_To_List (poly);
            break;
         case IN_BACK_OF:
            backlist.Add_To_List (poly);
            break;
         case IN_FRONT_OF:
            frontlist.Add_To_List (poly);
            break;
         case SPANNING:
            polygon   *front_piece, *back_piece;
            Split_Polygon (poly, tree->partition, front_piece, back_piece);
            backlist.Add_To_List (back_piece);
            frontlist.Add_To_List (front_piece);
            break;
      }
   }
   if ( ! front_list.Is_Empty_List ())
   {
      tree->front = new BSP_tree;
      Build_BSP_Tree (tree->front, front_list);
   }
   if ( ! back_list.Is_Empty_List ())
   {
      tree->back = new BSP_tree;
      Build_BSP_Tree (tree->back, back_list);
   }
}
  