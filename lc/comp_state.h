/*! @file
 *  @brief This file implements the lord lexer.
 */

#ifndef LORD_LC_COMP_STATE_H
#define LORD_LC_COMP_STATE_H

#include "lit.h"

/*!
 * This class is used as a data storage for visitors to store whatever data
 * they'd like to store.
 *
 * @see CompState_new
 * @see CompState_free
 * @see CompState_addlit
 */
typedef struct {

	size_t ls_len, ls_cap;
	Lit **ls;

} CompState;

/*!
 * constructor
 */
CompState *CompState_new();

/*!
 * destructor
 */
void CompState_free(CompState *self);

/*!
 * methods
 */
int CompState_addlit(CompState *self, Lit *l);

#endif
