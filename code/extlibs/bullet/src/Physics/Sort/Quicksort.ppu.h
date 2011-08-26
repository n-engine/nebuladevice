/* [SCE CONFIDENTIAL DOCUMENT]
 * $PSLibId$
 *                Copyright (C) 2006 Sony Computer Entertainment Inc.
 *                                                All Rights Reserved.
 */

#ifndef __QUICKSORT_PPU_H__
#define __QUICKSORT_PPU_H__

#include "Physics/Base/SortCommon.h"

static void quickSort(SortData *x, int left, int right)
{
	if(right - left < 1) return;

	int i, j;
    uint32_t pivot;

    i = left;
    j = right;

    pivot = Key(x[(left + right) / 2]);

    while(1) {
		while (Key(x[i]) < pivot)
            i++;

        while (pivot < Key(x[j]))
            j--;
        if (i >= j)
            break;

		SortData t = x[i];
		x[i] = x[j];
		x[j] = t;
		
		i++;
        j--;
    }

	int num0 = (i - 1) - left;
	int num1 = right - (j + 1);

	if(num0 > num1) {
		if(num1 > 0) quickSort(x, j + 1, right);
		if(num0 > 0) quickSort(x, left, i - 1);
	}
	else {
		if(num0 > 0) quickSort(x, left, i - 1);
		if(num1 > 0) quickSort(x, j + 1, right);
	}
}

#endif /* __QUICKSORT_PPU_H__ */
