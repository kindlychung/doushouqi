// *******************************************************************
//   (C) Copyright 2014 Leiden Institute of Advanced Computer Science
//   Universiteit Leiden
//   All Rights Reserved
// *******************************************************************
// Open Dag 21 maart 2014 --- King of the Jungle
// *******************************************************************
// FILE INFORMATION:
//   File:     search.cc (Depends on: search.h)
//   Author:   Jonathan K. Vis
//   Revision: 0.01a
//   Date:     2014/03/18
// *******************************************************************
// DESCRIPTION:
//   Implementatie van de zoekalgoritmen.
// *******************************************************************

#include "search.h"

uint64_t node_count = 0;
uint64_t leaf_count = 0;

// quiescence search without bounds by extending only captures
int quiescence(Position &position)
{
  ++node_count;

  // check for a winning position
  if (position.is_won())
  {
    ++leaf_count;
    return -INFINITY / 2;
  } // if

  Move_list move_list;
  position.generate_moves(move_list);

  // check for a stalemate position
  if (move_list.size() <= 0)
  {
    ++leaf_count;
    return 0;
  } // if

  // resursively search all capture sequences
  int alpha = -INFINITY;
  for (int i = 0; i < move_list.size(); ++i)
  {
    if (move_list.move(i).is_capture())
    {
      position.do_move(move_list.move(i));
      int const value = -quiescence(position);
      position.undo_move(move_list.move(i));
      if (value > alpha)
      {
        alpha = value;
      } // if
    } // if
  } // for

  // if no captures can be made from the current position return the
  // static evaluation of this position
  if (alpha == -INFINITY)
  {
    ++leaf_count;
    alpha = position.evaluate();
  } // if

  return alpha;
} // quiescence

// bounded quiescence search with ``standing pat'' in a fail-soft
// framework by extending only captures
int quiescence(Position &position,
               int       alpha,
               int       beta)
{
  ++node_count;

  // check for a winning position
  if (position.is_won())
  {
    ++leaf_count;
    return -INFINITY / 2;
  } // if

  // ``standing pat'' establishes a lower bound on the evaluation
  // be careful with Zugzwang positions
  int const value = position.evaluate();
  if (value > alpha)
  {
    alpha = value;
    if (alpha >= beta)
    {
      ++leaf_count;
      return alpha; // fail-soft
    } // if
  } // if

  Move_list move_list;
  position.generate_moves(move_list);

  // check for a stalemate position
  if (move_list.size() <= 0)
  {
    ++leaf_count;
    return 0;
  } // if

  // recursively search all capture sequences
  for (int i = 0; i < move_list.size(); ++i)
  {
    if (move_list.move(i).is_capture())
    {
      position.do_move(move_list.move(i));
      int const value = -quiescence(position, -beta, -alpha);
      position.undo_move(move_list.move(i));
      if (value > alpha)
      {
        alpha = value;
        if (alpha >= beta)
        {
          break;
        } // if
      } // if
    } // if
  } // for
  return alpha;
} // quiescence

int negamax(Position &position,
            int const depth,
            Move     &move)
{
  node_count++;
  if (position.is_won())
  {
    leaf_count++;
    return -INFINITY / 2 - depth;
  } // if
  if (position.is_threefold_repetition())
  {
    leaf_count++;
    return 0;
  } // if
  if (position.last_turn())
  {
    leaf_count++;
    return 0;
  } // if
  if (depth == 0)
  {
    leaf_count++;
    return quiescence(position);
  } // if
  Move local_move;
  Move_list move_list;
  position.generate_moves(move_list);
  if (move_list.size() == 0)
  {
    leaf_count++;
    return 0;
  } // if
  int best_value = -INFINITY;
  for (int i = 0; i < move_list.size(); i++)
  {
    position.do_move(move_list.move(i));
    int const value = -negamax(position, depth - 1, local_move);
    position.undo_move(move_list.move(i));
    if (value > best_value)
    {
      best_value = value;
      move = move_list.move(i);
    } // if
  } // for
  return best_value;
} // negamax

int alphabeta(Position &position,
              int const depth,
              int const alpha,
              int const beta,
              Move     &move)
{
  node_count++;
  if (position.is_won())
  {
    leaf_count++;
    return -INFINITY / 2 - depth;
  } // if
  if (position.is_threefold_repetition())
  {
    leaf_count++;
    return 0;
  } // if
  if (position.last_turn())
  {
    leaf_count++;
    return 0;
  } // if
  if (depth == 0)
  {
    leaf_count++;
    return quiescence(position, alpha, beta);
  } // if
  int local_alpha = alpha;
  Move local_move;
  Move_list move_list;
  position.generate_moves(move_list);
  if (move_list.size() == 0)
  {
    leaf_count++;
    return 0;
  } // if
  for (int i = 0; i < move_list.size(); i++)
  {
    position.do_move(move_list.move(i));
    int const value = -alphabeta(position, depth - 1, -beta, -local_alpha, local_move);
    position.undo_move(move_list.move(i));
    if (value >= beta)
    {
      return beta;
    } // if
    if (value > local_alpha)
    {
      local_alpha = value;
      move = move_list.move(i);
    } // if
  } // for
  return local_alpha;
} // alphabeta

