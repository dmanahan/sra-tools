/*===========================================================================
*
*                            PUBLIC DOMAIN NOTICE
*               National Center for Biotechnology Information
*
*  This software/database is a "United States Government Work" under the
*  terms of the United States Copyright Act.  It was written as part of
*  the author's official duties as a United States Government employee and
*  thus cannot be copyrighted.  This software/database is freely available
*  to the public for use. The National Library of Medicine and the U.S.
*  Government have not placed any restriction on its use or reproduction.
*
*  Although all reasonable efforts have been taken to ensure the accuracy
*  and reliability of the software and data, the NLM and the U.S.
*  Government do not and cannot warrant the performance or results that
*  may be obtained by using this software or data. The NLM and the U.S.
*  Government disclaim all warranties, express or implied, including
*  warranties of performance, merchantability or fitness for any particular
*  purpose.
*
*  Please cite the author in any work or product based on this material.
*
* ===========================================================================
*
*/

#ifndef _h_merge_sorter_
#define _h_merge_sorter_

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _h_klib_rc_
#include <klib/rc.h>
#endif

#ifndef _h_kfs_directory_
#include <kfs/directory.h>
#endif

#ifndef _h_klib_namelist_
#include <klib/namelist.h>
#endif

#include "cleanup_task.h"

#ifndef _h_helper_
#include "helper.h"
#endif

typedef struct merge_sort_params
{
    KDirectory * dir;
    const char * lookup_filename;
    const char * index_filename;
    const tmp_id * tmp_id;
    size_t num_threads, buf_size;
    bool show_progress;
} merge_sort_params;

rc_t execute_merge_sort( const merge_sort_params * mp, locked_file_list * files );


struct background_vector_merger;
struct background_file_merger;

/* ================================================================================= */

rc_t make_background_vector_merger( struct background_vector_merger ** merger,
                             KDirectory * dir,
                             const tmp_id * tmp_id,
                             struct KFastDumpCleanupTask * cleanup_task,                             
                             struct background_file_merger * file_merger,
                             uint32_t batch_size,
                             uint32_t q_wait_time,
                             size_t buf_size );

rc_t wait_for_background_vector_merger( struct background_vector_merger * self );

rc_t push_to_background_vector_merger( struct background_vector_merger * self, KVector * store );

rc_t seal_background_vector_merger( struct background_vector_merger * self );

void release_background_vector_merger( struct background_vector_merger * self );


/* ================================================================================= */

rc_t make_background_file_merger( struct background_file_merger ** merger,
                                KDirectory * dir,
                                const tmp_id * tmp_id,
                                struct KFastDumpCleanupTask * cleanup_task,                                
                                const char * lookup_filename,
                                const char * index_filename,
                                uint32_t batch_size,
                                uint32_t wait_time,
                                size_t buf_size );

rc_t wait_for_background_file_merger( struct background_file_merger * self );

rc_t push_to_background_file_merger( struct background_file_merger * self, const char * filename );

rc_t seal_background_file_merger( struct background_file_merger * self );

void release_background_file_merger( struct background_file_merger * self );


#ifdef __cplusplus
}
#endif

#endif
