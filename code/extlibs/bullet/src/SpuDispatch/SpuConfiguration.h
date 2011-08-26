/* SCE CONFIDENTIAL
 * $PSLibId$
 * Copyright (C) 2008 Sony Computer Entertainment Inc.
 * All Rights Reserved.
*/


#ifndef __CELL_SPU_CONFIG
#define __CELL_SPU_CONFIG

#include <cell/spurs.h>

#define CELL_SPURS_DEFAULT_SPU_COUNT 5

// "-Wl,--whole-archive -lprof_stub -Wl,--no-whole-archive"

enum CellSpursReturn {
	CELL_SPURS_OK=0,
	CELL_SPURS_EBUSY,
	CELL_SPURS_EINVAL,
};

/**
 * \brief This class controls the SPU usage of SPURS
 *
 * There are three ways to initialize SPU usage.  
 *
 * The first way is to initialize SPURS yourself, and to pass in a pointer to
 * SPURS as well as priorities for the use of the SPUs, using initWithSpurs.
 * This is good if you intend to use SPURS elsewhere in your code, the management
 * can be shared across all processes.
 *
 * The second way is to control the number of SPUs used by SPURS with
 * initWithSpuCount.  Software will create its own instance of SPURS when it needs
 * it using that maximum number of SPUs.
 *
 * If you do neither of the two, Software will create its own instance of SPURS when
 * it needs it using CELL_SPURS_DEFAULT_SPU_COUNT SPUs.
 *
 * terminate() can be used to either detatch from an existing SPURS or to
 * terminate the Software-created SPURS.  Note that this will only work if all collision
 * scenes have been destroyed, otherwise SPURS would still be needed.
 *
 * Creating a new scene will cause SPURS to re-initialize.
 *
 * isSpursInitialized can be used to query whether software is currently using SPURS.
 *
 **/
class CellSpursControl {
public:
	/**
	 * \brief Initializes SPUs given a pre-configured SPURS.
	 * \param[in] pSpurs            A pointer to SPURS
	 * \param[in] iSPUCount         The number of SPUs
	 * \param[in] auiPriorities     The priorities for the code to use
	 * \return Return is:
	 * CELL_SPURS_OK on success
	 * CELL_SPURS_EBUSY if SPU usage has already been initialized
	 * CELL_SPURS_EINVAL if the priorities or SPURS pointer is invalid.
	 */
	static int initWithSpurs(CellSpurs *pSpurs, int iSPUCount, uint8_t auiPriorities[8]);

	/**
	 * \brief Sets the number of SPUs to be used by a software-initialized SPURS.
	 * \param[in] iSPUCount         A valid value is in the range 1-6
	 * \return Return is:
	 * CELL_SPURS_OK on success
	 * CELL_SPURS_EBUSY if SPU usage has already been initialized
	 * CELL_SPURS_EINVAL if iSPUCount is out of range or if SPURS couldn't be
	 *   initialized to that many SPUs.
	 */
	static int initWithSpuCount(int iSPUCount=CELL_SPURS_DEFAULT_SPU_COUNT);

	/**
	 * \brief Terminates (or disconnects from) SPURS.
	 * \return Return is:
	 * CELL_SPURS_OK if SPURS terminates ok, or if it was previously terminated/
	 *   never initialized.
	 * CELL_SPURS_EBUSY if there are existing Scenes which would need SPURS.
	 */
	static int terminate(void);

	/**
	 * \brief Queries whether SPU usage has been initialized.
	 * \return True if initialized.
	 */
	static bool isSpursInitialized(void);
};

#endif //__CELL_SPU_CONFIG
