// *******************************************************************
//   (C) Copyright 2014 Leiden Institute of Advanced Computer Science
//   Universiteit Leiden
//   All Rights Reserved
// *******************************************************************
// Open Dag 21 maart 2014 --- King of the Jungle
// *******************************************************************
// FILE INFORMATION:
//   File:     search.h (Implementation file: search.cc)
//   Author:   Jonathan K. Vis
//   Revision: 0.01a
//   Date:     2014/03/18
// *******************************************************************
// DESCRIPTION:
//   Definitie van de zoekalgoritmen: negamax en alpha-beta. Deze
//   zijn in het bestand `search.cc' ge\"implementeerd.
// *******************************************************************

#ifndef __search_h__
#define __search_h__

#include "move.h"
#include "move_list.h"
#include "position.h"

#include <cassert>
#include <cstdlib>

// Gebruik deze variabelen om het aantal bezochte knopen (en bladeren)
// bij te houden.
extern uint64_t node_count;
extern uint64_t leaf_count;

static int const INFINITY = 999999;

int negamax(Position &position,
            int const depth,
            Move     &move);

int alphabeta(Position &position,
              int const depth,
              int const alpha,
              int const beta,
              Move     &move);

#endif // __search_h__

