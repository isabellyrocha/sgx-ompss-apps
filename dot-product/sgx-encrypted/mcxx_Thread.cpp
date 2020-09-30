typedef long int ptrdiff_t;
typedef unsigned long int size_t;
struct  max_align_t
{
    __attribute__((aligned(alignof(long long int)))) long long int __max_align_ll;
    __attribute__((aligned(alignof(long double)))) long double __max_align_ld;
};
typedef decltype(nullptr) nullptr_t;
typedef signed char int8_t;
typedef short int int16_t;
typedef int int32_t;
typedef long int int64_t;
typedef unsigned char uint8_t;
typedef unsigned short int uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long int uint64_t;
typedef signed char int_least8_t;
typedef short int int_least16_t;
typedef int int_least32_t;
typedef long int int_least64_t;
typedef unsigned char uint_least8_t;
typedef unsigned short int uint_least16_t;
typedef unsigned int uint_least32_t;
typedef unsigned long int uint_least64_t;
typedef signed char int_fast8_t;
typedef long int int_fast16_t;
typedef long int int_fast32_t;
typedef long int int_fast64_t;
typedef unsigned char uint_fast8_t;
typedef unsigned long int uint_fast16_t;
typedef unsigned long int uint_fast32_t;
typedef unsigned long int uint_fast64_t;
typedef long int intptr_t;
typedef unsigned long int uintptr_t;
typedef long int intmax_t;
typedef unsigned long int uintmax_t;
struct  nanos_region_dimension_internal_t
{
    ::size_t size;
    ::size_t lower_bound;
    ::size_t accessed_length;
};
struct  nanos_access_type_internal_t
{
    bool input:1;
    bool output:1;
    bool can_rename:1;
    bool concurrent:1;
    bool commutative:1;
};
struct  nanos_data_access_internal_t
{
    void *address;
    ::nanos_access_type_internal_t flags;
    short int dimension_count;
    const ::nanos_region_dimension_internal_t *dimensions;
    ::ptrdiff_t offset;
};
enum nanos_sharing_t
{
  NANOS_PRIVATE = 0,
  NANOS_SHARED = 1
};
struct  nanos_reduction_t
{
    void *original;
    void *privates;
    ::size_t element_size;
    ::size_t num_scalars;
    void *descriptor;
    void (*bop)(void *, void *, int);
    void (*vop)(int, void *, void *);
    void (*cleanup)(void *);
};
typedef unsigned int reg_t;
typedef unsigned int memory_space_id_t;
struct  nanos_copy_data_internal_t
{
    void *address;
    ::nanos_sharing_t sharing;
    struct  mcc_struct_anon_6
    {
        bool input:1;
        bool output:1;
    };
    ::nanos_copy_data_internal_t::mcc_struct_anon_6 flags;
    short int dimension_count;
    const ::nanos_region_dimension_internal_t *dimensions;
    ::ptrdiff_t offset;
    ::uint64_t host_base_address;
    ::reg_t host_region_id;
    bool remote_host;
    void *deducted_cd;
};
typedef ::nanos_access_type_internal_t nanos_access_type_t;
typedef ::nanos_region_dimension_internal_t nanos_region_dimension_t;
typedef ::nanos_data_access_internal_t nanos_data_access_t;
typedef ::nanos_copy_data_internal_t nanos_copy_data_t;
typedef void *nanos_thread_t;
typedef void *nanos_wd_t;
struct  nanos_compound_wd_data_t
{
    int nsect;
    ::nanos_wd_t lwd[];
};
struct  nanos_repeat_n_info_t
{
    int n;
};
struct  nanos_loop_info_t
{
    ::int64_t lower;
    ::int64_t upper;
    ::int64_t step;
    bool last;
    bool wait;
    ::int64_t chunk;
    ::int64_t stride;
    int thid;
    int threads;
    void *args;
};
typedef void *nanos_ws_t;
typedef void *nanos_ws_info_t;
typedef void *nanos_ws_data_t;
typedef void *nanos_ws_item_t;
struct  nanos_ws_info_loop_t
{
    ::int64_t lower_bound;
    ::int64_t upper_bound;
    ::int64_t loop_step;
    ::int64_t chunk_size;
};
struct  nanos_ws_item_loop_t
{
    ::int64_t lower;
    ::int64_t upper;
    bool execute:1;
    bool last:1;
};
struct nanos_ws_desc;
struct  nanos_ws_desc
{
    volatile ::nanos_ws_t ws;
    ::nanos_ws_data_t data;
    ::nanos_ws_desc *next;
    ::nanos_thread_t *threads;
    int nths;
};
typedef ::nanos_ws_desc nanos_ws_desc_t;
struct  nanos_wd_props_t
{
    bool mandatory_creation:1;
    bool tied:1;
    bool clear_chunk:1;
    bool reserved0:1;
    bool reserved1:1;
    bool reserved2:1;
    bool reserved3:1;
    bool reserved4:1;
};
struct  nanos_wd_dyn_flags_t
{
    bool is_final:1;
    bool is_recover:1;
    bool is_implicit:1;
    bool reserved3:1;
    bool reserved4:1;
    bool reserved5:1;
    bool reserved6:1;
    bool reserved7:1;
};
struct  nanos_wd_dyn_props_t
{
    ::nanos_wd_dyn_flags_t flags;
    ::nanos_thread_t tie_to;
    int priority;
    void *callback;
    void *arguments;
};
struct  nanos_device_t
{
    void *(*factory)(void *);
    void *arg;
};
struct  nanos_smp_args_t
{
    void (*outline)(void *);
};
extern "C"
{
  extern void *nanos_smp_factory_(void *args);
}
extern "C"
{
  extern void *nanos_smp_factory(void *args);
}
enum nanos_event_type_t
{
  NANOS_STATE_START = 0,
  NANOS_STATE_END = 1,
  NANOS_SUBSTATE_START = 2,
  NANOS_SUBSTATE_END = 3,
  NANOS_BURST_START = 4,
  NANOS_BURST_END = 5,
  NANOS_PTP_START = 6,
  NANOS_PTP_END = 7,
  NANOS_POINT = 8,
  EVENT_TYPES = 9
};
typedef unsigned int nanos_event_key_t;
typedef unsigned long long int nanos_event_value_t;
enum nanos_event_state_value_t
{
  NANOS_NOT_CREATED = 0,
  NANOS_NOT_RUNNING = 1,
  NANOS_STARTUP = 2,
  NANOS_SHUTDOWN = 3,
  NANOS_ERROR = 4,
  NANOS_IDLE = 5,
  NANOS_RUNTIME = 6,
  NANOS_RUNNING = 7,
  NANOS_SYNCHRONIZATION = 8,
  NANOS_SCHEDULING = 9,
  NANOS_CREATION = 10,
  NANOS_MEM_TRANSFER_ISSUE = 11,
  NANOS_CACHE = 12,
  NANOS_YIELD = 13,
  NANOS_ACQUIRING_LOCK = 14,
  NANOS_CONTEXT_SWITCH = 15,
  NANOS_FILL1 = 16,
  NANOS_WAKINGUP = 17,
  NANOS_STOPPED = 18,
  NANOS_SYNCED_RUNNING = 19,
  NANOS_DEBUG = 20,
  NANOS_EVENT_STATE_TYPES = 21
};
enum nanos_event_domain_t
{
  NANOS_WD_DOMAIN = 0,
  NANOS_WD_DEPENDENCY = 1,
  NANOS_WAIT = 2,
  NANOS_XFER_DATA = 3,
  NANOS_XFER_REQ = 4,
  NANOS_WD_REMOTE = 5,
  NANOS_AM_WORK = 6,
  NANOS_AM_WORK_DONE = 7,
  NANOS_XFER_WAIT_REQ_PUT = 8,
  NANOS_XFER_FREE_TMP_BUFF = 9
};
typedef long long int nanos_event_id_t;
struct  nanos_event_t
{
    ::nanos_event_type_t type;
    ::nanos_event_key_t key;
    ::nanos_event_value_t value;
    ::nanos_event_domain_t domain;
    ::nanos_event_id_t id;
};
enum nanos_lock_state_t
{
  NANOS_LOCK_FREE = 0,
  NANOS_LOCK_BUSY = 1
};
struct  nanos_lock_t
{
    volatile ::nanos_lock_state_t state_;
    inline nanos_lock_t(::nanos_lock_state_t init  = (::NANOS_LOCK_FREE))
      : state_(init)
    {
    }
};
typedef void (*nanos_translate_args_t)(void *, ::nanos_wd_t);
typedef void nanos_init_func_t(void *);
struct  nanos_init_desc_t
{
    ::nanos_init_func_t (*func);
    void *data;
};
enum nanos_err_t
{
  NANOS_OK = 0,
  NANOS_UNKNOWN_ERR = 1,
  NANOS_UNIMPLEMENTED = 2,
  NANOS_ENOMEM = 3,
  NANOS_INVALID_PARAM = 4,
  NANOS_INVALID_REQUEST = 5
};
typedef void *nanos_wg_t;
typedef void *nanos_team_t;
typedef void *nanos_sched_t;
typedef void *nanos_slicer_t;
typedef void *nanos_dd_t;
typedef void *nanos_sync_cond_t;
typedef unsigned int nanos_copy_id_t;
struct  nanos_const_wd_definition_tag
{
    ::nanos_wd_props_t props;
    ::size_t data_alignment;
    ::size_t num_copies;
    ::size_t num_devices;
    ::size_t num_dimensions;
    const char *description;
};
typedef ::nanos_const_wd_definition_tag nanos_const_wd_definition_t;
struct  nanos_constraint_t
{
    int nthreads;
    void *arch;
};
typedef void *nanos_cpu_set_t;
typedef const void *const_nanos_cpu_set_t;
struct  nanos_const_wd_definition_internal_t : ::nanos_const_wd_definition_tag
{
    ::nanos_device_t devices[1L];
};
extern "C"
{
  extern char *nanos_get_mode_();
}
extern "C"
{
  extern char *nanos_get_mode();
}
extern "C"
{
  extern ::nanos_wd_t nanos_current_wd_();
}
extern "C"
{
  extern ::nanos_wd_t nanos_current_wd();
}
extern "C"
{
  extern int nanos_get_wd_id_(::nanos_wd_t wd);
}
extern "C"
{
  extern int nanos_get_wd_id(::nanos_wd_t wd);
}
extern "C"
{
  extern int nanos_get_wd_priority_(::nanos_wd_t wd);
}
extern "C"
{
  extern int nanos_get_wd_priority(::nanos_wd_t wd);
}
extern "C"
{
  extern void nanos_set_wd_priority_(::nanos_wd_t wd, int p);
}
extern "C"
{
  extern void nanos_set_wd_priority(::nanos_wd_t wd, int p);
}
extern "C"
{
  extern ::nanos_err_t nanos_get_wd_description_(const char **description, ::nanos_wd_t wd);
}
extern "C"
{
  extern ::nanos_err_t nanos_get_wd_description(const char **description, ::nanos_wd_t wd);
}
extern "C"
{
  extern ::nanos_slicer_t nanos_find_slicer_(const char *slicer);
}
extern "C"
{
  extern ::nanos_slicer_t nanos_find_slicer(const char *slicer);
}
extern "C"
{
  extern ::nanos_ws_t nanos_find_worksharing_(const char *label);
}
extern "C"
{
  extern ::nanos_ws_t nanos_find_worksharing(const char *label);
}
extern "C"
{
  extern ::nanos_err_t nanos_create_wd_compact_(::nanos_wd_t *wd, ::nanos_const_wd_definition_t *const_data, ::nanos_wd_dyn_props_t *dyn_props, ::size_t data_size, void **data, ::nanos_wg_t wg, ::nanos_copy_data_t **copies, ::nanos_region_dimension_internal_t **dimensions);
}
extern "C"
{
  extern ::nanos_err_t nanos_create_wd_compact(::nanos_wd_t *wd, ::nanos_const_wd_definition_t *const_data, ::nanos_wd_dyn_props_t *dyn_props, ::size_t data_size, void **data, ::nanos_wg_t wg, ::nanos_copy_data_t **copies, ::nanos_region_dimension_internal_t **dimensions);
}
extern "C"
{
  extern ::nanos_err_t nanos_set_translate_function_(::nanos_wd_t wd, ::nanos_translate_args_t translate_args);
}
extern "C"
{
  extern ::nanos_err_t nanos_set_translate_function(::nanos_wd_t wd, ::nanos_translate_args_t translate_args);
}
extern "C"
{
  extern ::nanos_err_t nanos_create_sliced_wd_(::nanos_wd_t *uwd, ::size_t num_devices, ::nanos_device_t *devices, ::size_t outline_data_size, int outline_data_align, void **outline_data, ::nanos_wg_t uwg, ::nanos_slicer_t slicer, ::nanos_wd_props_t *props, ::nanos_wd_dyn_props_t *dyn_props, ::size_t num_copies, ::nanos_copy_data_t **copies, ::size_t num_dimensions, ::nanos_region_dimension_internal_t **dimensions);
}
extern "C"
{
  extern ::nanos_err_t nanos_create_sliced_wd(::nanos_wd_t *uwd, ::size_t num_devices, ::nanos_device_t *devices, ::size_t outline_data_size, int outline_data_align, void **outline_data, ::nanos_wg_t uwg, ::nanos_slicer_t slicer, ::nanos_wd_props_t *props, ::nanos_wd_dyn_props_t *dyn_props, ::size_t num_copies, ::nanos_copy_data_t **copies, ::size_t num_dimensions, ::nanos_region_dimension_internal_t **dimensions);
}
extern "C"
{
  extern ::nanos_err_t nanos_submit_(::nanos_wd_t wd, ::size_t num_data_accesses, ::nanos_data_access_t *data_accesses, ::nanos_team_t team);
}
extern "C"
{
  extern ::nanos_err_t nanos_submit(::nanos_wd_t wd, ::size_t num_data_accesses, ::nanos_data_access_t *data_accesses, ::nanos_team_t team);
}
extern "C"
{
  extern ::nanos_err_t nanos_create_wd_and_run_compact_(::nanos_const_wd_definition_t *const_data, ::nanos_wd_dyn_props_t *dyn_props, ::size_t data_size, void *data, ::size_t num_data_accesses, ::nanos_data_access_t *data_accesses, ::nanos_copy_data_t *copies, ::nanos_region_dimension_internal_t *dimensions, ::nanos_translate_args_t translate_args);
}
extern "C"
{
  extern ::nanos_err_t nanos_create_wd_and_run_compact(::nanos_const_wd_definition_t *const_data, ::nanos_wd_dyn_props_t *dyn_props, ::size_t data_size, void *data, ::size_t num_data_accesses, ::nanos_data_access_t *data_accesses, ::nanos_copy_data_t *copies, ::nanos_region_dimension_internal_t *dimensions, ::nanos_translate_args_t translate_args);
}
extern "C"
{
  extern ::nanos_err_t nanos_create_for_();
}
extern "C"
{
  extern ::nanos_err_t nanos_create_for();
}
extern "C"
{
  extern ::nanos_err_t nanos_set_internal_wd_data_(::nanos_wd_t wd, void *data);
}
extern "C"
{
  extern ::nanos_err_t nanos_set_internal_wd_data(::nanos_wd_t wd, void *data);
}
extern "C"
{
  extern ::nanos_err_t nanos_get_internal_wd_data_(::nanos_wd_t wd, void **data);
}
extern "C"
{
  extern ::nanos_err_t nanos_get_internal_wd_data(::nanos_wd_t wd, void **data);
}
extern "C"
{
  extern ::nanos_err_t nanos_yield_();
}
extern "C"
{
  extern ::nanos_err_t nanos_yield();
}
extern "C"
{
  extern ::nanos_err_t nanos_slicer_get_specific_data_(::nanos_slicer_t slicer, void **data);
}
extern "C"
{
  extern ::nanos_err_t nanos_slicer_get_specific_data(::nanos_slicer_t slicer, void **data);
}
extern "C"
{
  extern ::nanos_err_t nanos_get_num_ready_tasks_(unsigned int *ready_tasks);
}
extern "C"
{
  extern ::nanos_err_t nanos_get_num_ready_tasks(unsigned int *ready_tasks);
}
extern "C"
{
  extern ::nanos_err_t nanos_get_num_total_tasks_(unsigned int *total_tasks);
}
extern "C"
{
  extern ::nanos_err_t nanos_get_num_total_tasks(unsigned int *total_tasks);
}
extern "C"
{
  extern ::nanos_err_t nanos_get_num_nonready_tasks_(unsigned int *nonready_tasks);
}
extern "C"
{
  extern ::nanos_err_t nanos_get_num_nonready_tasks(unsigned int *nonready_tasks);
}
extern "C"
{
  extern ::nanos_err_t nanos_get_num_running_tasks_(unsigned int *running_tasks);
}
extern "C"
{
  extern ::nanos_err_t nanos_get_num_running_tasks(unsigned int *running_tasks);
}
extern "C"
{
  extern ::nanos_err_t nanos_get_num_blocked_tasks_(unsigned int *blocked_tasks);
}
extern "C"
{
  extern ::nanos_err_t nanos_get_num_blocked_tasks(unsigned int *blocked_tasks);
}
extern "C"
{
  extern ::nanos_err_t nanos_in_final_(bool *result);
}
extern "C"
{
  extern ::nanos_err_t nanos_in_final(bool *result);
}
extern "C"
{
  extern ::nanos_err_t nanos_set_final_(bool value);
}
extern "C"
{
  extern ::nanos_err_t nanos_set_final(bool value);
}
extern "C"
{
  extern ::nanos_err_t nanos_switch_to_thread_(unsigned int *thid);
}
extern "C"
{
  extern ::nanos_err_t nanos_switch_to_thread(unsigned int *thid);
}
extern "C"
{
  extern ::nanos_err_t nanos_is_tied_(bool *result);
}
extern "C"
{
  extern ::nanos_err_t nanos_is_tied(bool *result);
}
extern "C"
{
  extern ::nanos_err_t nanos_create_team_(::nanos_team_t *team, ::nanos_sched_t sg, unsigned int *nthreads, ::nanos_constraint_t *constraints, bool reuse, ::nanos_thread_t *info, ::nanos_const_wd_definition_t *const_data);
}
extern "C"
{
  extern ::nanos_err_t nanos_create_team(::nanos_team_t *team, ::nanos_sched_t sg, unsigned int *nthreads, ::nanos_constraint_t *constraints, bool reuse, ::nanos_thread_t *info, ::nanos_const_wd_definition_t *const_data);
}
extern "C"
{
  extern ::nanos_err_t nanos_create_team_mapped_(::nanos_team_t *team, ::nanos_sched_t sg, unsigned int *nthreads, unsigned int *mapping);
}
extern "C"
{
  extern ::nanos_err_t nanos_create_team_mapped(::nanos_team_t *team, ::nanos_sched_t sg, unsigned int *nthreads, unsigned int *mapping);
}
extern "C"
{
  extern ::nanos_err_t nanos_enter_team_();
}
extern "C"
{
  extern ::nanos_err_t nanos_enter_team();
}
extern "C"
{
  extern ::nanos_err_t nanos_leave_team_();
}
extern "C"
{
  extern ::nanos_err_t nanos_leave_team();
}
extern "C"
{
  extern ::nanos_err_t nanos_end_team_(::nanos_team_t team);
}
extern "C"
{
  extern ::nanos_err_t nanos_end_team(::nanos_team_t team);
}
extern "C"
{
  extern ::nanos_err_t nanos_team_barrier_();
}
extern "C"
{
  extern ::nanos_err_t nanos_team_barrier();
}
extern "C"
{
  extern ::nanos_err_t nanos_single_guard_(bool *);
}
extern "C"
{
  extern ::nanos_err_t nanos_single_guard(bool *);
}
extern "C"
{
  extern ::nanos_err_t nanos_enter_sync_init_(bool *b);
}
extern "C"
{
  extern ::nanos_err_t nanos_enter_sync_init(bool *b);
}
extern "C"
{
  extern ::nanos_err_t nanos_wait_sync_init_();
}
extern "C"
{
  extern ::nanos_err_t nanos_wait_sync_init();
}
extern "C"
{
  extern ::nanos_err_t nanos_release_sync_init_();
}
extern "C"
{
  extern ::nanos_err_t nanos_release_sync_init();
}
extern "C"
{
  extern ::nanos_err_t nanos_memory_fence_();
}
extern "C"
{
  extern ::nanos_err_t nanos_memory_fence();
}
extern "C"
{
  extern ::nanos_err_t nanos_team_get_num_supporting_threads_(int *n);
}
extern "C"
{
  extern ::nanos_err_t nanos_team_get_num_supporting_threads(int *n);
}
extern "C"
{
  extern ::nanos_err_t nanos_team_get_supporting_threads_(int *n, ::nanos_thread_t *list_of_threads);
}
extern "C"
{
  extern ::nanos_err_t nanos_team_get_supporting_threads(int *n, ::nanos_thread_t *list_of_threads);
}
extern "C"
{
  extern ::nanos_err_t nanos_register_reduction_(::nanos_reduction_t *red);
}
extern "C"
{
  extern ::nanos_err_t nanos_register_reduction(::nanos_reduction_t *red);
}
extern "C"
{
  extern ::nanos_err_t nanos_reduction_get_private_data_(void **copy, void *original);
}
extern "C"
{
  extern ::nanos_err_t nanos_reduction_get_private_data(void **copy, void *original);
}
extern "C"
{
  extern ::nanos_err_t nanos_reduction_get_(::nanos_reduction_t **dest, void *original);
}
extern "C"
{
  extern ::nanos_err_t nanos_reduction_get(::nanos_reduction_t **dest, void *original);
}
extern "C"
{
  extern ::nanos_err_t nanos_task_reduction_register_(void *orig, ::size_t size_target, ::size_t size_elem, void (*init)(void *, void *), void (*reducer)(void *, void *));
}
extern "C"
{
  extern ::nanos_err_t nanos_task_reduction_register(void *orig, ::size_t size_target, ::size_t size_elem, void (*init)(void *, void *), void (*reducer)(void *, void *));
}
extern "C"
{
  extern ::nanos_err_t nanos_task_fortran_array_reduction_register_(void *orig, void *dep, ::size_t array_descriptor_size, void (*init)(void *, void *), void (*reducer)(void *, void *), void (*reducer_orig_var)(void *, void *));
}
extern "C"
{
  extern ::nanos_err_t nanos_task_fortran_array_reduction_register(void *orig, void *dep, ::size_t array_descriptor_size, void (*init)(void *, void *), void (*reducer)(void *, void *), void (*reducer_orig_var)(void *, void *));
}
extern "C"
{
  extern ::nanos_err_t nanos_task_reduction_get_thread_storage_(void *orig, void **tpd);
}
extern "C"
{
  extern ::nanos_err_t nanos_task_reduction_get_thread_storage(void *orig, void **tpd);
}
extern "C"
{
  extern ::nanos_err_t nanos_admit_current_thread_();
}
extern "C"
{
  extern ::nanos_err_t nanos_admit_current_thread();
}
extern "C"
{
  extern ::nanos_err_t nanos_expel_current_thread_();
}
extern "C"
{
  extern ::nanos_err_t nanos_expel_current_thread();
}
extern "C"
{
  extern ::nanos_err_t nanos_dependence_release_all_();
}
extern "C"
{
  extern ::nanos_err_t nanos_dependence_release_all();
}
extern "C"
{
  extern ::nanos_err_t nanos_dependence_pendant_writes_(bool *res, void *addr);
}
extern "C"
{
  extern ::nanos_err_t nanos_dependence_pendant_writes(bool *res, void *addr);
}
extern "C"
{
  extern ::nanos_err_t nanos_dependence_create_(::nanos_wd_t pred, ::nanos_wd_t succ);
}
extern "C"
{
  extern ::nanos_err_t nanos_dependence_create(::nanos_wd_t pred, ::nanos_wd_t succ);
}
extern "C"
{
  extern ::nanos_err_t nanos_worksharing_create_(::nanos_ws_desc_t **wsd, ::nanos_ws_t ws, ::nanos_ws_info_t *info, bool *b);
}
extern "C"
{
  extern ::nanos_err_t nanos_worksharing_create(::nanos_ws_desc_t **wsd, ::nanos_ws_t ws, ::nanos_ws_info_t *info, bool *b);
}
extern "C"
{
  extern ::nanos_err_t nanos_worksharing_next_item_(::nanos_ws_desc_t *wsd, ::nanos_ws_item_t *wsi);
}
extern "C"
{
  extern ::nanos_err_t nanos_worksharing_next_item(::nanos_ws_desc_t *wsd, ::nanos_ws_item_t *wsi);
}
extern "C"
{
  extern ::nanos_err_t nanos_wg_wait_completion_mandatory_(::nanos_wg_t wg, bool avoid_flush);
}
extern "C"
{
  extern ::nanos_err_t nanos_wg_wait_completion_mandatory(::nanos_wg_t wg, bool avoid_flush);
}
extern "C"
{
  extern ::nanos_err_t nanos_wg_wait_completion_(::nanos_wg_t wg, bool avoid_flush);
}
extern "C"
{
  extern ::nanos_err_t nanos_wg_wait_completion(::nanos_wg_t wg, bool avoid_flush);
}
extern "C"
{
  extern ::nanos_err_t nanos_create_int_sync_cond_(::nanos_sync_cond_t *sync_cond, volatile int *p, int condition);
}
extern "C"
{
  extern ::nanos_err_t nanos_create_int_sync_cond(::nanos_sync_cond_t *sync_cond, volatile int *p, int condition);
}
extern "C"
{
  extern ::nanos_err_t nanos_create_bool_sync_cond_(::nanos_sync_cond_t *sync_cond, volatile bool *p, bool condition);
}
extern "C"
{
  extern ::nanos_err_t nanos_create_bool_sync_cond(::nanos_sync_cond_t *sync_cond, volatile bool *p, bool condition);
}
extern "C"
{
  extern ::nanos_err_t nanos_sync_cond_wait_(::nanos_sync_cond_t sync_cond);
}
extern "C"
{
  extern ::nanos_err_t nanos_sync_cond_wait(::nanos_sync_cond_t sync_cond);
}
extern "C"
{
  extern ::nanos_err_t nanos_sync_cond_signal_(::nanos_sync_cond_t sync_cond);
}
extern "C"
{
  extern ::nanos_err_t nanos_sync_cond_signal(::nanos_sync_cond_t sync_cond);
}
extern "C"
{
  extern ::nanos_err_t nanos_destroy_sync_cond_(::nanos_sync_cond_t sync_cond);
}
extern "C"
{
  extern ::nanos_err_t nanos_destroy_sync_cond(::nanos_sync_cond_t sync_cond);
}
extern "C"
{
  extern ::nanos_err_t nanos_wait_on_(::size_t num_data_accesses, ::nanos_data_access_t *data_accesses);
}
extern "C"
{
  extern ::nanos_err_t nanos_wait_on(::size_t num_data_accesses, ::nanos_data_access_t *data_accesses);
}
extern "C"
{
  extern ::nanos_err_t nanos_init_lock_(::nanos_lock_t **lock);
}
extern "C"
{
  extern ::nanos_err_t nanos_init_lock(::nanos_lock_t **lock);
}
extern "C"
{
  extern ::nanos_err_t nanos_init_lock_at_(::nanos_lock_t *lock);
}
extern "C"
{
  extern ::nanos_err_t nanos_init_lock_at(::nanos_lock_t *lock);
}
extern "C"
{
  extern ::nanos_err_t nanos_set_lock_(::nanos_lock_t *lock);
}
extern "C"
{
  extern ::nanos_err_t nanos_set_lock(::nanos_lock_t *lock);
}
extern "C"
{
  extern ::nanos_err_t nanos_unset_lock_(::nanos_lock_t *lock);
}
extern "C"
{
  extern ::nanos_err_t nanos_unset_lock(::nanos_lock_t *lock);
}
extern "C"
{
  extern ::nanos_err_t nanos_try_lock_(::nanos_lock_t *lock, bool *result);
}
extern "C"
{
  extern ::nanos_err_t nanos_try_lock(::nanos_lock_t *lock, bool *result);
}
extern "C"
{
  extern ::nanos_err_t nanos_destroy_lock_(::nanos_lock_t *lock);
}
extern "C"
{
  extern ::nanos_err_t nanos_destroy_lock(::nanos_lock_t *lock);
}
extern "C"
{
  extern ::nanos_err_t nanos_get_lock_address_(void *addr, ::nanos_lock_t **lock);
}
extern "C"
{
  extern ::nanos_err_t nanos_get_lock_address(void *addr, ::nanos_lock_t **lock);
}
extern "C"
{
  extern ::nanos_err_t nanos_set_copies_(::nanos_wd_t wd, int num_copies, ::nanos_copy_data_t *copies);
}
extern "C"
{
  extern ::nanos_err_t nanos_set_copies(::nanos_wd_t wd, int num_copies, ::nanos_copy_data_t *copies);
}
extern "C"
{
  extern ::nanos_err_t nanos_get_addr_(::nanos_copy_id_t copy_id, void **addr, ::nanos_wd_t cwd);
}
extern "C"
{
  extern ::nanos_err_t nanos_get_addr(::nanos_copy_id_t copy_id, void **addr, ::nanos_wd_t cwd);
}
extern "C"
{
  extern ::nanos_err_t nanos_copy_value_(void *dst, ::nanos_copy_id_t copy_id, ::nanos_wd_t cwd);
}
extern "C"
{
  extern ::nanos_err_t nanos_copy_value(void *dst, ::nanos_copy_id_t copy_id, ::nanos_wd_t cwd);
}
extern "C"
{
  extern const char *nanos_get_runtime_version_();
}
extern "C"
{
  extern const char *nanos_get_runtime_version();
}
extern "C"
{
  extern const char *nanos_get_default_architecture_();
}
extern "C"
{
  extern const char *nanos_get_default_architecture();
}
extern "C"
{
  extern const char *nanos_get_pm_();
}
extern "C"
{
  extern const char *nanos_get_pm();
}
extern "C"
{
  extern ::nanos_err_t nanos_get_default_binding_(bool *res);
}
extern "C"
{
  extern ::nanos_err_t nanos_get_default_binding(bool *res);
}
extern "C"
{
  extern ::nanos_err_t nanos_get_binding_(::nanos_cpu_set_t *);
}
extern "C"
{
  extern ::nanos_err_t nanos_get_binding(::nanos_cpu_set_t *);
}
extern "C"
{
  extern ::nanos_err_t nanos_delay_start_();
}
extern "C"
{
  extern ::nanos_err_t nanos_delay_start();
}
extern "C"
{
  extern ::nanos_err_t nanos_start_();
}
extern "C"
{
  extern ::nanos_err_t nanos_start();
}
extern "C"
{
  extern ::nanos_err_t nanos_finish_();
}
extern "C"
{
  extern ::nanos_err_t nanos_finish();
}
extern "C"
{
  extern ::nanos_err_t nanos_current_socket_(int socket);
}
extern "C"
{
  extern ::nanos_err_t nanos_current_socket(int socket);
}
extern "C"
{
  extern ::nanos_err_t nanos_get_num_sockets_(int *num_sockets);
}
extern "C"
{
  extern ::nanos_err_t nanos_get_num_sockets(int *num_sockets);
}
extern "C"
{
  extern ::nanos_err_t nanos_malloc_(void **p, ::size_t size, const char *file, int line);
}
extern "C"
{
  extern ::nanos_err_t nanos_malloc(void **p, ::size_t size, const char *file, int line);
}
extern "C"
{
  extern ::nanos_err_t nanos_memalign_(void **p, ::size_t size, const char *file, int line);
}
extern "C"
{
  extern ::nanos_err_t nanos_memalign(void **p, ::size_t size, const char *file, int line);
}
extern "C"
{
  extern ::nanos_err_t nanos_cmalloc_(void **p, ::size_t size, unsigned int node, const char *file, int line);
}
extern "C"
{
  extern ::nanos_err_t nanos_cmalloc(void **p, ::size_t size, unsigned int node, const char *file, int line);
}
extern "C"
{
  extern ::nanos_err_t nanos_cmalloc_2dim_distributed_(void **p, ::size_t rows, ::size_t cols, ::size_t elem_size, unsigned int start_node, ::size_t num_nodes, const char *file, int line);
}
extern "C"
{
  extern ::nanos_err_t nanos_cmalloc_2dim_distributed(void **p, ::size_t rows, ::size_t cols, ::size_t elem_size, unsigned int start_node, ::size_t num_nodes, const char *file, int line);
}
extern "C"
{
  extern ::nanos_err_t nanos_stick_to_producer_(void *p, ::size_t size);
}
extern "C"
{
  extern ::nanos_err_t nanos_stick_to_producer(void *p, ::size_t size);
}
extern "C"
{
  extern ::nanos_err_t nanos_free_(void *p);
}
extern "C"
{
  extern ::nanos_err_t nanos_free(void *p);
}
extern "C"
{
  extern void nanos_free0_(void *p);
}
extern "C"
{
  extern void nanos_free0(void *p);
}
extern "C"
{
  extern void nanos_handle_error_(::nanos_err_t err);
}
extern "C"
{
  extern void nanos_handle_error(::nanos_err_t err);
}
extern "C"
{
  extern ::nanos_err_t nanos_instrument_register_key_(::nanos_event_key_t *event_key, const char *key, const char *description, bool abort_when_registered);
}
extern "C"
{
  extern ::nanos_err_t nanos_instrument_register_key(::nanos_event_key_t *event_key, const char *key, const char *description, bool abort_when_registered);
}
extern "C"
{
  extern ::nanos_err_t nanos_instrument_register_value_(::nanos_event_value_t *event_value, const char *key, const char *value, const char *description, bool abort_when_registered);
}
extern "C"
{
  extern ::nanos_err_t nanos_instrument_register_value(::nanos_event_value_t *event_value, const char *key, const char *value, const char *description, bool abort_when_registered);
}
extern "C"
{
  extern ::nanos_err_t nanos_instrument_register_value_with_val_(::nanos_event_value_t val, const char *key, const char *value, const char *description, bool abort_when_registered);
}
extern "C"
{
  extern ::nanos_err_t nanos_instrument_register_value_with_val(::nanos_event_value_t val, const char *key, const char *value, const char *description, bool abort_when_registered);
}
extern "C"
{
  extern ::nanos_err_t nanos_instrument_get_key_(const char *key, ::nanos_event_key_t *event_key);
}
extern "C"
{
  extern ::nanos_err_t nanos_instrument_get_key(const char *key, ::nanos_event_key_t *event_key);
}
extern "C"
{
  extern ::nanos_err_t nanos_instrument_get_value_(const char *key, const char *value, ::nanos_event_value_t *event_value);
}
extern "C"
{
  extern ::nanos_err_t nanos_instrument_get_value(const char *key, const char *value, ::nanos_event_value_t *event_value);
}
extern "C"
{
  extern ::nanos_err_t nanos_instrument_events_(unsigned int num_events, ::nanos_event_t events[]);
}
extern "C"
{
  extern ::nanos_err_t nanos_instrument_events(unsigned int num_events, ::nanos_event_t events[]);
}
extern "C"
{
  extern ::nanos_err_t nanos_instrument_close_user_fun_event_();
}
extern "C"
{
  extern ::nanos_err_t nanos_instrument_close_user_fun_event();
}
extern "C"
{
  extern ::nanos_err_t nanos_instrument_raise_gpu_kernel_launch_event_();
}
extern "C"
{
  extern ::nanos_err_t nanos_instrument_raise_gpu_kernel_launch_event();
}
extern "C"
{
  extern ::nanos_err_t nanos_instrument_close_gpu_kernel_launch_event_();
}
extern "C"
{
  extern ::nanos_err_t nanos_instrument_close_gpu_kernel_launch_event();
}
extern "C"
{
  extern ::nanos_err_t nanos_instrument_enable_();
}
extern "C"
{
  extern ::nanos_err_t nanos_instrument_enable();
}
extern "C"
{
  extern ::nanos_err_t nanos_instrument_disable_();
}
extern "C"
{
  extern ::nanos_err_t nanos_instrument_disable();
}
extern "C"
{
  extern ::nanos_err_t nanos_get_node_num_(unsigned int *num);
}
extern "C"
{
  extern ::nanos_err_t nanos_get_node_num(unsigned int *num);
}
extern "C"
{
  extern int nanos_get_num_nodes_();
}
extern "C"
{
  extern int nanos_get_num_nodes();
}
extern "C"
{
  extern ::nanos_err_t nanos_set_create_local_tasks_(bool value);
}
extern "C"
{
  extern ::nanos_err_t nanos_set_create_local_tasks(bool value);
}
typedef const char *nanos_string_t;
extern "C"
{
  extern ::nanos_err_t nanos_instrument_begin_burst_(::nanos_string_t key, ::nanos_string_t key_descr, ::nanos_string_t value, ::nanos_string_t value_descr);
}
extern "C"
{
  extern ::nanos_err_t nanos_instrument_begin_burst(::nanos_string_t key, ::nanos_string_t key_descr, ::nanos_string_t value, ::nanos_string_t value_descr);
}
extern "C"
{
  extern ::nanos_err_t nanos_instrument_end_burst_(::nanos_string_t key, ::nanos_string_t value);
}
extern "C"
{
  extern ::nanos_err_t nanos_instrument_end_burst(::nanos_string_t key, ::nanos_string_t value);
}
extern "C"
{
  extern ::nanos_err_t nanos_instrument_begin_burst_with_val_(::nanos_string_t key, ::nanos_string_t key_descr, ::nanos_event_value_t *val);
}
extern "C"
{
  extern ::nanos_err_t nanos_instrument_begin_burst_with_val(::nanos_string_t key, ::nanos_string_t key_descr, ::nanos_event_value_t *val);
}
extern "C"
{
  extern ::nanos_err_t nanos_instrument_end_burst_with_val_(::nanos_string_t key, ::nanos_event_value_t *val);
}
extern "C"
{
  extern ::nanos_err_t nanos_instrument_end_burst_with_val(::nanos_string_t key, ::nanos_event_value_t *val);
}
extern "C"
{
  extern ::nanos_err_t nanos_memcpy_(void *dest, const void *src, ::size_t n);
}
extern "C"
{
  extern ::nanos_err_t nanos_memcpy(void *dest, const void *src, ::size_t n);
}
extern "C"
{
  extern ::nanos_err_t nanos_register_object_(int num_objects, ::nanos_copy_data_t *obj);
}
extern "C"
{
  extern ::nanos_err_t nanos_register_object(int num_objects, ::nanos_copy_data_t *obj);
}
extern "C"
{
  extern ::nanos_err_t nanos_unregister_object_(int num_objects, void *base_addresses);
}
extern "C"
{
  extern ::nanos_err_t nanos_unregister_object(int num_objects, void *base_addresses);
}
extern "C"
{
  extern const char *nanos_get_default_scheduler_();
}
extern "C"
{
  extern const char *nanos_get_default_scheduler();
}
extern "C"
{
  extern ::nanos_err_t nanos_start_scheduler_();
}
extern "C"
{
  extern ::nanos_err_t nanos_start_scheduler();
}
extern "C"
{
  extern ::nanos_err_t nanos_stop_scheduler_();
}
extern "C"
{
  extern ::nanos_err_t nanos_stop_scheduler();
}
extern "C"
{
  extern ::nanos_err_t nanos_scheduler_enabled_(bool *res);
}
extern "C"
{
  extern ::nanos_err_t nanos_scheduler_enabled(bool *res);
}
extern "C"
{
  extern ::nanos_err_t nanos_wait_until_threads_paused_();
}
extern "C"
{
  extern ::nanos_err_t nanos_wait_until_threads_paused();
}
extern "C"
{
  extern ::nanos_err_t nanos_wait_until_threads_unpaused_();
}
extern "C"
{
  extern ::nanos_err_t nanos_wait_until_threads_unpaused();
}
extern "C"
{
  extern ::nanos_err_t nanos_scheduler_get_stealing_(bool *res);
}
extern "C"
{
  extern ::nanos_err_t nanos_scheduler_get_stealing(bool *res);
}
extern "C"
{
  extern ::nanos_err_t nanos_scheduler_set_stealing_(bool value);
}
extern "C"
{
  extern ::nanos_err_t nanos_scheduler_set_stealing(bool value);
}
extern "C"
{
  extern void ompss_nanox_main_begin_(void *addr, const char *filename, int line);
}
extern "C"
{
  extern void ompss_nanox_main_begin(void *addr, const char *filename, int line);
}
extern "C"
{
  extern void ompss_nanox_main_end_();
}
extern "C"
{
  extern void ompss_nanox_main_end();
}
extern "C"
{
  extern void ompss_nanox_main_();
}
extern "C"
{
  extern void ompss_nanox_main();
}
extern "C"
{
  extern void nanos_atexit_(void *);
}
extern "C"
{
  extern void nanos_atexit(void *);
}
extern "C"
{
  void nanos_reduction_int_vop(int, void *, void *);
}
extern "C"
{
  extern int nanos_cmpi_init_(int *argc, char **argv[]);
}
extern "C"
{
  extern int nanos_cmpi_init(int *argc, char **argv[]);
}
extern "C"
{
  extern void nanos_cmpi_finalize_();
}
extern "C"
{
  extern void nanos_cmpi_finalize();
}
extern "C"
{
  extern void nanos_into_blocking_mpi_call_();
}
extern "C"
{
  extern void nanos_into_blocking_mpi_call();
}
extern "C"
{
  extern void nanos_out_of_blocking_mpi_call_();
}
extern "C"
{
  extern void nanos_out_of_blocking_mpi_call();
}
extern "C"
{
  extern void nanos_thread_print_(char *str);
}
extern "C"
{
  extern void nanos_thread_print(char *str);
}
extern "C"
{
  extern void nanos_set_watch_addr_(void *addr);
}
extern "C"
{
  extern void nanos_set_watch_addr(void *addr);
}
extern "C"
{
  extern void nanos_print_bt_();
}
extern "C"
{
  extern void nanos_print_bt();
}
extern "C"
{
  extern void nanos_enable_verbose_copies_();
}
extern "C"
{
  extern void nanos_enable_verbose_copies();
}
extern "C"
{
  extern void nanos_disable_verbose_copies_();
}
extern "C"
{
  extern void nanos_disable_verbose_copies();
}
extern "C"
{
  extern void nanos_atomic_assig_schar_(volatile signed char *, signed char);
}
extern "C"
{
  extern void nanos_atomic_assig_schar(volatile signed char *, signed char);
}
extern "C"
{
  extern void nanos_atomic_assig_short_(volatile short int *, short int);
}
extern "C"
{
  extern void nanos_atomic_assig_short(volatile short int *, short int);
}
extern "C"
{
  extern void nanos_atomic_assig_int_(volatile int *, int);
}
extern "C"
{
  extern void nanos_atomic_assig_int(volatile int *, int);
}
extern "C"
{
  extern void nanos_atomic_assig_long_(volatile long int *, long int);
}
extern "C"
{
  extern void nanos_atomic_assig_long(volatile long int *, long int);
}
extern "C"
{
  extern void nanos_atomic_assig_longlong_(volatile long long int *, long long int);
}
extern "C"
{
  extern void nanos_atomic_assig_longlong(volatile long long int *, long long int);
}
extern "C"
{
  extern void nanos_atomic_assig_uchar_(volatile unsigned char *, unsigned char);
}
extern "C"
{
  extern void nanos_atomic_assig_uchar(volatile unsigned char *, unsigned char);
}
extern "C"
{
  extern void nanos_atomic_assig_ushort_(volatile unsigned short int *, unsigned short int);
}
extern "C"
{
  extern void nanos_atomic_assig_ushort(volatile unsigned short int *, unsigned short int);
}
extern "C"
{
  extern void nanos_atomic_assig_uint_(volatile unsigned int *, unsigned int);
}
extern "C"
{
  extern void nanos_atomic_assig_uint(volatile unsigned int *, unsigned int);
}
extern "C"
{
  extern void nanos_atomic_assig_ulong_(volatile unsigned long int *, unsigned long int);
}
extern "C"
{
  extern void nanos_atomic_assig_ulong(volatile unsigned long int *, unsigned long int);
}
extern "C"
{
  extern void nanos_atomic_assig_ulonglong_(volatile unsigned long long int *, unsigned long long int);
}
extern "C"
{
  extern void nanos_atomic_assig_ulonglong(volatile unsigned long long int *, unsigned long long int);
}
extern "C"
{
  extern void nanos_atomic_assig_bytebool_(volatile signed char *, signed char);
}
extern "C"
{
  extern void nanos_atomic_assig_bytebool(volatile signed char *, signed char);
}
extern "C"
{
  extern void nanos_atomic_assig_shortbool_(volatile short int *, short int);
}
extern "C"
{
  extern void nanos_atomic_assig_shortbool(volatile short int *, short int);
}
extern "C"
{
  extern void nanos_atomic_assig_intbool_(volatile int *, int);
}
extern "C"
{
  extern void nanos_atomic_assig_intbool(volatile int *, int);
}
extern "C"
{
  extern void nanos_atomic_assig_longbool_(volatile long int *, long int);
}
extern "C"
{
  extern void nanos_atomic_assig_longbool(volatile long int *, long int);
}
extern "C"
{
  extern void nanos_atomic_assig_longlongbool_(volatile long long int *, long long int);
}
extern "C"
{
  extern void nanos_atomic_assig_longlongbool(volatile long long int *, long long int);
}
extern "C"
{
  extern void nanos_atomic_assig_float_(volatile float *, float);
}
extern "C"
{
  extern void nanos_atomic_assig_float(volatile float *, float);
}
extern "C"
{
  extern void nanos_atomic_assig_double_(volatile double *, double);
}
extern "C"
{
  extern void nanos_atomic_assig_double(volatile double *, double);
}
extern "C"
{
  extern void nanos_atomic_assig_ldouble_(volatile long double *, long double);
}
extern "C"
{
  extern void nanos_atomic_assig_ldouble(volatile long double *, long double);
}
extern "C"
{
  extern void nanos_atomic_assig_cfloat_(volatile _Complex float *, _Complex float);
}
extern "C"
{
  extern void nanos_atomic_assig_cfloat(volatile _Complex float *, _Complex float);
}
extern "C"
{
  extern void nanos_atomic_assig_cdouble_(volatile _Complex double *, _Complex double);
}
extern "C"
{
  extern void nanos_atomic_assig_cdouble(volatile _Complex double *, _Complex double);
}
extern "C"
{
  extern void nanos_atomic_assig_cldouble_(volatile _Complex long double *, _Complex long double);
}
extern "C"
{
  extern void nanos_atomic_assig_cldouble(volatile _Complex long double *, _Complex long double);
}
extern "C"
{
  extern void nanos_atomic_add_schar_(volatile signed char *, signed char);
}
extern "C"
{
  extern void nanos_atomic_add_schar(volatile signed char *, signed char);
}
extern "C"
{
  extern void nanos_atomic_add_short_(volatile short int *, short int);
}
extern "C"
{
  extern void nanos_atomic_add_short(volatile short int *, short int);
}
extern "C"
{
  extern void nanos_atomic_add_int_(volatile int *, int);
}
extern "C"
{
  extern void nanos_atomic_add_int(volatile int *, int);
}
extern "C"
{
  extern void nanos_atomic_add_long_(volatile long int *, long int);
}
extern "C"
{
  extern void nanos_atomic_add_long(volatile long int *, long int);
}
extern "C"
{
  extern void nanos_atomic_add_longlong_(volatile long long int *, long long int);
}
extern "C"
{
  extern void nanos_atomic_add_longlong(volatile long long int *, long long int);
}
extern "C"
{
  extern void nanos_atomic_add_uchar_(volatile unsigned char *, unsigned char);
}
extern "C"
{
  extern void nanos_atomic_add_uchar(volatile unsigned char *, unsigned char);
}
extern "C"
{
  extern void nanos_atomic_add_ushort_(volatile unsigned short int *, unsigned short int);
}
extern "C"
{
  extern void nanos_atomic_add_ushort(volatile unsigned short int *, unsigned short int);
}
extern "C"
{
  extern void nanos_atomic_add_uint_(volatile unsigned int *, unsigned int);
}
extern "C"
{
  extern void nanos_atomic_add_uint(volatile unsigned int *, unsigned int);
}
extern "C"
{
  extern void nanos_atomic_add_ulong_(volatile unsigned long int *, unsigned long int);
}
extern "C"
{
  extern void nanos_atomic_add_ulong(volatile unsigned long int *, unsigned long int);
}
extern "C"
{
  extern void nanos_atomic_add_ulonglong_(volatile unsigned long long int *, unsigned long long int);
}
extern "C"
{
  extern void nanos_atomic_add_ulonglong(volatile unsigned long long int *, unsigned long long int);
}
extern "C"
{
  extern void nanos_atomic_add_bytebool_(volatile signed char *, signed char);
}
extern "C"
{
  extern void nanos_atomic_add_bytebool(volatile signed char *, signed char);
}
extern "C"
{
  extern void nanos_atomic_add_shortbool_(volatile short int *, short int);
}
extern "C"
{
  extern void nanos_atomic_add_shortbool(volatile short int *, short int);
}
extern "C"
{
  extern void nanos_atomic_add_intbool_(volatile int *, int);
}
extern "C"
{
  extern void nanos_atomic_add_intbool(volatile int *, int);
}
extern "C"
{
  extern void nanos_atomic_add_longbool_(volatile long int *, long int);
}
extern "C"
{
  extern void nanos_atomic_add_longbool(volatile long int *, long int);
}
extern "C"
{
  extern void nanos_atomic_add_longlongbool_(volatile long long int *, long long int);
}
extern "C"
{
  extern void nanos_atomic_add_longlongbool(volatile long long int *, long long int);
}
extern "C"
{
  extern void nanos_atomic_add_float_(volatile float *, float);
}
extern "C"
{
  extern void nanos_atomic_add_float(volatile float *, float);
}
extern "C"
{
  extern void nanos_atomic_add_double_(volatile double *, double);
}
extern "C"
{
  extern void nanos_atomic_add_double(volatile double *, double);
}
extern "C"
{
  extern void nanos_atomic_add_ldouble_(volatile long double *, long double);
}
extern "C"
{
  extern void nanos_atomic_add_ldouble(volatile long double *, long double);
}
extern "C"
{
  extern void nanos_atomic_add_cfloat_(volatile _Complex float *, _Complex float);
}
extern "C"
{
  extern void nanos_atomic_add_cfloat(volatile _Complex float *, _Complex float);
}
extern "C"
{
  extern void nanos_atomic_add_cdouble_(volatile _Complex double *, _Complex double);
}
extern "C"
{
  extern void nanos_atomic_add_cdouble(volatile _Complex double *, _Complex double);
}
extern "C"
{
  extern void nanos_atomic_add_cldouble_(volatile _Complex long double *, _Complex long double);
}
extern "C"
{
  extern void nanos_atomic_add_cldouble(volatile _Complex long double *, _Complex long double);
}
extern "C"
{
  extern void nanos_atomic_sub_schar_(volatile signed char *, signed char);
}
extern "C"
{
  extern void nanos_atomic_sub_schar(volatile signed char *, signed char);
}
extern "C"
{
  extern void nanos_atomic_sub_short_(volatile short int *, short int);
}
extern "C"
{
  extern void nanos_atomic_sub_short(volatile short int *, short int);
}
extern "C"
{
  extern void nanos_atomic_sub_int_(volatile int *, int);
}
extern "C"
{
  extern void nanos_atomic_sub_int(volatile int *, int);
}
extern "C"
{
  extern void nanos_atomic_sub_long_(volatile long int *, long int);
}
extern "C"
{
  extern void nanos_atomic_sub_long(volatile long int *, long int);
}
extern "C"
{
  extern void nanos_atomic_sub_longlong_(volatile long long int *, long long int);
}
extern "C"
{
  extern void nanos_atomic_sub_longlong(volatile long long int *, long long int);
}
extern "C"
{
  extern void nanos_atomic_sub_uchar_(volatile unsigned char *, unsigned char);
}
extern "C"
{
  extern void nanos_atomic_sub_uchar(volatile unsigned char *, unsigned char);
}
extern "C"
{
  extern void nanos_atomic_sub_ushort_(volatile unsigned short int *, unsigned short int);
}
extern "C"
{
  extern void nanos_atomic_sub_ushort(volatile unsigned short int *, unsigned short int);
}
extern "C"
{
  extern void nanos_atomic_sub_uint_(volatile unsigned int *, unsigned int);
}
extern "C"
{
  extern void nanos_atomic_sub_uint(volatile unsigned int *, unsigned int);
}
extern "C"
{
  extern void nanos_atomic_sub_ulong_(volatile unsigned long int *, unsigned long int);
}
extern "C"
{
  extern void nanos_atomic_sub_ulong(volatile unsigned long int *, unsigned long int);
}
extern "C"
{
  extern void nanos_atomic_sub_ulonglong_(volatile unsigned long long int *, unsigned long long int);
}
extern "C"
{
  extern void nanos_atomic_sub_ulonglong(volatile unsigned long long int *, unsigned long long int);
}
extern "C"
{
  extern void nanos_atomic_sub_bytebool_(volatile signed char *, signed char);
}
extern "C"
{
  extern void nanos_atomic_sub_bytebool(volatile signed char *, signed char);
}
extern "C"
{
  extern void nanos_atomic_sub_shortbool_(volatile short int *, short int);
}
extern "C"
{
  extern void nanos_atomic_sub_shortbool(volatile short int *, short int);
}
extern "C"
{
  extern void nanos_atomic_sub_intbool_(volatile int *, int);
}
extern "C"
{
  extern void nanos_atomic_sub_intbool(volatile int *, int);
}
extern "C"
{
  extern void nanos_atomic_sub_longbool_(volatile long int *, long int);
}
extern "C"
{
  extern void nanos_atomic_sub_longbool(volatile long int *, long int);
}
extern "C"
{
  extern void nanos_atomic_sub_longlongbool_(volatile long long int *, long long int);
}
extern "C"
{
  extern void nanos_atomic_sub_longlongbool(volatile long long int *, long long int);
}
extern "C"
{
  extern void nanos_atomic_sub_float_(volatile float *, float);
}
extern "C"
{
  extern void nanos_atomic_sub_float(volatile float *, float);
}
extern "C"
{
  extern void nanos_atomic_sub_double_(volatile double *, double);
}
extern "C"
{
  extern void nanos_atomic_sub_double(volatile double *, double);
}
extern "C"
{
  extern void nanos_atomic_sub_ldouble_(volatile long double *, long double);
}
extern "C"
{
  extern void nanos_atomic_sub_ldouble(volatile long double *, long double);
}
extern "C"
{
  extern void nanos_atomic_sub_cfloat_(volatile _Complex float *, _Complex float);
}
extern "C"
{
  extern void nanos_atomic_sub_cfloat(volatile _Complex float *, _Complex float);
}
extern "C"
{
  extern void nanos_atomic_sub_cdouble_(volatile _Complex double *, _Complex double);
}
extern "C"
{
  extern void nanos_atomic_sub_cdouble(volatile _Complex double *, _Complex double);
}
extern "C"
{
  extern void nanos_atomic_sub_cldouble_(volatile _Complex long double *, _Complex long double);
}
extern "C"
{
  extern void nanos_atomic_sub_cldouble(volatile _Complex long double *, _Complex long double);
}
extern "C"
{
  extern void nanos_atomic_mul_schar_(volatile signed char *, signed char);
}
extern "C"
{
  extern void nanos_atomic_mul_schar(volatile signed char *, signed char);
}
extern "C"
{
  extern void nanos_atomic_mul_short_(volatile short int *, short int);
}
extern "C"
{
  extern void nanos_atomic_mul_short(volatile short int *, short int);
}
extern "C"
{
  extern void nanos_atomic_mul_int_(volatile int *, int);
}
extern "C"
{
  extern void nanos_atomic_mul_int(volatile int *, int);
}
extern "C"
{
  extern void nanos_atomic_mul_long_(volatile long int *, long int);
}
extern "C"
{
  extern void nanos_atomic_mul_long(volatile long int *, long int);
}
extern "C"
{
  extern void nanos_atomic_mul_longlong_(volatile long long int *, long long int);
}
extern "C"
{
  extern void nanos_atomic_mul_longlong(volatile long long int *, long long int);
}
extern "C"
{
  extern void nanos_atomic_mul_uchar_(volatile unsigned char *, unsigned char);
}
extern "C"
{
  extern void nanos_atomic_mul_uchar(volatile unsigned char *, unsigned char);
}
extern "C"
{
  extern void nanos_atomic_mul_ushort_(volatile unsigned short int *, unsigned short int);
}
extern "C"
{
  extern void nanos_atomic_mul_ushort(volatile unsigned short int *, unsigned short int);
}
extern "C"
{
  extern void nanos_atomic_mul_uint_(volatile unsigned int *, unsigned int);
}
extern "C"
{
  extern void nanos_atomic_mul_uint(volatile unsigned int *, unsigned int);
}
extern "C"
{
  extern void nanos_atomic_mul_ulong_(volatile unsigned long int *, unsigned long int);
}
extern "C"
{
  extern void nanos_atomic_mul_ulong(volatile unsigned long int *, unsigned long int);
}
extern "C"
{
  extern void nanos_atomic_mul_ulonglong_(volatile unsigned long long int *, unsigned long long int);
}
extern "C"
{
  extern void nanos_atomic_mul_ulonglong(volatile unsigned long long int *, unsigned long long int);
}
extern "C"
{
  extern void nanos_atomic_mul_bytebool_(volatile signed char *, signed char);
}
extern "C"
{
  extern void nanos_atomic_mul_bytebool(volatile signed char *, signed char);
}
extern "C"
{
  extern void nanos_atomic_mul_shortbool_(volatile short int *, short int);
}
extern "C"
{
  extern void nanos_atomic_mul_shortbool(volatile short int *, short int);
}
extern "C"
{
  extern void nanos_atomic_mul_intbool_(volatile int *, int);
}
extern "C"
{
  extern void nanos_atomic_mul_intbool(volatile int *, int);
}
extern "C"
{
  extern void nanos_atomic_mul_longbool_(volatile long int *, long int);
}
extern "C"
{
  extern void nanos_atomic_mul_longbool(volatile long int *, long int);
}
extern "C"
{
  extern void nanos_atomic_mul_longlongbool_(volatile long long int *, long long int);
}
extern "C"
{
  extern void nanos_atomic_mul_longlongbool(volatile long long int *, long long int);
}
extern "C"
{
  extern void nanos_atomic_mul_float_(volatile float *, float);
}
extern "C"
{
  extern void nanos_atomic_mul_float(volatile float *, float);
}
extern "C"
{
  extern void nanos_atomic_mul_double_(volatile double *, double);
}
extern "C"
{
  extern void nanos_atomic_mul_double(volatile double *, double);
}
extern "C"
{
  extern void nanos_atomic_mul_ldouble_(volatile long double *, long double);
}
extern "C"
{
  extern void nanos_atomic_mul_ldouble(volatile long double *, long double);
}
extern "C"
{
  extern void nanos_atomic_mul_cfloat_(volatile _Complex float *, _Complex float);
}
extern "C"
{
  extern void nanos_atomic_mul_cfloat(volatile _Complex float *, _Complex float);
}
extern "C"
{
  extern void nanos_atomic_mul_cdouble_(volatile _Complex double *, _Complex double);
}
extern "C"
{
  extern void nanos_atomic_mul_cdouble(volatile _Complex double *, _Complex double);
}
extern "C"
{
  extern void nanos_atomic_mul_cldouble_(volatile _Complex long double *, _Complex long double);
}
extern "C"
{
  extern void nanos_atomic_mul_cldouble(volatile _Complex long double *, _Complex long double);
}
extern "C"
{
  extern void nanos_atomic_div_schar_(volatile signed char *, signed char);
}
extern "C"
{
  extern void nanos_atomic_div_schar(volatile signed char *, signed char);
}
extern "C"
{
  extern void nanos_atomic_div_short_(volatile short int *, short int);
}
extern "C"
{
  extern void nanos_atomic_div_short(volatile short int *, short int);
}
extern "C"
{
  extern void nanos_atomic_div_int_(volatile int *, int);
}
extern "C"
{
  extern void nanos_atomic_div_int(volatile int *, int);
}
extern "C"
{
  extern void nanos_atomic_div_long_(volatile long int *, long int);
}
extern "C"
{
  extern void nanos_atomic_div_long(volatile long int *, long int);
}
extern "C"
{
  extern void nanos_atomic_div_longlong_(volatile long long int *, long long int);
}
extern "C"
{
  extern void nanos_atomic_div_longlong(volatile long long int *, long long int);
}
extern "C"
{
  extern void nanos_atomic_div_uchar_(volatile unsigned char *, unsigned char);
}
extern "C"
{
  extern void nanos_atomic_div_uchar(volatile unsigned char *, unsigned char);
}
extern "C"
{
  extern void nanos_atomic_div_ushort_(volatile unsigned short int *, unsigned short int);
}
extern "C"
{
  extern void nanos_atomic_div_ushort(volatile unsigned short int *, unsigned short int);
}
extern "C"
{
  extern void nanos_atomic_div_uint_(volatile unsigned int *, unsigned int);
}
extern "C"
{
  extern void nanos_atomic_div_uint(volatile unsigned int *, unsigned int);
}
extern "C"
{
  extern void nanos_atomic_div_ulong_(volatile unsigned long int *, unsigned long int);
}
extern "C"
{
  extern void nanos_atomic_div_ulong(volatile unsigned long int *, unsigned long int);
}
extern "C"
{
  extern void nanos_atomic_div_ulonglong_(volatile unsigned long long int *, unsigned long long int);
}
extern "C"
{
  extern void nanos_atomic_div_ulonglong(volatile unsigned long long int *, unsigned long long int);
}
extern "C"
{
  extern void nanos_atomic_div_bytebool_(volatile signed char *, signed char);
}
extern "C"
{
  extern void nanos_atomic_div_bytebool(volatile signed char *, signed char);
}
extern "C"
{
  extern void nanos_atomic_div_shortbool_(volatile short int *, short int);
}
extern "C"
{
  extern void nanos_atomic_div_shortbool(volatile short int *, short int);
}
extern "C"
{
  extern void nanos_atomic_div_intbool_(volatile int *, int);
}
extern "C"
{
  extern void nanos_atomic_div_intbool(volatile int *, int);
}
extern "C"
{
  extern void nanos_atomic_div_longbool_(volatile long int *, long int);
}
extern "C"
{
  extern void nanos_atomic_div_longbool(volatile long int *, long int);
}
extern "C"
{
  extern void nanos_atomic_div_longlongbool_(volatile long long int *, long long int);
}
extern "C"
{
  extern void nanos_atomic_div_longlongbool(volatile long long int *, long long int);
}
extern "C"
{
  extern void nanos_atomic_div_float_(volatile float *, float);
}
extern "C"
{
  extern void nanos_atomic_div_float(volatile float *, float);
}
extern "C"
{
  extern void nanos_atomic_div_double_(volatile double *, double);
}
extern "C"
{
  extern void nanos_atomic_div_double(volatile double *, double);
}
extern "C"
{
  extern void nanos_atomic_div_ldouble_(volatile long double *, long double);
}
extern "C"
{
  extern void nanos_atomic_div_ldouble(volatile long double *, long double);
}
extern "C"
{
  extern void nanos_atomic_div_cfloat_(volatile _Complex float *, _Complex float);
}
extern "C"
{
  extern void nanos_atomic_div_cfloat(volatile _Complex float *, _Complex float);
}
extern "C"
{
  extern void nanos_atomic_div_cdouble_(volatile _Complex double *, _Complex double);
}
extern "C"
{
  extern void nanos_atomic_div_cdouble(volatile _Complex double *, _Complex double);
}
extern "C"
{
  extern void nanos_atomic_div_cldouble_(volatile _Complex long double *, _Complex long double);
}
extern "C"
{
  extern void nanos_atomic_div_cldouble(volatile _Complex long double *, _Complex long double);
}
extern "C"
{
  extern void nanos_atomic_pow_schar_(volatile signed char *, signed char);
}
extern "C"
{
  extern void nanos_atomic_pow_schar(volatile signed char *, signed char);
}
extern "C"
{
  extern void nanos_atomic_pow_short_(volatile short int *, short int);
}
extern "C"
{
  extern void nanos_atomic_pow_short(volatile short int *, short int);
}
extern "C"
{
  extern void nanos_atomic_pow_int_(volatile int *, int);
}
extern "C"
{
  extern void nanos_atomic_pow_int(volatile int *, int);
}
extern "C"
{
  extern void nanos_atomic_pow_long_(volatile long int *, long int);
}
extern "C"
{
  extern void nanos_atomic_pow_long(volatile long int *, long int);
}
extern "C"
{
  extern void nanos_atomic_pow_longlong_(volatile long long int *, long long int);
}
extern "C"
{
  extern void nanos_atomic_pow_longlong(volatile long long int *, long long int);
}
extern "C"
{
  extern void nanos_atomic_pow_uchar_(volatile unsigned char *, unsigned char);
}
extern "C"
{
  extern void nanos_atomic_pow_uchar(volatile unsigned char *, unsigned char);
}
extern "C"
{
  extern void nanos_atomic_pow_ushort_(volatile unsigned short int *, unsigned short int);
}
extern "C"
{
  extern void nanos_atomic_pow_ushort(volatile unsigned short int *, unsigned short int);
}
extern "C"
{
  extern void nanos_atomic_pow_uint_(volatile unsigned int *, unsigned int);
}
extern "C"
{
  extern void nanos_atomic_pow_uint(volatile unsigned int *, unsigned int);
}
extern "C"
{
  extern void nanos_atomic_pow_ulong_(volatile unsigned long int *, unsigned long int);
}
extern "C"
{
  extern void nanos_atomic_pow_ulong(volatile unsigned long int *, unsigned long int);
}
extern "C"
{
  extern void nanos_atomic_pow_ulonglong_(volatile unsigned long long int *, unsigned long long int);
}
extern "C"
{
  extern void nanos_atomic_pow_ulonglong(volatile unsigned long long int *, unsigned long long int);
}
extern "C"
{
  extern void nanos_atomic_pow_bytebool_(volatile signed char *, signed char);
}
extern "C"
{
  extern void nanos_atomic_pow_bytebool(volatile signed char *, signed char);
}
extern "C"
{
  extern void nanos_atomic_pow_shortbool_(volatile short int *, short int);
}
extern "C"
{
  extern void nanos_atomic_pow_shortbool(volatile short int *, short int);
}
extern "C"
{
  extern void nanos_atomic_pow_intbool_(volatile int *, int);
}
extern "C"
{
  extern void nanos_atomic_pow_intbool(volatile int *, int);
}
extern "C"
{
  extern void nanos_atomic_pow_longbool_(volatile long int *, long int);
}
extern "C"
{
  extern void nanos_atomic_pow_longbool(volatile long int *, long int);
}
extern "C"
{
  extern void nanos_atomic_pow_longlongbool_(volatile long long int *, long long int);
}
extern "C"
{
  extern void nanos_atomic_pow_longlongbool(volatile long long int *, long long int);
}
extern "C"
{
  extern void nanos_atomic_pow_float_(volatile float *, float);
}
extern "C"
{
  extern void nanos_atomic_pow_float(volatile float *, float);
}
extern "C"
{
  extern void nanos_atomic_pow_double_(volatile double *, double);
}
extern "C"
{
  extern void nanos_atomic_pow_double(volatile double *, double);
}
extern "C"
{
  extern void nanos_atomic_pow_ldouble_(volatile long double *, long double);
}
extern "C"
{
  extern void nanos_atomic_pow_ldouble(volatile long double *, long double);
}
extern "C"
{
  extern void nanos_atomic_pow_cfloat_(volatile _Complex float *, _Complex float);
}
extern "C"
{
  extern void nanos_atomic_pow_cfloat(volatile _Complex float *, _Complex float);
}
extern "C"
{
  extern void nanos_atomic_pow_cdouble_(volatile _Complex double *, _Complex double);
}
extern "C"
{
  extern void nanos_atomic_pow_cdouble(volatile _Complex double *, _Complex double);
}
extern "C"
{
  extern void nanos_atomic_pow_cldouble_(volatile _Complex long double *, _Complex long double);
}
extern "C"
{
  extern void nanos_atomic_pow_cldouble(volatile _Complex long double *, _Complex long double);
}
extern "C"
{
  extern void nanos_atomic_max_schar_(volatile signed char *, signed char);
}
extern "C"
{
  extern void nanos_atomic_max_schar(volatile signed char *, signed char);
}
extern "C"
{
  extern void nanos_atomic_max_short_(volatile short int *, short int);
}
extern "C"
{
  extern void nanos_atomic_max_short(volatile short int *, short int);
}
extern "C"
{
  extern void nanos_atomic_max_int_(volatile int *, int);
}
extern "C"
{
  extern void nanos_atomic_max_int(volatile int *, int);
}
extern "C"
{
  extern void nanos_atomic_max_long_(volatile long int *, long int);
}
extern "C"
{
  extern void nanos_atomic_max_long(volatile long int *, long int);
}
extern "C"
{
  extern void nanos_atomic_max_longlong_(volatile long long int *, long long int);
}
extern "C"
{
  extern void nanos_atomic_max_longlong(volatile long long int *, long long int);
}
extern "C"
{
  extern void nanos_atomic_max_uchar_(volatile unsigned char *, unsigned char);
}
extern "C"
{
  extern void nanos_atomic_max_uchar(volatile unsigned char *, unsigned char);
}
extern "C"
{
  extern void nanos_atomic_max_ushort_(volatile unsigned short int *, unsigned short int);
}
extern "C"
{
  extern void nanos_atomic_max_ushort(volatile unsigned short int *, unsigned short int);
}
extern "C"
{
  extern void nanos_atomic_max_uint_(volatile unsigned int *, unsigned int);
}
extern "C"
{
  extern void nanos_atomic_max_uint(volatile unsigned int *, unsigned int);
}
extern "C"
{
  extern void nanos_atomic_max_ulong_(volatile unsigned long int *, unsigned long int);
}
extern "C"
{
  extern void nanos_atomic_max_ulong(volatile unsigned long int *, unsigned long int);
}
extern "C"
{
  extern void nanos_atomic_max_ulonglong_(volatile unsigned long long int *, unsigned long long int);
}
extern "C"
{
  extern void nanos_atomic_max_ulonglong(volatile unsigned long long int *, unsigned long long int);
}
extern "C"
{
  extern void nanos_atomic_max_bytebool_(volatile signed char *, signed char);
}
extern "C"
{
  extern void nanos_atomic_max_bytebool(volatile signed char *, signed char);
}
extern "C"
{
  extern void nanos_atomic_max_shortbool_(volatile short int *, short int);
}
extern "C"
{
  extern void nanos_atomic_max_shortbool(volatile short int *, short int);
}
extern "C"
{
  extern void nanos_atomic_max_intbool_(volatile int *, int);
}
extern "C"
{
  extern void nanos_atomic_max_intbool(volatile int *, int);
}
extern "C"
{
  extern void nanos_atomic_max_longbool_(volatile long int *, long int);
}
extern "C"
{
  extern void nanos_atomic_max_longbool(volatile long int *, long int);
}
extern "C"
{
  extern void nanos_atomic_max_longlongbool_(volatile long long int *, long long int);
}
extern "C"
{
  extern void nanos_atomic_max_longlongbool(volatile long long int *, long long int);
}
extern "C"
{
  extern void nanos_atomic_min_schar_(volatile signed char *, signed char);
}
extern "C"
{
  extern void nanos_atomic_min_schar(volatile signed char *, signed char);
}
extern "C"
{
  extern void nanos_atomic_min_short_(volatile short int *, short int);
}
extern "C"
{
  extern void nanos_atomic_min_short(volatile short int *, short int);
}
extern "C"
{
  extern void nanos_atomic_min_int_(volatile int *, int);
}
extern "C"
{
  extern void nanos_atomic_min_int(volatile int *, int);
}
extern "C"
{
  extern void nanos_atomic_min_long_(volatile long int *, long int);
}
extern "C"
{
  extern void nanos_atomic_min_long(volatile long int *, long int);
}
extern "C"
{
  extern void nanos_atomic_min_longlong_(volatile long long int *, long long int);
}
extern "C"
{
  extern void nanos_atomic_min_longlong(volatile long long int *, long long int);
}
extern "C"
{
  extern void nanos_atomic_min_uchar_(volatile unsigned char *, unsigned char);
}
extern "C"
{
  extern void nanos_atomic_min_uchar(volatile unsigned char *, unsigned char);
}
extern "C"
{
  extern void nanos_atomic_min_ushort_(volatile unsigned short int *, unsigned short int);
}
extern "C"
{
  extern void nanos_atomic_min_ushort(volatile unsigned short int *, unsigned short int);
}
extern "C"
{
  extern void nanos_atomic_min_uint_(volatile unsigned int *, unsigned int);
}
extern "C"
{
  extern void nanos_atomic_min_uint(volatile unsigned int *, unsigned int);
}
extern "C"
{
  extern void nanos_atomic_min_ulong_(volatile unsigned long int *, unsigned long int);
}
extern "C"
{
  extern void nanos_atomic_min_ulong(volatile unsigned long int *, unsigned long int);
}
extern "C"
{
  extern void nanos_atomic_min_ulonglong_(volatile unsigned long long int *, unsigned long long int);
}
extern "C"
{
  extern void nanos_atomic_min_ulonglong(volatile unsigned long long int *, unsigned long long int);
}
extern "C"
{
  extern void nanos_atomic_min_bytebool_(volatile signed char *, signed char);
}
extern "C"
{
  extern void nanos_atomic_min_bytebool(volatile signed char *, signed char);
}
extern "C"
{
  extern void nanos_atomic_min_shortbool_(volatile short int *, short int);
}
extern "C"
{
  extern void nanos_atomic_min_shortbool(volatile short int *, short int);
}
extern "C"
{
  extern void nanos_atomic_min_intbool_(volatile int *, int);
}
extern "C"
{
  extern void nanos_atomic_min_intbool(volatile int *, int);
}
extern "C"
{
  extern void nanos_atomic_min_longbool_(volatile long int *, long int);
}
extern "C"
{
  extern void nanos_atomic_min_longbool(volatile long int *, long int);
}
extern "C"
{
  extern void nanos_atomic_min_longlongbool_(volatile long long int *, long long int);
}
extern "C"
{
  extern void nanos_atomic_min_longlongbool(volatile long long int *, long long int);
}
extern "C"
{
  extern void nanos_atomic_max_float_(volatile float *, float);
}
extern "C"
{
  extern void nanos_atomic_max_float(volatile float *, float);
}
extern "C"
{
  extern void nanos_atomic_max_double_(volatile double *, double);
}
extern "C"
{
  extern void nanos_atomic_max_double(volatile double *, double);
}
extern "C"
{
  extern void nanos_atomic_max_ldouble_(volatile long double *, long double);
}
extern "C"
{
  extern void nanos_atomic_max_ldouble(volatile long double *, long double);
}
extern "C"
{
  extern void nanos_atomic_min_float_(volatile float *, float);
}
extern "C"
{
  extern void nanos_atomic_min_float(volatile float *, float);
}
extern "C"
{
  extern void nanos_atomic_min_double_(volatile double *, double);
}
extern "C"
{
  extern void nanos_atomic_min_double(volatile double *, double);
}
extern "C"
{
  extern void nanos_atomic_min_ldouble_(volatile long double *, long double);
}
extern "C"
{
  extern void nanos_atomic_min_ldouble(volatile long double *, long double);
}
extern "C"
{
  extern void nanos_atomic_eq_schar_(volatile signed char *, signed char);
}
extern "C"
{
  extern void nanos_atomic_eq_schar(volatile signed char *, signed char);
}
extern "C"
{
  extern void nanos_atomic_eq_short_(volatile short int *, short int);
}
extern "C"
{
  extern void nanos_atomic_eq_short(volatile short int *, short int);
}
extern "C"
{
  extern void nanos_atomic_eq_int_(volatile int *, int);
}
extern "C"
{
  extern void nanos_atomic_eq_int(volatile int *, int);
}
extern "C"
{
  extern void nanos_atomic_eq_long_(volatile long int *, long int);
}
extern "C"
{
  extern void nanos_atomic_eq_long(volatile long int *, long int);
}
extern "C"
{
  extern void nanos_atomic_eq_longlong_(volatile long long int *, long long int);
}
extern "C"
{
  extern void nanos_atomic_eq_longlong(volatile long long int *, long long int);
}
extern "C"
{
  extern void nanos_atomic_eq_uchar_(volatile unsigned char *, unsigned char);
}
extern "C"
{
  extern void nanos_atomic_eq_uchar(volatile unsigned char *, unsigned char);
}
extern "C"
{
  extern void nanos_atomic_eq_ushort_(volatile unsigned short int *, unsigned short int);
}
extern "C"
{
  extern void nanos_atomic_eq_ushort(volatile unsigned short int *, unsigned short int);
}
extern "C"
{
  extern void nanos_atomic_eq_uint_(volatile unsigned int *, unsigned int);
}
extern "C"
{
  extern void nanos_atomic_eq_uint(volatile unsigned int *, unsigned int);
}
extern "C"
{
  extern void nanos_atomic_eq_ulong_(volatile unsigned long int *, unsigned long int);
}
extern "C"
{
  extern void nanos_atomic_eq_ulong(volatile unsigned long int *, unsigned long int);
}
extern "C"
{
  extern void nanos_atomic_eq_ulonglong_(volatile unsigned long long int *, unsigned long long int);
}
extern "C"
{
  extern void nanos_atomic_eq_ulonglong(volatile unsigned long long int *, unsigned long long int);
}
extern "C"
{
  extern void nanos_atomic_eq_bytebool_(volatile signed char *, signed char);
}
extern "C"
{
  extern void nanos_atomic_eq_bytebool(volatile signed char *, signed char);
}
extern "C"
{
  extern void nanos_atomic_eq_shortbool_(volatile short int *, short int);
}
extern "C"
{
  extern void nanos_atomic_eq_shortbool(volatile short int *, short int);
}
extern "C"
{
  extern void nanos_atomic_eq_intbool_(volatile int *, int);
}
extern "C"
{
  extern void nanos_atomic_eq_intbool(volatile int *, int);
}
extern "C"
{
  extern void nanos_atomic_eq_longbool_(volatile long int *, long int);
}
extern "C"
{
  extern void nanos_atomic_eq_longbool(volatile long int *, long int);
}
extern "C"
{
  extern void nanos_atomic_eq_longlongbool_(volatile long long int *, long long int);
}
extern "C"
{
  extern void nanos_atomic_eq_longlongbool(volatile long long int *, long long int);
}
extern "C"
{
  extern void nanos_atomic_eq_float_(volatile float *, float);
}
extern "C"
{
  extern void nanos_atomic_eq_float(volatile float *, float);
}
extern "C"
{
  extern void nanos_atomic_eq_double_(volatile double *, double);
}
extern "C"
{
  extern void nanos_atomic_eq_double(volatile double *, double);
}
extern "C"
{
  extern void nanos_atomic_eq_ldouble_(volatile long double *, long double);
}
extern "C"
{
  extern void nanos_atomic_eq_ldouble(volatile long double *, long double);
}
extern "C"
{
  extern void nanos_atomic_eq_cfloat_(volatile _Complex float *, _Complex float);
}
extern "C"
{
  extern void nanos_atomic_eq_cfloat(volatile _Complex float *, _Complex float);
}
extern "C"
{
  extern void nanos_atomic_eq_cdouble_(volatile _Complex double *, _Complex double);
}
extern "C"
{
  extern void nanos_atomic_eq_cdouble(volatile _Complex double *, _Complex double);
}
extern "C"
{
  extern void nanos_atomic_eq_cldouble_(volatile _Complex long double *, _Complex long double);
}
extern "C"
{
  extern void nanos_atomic_eq_cldouble(volatile _Complex long double *, _Complex long double);
}
extern "C"
{
  extern void nanos_atomic_neq_schar_(volatile signed char *, signed char);
}
extern "C"
{
  extern void nanos_atomic_neq_schar(volatile signed char *, signed char);
}
extern "C"
{
  extern void nanos_atomic_neq_short_(volatile short int *, short int);
}
extern "C"
{
  extern void nanos_atomic_neq_short(volatile short int *, short int);
}
extern "C"
{
  extern void nanos_atomic_neq_int_(volatile int *, int);
}
extern "C"
{
  extern void nanos_atomic_neq_int(volatile int *, int);
}
extern "C"
{
  extern void nanos_atomic_neq_long_(volatile long int *, long int);
}
extern "C"
{
  extern void nanos_atomic_neq_long(volatile long int *, long int);
}
extern "C"
{
  extern void nanos_atomic_neq_longlong_(volatile long long int *, long long int);
}
extern "C"
{
  extern void nanos_atomic_neq_longlong(volatile long long int *, long long int);
}
extern "C"
{
  extern void nanos_atomic_neq_uchar_(volatile unsigned char *, unsigned char);
}
extern "C"
{
  extern void nanos_atomic_neq_uchar(volatile unsigned char *, unsigned char);
}
extern "C"
{
  extern void nanos_atomic_neq_ushort_(volatile unsigned short int *, unsigned short int);
}
extern "C"
{
  extern void nanos_atomic_neq_ushort(volatile unsigned short int *, unsigned short int);
}
extern "C"
{
  extern void nanos_atomic_neq_uint_(volatile unsigned int *, unsigned int);
}
extern "C"
{
  extern void nanos_atomic_neq_uint(volatile unsigned int *, unsigned int);
}
extern "C"
{
  extern void nanos_atomic_neq_ulong_(volatile unsigned long int *, unsigned long int);
}
extern "C"
{
  extern void nanos_atomic_neq_ulong(volatile unsigned long int *, unsigned long int);
}
extern "C"
{
  extern void nanos_atomic_neq_ulonglong_(volatile unsigned long long int *, unsigned long long int);
}
extern "C"
{
  extern void nanos_atomic_neq_ulonglong(volatile unsigned long long int *, unsigned long long int);
}
extern "C"
{
  extern void nanos_atomic_neq_bytebool_(volatile signed char *, signed char);
}
extern "C"
{
  extern void nanos_atomic_neq_bytebool(volatile signed char *, signed char);
}
extern "C"
{
  extern void nanos_atomic_neq_shortbool_(volatile short int *, short int);
}
extern "C"
{
  extern void nanos_atomic_neq_shortbool(volatile short int *, short int);
}
extern "C"
{
  extern void nanos_atomic_neq_intbool_(volatile int *, int);
}
extern "C"
{
  extern void nanos_atomic_neq_intbool(volatile int *, int);
}
extern "C"
{
  extern void nanos_atomic_neq_longbool_(volatile long int *, long int);
}
extern "C"
{
  extern void nanos_atomic_neq_longbool(volatile long int *, long int);
}
extern "C"
{
  extern void nanos_atomic_neq_longlongbool_(volatile long long int *, long long int);
}
extern "C"
{
  extern void nanos_atomic_neq_longlongbool(volatile long long int *, long long int);
}
extern "C"
{
  extern void nanos_atomic_neq_float_(volatile float *, float);
}
extern "C"
{
  extern void nanos_atomic_neq_float(volatile float *, float);
}
extern "C"
{
  extern void nanos_atomic_neq_double_(volatile double *, double);
}
extern "C"
{
  extern void nanos_atomic_neq_double(volatile double *, double);
}
extern "C"
{
  extern void nanos_atomic_neq_ldouble_(volatile long double *, long double);
}
extern "C"
{
  extern void nanos_atomic_neq_ldouble(volatile long double *, long double);
}
extern "C"
{
  extern void nanos_atomic_neq_cfloat_(volatile _Complex float *, _Complex float);
}
extern "C"
{
  extern void nanos_atomic_neq_cfloat(volatile _Complex float *, _Complex float);
}
extern "C"
{
  extern void nanos_atomic_neq_cdouble_(volatile _Complex double *, _Complex double);
}
extern "C"
{
  extern void nanos_atomic_neq_cdouble(volatile _Complex double *, _Complex double);
}
extern "C"
{
  extern void nanos_atomic_neq_cldouble_(volatile _Complex long double *, _Complex long double);
}
extern "C"
{
  extern void nanos_atomic_neq_cldouble(volatile _Complex long double *, _Complex long double);
}
extern "C"
{
  extern void nanos_atomic_mod_schar_(volatile signed char *, signed char);
}
extern "C"
{
  extern void nanos_atomic_mod_schar(volatile signed char *, signed char);
}
extern "C"
{
  extern void nanos_atomic_mod_short_(volatile short int *, short int);
}
extern "C"
{
  extern void nanos_atomic_mod_short(volatile short int *, short int);
}
extern "C"
{
  extern void nanos_atomic_mod_int_(volatile int *, int);
}
extern "C"
{
  extern void nanos_atomic_mod_int(volatile int *, int);
}
extern "C"
{
  extern void nanos_atomic_mod_long_(volatile long int *, long int);
}
extern "C"
{
  extern void nanos_atomic_mod_long(volatile long int *, long int);
}
extern "C"
{
  extern void nanos_atomic_mod_longlong_(volatile long long int *, long long int);
}
extern "C"
{
  extern void nanos_atomic_mod_longlong(volatile long long int *, long long int);
}
extern "C"
{
  extern void nanos_atomic_mod_uchar_(volatile unsigned char *, unsigned char);
}
extern "C"
{
  extern void nanos_atomic_mod_uchar(volatile unsigned char *, unsigned char);
}
extern "C"
{
  extern void nanos_atomic_mod_ushort_(volatile unsigned short int *, unsigned short int);
}
extern "C"
{
  extern void nanos_atomic_mod_ushort(volatile unsigned short int *, unsigned short int);
}
extern "C"
{
  extern void nanos_atomic_mod_uint_(volatile unsigned int *, unsigned int);
}
extern "C"
{
  extern void nanos_atomic_mod_uint(volatile unsigned int *, unsigned int);
}
extern "C"
{
  extern void nanos_atomic_mod_ulong_(volatile unsigned long int *, unsigned long int);
}
extern "C"
{
  extern void nanos_atomic_mod_ulong(volatile unsigned long int *, unsigned long int);
}
extern "C"
{
  extern void nanos_atomic_mod_ulonglong_(volatile unsigned long long int *, unsigned long long int);
}
extern "C"
{
  extern void nanos_atomic_mod_ulonglong(volatile unsigned long long int *, unsigned long long int);
}
extern "C"
{
  extern void nanos_atomic_mod_bytebool_(volatile signed char *, signed char);
}
extern "C"
{
  extern void nanos_atomic_mod_bytebool(volatile signed char *, signed char);
}
extern "C"
{
  extern void nanos_atomic_mod_shortbool_(volatile short int *, short int);
}
extern "C"
{
  extern void nanos_atomic_mod_shortbool(volatile short int *, short int);
}
extern "C"
{
  extern void nanos_atomic_mod_intbool_(volatile int *, int);
}
extern "C"
{
  extern void nanos_atomic_mod_intbool(volatile int *, int);
}
extern "C"
{
  extern void nanos_atomic_mod_longbool_(volatile long int *, long int);
}
extern "C"
{
  extern void nanos_atomic_mod_longbool(volatile long int *, long int);
}
extern "C"
{
  extern void nanos_atomic_mod_longlongbool_(volatile long long int *, long long int);
}
extern "C"
{
  extern void nanos_atomic_mod_longlongbool(volatile long long int *, long long int);
}
extern "C"
{
  extern void nanos_atomic_shl_schar_(volatile signed char *, signed char);
}
extern "C"
{
  extern void nanos_atomic_shl_schar(volatile signed char *, signed char);
}
extern "C"
{
  extern void nanos_atomic_shl_short_(volatile short int *, short int);
}
extern "C"
{
  extern void nanos_atomic_shl_short(volatile short int *, short int);
}
extern "C"
{
  extern void nanos_atomic_shl_int_(volatile int *, int);
}
extern "C"
{
  extern void nanos_atomic_shl_int(volatile int *, int);
}
extern "C"
{
  extern void nanos_atomic_shl_long_(volatile long int *, long int);
}
extern "C"
{
  extern void nanos_atomic_shl_long(volatile long int *, long int);
}
extern "C"
{
  extern void nanos_atomic_shl_longlong_(volatile long long int *, long long int);
}
extern "C"
{
  extern void nanos_atomic_shl_longlong(volatile long long int *, long long int);
}
extern "C"
{
  extern void nanos_atomic_shl_uchar_(volatile unsigned char *, unsigned char);
}
extern "C"
{
  extern void nanos_atomic_shl_uchar(volatile unsigned char *, unsigned char);
}
extern "C"
{
  extern void nanos_atomic_shl_ushort_(volatile unsigned short int *, unsigned short int);
}
extern "C"
{
  extern void nanos_atomic_shl_ushort(volatile unsigned short int *, unsigned short int);
}
extern "C"
{
  extern void nanos_atomic_shl_uint_(volatile unsigned int *, unsigned int);
}
extern "C"
{
  extern void nanos_atomic_shl_uint(volatile unsigned int *, unsigned int);
}
extern "C"
{
  extern void nanos_atomic_shl_ulong_(volatile unsigned long int *, unsigned long int);
}
extern "C"
{
  extern void nanos_atomic_shl_ulong(volatile unsigned long int *, unsigned long int);
}
extern "C"
{
  extern void nanos_atomic_shl_ulonglong_(volatile unsigned long long int *, unsigned long long int);
}
extern "C"
{
  extern void nanos_atomic_shl_ulonglong(volatile unsigned long long int *, unsigned long long int);
}
extern "C"
{
  extern void nanos_atomic_shl_bytebool_(volatile signed char *, signed char);
}
extern "C"
{
  extern void nanos_atomic_shl_bytebool(volatile signed char *, signed char);
}
extern "C"
{
  extern void nanos_atomic_shl_shortbool_(volatile short int *, short int);
}
extern "C"
{
  extern void nanos_atomic_shl_shortbool(volatile short int *, short int);
}
extern "C"
{
  extern void nanos_atomic_shl_intbool_(volatile int *, int);
}
extern "C"
{
  extern void nanos_atomic_shl_intbool(volatile int *, int);
}
extern "C"
{
  extern void nanos_atomic_shl_longbool_(volatile long int *, long int);
}
extern "C"
{
  extern void nanos_atomic_shl_longbool(volatile long int *, long int);
}
extern "C"
{
  extern void nanos_atomic_shl_longlongbool_(volatile long long int *, long long int);
}
extern "C"
{
  extern void nanos_atomic_shl_longlongbool(volatile long long int *, long long int);
}
extern "C"
{
  extern void nanos_atomic_shr_schar_(volatile signed char *, signed char);
}
extern "C"
{
  extern void nanos_atomic_shr_schar(volatile signed char *, signed char);
}
extern "C"
{
  extern void nanos_atomic_shr_short_(volatile short int *, short int);
}
extern "C"
{
  extern void nanos_atomic_shr_short(volatile short int *, short int);
}
extern "C"
{
  extern void nanos_atomic_shr_int_(volatile int *, int);
}
extern "C"
{
  extern void nanos_atomic_shr_int(volatile int *, int);
}
extern "C"
{
  extern void nanos_atomic_shr_long_(volatile long int *, long int);
}
extern "C"
{
  extern void nanos_atomic_shr_long(volatile long int *, long int);
}
extern "C"
{
  extern void nanos_atomic_shr_longlong_(volatile long long int *, long long int);
}
extern "C"
{
  extern void nanos_atomic_shr_longlong(volatile long long int *, long long int);
}
extern "C"
{
  extern void nanos_atomic_shr_uchar_(volatile unsigned char *, unsigned char);
}
extern "C"
{
  extern void nanos_atomic_shr_uchar(volatile unsigned char *, unsigned char);
}
extern "C"
{
  extern void nanos_atomic_shr_ushort_(volatile unsigned short int *, unsigned short int);
}
extern "C"
{
  extern void nanos_atomic_shr_ushort(volatile unsigned short int *, unsigned short int);
}
extern "C"
{
  extern void nanos_atomic_shr_uint_(volatile unsigned int *, unsigned int);
}
extern "C"
{
  extern void nanos_atomic_shr_uint(volatile unsigned int *, unsigned int);
}
extern "C"
{
  extern void nanos_atomic_shr_ulong_(volatile unsigned long int *, unsigned long int);
}
extern "C"
{
  extern void nanos_atomic_shr_ulong(volatile unsigned long int *, unsigned long int);
}
extern "C"
{
  extern void nanos_atomic_shr_ulonglong_(volatile unsigned long long int *, unsigned long long int);
}
extern "C"
{
  extern void nanos_atomic_shr_ulonglong(volatile unsigned long long int *, unsigned long long int);
}
extern "C"
{
  extern void nanos_atomic_shr_bytebool_(volatile signed char *, signed char);
}
extern "C"
{
  extern void nanos_atomic_shr_bytebool(volatile signed char *, signed char);
}
extern "C"
{
  extern void nanos_atomic_shr_shortbool_(volatile short int *, short int);
}
extern "C"
{
  extern void nanos_atomic_shr_shortbool(volatile short int *, short int);
}
extern "C"
{
  extern void nanos_atomic_shr_intbool_(volatile int *, int);
}
extern "C"
{
  extern void nanos_atomic_shr_intbool(volatile int *, int);
}
extern "C"
{
  extern void nanos_atomic_shr_longbool_(volatile long int *, long int);
}
extern "C"
{
  extern void nanos_atomic_shr_longbool(volatile long int *, long int);
}
extern "C"
{
  extern void nanos_atomic_shr_longlongbool_(volatile long long int *, long long int);
}
extern "C"
{
  extern void nanos_atomic_shr_longlongbool(volatile long long int *, long long int);
}
extern "C"
{
  extern void nanos_atomic_land_schar_(volatile signed char *, signed char);
}
extern "C"
{
  extern void nanos_atomic_land_schar(volatile signed char *, signed char);
}
extern "C"
{
  extern void nanos_atomic_land_short_(volatile short int *, short int);
}
extern "C"
{
  extern void nanos_atomic_land_short(volatile short int *, short int);
}
extern "C"
{
  extern void nanos_atomic_land_int_(volatile int *, int);
}
extern "C"
{
  extern void nanos_atomic_land_int(volatile int *, int);
}
extern "C"
{
  extern void nanos_atomic_land_long_(volatile long int *, long int);
}
extern "C"
{
  extern void nanos_atomic_land_long(volatile long int *, long int);
}
extern "C"
{
  extern void nanos_atomic_land_longlong_(volatile long long int *, long long int);
}
extern "C"
{
  extern void nanos_atomic_land_longlong(volatile long long int *, long long int);
}
extern "C"
{
  extern void nanos_atomic_land_uchar_(volatile unsigned char *, unsigned char);
}
extern "C"
{
  extern void nanos_atomic_land_uchar(volatile unsigned char *, unsigned char);
}
extern "C"
{
  extern void nanos_atomic_land_ushort_(volatile unsigned short int *, unsigned short int);
}
extern "C"
{
  extern void nanos_atomic_land_ushort(volatile unsigned short int *, unsigned short int);
}
extern "C"
{
  extern void nanos_atomic_land_uint_(volatile unsigned int *, unsigned int);
}
extern "C"
{
  extern void nanos_atomic_land_uint(volatile unsigned int *, unsigned int);
}
extern "C"
{
  extern void nanos_atomic_land_ulong_(volatile unsigned long int *, unsigned long int);
}
extern "C"
{
  extern void nanos_atomic_land_ulong(volatile unsigned long int *, unsigned long int);
}
extern "C"
{
  extern void nanos_atomic_land_ulonglong_(volatile unsigned long long int *, unsigned long long int);
}
extern "C"
{
  extern void nanos_atomic_land_ulonglong(volatile unsigned long long int *, unsigned long long int);
}
extern "C"
{
  extern void nanos_atomic_land_bytebool_(volatile signed char *, signed char);
}
extern "C"
{
  extern void nanos_atomic_land_bytebool(volatile signed char *, signed char);
}
extern "C"
{
  extern void nanos_atomic_land_shortbool_(volatile short int *, short int);
}
extern "C"
{
  extern void nanos_atomic_land_shortbool(volatile short int *, short int);
}
extern "C"
{
  extern void nanos_atomic_land_intbool_(volatile int *, int);
}
extern "C"
{
  extern void nanos_atomic_land_intbool(volatile int *, int);
}
extern "C"
{
  extern void nanos_atomic_land_longbool_(volatile long int *, long int);
}
extern "C"
{
  extern void nanos_atomic_land_longbool(volatile long int *, long int);
}
extern "C"
{
  extern void nanos_atomic_land_longlongbool_(volatile long long int *, long long int);
}
extern "C"
{
  extern void nanos_atomic_land_longlongbool(volatile long long int *, long long int);
}
extern "C"
{
  extern void nanos_atomic_lor_schar_(volatile signed char *, signed char);
}
extern "C"
{
  extern void nanos_atomic_lor_schar(volatile signed char *, signed char);
}
extern "C"
{
  extern void nanos_atomic_lor_short_(volatile short int *, short int);
}
extern "C"
{
  extern void nanos_atomic_lor_short(volatile short int *, short int);
}
extern "C"
{
  extern void nanos_atomic_lor_int_(volatile int *, int);
}
extern "C"
{
  extern void nanos_atomic_lor_int(volatile int *, int);
}
extern "C"
{
  extern void nanos_atomic_lor_long_(volatile long int *, long int);
}
extern "C"
{
  extern void nanos_atomic_lor_long(volatile long int *, long int);
}
extern "C"
{
  extern void nanos_atomic_lor_longlong_(volatile long long int *, long long int);
}
extern "C"
{
  extern void nanos_atomic_lor_longlong(volatile long long int *, long long int);
}
extern "C"
{
  extern void nanos_atomic_lor_uchar_(volatile unsigned char *, unsigned char);
}
extern "C"
{
  extern void nanos_atomic_lor_uchar(volatile unsigned char *, unsigned char);
}
extern "C"
{
  extern void nanos_atomic_lor_ushort_(volatile unsigned short int *, unsigned short int);
}
extern "C"
{
  extern void nanos_atomic_lor_ushort(volatile unsigned short int *, unsigned short int);
}
extern "C"
{
  extern void nanos_atomic_lor_uint_(volatile unsigned int *, unsigned int);
}
extern "C"
{
  extern void nanos_atomic_lor_uint(volatile unsigned int *, unsigned int);
}
extern "C"
{
  extern void nanos_atomic_lor_ulong_(volatile unsigned long int *, unsigned long int);
}
extern "C"
{
  extern void nanos_atomic_lor_ulong(volatile unsigned long int *, unsigned long int);
}
extern "C"
{
  extern void nanos_atomic_lor_ulonglong_(volatile unsigned long long int *, unsigned long long int);
}
extern "C"
{
  extern void nanos_atomic_lor_ulonglong(volatile unsigned long long int *, unsigned long long int);
}
extern "C"
{
  extern void nanos_atomic_lor_bytebool_(volatile signed char *, signed char);
}
extern "C"
{
  extern void nanos_atomic_lor_bytebool(volatile signed char *, signed char);
}
extern "C"
{
  extern void nanos_atomic_lor_shortbool_(volatile short int *, short int);
}
extern "C"
{
  extern void nanos_atomic_lor_shortbool(volatile short int *, short int);
}
extern "C"
{
  extern void nanos_atomic_lor_intbool_(volatile int *, int);
}
extern "C"
{
  extern void nanos_atomic_lor_intbool(volatile int *, int);
}
extern "C"
{
  extern void nanos_atomic_lor_longbool_(volatile long int *, long int);
}
extern "C"
{
  extern void nanos_atomic_lor_longbool(volatile long int *, long int);
}
extern "C"
{
  extern void nanos_atomic_lor_longlongbool_(volatile long long int *, long long int);
}
extern "C"
{
  extern void nanos_atomic_lor_longlongbool(volatile long long int *, long long int);
}
extern "C"
{
  extern void nanos_atomic_band_schar_(volatile signed char *, signed char);
}
extern "C"
{
  extern void nanos_atomic_band_schar(volatile signed char *, signed char);
}
extern "C"
{
  extern void nanos_atomic_band_short_(volatile short int *, short int);
}
extern "C"
{
  extern void nanos_atomic_band_short(volatile short int *, short int);
}
extern "C"
{
  extern void nanos_atomic_band_int_(volatile int *, int);
}
extern "C"
{
  extern void nanos_atomic_band_int(volatile int *, int);
}
extern "C"
{
  extern void nanos_atomic_band_long_(volatile long int *, long int);
}
extern "C"
{
  extern void nanos_atomic_band_long(volatile long int *, long int);
}
extern "C"
{
  extern void nanos_atomic_band_longlong_(volatile long long int *, long long int);
}
extern "C"
{
  extern void nanos_atomic_band_longlong(volatile long long int *, long long int);
}
extern "C"
{
  extern void nanos_atomic_band_uchar_(volatile unsigned char *, unsigned char);
}
extern "C"
{
  extern void nanos_atomic_band_uchar(volatile unsigned char *, unsigned char);
}
extern "C"
{
  extern void nanos_atomic_band_ushort_(volatile unsigned short int *, unsigned short int);
}
extern "C"
{
  extern void nanos_atomic_band_ushort(volatile unsigned short int *, unsigned short int);
}
extern "C"
{
  extern void nanos_atomic_band_uint_(volatile unsigned int *, unsigned int);
}
extern "C"
{
  extern void nanos_atomic_band_uint(volatile unsigned int *, unsigned int);
}
extern "C"
{
  extern void nanos_atomic_band_ulong_(volatile unsigned long int *, unsigned long int);
}
extern "C"
{
  extern void nanos_atomic_band_ulong(volatile unsigned long int *, unsigned long int);
}
extern "C"
{
  extern void nanos_atomic_band_ulonglong_(volatile unsigned long long int *, unsigned long long int);
}
extern "C"
{
  extern void nanos_atomic_band_ulonglong(volatile unsigned long long int *, unsigned long long int);
}
extern "C"
{
  extern void nanos_atomic_band_bytebool_(volatile signed char *, signed char);
}
extern "C"
{
  extern void nanos_atomic_band_bytebool(volatile signed char *, signed char);
}
extern "C"
{
  extern void nanos_atomic_band_shortbool_(volatile short int *, short int);
}
extern "C"
{
  extern void nanos_atomic_band_shortbool(volatile short int *, short int);
}
extern "C"
{
  extern void nanos_atomic_band_intbool_(volatile int *, int);
}
extern "C"
{
  extern void nanos_atomic_band_intbool(volatile int *, int);
}
extern "C"
{
  extern void nanos_atomic_band_longbool_(volatile long int *, long int);
}
extern "C"
{
  extern void nanos_atomic_band_longbool(volatile long int *, long int);
}
extern "C"
{
  extern void nanos_atomic_band_longlongbool_(volatile long long int *, long long int);
}
extern "C"
{
  extern void nanos_atomic_band_longlongbool(volatile long long int *, long long int);
}
extern "C"
{
  extern void nanos_atomic_bor_schar_(volatile signed char *, signed char);
}
extern "C"
{
  extern void nanos_atomic_bor_schar(volatile signed char *, signed char);
}
extern "C"
{
  extern void nanos_atomic_bor_short_(volatile short int *, short int);
}
extern "C"
{
  extern void nanos_atomic_bor_short(volatile short int *, short int);
}
extern "C"
{
  extern void nanos_atomic_bor_int_(volatile int *, int);
}
extern "C"
{
  extern void nanos_atomic_bor_int(volatile int *, int);
}
extern "C"
{
  extern void nanos_atomic_bor_long_(volatile long int *, long int);
}
extern "C"
{
  extern void nanos_atomic_bor_long(volatile long int *, long int);
}
extern "C"
{
  extern void nanos_atomic_bor_longlong_(volatile long long int *, long long int);
}
extern "C"
{
  extern void nanos_atomic_bor_longlong(volatile long long int *, long long int);
}
extern "C"
{
  extern void nanos_atomic_bor_uchar_(volatile unsigned char *, unsigned char);
}
extern "C"
{
  extern void nanos_atomic_bor_uchar(volatile unsigned char *, unsigned char);
}
extern "C"
{
  extern void nanos_atomic_bor_ushort_(volatile unsigned short int *, unsigned short int);
}
extern "C"
{
  extern void nanos_atomic_bor_ushort(volatile unsigned short int *, unsigned short int);
}
extern "C"
{
  extern void nanos_atomic_bor_uint_(volatile unsigned int *, unsigned int);
}
extern "C"
{
  extern void nanos_atomic_bor_uint(volatile unsigned int *, unsigned int);
}
extern "C"
{
  extern void nanos_atomic_bor_ulong_(volatile unsigned long int *, unsigned long int);
}
extern "C"
{
  extern void nanos_atomic_bor_ulong(volatile unsigned long int *, unsigned long int);
}
extern "C"
{
  extern void nanos_atomic_bor_ulonglong_(volatile unsigned long long int *, unsigned long long int);
}
extern "C"
{
  extern void nanos_atomic_bor_ulonglong(volatile unsigned long long int *, unsigned long long int);
}
extern "C"
{
  extern void nanos_atomic_bor_bytebool_(volatile signed char *, signed char);
}
extern "C"
{
  extern void nanos_atomic_bor_bytebool(volatile signed char *, signed char);
}
extern "C"
{
  extern void nanos_atomic_bor_shortbool_(volatile short int *, short int);
}
extern "C"
{
  extern void nanos_atomic_bor_shortbool(volatile short int *, short int);
}
extern "C"
{
  extern void nanos_atomic_bor_intbool_(volatile int *, int);
}
extern "C"
{
  extern void nanos_atomic_bor_intbool(volatile int *, int);
}
extern "C"
{
  extern void nanos_atomic_bor_longbool_(volatile long int *, long int);
}
extern "C"
{
  extern void nanos_atomic_bor_longbool(volatile long int *, long int);
}
extern "C"
{
  extern void nanos_atomic_bor_longlongbool_(volatile long long int *, long long int);
}
extern "C"
{
  extern void nanos_atomic_bor_longlongbool(volatile long long int *, long long int);
}
extern "C"
{
  extern void nanos_atomic_bxor_schar_(volatile signed char *, signed char);
}
extern "C"
{
  extern void nanos_atomic_bxor_schar(volatile signed char *, signed char);
}
extern "C"
{
  extern void nanos_atomic_bxor_short_(volatile short int *, short int);
}
extern "C"
{
  extern void nanos_atomic_bxor_short(volatile short int *, short int);
}
extern "C"
{
  extern void nanos_atomic_bxor_int_(volatile int *, int);
}
extern "C"
{
  extern void nanos_atomic_bxor_int(volatile int *, int);
}
extern "C"
{
  extern void nanos_atomic_bxor_long_(volatile long int *, long int);
}
extern "C"
{
  extern void nanos_atomic_bxor_long(volatile long int *, long int);
}
extern "C"
{
  extern void nanos_atomic_bxor_longlong_(volatile long long int *, long long int);
}
extern "C"
{
  extern void nanos_atomic_bxor_longlong(volatile long long int *, long long int);
}
extern "C"
{
  extern void nanos_atomic_bxor_uchar_(volatile unsigned char *, unsigned char);
}
extern "C"
{
  extern void nanos_atomic_bxor_uchar(volatile unsigned char *, unsigned char);
}
extern "C"
{
  extern void nanos_atomic_bxor_ushort_(volatile unsigned short int *, unsigned short int);
}
extern "C"
{
  extern void nanos_atomic_bxor_ushort(volatile unsigned short int *, unsigned short int);
}
extern "C"
{
  extern void nanos_atomic_bxor_uint_(volatile unsigned int *, unsigned int);
}
extern "C"
{
  extern void nanos_atomic_bxor_uint(volatile unsigned int *, unsigned int);
}
extern "C"
{
  extern void nanos_atomic_bxor_ulong_(volatile unsigned long int *, unsigned long int);
}
extern "C"
{
  extern void nanos_atomic_bxor_ulong(volatile unsigned long int *, unsigned long int);
}
extern "C"
{
  extern void nanos_atomic_bxor_ulonglong_(volatile unsigned long long int *, unsigned long long int);
}
extern "C"
{
  extern void nanos_atomic_bxor_ulonglong(volatile unsigned long long int *, unsigned long long int);
}
extern "C"
{
  extern void nanos_atomic_bxor_bytebool_(volatile signed char *, signed char);
}
extern "C"
{
  extern void nanos_atomic_bxor_bytebool(volatile signed char *, signed char);
}
extern "C"
{
  extern void nanos_atomic_bxor_shortbool_(volatile short int *, short int);
}
extern "C"
{
  extern void nanos_atomic_bxor_shortbool(volatile short int *, short int);
}
extern "C"
{
  extern void nanos_atomic_bxor_intbool_(volatile int *, int);
}
extern "C"
{
  extern void nanos_atomic_bxor_intbool(volatile int *, int);
}
extern "C"
{
  extern void nanos_atomic_bxor_longbool_(volatile long int *, long int);
}
extern "C"
{
  extern void nanos_atomic_bxor_longbool(volatile long int *, long int);
}
extern "C"
{
  extern void nanos_atomic_bxor_longlongbool_(volatile long long int *, long long int);
}
extern "C"
{
  extern void nanos_atomic_bxor_longlongbool(volatile long long int *, long long int);
}
enum nanos_omp_sched_t
{
  nanos_omp_sched_static = 1,
  nanos_omp_sched_dynamic = 2,
  nanos_omp_sched_guided = 3,
  nanos_omp_sched_auto = 4
};
extern "C"
{
  extern ::nanos_err_t nanos_omp_single_(bool *);
}
extern "C"
{
  extern ::nanos_err_t nanos_omp_single(bool *);
}
extern "C"
{
  extern ::nanos_err_t nanos_omp_barrier_();
}
extern "C"
{
  extern ::nanos_err_t nanos_omp_barrier();
}
extern "C"
{
  extern ::nanos_err_t nanos_omp_set_implicit_(::nanos_wd_t uwd);
}
extern "C"
{
  extern ::nanos_err_t nanos_omp_set_implicit(::nanos_wd_t uwd);
}
extern "C"
{
  extern int nanos_omp_get_max_threads_();
}
extern "C"
{
  extern int nanos_omp_get_max_threads();
}
extern "C"
{
  extern int nanos_omp_get_num_threads_();
}
extern "C"
{
  extern int nanos_omp_get_num_threads();
}
extern "C"
{
  extern int nanos_omp_get_thread_num_();
}
extern "C"
{
  extern int nanos_omp_get_thread_num();
}
extern "C"
{
  extern void nanos_omp_set_num_threads_(int nthreads);
}
extern "C"
{
  extern void nanos_omp_set_num_threads(int nthreads);
}
extern "C"
{
  extern ::nanos_ws_t nanos_omp_find_worksharing_(::nanos_omp_sched_t kind);
}
extern "C"
{
  extern ::nanos_ws_t nanos_omp_find_worksharing(::nanos_omp_sched_t kind);
}
extern "C"
{
  extern ::nanos_err_t nanos_omp_get_schedule_(::nanos_omp_sched_t *kind, int *modifier);
}
extern "C"
{
  extern ::nanos_err_t nanos_omp_get_schedule(::nanos_omp_sched_t *kind, int *modifier);
}
extern "C"
{
  extern int nanos_omp_get_num_threads_next_parallel_(int threads_requested);
}
extern "C"
{
  extern int nanos_omp_get_num_threads_next_parallel(int threads_requested);
}
extern "C"
{
  extern void nanos_omp_get_process_mask_(::nanos_cpu_set_t cpu_set);
}
extern "C"
{
  extern void nanos_omp_get_process_mask(::nanos_cpu_set_t cpu_set);
}
extern "C"
{
  extern int nanos_omp_set_process_mask_(::const_nanos_cpu_set_t cpu_set);
}
extern "C"
{
  extern int nanos_omp_set_process_mask(::const_nanos_cpu_set_t cpu_set);
}
extern "C"
{
  extern void nanos_omp_add_process_mask_(::const_nanos_cpu_set_t cpu_set);
}
extern "C"
{
  extern void nanos_omp_add_process_mask(::const_nanos_cpu_set_t cpu_set);
}
extern "C"
{
  extern void nanos_omp_get_active_mask_(::nanos_cpu_set_t cpu_set);
}
extern "C"
{
  extern void nanos_omp_get_active_mask(::nanos_cpu_set_t cpu_set);
}
extern "C"
{
  extern int nanos_omp_set_active_mask_(::const_nanos_cpu_set_t cpu_set);
}
extern "C"
{
  extern int nanos_omp_set_active_mask(::const_nanos_cpu_set_t cpu_set);
}
extern "C"
{
  extern void nanos_omp_add_active_mask_(::const_nanos_cpu_set_t cpu_set);
}
extern "C"
{
  extern void nanos_omp_add_active_mask(::const_nanos_cpu_set_t cpu_set);
}
extern "C"
{
  extern int nanos_omp_enable_cpu_(int cpuid);
}
extern "C"
{
  extern int nanos_omp_enable_cpu(int cpuid);
}
extern "C"
{
  extern int nanos_omp_disable_cpu_(int cpuid);
}
extern "C"
{
  extern int nanos_omp_disable_cpu(int cpuid);
}
extern "C"
{
  extern int nanos_omp_get_max_processors_();
}
extern "C"
{
  extern int nanos_omp_get_max_processors();
}
namespace std __attribute__((__visibility__("default"))) {
  typedef unsigned long int size_t;
  typedef long int ptrdiff_t;
  typedef decltype(nullptr) nullptr_t;
}
#pragma GCC visibility push(default)
namespace std __attribute__((__visibility__("default"))) {
  class  exception
  {
    public:
      inline exception() noexcept
      {
      }
      virtual ~exception() noexcept;
      virtual const char *what() const  noexcept;
  };
  class  bad_exception : public ::std::exception
  {
    public:
      inline bad_exception() noexcept
      {
      }
      virtual ~bad_exception() noexcept;
      virtual const char *what() const  noexcept;
  };
  typedef void (*terminate_handler)();
  typedef void (*unexpected_handler)();
  ::std::terminate_handler set_terminate(::std::terminate_handler) noexcept;
  ::std::terminate_handler get_terminate() noexcept;
  void terminate() noexcept __attribute__((__noreturn__));
  ::std::unexpected_handler set_unexpected(::std::unexpected_handler) noexcept;
  ::std::unexpected_handler get_unexpected() noexcept;
  void unexpected() __attribute__((__noreturn__));
  bool uncaught_exception() noexcept __attribute__((__pure__));
}
namespace __gnu_cxx __attribute__((__visibility__("default"))) {
  void __verbose_terminate_handler();
}
#pragma GCC visibility pop
#pragma GCC visibility push(default)
namespace std __attribute__((__visibility__("default"))) {
  class type_info;
  namespace __exception_ptr {
    class exception_ptr;
  }
  using ::std::__exception_ptr::exception_ptr;
  ::std::__exception_ptr::exception_ptr current_exception() noexcept;
  void rethrow_exception(::std::__exception_ptr::exception_ptr) __attribute__((__noreturn__));
  namespace __exception_ptr {
    using ::std::rethrow_exception;
    class  exception_ptr
    {
        void *_M_exception_object;
        explicit exception_ptr(void *__e) noexcept;
        void _M_addref() noexcept;
        void _M_release() noexcept;
        void *_M_get() const  noexcept __attribute__((__pure__));
      public:
        exception_ptr() noexcept;
        exception_ptr(const ::std::__exception_ptr::exception_ptr &) noexcept;
        inline exception_ptr(::std::nullptr_t) noexcept
          : _M_exception_object(0)
        {
        }
        inline exception_ptr(::std::__exception_ptr::exception_ptr &&__o) noexcept
          : _M_exception_object(__o._M_exception_object)
        {
          __o._M_exception_object = 0;
        }
        ::std::__exception_ptr::exception_ptr &operator =(const ::std::__exception_ptr::exception_ptr &) noexcept;
        inline ::std::__exception_ptr::exception_ptr &operator =(::std::__exception_ptr::exception_ptr &&__o) noexcept
        {
          ::std::__exception_ptr::exception_ptr(static_cast< ::std::__exception_ptr::exception_ptr &&>(__o)).::std::__exception_ptr::exception_ptr::swap(*this);
          return *this;
        }
        ~exception_ptr() noexcept;
        void swap(::std::__exception_ptr::exception_ptr &) noexcept;
        inline explicit operator bool() const 
        {
          return (*this)._M_exception_object;
        }
        const ::std::type_info *__cxa_exception_type() const  noexcept __attribute__((__pure__));
      friend ::std::__exception_ptr::exception_ptr (::std::current_exception)() noexcept;
      friend void (::std::rethrow_exception)(::std::__exception_ptr::exception_ptr);
      friend bool operator ==(const ::std::__exception_ptr::exception_ptr &, const ::std::__exception_ptr::exception_ptr &) noexcept;
    };
    bool operator ==(const ::std::__exception_ptr::exception_ptr &, const ::std::__exception_ptr::exception_ptr &) noexcept __attribute__((__pure__));
    bool operator !=(const ::std::__exception_ptr::exception_ptr &, const ::std::__exception_ptr::exception_ptr &) noexcept __attribute__((__pure__));
    inline void swap(::std::__exception_ptr::exception_ptr &__lhs, ::std::__exception_ptr::exception_ptr &__rhs)
    {
      __lhs.::std::__exception_ptr::exception_ptr::swap(__rhs);
    }
  }
  template < typename _Ex >
  ::std::__exception_ptr::exception_ptr make_exception_ptr(_Ex __ex) noexcept;
  template < typename _Ex >
  ::std::__exception_ptr::exception_ptr make_exception_ptr(_Ex __ex) noexcept
  {
    try
    {
      throw __ex;
    }
    catch (...)
    {
      return ::std::current_exception();
    }
  }
  template < typename _Ex >
  ::std::__exception_ptr::exception_ptr copy_exception(_Ex __ex) noexcept;
  template < typename _Ex >
  ::std::__exception_ptr::exception_ptr copy_exception(_Ex __ex) noexcept
  {
    return std::make_exception_ptr<_Ex>(__ex);
  }
}
#pragma GCC visibility pop
#pragma GCC visibility push(default)
namespace std __attribute__((__visibility__("default"))) {
  template < typename _Tp >
  inline _Tp *__addressof(_Tp &__r) noexcept;
  template < typename _Tp >
  inline _Tp *__addressof(_Tp &__r) noexcept
  {
    return reinterpret_cast<_Tp *>(&const_cast<char &>(reinterpret_cast<const volatile char &>(__r)));
  }
  typedef unsigned short int uint_least16_t;
  typedef unsigned int uint_least32_t;
  template < typename _Tp, _Tp __v >
  struct  integral_constant
  {
      static constexpr const _Tp value = __v;
      typedef _Tp value_type;
      typedef ::std::integral_constant<_Tp, __v> type;
      inline constexpr operator typename ::std::integral_constant<_Tp, __v>::value_type() const  noexcept
      {
        return ::std::integral_constant<_Tp, __v>::value;
      }
  };
  template < typename _Tp, _Tp __v >
  constexpr const _Tp integral_constant<_Tp, __v>::value;
  typedef ::std::integral_constant<bool, true> true_type;
  typedef ::std::integral_constant<bool, false> false_type;
  template < bool __v >
  using __bool_constant = ::std::integral_constant<bool, __v>;
  template < bool __nontype_tpl_param_1_0__, typename __type_tpl__param_1_1__, typename __type_tpl__param_1_2__ >
  struct conditional;
  template < typename ...__type_tpl__param_1_0__ >
  struct __or_;
 /* Instantiation of class template '::std::integral_constant<bool, false>' */ 
  template <>
  struct  __or_<> : ::std::integral_constant<bool, false>
  {
  };
  template < typename _B1 >
  struct  __or_<_B1> : _B1
  {
  };
  template < typename _B1, typename _B2 >
  struct  __or_<_B1, _B2> : ::std::conditional<_B1::value, _B1, _B2>::type
  {
  };
  template < typename _B1, typename _B2, typename _B3, typename ..._Bn >
  struct  __or_<_B1, _B2, _B3, _Bn ...> : ::std::conditional<_B1::value, _B1, ::std::__or_<_B2, _B3, _Bn ...> >::type
  {
  };
  template < typename ...__type_tpl__param_1_0__ >
  struct __and_;
 /* Instantiation of class template '::std::integral_constant<bool, true>' */ 
  template <>
  struct  __and_<> : ::std::integral_constant<bool, true>
  {
  };
  template < typename _B1 >
  struct  __and_<_B1> : _B1
  {
  };
  template < typename _B1, typename _B2 >
  struct  __and_<_B1, _B2> : ::std::conditional<_B1::value, _B2, _B1>::type
  {
  };
  template < typename _B1, typename _B2, typename _B3, typename ..._Bn >
  struct  __and_<_B1, _B2, _B3, _Bn ...> : ::std::conditional<_B1::value, ::std::__and_<_B2, _B3, _Bn ...>, _B1>::type
  {
  };
  template < typename _Pp >
  struct  __not_ : ::std::integral_constant<bool, !_Pp::value>
  {
  };
  struct  __nonesuch
  {
      __nonesuch() = delete ;
      ~__nonesuch() = delete ;
      __nonesuch(const ::std::__nonesuch &) = delete ;
      void operator =(const ::std::__nonesuch &) = delete ;
  };
  template < typename _Tp >
  struct  __success_type
  {
      typedef _Tp type;
  };
  struct  __failure_type
  {
  };
  template < typename __type_tpl__param_1_0__ >
  struct remove_cv;
  template < typename __type_tpl__param_1_0__ >
  struct  __is_void_helper : ::std::integral_constant<bool, false>
  {
  };
  template <>
  struct  __is_void_helper<void> : ::std::integral_constant<bool, true>
  {
  };
  template < typename _Tp >
  struct  is_void : ::std::__is_void_helper<typename ::std::remove_cv<_Tp>::type>::type
  {
  };
  template < typename __type_tpl__param_1_0__ >
  struct  __is_integral_helper : ::std::integral_constant<bool, false>
  {
  };
  template <>
  struct  __is_integral_helper<bool> : ::std::integral_constant<bool, true>
  {
  };
  template <>
  struct  __is_integral_helper<char> : ::std::integral_constant<bool, true>
  {
  };
  template <>
  struct  __is_integral_helper<signed char> : ::std::integral_constant<bool, true>
  {
  };
  template <>
  struct  __is_integral_helper<unsigned char> : ::std::integral_constant<bool, true>
  {
  };
  template <>
  struct  __is_integral_helper<wchar_t> : ::std::integral_constant<bool, true>
  {
  };
  template <>
  struct  __is_integral_helper<char16_t> : ::std::integral_constant<bool, true>
  {
  };
  template <>
  struct  __is_integral_helper<char32_t> : ::std::integral_constant<bool, true>
  {
  };
  template <>
  struct  __is_integral_helper<short int> : ::std::integral_constant<bool, true>
  {
  };
  template <>
  struct  __is_integral_helper<unsigned short int> : ::std::integral_constant<bool, true>
  {
  };
  template <>
  struct  __is_integral_helper<int> : ::std::integral_constant<bool, true>
  {
  };
  template <>
  struct  __is_integral_helper<unsigned int> : ::std::integral_constant<bool, true>
  {
  };
  template <>
  struct  __is_integral_helper<long int> : ::std::integral_constant<bool, true>
  {
  };
  template <>
  struct  __is_integral_helper<unsigned long int> : ::std::integral_constant<bool, true>
  {
  };
  template <>
  struct  __is_integral_helper<long long int> : ::std::integral_constant<bool, true>
  {
  };
  template <>
  struct  __is_integral_helper<unsigned long long int> : ::std::integral_constant<bool, true>
  {
  };
  template < typename _Tp >
  struct  is_integral : ::std::__is_integral_helper<typename ::std::remove_cv<_Tp>::type>::type
  {
  };
  template < typename __type_tpl__param_1_0__ >
  struct  __is_floating_point_helper : ::std::integral_constant<bool, false>
  {
  };
  template <>
  struct  __is_floating_point_helper<float> : ::std::integral_constant<bool, true>
  {
  };
  template <>
  struct  __is_floating_point_helper<double> : ::std::integral_constant<bool, true>
  {
  };
  template <>
  struct  __is_floating_point_helper<long double> : ::std::integral_constant<bool, true>
  {
  };
  template < typename _Tp >
  struct  is_floating_point : ::std::__is_floating_point_helper<typename ::std::remove_cv<_Tp>::type>::type
  {
  };
  template < typename __type_tpl__param_1_0__ >
  struct  is_array : ::std::integral_constant<bool, false>
  {
  };
  template < typename _Tp, ::std::size_t _Size >
  struct  is_array<_Tp [_Size]> : ::std::integral_constant<bool, true>
  {
  };
  template < typename _Tp >
  struct  is_array<_Tp []> : ::std::integral_constant<bool, true>
  {
  };
  template < typename __type_tpl__param_1_0__ >
  struct  __is_pointer_helper : ::std::integral_constant<bool, false>
  {
  };
  template < typename _Tp >
  struct  __is_pointer_helper<_Tp *> : ::std::integral_constant<bool, true>
  {
  };
  template < typename _Tp >
  struct  is_pointer : ::std::__is_pointer_helper<typename ::std::remove_cv<_Tp>::type>::type
  {
  };
  template < typename __type_tpl__param_1_0__ >
  struct  is_lvalue_reference : ::std::integral_constant<bool, false>
  {
  };
  template < typename _Tp >
  struct  is_lvalue_reference<_Tp &> : ::std::integral_constant<bool, true>
  {
  };
  template < typename __type_tpl__param_1_0__ >
  struct  is_rvalue_reference : ::std::integral_constant<bool, false>
  {
  };
  template < typename _Tp >
  struct  is_rvalue_reference<_Tp &&> : ::std::integral_constant<bool, true>
  {
  };
  template < typename __type_tpl__param_1_0__ >
  struct is_function;
  template < typename __type_tpl__param_1_0__ >
  struct  __is_member_object_pointer_helper : ::std::integral_constant<bool, false>
  {
  };
  template < typename _Tp, typename _Cp >
  struct  __is_member_object_pointer_helper<_Tp _Cp::*> : ::std::integral_constant<bool, !is_function<_Tp>::value>
  {
  };
  template < typename _Tp >
  struct  is_member_object_pointer : ::std::__is_member_object_pointer_helper<typename ::std::remove_cv<_Tp>::type>::type
  {
  };
  template < typename __type_tpl__param_1_0__ >
  struct  __is_member_function_pointer_helper : ::std::integral_constant<bool, false>
  {
  };
  template < typename _Tp, typename _Cp >
  struct  __is_member_function_pointer_helper<_Tp _Cp::*> : ::std::integral_constant<bool, is_function<_Tp>::value>
  {
  };
  template < typename _Tp >
  struct  is_member_function_pointer : ::std::__is_member_function_pointer_helper<typename ::std::remove_cv<_Tp>::type>::type
  {
  };
  template < typename _Tp >
  struct  is_enum : ::std::integral_constant<bool, __is_enum(_Tp)>
  {
  };
  template < typename _Tp >
  struct  is_union : ::std::integral_constant<bool, __is_union(_Tp)>
  {
  };
  template < typename _Tp >
  struct  is_class : ::std::integral_constant<bool, __is_class(_Tp)>
  {
  };
  template < typename __type_tpl__param_1_0__ >
  struct  is_function : ::std::integral_constant<bool, false>
  {
  };
  template < typename _Res, typename ..._ArgTypes >
  struct  is_function<_Res (_ArgTypes ...)> : ::std::integral_constant<bool, true>
  {
  };
  template < typename _Res, typename ..._ArgTypes >
  struct  is_function<_Res (_ArgTypes ...) &> : ::std::integral_constant<bool, true>
  {
  };
  template < typename _Res, typename ..._ArgTypes >
  struct  is_function<_Res (_ArgTypes ...) &&> : ::std::integral_constant<bool, true>
  {
  };
  template < typename _Res, typename ..._ArgTypes >
  struct  is_function<_Res (_ArgTypes ..., ...)> : ::std::integral_constant<bool, true>
  {
  };
  template < typename _Res, typename ..._ArgTypes >
  struct  is_function<_Res (_ArgTypes ..., ...) &> : ::std::integral_constant<bool, true>
  {
  };
  template < typename _Res, typename ..._ArgTypes >
  struct  is_function<_Res (_ArgTypes ..., ...) &&> : ::std::integral_constant<bool, true>
  {
  };
  template < typename _Res, typename ..._ArgTypes >
  struct  is_function<_Res (_ArgTypes ...) const > : ::std::integral_constant<bool, true>
  {
  };
  template < typename _Res, typename ..._ArgTypes >
  struct  is_function<_Res (_ArgTypes ...) const  &> : ::std::integral_constant<bool, true>
  {
  };
  template < typename _Res, typename ..._ArgTypes >
  struct  is_function<_Res (_ArgTypes ...) const  &&> : ::std::integral_constant<bool, true>
  {
  };
  template < typename _Res, typename ..._ArgTypes >
  struct  is_function<_Res (_ArgTypes ..., ...) const > : ::std::integral_constant<bool, true>
  {
  };
  template < typename _Res, typename ..._ArgTypes >
  struct  is_function<_Res (_ArgTypes ..., ...) const  &> : ::std::integral_constant<bool, true>
  {
  };
  template < typename _Res, typename ..._ArgTypes >
  struct  is_function<_Res (_ArgTypes ..., ...) const  &&> : ::std::integral_constant<bool, true>
  {
  };
  template < typename _Res, typename ..._ArgTypes >
  struct  is_function<_Res (_ArgTypes ...) volatile > : ::std::integral_constant<bool, true>
  {
  };
  template < typename _Res, typename ..._ArgTypes >
  struct  is_function<_Res (_ArgTypes ...) volatile  &> : ::std::integral_constant<bool, true>
  {
  };
  template < typename _Res, typename ..._ArgTypes >
  struct  is_function<_Res (_ArgTypes ...) volatile  &&> : ::std::integral_constant<bool, true>
  {
  };
  template < typename _Res, typename ..._ArgTypes >
  struct  is_function<_Res (_ArgTypes ..., ...) volatile > : ::std::integral_constant<bool, true>
  {
  };
  template < typename _Res, typename ..._ArgTypes >
  struct  is_function<_Res (_ArgTypes ..., ...) volatile  &> : ::std::integral_constant<bool, true>
  {
  };
  template < typename _Res, typename ..._ArgTypes >
  struct  is_function<_Res (_ArgTypes ..., ...) volatile  &&> : ::std::integral_constant<bool, true>
  {
  };
  template < typename _Res, typename ..._ArgTypes >
  struct  is_function<_Res (_ArgTypes ...) const volatile > : ::std::integral_constant<bool, true>
  {
  };
  template < typename _Res, typename ..._ArgTypes >
  struct  is_function<_Res (_ArgTypes ...) const volatile  &> : ::std::integral_constant<bool, true>
  {
  };
  template < typename _Res, typename ..._ArgTypes >
  struct  is_function<_Res (_ArgTypes ...) const volatile  &&> : ::std::integral_constant<bool, true>
  {
  };
  template < typename _Res, typename ..._ArgTypes >
  struct  is_function<_Res (_ArgTypes ..., ...) const volatile > : ::std::integral_constant<bool, true>
  {
  };
  template < typename _Res, typename ..._ArgTypes >
  struct  is_function<_Res (_ArgTypes ..., ...) const volatile  &> : ::std::integral_constant<bool, true>
  {
  };
  template < typename _Res, typename ..._ArgTypes >
  struct  is_function<_Res (_ArgTypes ..., ...) const volatile  &&> : ::std::integral_constant<bool, true>
  {
  };
  template < typename __type_tpl__param_1_0__ >
  struct  __is_null_pointer_helper : ::std::integral_constant<bool, false>
  {
  };
  template <>
  struct  __is_null_pointer_helper<decltype(nullptr)> : ::std::integral_constant<bool, true>
  {
  };
  template < typename _Tp >
  struct  is_null_pointer : ::std::__is_null_pointer_helper<typename ::std::remove_cv<_Tp>::type>::type
  {
  };
  template < typename _Tp >
  struct  __is_nullptr_t : ::std::is_null_pointer<_Tp>
  {
  };
  template < typename _Tp >
  struct  is_reference : ::std::__or_< ::std::is_lvalue_reference<_Tp>, ::std::is_rvalue_reference<_Tp> >::type
  {
  };
  template < typename _Tp >
  struct  is_arithmetic : ::std::__or_< ::std::is_integral<_Tp>, ::std::is_floating_point<_Tp> >::type
  {
  };
  template < typename _Tp >
  struct  is_fundamental : ::std::__or_< ::std::is_arithmetic<_Tp>, ::std::is_void<_Tp>, ::std::is_null_pointer<_Tp> >::type
  {
  };
  template < typename _Tp >
  struct  is_object : ::std::__not_< ::std::__or_< ::std::is_function<_Tp>, ::std::is_reference<_Tp>, ::std::is_void<_Tp> > >::type
  {
  };
  template < typename __type_tpl__param_1_0__ >
  struct is_member_pointer;
  template < typename _Tp >
  struct  is_scalar : ::std::__or_< ::std::is_arithmetic<_Tp>, ::std::is_enum<_Tp>, ::std::is_pointer<_Tp>, ::std::is_member_pointer<_Tp>, ::std::is_null_pointer<_Tp> >::type
  {
  };
  template < typename _Tp >
  struct  is_compound : ::std::integral_constant<bool, !is_fundamental<_Tp>::value>
  {
  };
  template < typename _Tp >
  struct  __is_member_pointer_helper : ::std::integral_constant<bool, false>
  {
  };
  template < typename _Tp, typename _Cp >
  struct  __is_member_pointer_helper<_Tp _Cp::*> : ::std::integral_constant<bool, true>
  {
  };
  template < typename _Tp >
  struct  is_member_pointer : ::std::__is_member_pointer_helper<typename ::std::remove_cv<_Tp>::type>::type
  {
  };
  template < typename _Tp >
  struct  __is_referenceable : ::std::__or_< ::std::is_object<_Tp>, ::std::is_reference<_Tp> >::type
  {
  };
  template < typename _Res, typename ..._Args >
  struct  __is_referenceable<_Res (_Args ...)> : ::std::integral_constant<bool, true>
  {
  };
  template < typename _Res, typename ..._Args >
  struct  __is_referenceable<_Res (_Args ..., ...)> : ::std::integral_constant<bool, true>
  {
  };
  template < typename __type_tpl__param_1_0__ >
  struct  is_const : ::std::integral_constant<bool, false>
  {
  };
  template < typename _Tp >
  struct  is_const<const _Tp> : ::std::integral_constant<bool, true>
  {
  };
  template < typename __type_tpl__param_1_0__ >
  struct  is_volatile : ::std::integral_constant<bool, false>
  {
  };
  template < typename _Tp >
  struct  is_volatile<volatile _Tp> : ::std::integral_constant<bool, true>
  {
  };
  template < typename _Tp >
  struct  is_trivial : ::std::integral_constant<bool, __is_trivial(_Tp)>
  {
  };
  template < typename _Tp >
  struct  is_trivially_copyable : ::std::integral_constant<bool, __is_trivially_copyable(_Tp)>
  {
  };
  template < typename _Tp >
  struct  is_standard_layout : ::std::integral_constant<bool, __is_standard_layout(_Tp)>
  {
  };
  template < typename _Tp >
  struct  is_pod : ::std::integral_constant<bool, __is_pod(_Tp)>
  {
  };
  template < typename _Tp >
  struct  is_literal_type : ::std::integral_constant<bool, __is_literal_type(_Tp)>
  {
  };
  template < typename _Tp >
  struct  is_empty : ::std::integral_constant<bool, __is_empty(_Tp)>
  {
  };
  template < typename _Tp >
  struct  is_polymorphic : ::std::integral_constant<bool, __is_polymorphic(_Tp)>
  {
  };
  template < typename _Tp >
  struct  is_abstract : ::std::integral_constant<bool, __is_abstract(_Tp)>
  {
  };
  template < typename _Tp, bool __nontype_tpl_param_1_1__ = is_arithmetic<_Tp>::value >
  struct  __is_signed_helper : ::std::integral_constant<bool, false>
  {
  };
  template < typename _Tp >
  struct  __is_signed_helper<_Tp, true> : ::std::integral_constant<bool, _Tp( -1) < _Tp(0)>
  {
  };
  template < typename _Tp >
  struct  is_signed : ::std::__is_signed_helper<_Tp>::type
  {
  };
  template < typename _Tp >
  struct  is_unsigned : ::std::__and_< ::std::is_arithmetic<_Tp>, ::std::__not_< ::std::is_signed<_Tp> > >
  {
  };
  template < typename __type_tpl__param_1_0__ >
  struct add_rvalue_reference;
  template < typename _Tp >
  inline typename ::std::add_rvalue_reference<_Tp>::type declval() noexcept;
  template < typename __type_tpl__param_1_0__, unsigned int __nontype_tpl_param_1_1__ = 0 >
  struct extent;
  template < typename __type_tpl__param_1_0__ >
  struct remove_all_extents;
  template < typename _Tp >
  struct  __is_array_known_bounds : ::std::integral_constant<bool, (extent<_Tp>::value > 0)>
  {
  };
  template < typename _Tp >
  struct  __is_array_unknown_bounds : ::std::__and_< ::std::is_array<_Tp>, ::std::__not_< ::std::extent<_Tp> > >
  {
  };
  struct  __do_is_destructible_impl
  {
      template < typename _Tp, typename __type_tpl__param_1_1__ = decltype(declval<_Tp &>().~_Tp()) >
      static ::std::true_type __test(int);
      template < typename __type_tpl__param_1_0__ >
      static ::std::false_type __test(...);
  };
  template < typename _Tp >
  struct  __is_destructible_impl : ::std::__do_is_destructible_impl
  {
      typedef decltype(__test<_Tp>(0)) type;
  };
  template < typename _Tp, bool __nontype_tpl_param_1_1__ = __or_< ::std::is_void<_Tp>, ::std::__is_array_unknown_bounds<_Tp>, ::std::is_function<_Tp> >::value, bool __nontype_tpl_param_1_2__ = __or_< ::std::is_reference<_Tp>, ::std::is_scalar<_Tp> >::value >
  struct __is_destructible_safe;
  template < typename _Tp >
  struct  __is_destructible_safe<_Tp, false, false> : ::std::__is_destructible_impl<typename ::std::remove_all_extents<_Tp>::type>::type
  {
  };
  template < typename _Tp >
  struct  __is_destructible_safe<_Tp, true, false> : ::std::integral_constant<bool, false>
  {
  };
  template < typename _Tp >
  struct  __is_destructible_safe<_Tp, false, true> : ::std::integral_constant<bool, true>
  {
  };
  template < typename _Tp >
  struct  is_destructible : ::std::__is_destructible_safe<_Tp>::type
  {
  };
  struct  __do_is_nt_destructible_impl
  {
      template < typename _Tp >
      static ::std::integral_constant<bool, noexcept(declval<_Tp &>().~_Tp())> __test(int);
      template < typename __type_tpl__param_1_0__ >
      static ::std::false_type __test(...);
  };
  template < typename _Tp >
  struct  __is_nt_destructible_impl : ::std::__do_is_nt_destructible_impl
  {
      typedef decltype(__test<_Tp>(0)) type;
  };
  template < typename _Tp, bool __nontype_tpl_param_1_1__ = __or_< ::std::is_void<_Tp>, ::std::__is_array_unknown_bounds<_Tp>, ::std::is_function<_Tp> >::value, bool __nontype_tpl_param_1_2__ = __or_< ::std::is_reference<_Tp>, ::std::is_scalar<_Tp> >::value >
  struct __is_nt_destructible_safe;
  template < typename _Tp >
  struct  __is_nt_destructible_safe<_Tp, false, false> : ::std::__is_nt_destructible_impl<typename ::std::remove_all_extents<_Tp>::type>::type
  {
  };
  template < typename _Tp >
  struct  __is_nt_destructible_safe<_Tp, true, false> : ::std::integral_constant<bool, false>
  {
  };
  template < typename _Tp >
  struct  __is_nt_destructible_safe<_Tp, false, true> : ::std::integral_constant<bool, true>
  {
  };
  template < typename _Tp >
  struct  is_nothrow_destructible : ::std::__is_nt_destructible_safe<_Tp>::type
  {
  };
  struct  __do_is_default_constructible_impl
  {
      template < typename _Tp, typename __type_tpl__param_1_1__ = decltype(_Tp()) >
      static ::std::true_type __test(int);
      template < typename __type_tpl__param_1_0__ >
      static ::std::false_type __test(...);
  };
  template < typename _Tp >
  struct  __is_default_constructible_impl : ::std::__do_is_default_constructible_impl
  {
      typedef decltype(__test<_Tp>(0)) type;
  };
  template < typename _Tp >
  struct  __is_default_constructible_atom : ::std::__and_< ::std::__not_< ::std::is_void<_Tp> >, ::std::__is_default_constructible_impl<_Tp> >
  {
  };
  template < typename _Tp, bool __nontype_tpl_param_1_1__ = is_array<_Tp>::value >
  struct __is_default_constructible_safe;
  template < typename _Tp >
  struct  __is_default_constructible_safe<_Tp, true> : ::std::__and_< ::std::__is_array_known_bounds<_Tp>, ::std::__is_default_constructible_atom<typename ::std::remove_all_extents<_Tp>::type> >
  {
  };
  template < typename _Tp >
  struct  __is_default_constructible_safe<_Tp, false> : ::std::__is_default_constructible_atom<_Tp>::type
  {
  };
  template < typename _Tp >
  struct  is_default_constructible : ::std::__is_default_constructible_safe<_Tp>::type
  {
  };
  struct  __do_is_static_castable_impl
  {
      template < typename _From, typename _To, typename __type_tpl__param_1_2__ = decltype(static_cast<_To>(declval<_From>())) >
      static ::std::true_type __test(int);
      template < typename __type_tpl__param_1_0__, typename __type_tpl__param_1_1__ >
      static ::std::false_type __test(...);
  };
  template < typename _From, typename _To >
  struct  __is_static_castable_impl : ::std::__do_is_static_castable_impl
  {
      typedef decltype(__test<_From, _To>(0)) type;
  };
  template < typename _From, typename _To >
  struct  __is_static_castable_safe : ::std::__is_static_castable_impl<_From, _To>::type
  {
  };
  template < typename _From, typename _To >
  struct  __is_static_castable : ::std::integral_constant<bool, __is_static_castable_safe<_From, _To>::value>
  {
  };
  struct  __do_is_direct_constructible_impl
  {
      template < typename _Tp, typename _Arg, typename __type_tpl__param_1_2__ = decltype(::new _Tp(declval<_Arg>())) >
      static ::std::true_type __test(int);
      template < typename __type_tpl__param_1_0__, typename __type_tpl__param_1_1__ >
      static ::std::false_type __test(...);
  };
  template < typename _Tp, typename _Arg >
  struct  __is_direct_constructible_impl : ::std::__do_is_direct_constructible_impl
  {
      typedef decltype(__test<_Tp, _Arg>(0)) type;
  };
  template < typename _Tp, typename _Arg >
  struct  __is_direct_constructible_new_safe : ::std::__and_< ::std::is_destructible<_Tp>, ::std::__is_direct_constructible_impl<_Tp, _Arg> >
  {
  };
  template < typename __type_tpl__param_1_0__, typename __type_tpl__param_1_1__ >
  struct is_same;
  template < typename __type_tpl__param_1_0__, typename __type_tpl__param_1_1__ >
  struct is_base_of;
  template < typename __type_tpl__param_1_0__ >
  struct remove_reference;
  template < typename _From, typename _To, bool __nontype_tpl_param_1_2__ = __not_< ::std::__or_< ::std::is_void<_From>, ::std::is_function<_From> > >::value >
  struct __is_base_to_derived_ref;
  template < typename _Tp, typename ..._Args >
  struct is_constructible;
  template < typename _From, typename _To >
  struct  __is_base_to_derived_ref<_From, _To, true>
  {
      typedef typename ::std::remove_cv<typename ::std::remove_reference<_From>::type>::type __src_t;
      typedef typename ::std::remove_cv<typename ::std::remove_reference<_To>::type>::type __dst_t;
      typedef ::std::__and_< ::std::__not_< ::std::is_same<typename ::std::__is_base_to_derived_ref<_From, _To, true>::__src_t, typename ::std::__is_base_to_derived_ref<_From, _To, true>::__dst_t> >, ::std::is_base_of<typename ::std::__is_base_to_derived_ref<_From, _To, true>::__src_t, typename ::std::__is_base_to_derived_ref<_From, _To, true>::__dst_t>, ::std::__not_< ::std::is_constructible<typename ::std::__is_base_to_derived_ref<_From, _To, true>::__dst_t, _From> > > type;
      static constexpr const bool value = type::value;
  };
  template < typename _From, typename _To >
  struct  __is_base_to_derived_ref<_From, _To, false> : ::std::integral_constant<bool, false>
  {
  };
  template < typename _From, typename _To, bool __nontype_tpl_param_1_2__ = __and_< ::std::is_lvalue_reference<_From>, ::std::is_rvalue_reference<_To> >::value >
  struct __is_lvalue_to_rvalue_ref;
  template < typename _From, typename _To >
  struct  __is_lvalue_to_rvalue_ref<_From, _To, true>
  {
      typedef typename ::std::remove_cv<typename ::std::remove_reference<_From>::type>::type __src_t;
      typedef typename ::std::remove_cv<typename ::std::remove_reference<_To>::type>::type __dst_t;
      typedef ::std::__and_< ::std::__not_< ::std::is_function<typename ::std::__is_lvalue_to_rvalue_ref<_From, _To, true>::__src_t> >, ::std::__or_< ::std::is_same<typename ::std::__is_lvalue_to_rvalue_ref<_From, _To, true>::__src_t, typename ::std::__is_lvalue_to_rvalue_ref<_From, _To, true>::__dst_t>, ::std::is_base_of<typename ::std::__is_lvalue_to_rvalue_ref<_From, _To, true>::__dst_t, typename ::std::__is_lvalue_to_rvalue_ref<_From, _To, true>::__src_t> > > type;
      static constexpr const bool value = type::value;
  };
  template < typename _From, typename _To >
  struct  __is_lvalue_to_rvalue_ref<_From, _To, false> : ::std::integral_constant<bool, false>
  {
  };
  template < typename _Tp, typename _Arg >
  struct  __is_direct_constructible_ref_cast : ::std::__and_< ::std::__is_static_castable<_Arg, _Tp>, ::std::__not_< ::std::__or_< ::std::__is_base_to_derived_ref<_Arg, _Tp>, ::std::__is_lvalue_to_rvalue_ref<_Arg, _Tp> > > >
  {
  };
  template < typename _Tp, typename _Arg >
  struct  __is_direct_constructible_new : ::std::conditional<is_reference<_Tp>::value, ::std::__is_direct_constructible_ref_cast<_Tp, _Arg>, ::std::__is_direct_constructible_new_safe<_Tp, _Arg> >::type
  {
  };
  template < typename _Tp, typename _Arg >
  struct  __is_direct_constructible : ::std::__is_direct_constructible_new<_Tp, _Arg>::type
  {
  };
  struct  __do_is_nary_constructible_impl
  {
      template < typename _Tp, typename ..._Args, typename __type_tpl__param_1_2__ = decltype(_Tp(declval<_Args>() ...)) >
      static ::std::true_type __test(int);
      template < typename __type_tpl__param_1_0__, typename ...__type_tpl__param_1_1__ >
      static ::std::false_type __test(...);
  };
  template < typename _Tp, typename ..._Args >
  struct  __is_nary_constructible_impl : ::std::__do_is_nary_constructible_impl
  {
      typedef decltype(__test<_Tp, _Args ...>(0)) type;
  };
  template < typename _Tp, typename ..._Args >
  struct  __is_nary_constructible : ::std::__is_nary_constructible_impl<_Tp, _Args ...>::type
  {
      static_assert((sizeof...(_Args)) > 1, "Only useful for > 1 arguments");
  };
  template < typename _Tp, typename ..._Args >
  struct  __is_constructible_impl : ::std::__is_nary_constructible<_Tp, _Args ...>
  {
  };
  template < typename _Tp, typename _Arg >
  struct  __is_constructible_impl<_Tp, _Arg> : ::std::__is_direct_constructible<_Tp, _Arg>
  {
  };
  template < typename _Tp >
  struct  __is_constructible_impl<_Tp> : ::std::is_default_constructible<_Tp>
  {
  };
  template < typename _Tp, typename ..._Args >
  struct  is_constructible : ::std::__is_constructible_impl<_Tp, _Args ...>::type
  {
  };
  template < typename _Tp, bool __nontype_tpl_param_1_1__ = __is_referenceable<_Tp>::value >
  struct __is_copy_constructible_impl;
  template < typename _Tp >
  struct  __is_copy_constructible_impl<_Tp, false> : ::std::integral_constant<bool, false>
  {
  };
  template < typename _Tp >
  struct  __is_copy_constructible_impl<_Tp, true> : ::std::is_constructible<_Tp, const _Tp &>
  {
  };
  template < typename _Tp >
  struct  is_copy_constructible : ::std::__is_copy_constructible_impl<_Tp>
  {
  };
  template < typename _Tp, bool __nontype_tpl_param_1_1__ = __is_referenceable<_Tp>::value >
  struct __is_move_constructible_impl;
  template < typename _Tp >
  struct  __is_move_constructible_impl<_Tp, false> : ::std::integral_constant<bool, false>
  {
  };
  template < typename _Tp >
  struct  __is_move_constructible_impl<_Tp, true> : ::std::is_constructible<_Tp, _Tp &&>
  {
  };
  template < typename _Tp >
  struct  is_move_constructible : ::std::__is_move_constructible_impl<_Tp>
  {
  };
  template < typename _Tp >
  struct  __is_nt_default_constructible_atom : ::std::integral_constant<bool, noexcept(_Tp())>
  {
  };
  template < typename _Tp, bool __nontype_tpl_param_1_1__ = is_array<_Tp>::value >
  struct __is_nt_default_constructible_impl;
  template < typename _Tp >
  struct  __is_nt_default_constructible_impl<_Tp, true> : ::std::__and_< ::std::__is_array_known_bounds<_Tp>, ::std::__is_nt_default_constructible_atom<typename ::std::remove_all_extents<_Tp>::type> >
  {
  };
  template < typename _Tp >
  struct  __is_nt_default_constructible_impl<_Tp, false> : ::std::__is_nt_default_constructible_atom<_Tp>
  {
  };
  template < typename _Tp >
  struct  is_nothrow_default_constructible : ::std::__and_< ::std::is_default_constructible<_Tp>, ::std::__is_nt_default_constructible_impl<_Tp> >
  {
  };
  template < typename _Tp, typename ..._Args >
  struct  __is_nt_constructible_impl : ::std::integral_constant<bool, noexcept(_Tp(declval<_Args>() ...))>
  {
  };
  template < typename _Tp, typename _Arg >
  struct  __is_nt_constructible_impl<_Tp, _Arg> : ::std::integral_constant<bool, noexcept(static_cast<_Tp>(declval<_Arg>()))>
  {
  };
  template < typename _Tp >
  struct  __is_nt_constructible_impl<_Tp> : ::std::is_nothrow_default_constructible<_Tp>
  {
  };
  template < typename _Tp, typename ..._Args >
  struct  is_nothrow_constructible : ::std::__and_< ::std::is_constructible<_Tp, _Args ...>, ::std::__is_nt_constructible_impl<_Tp, _Args ...> >
  {
  };
  template < typename _Tp, bool __nontype_tpl_param_1_1__ = __is_referenceable<_Tp>::value >
  struct __is_nothrow_copy_constructible_impl;
  template < typename _Tp >
  struct  __is_nothrow_copy_constructible_impl<_Tp, false> : ::std::integral_constant<bool, false>
  {
  };
  template < typename _Tp >
  struct  __is_nothrow_copy_constructible_impl<_Tp, true> : ::std::is_nothrow_constructible<_Tp, const _Tp &>
  {
  };
  template < typename _Tp >
  struct  is_nothrow_copy_constructible : ::std::__is_nothrow_copy_constructible_impl<_Tp>
  {
  };
  template < typename _Tp, bool __nontype_tpl_param_1_1__ = __is_referenceable<_Tp>::value >
  struct __is_nothrow_move_constructible_impl;
  template < typename _Tp >
  struct  __is_nothrow_move_constructible_impl<_Tp, false> : ::std::integral_constant<bool, false>
  {
  };
  template < typename _Tp >
  struct  __is_nothrow_move_constructible_impl<_Tp, true> : ::std::is_nothrow_constructible<_Tp, _Tp &&>
  {
  };
  template < typename _Tp >
  struct  is_nothrow_move_constructible : ::std::__is_nothrow_move_constructible_impl<_Tp>
  {
  };
  template < typename _Tp, typename _Up >
  class  __is_assignable_helper
  {
      template < typename _Tp1, typename _Up1, typename __type_tpl__param_2_2__ = decltype(declval<_Tp1>() = declval<_Up1>()) >
      static ::std::true_type __test(int);
      template < typename __type_tpl__param_2_0__, typename __type_tpl__param_2_1__ >
      static ::std::false_type __test(...);
    public:
      typedef decltype(__test<_Tp, _Up>(0)) type;
  };
  template < typename _Tp, typename _Up >
  struct  is_assignable : ::std::__is_assignable_helper<_Tp, _Up>::type
  {
  };
  template < typename _Tp, bool __nontype_tpl_param_1_1__ = __is_referenceable<_Tp>::value >
  struct __is_copy_assignable_impl;
  template < typename _Tp >
  struct  __is_copy_assignable_impl<_Tp, false> : ::std::integral_constant<bool, false>
  {
  };
  template < typename _Tp >
  struct  __is_copy_assignable_impl<_Tp, true> : ::std::is_assignable<_Tp &, const _Tp &>
  {
  };
  template < typename _Tp >
  struct  is_copy_assignable : ::std::__is_copy_assignable_impl<_Tp>
  {
  };
  template < typename _Tp, bool __nontype_tpl_param_1_1__ = __is_referenceable<_Tp>::value >
  struct __is_move_assignable_impl;
  template < typename _Tp >
  struct  __is_move_assignable_impl<_Tp, false> : ::std::integral_constant<bool, false>
  {
  };
  template < typename _Tp >
  struct  __is_move_assignable_impl<_Tp, true> : ::std::is_assignable<_Tp &, _Tp &&>
  {
  };
  template < typename _Tp >
  struct  is_move_assignable : ::std::__is_move_assignable_impl<_Tp>
  {
  };
  template < typename _Tp, typename _Up >
  struct  __is_nt_assignable_impl : ::std::integral_constant<bool, noexcept(declval<_Tp>() = declval<_Up>())>
  {
  };
  template < typename _Tp, typename _Up >
  struct  is_nothrow_assignable : ::std::__and_< ::std::is_assignable<_Tp, _Up>, ::std::__is_nt_assignable_impl<_Tp, _Up> >
  {
  };
  template < typename _Tp, bool __nontype_tpl_param_1_1__ = __is_referenceable<_Tp>::value >
  struct __is_nt_copy_assignable_impl;
  template < typename _Tp >
  struct  __is_nt_copy_assignable_impl<_Tp, false> : ::std::integral_constant<bool, false>
  {
  };
  template < typename _Tp >
  struct  __is_nt_copy_assignable_impl<_Tp, true> : ::std::is_nothrow_assignable<_Tp &, const _Tp &>
  {
  };
  template < typename _Tp >
  struct  is_nothrow_copy_assignable : ::std::__is_nt_copy_assignable_impl<_Tp>
  {
  };
  template < typename _Tp, bool __nontype_tpl_param_1_1__ = __is_referenceable<_Tp>::value >
  struct __is_nt_move_assignable_impl;
  template < typename _Tp >
  struct  __is_nt_move_assignable_impl<_Tp, false> : ::std::integral_constant<bool, false>
  {
  };
  template < typename _Tp >
  struct  __is_nt_move_assignable_impl<_Tp, true> : ::std::is_nothrow_assignable<_Tp &, _Tp &&>
  {
  };
  template < typename _Tp >
  struct  is_nothrow_move_assignable : ::std::__is_nt_move_assignable_impl<_Tp>
  {
  };
  template < typename _Tp, typename ..._Args >
  struct  is_trivially_constructible : ::std::__and_< ::std::is_constructible<_Tp, _Args ...>, ::std::integral_constant<bool, __is_trivially_constructible(_Tp, _Args ...)> >
  {
  };
  template < typename _Tp >
  struct  is_trivially_default_constructible : ::std::is_trivially_constructible<_Tp>::type
  {
  };
  struct  __do_is_implicitly_default_constructible_impl
  {
      template < typename _Tp >
      static void __helper(const _Tp &);
      template < typename _Tp >
      static ::std::true_type __test(const _Tp &, decltype(__helper<const _Tp &>({  })) *  = (0));
      static ::std::false_type __test(...);
  };
  template < typename _Tp >
  struct  __is_implicitly_default_constructible_impl : ::std::__do_is_implicitly_default_constructible_impl
  {
      typedef decltype(__test(declval<_Tp>())) type;
  };
  template < typename _Tp >
  struct  __is_implicitly_default_constructible_safe : ::std::__is_implicitly_default_constructible_impl<_Tp>::type
  {
  };
  template < typename _Tp >
  struct  __is_implicitly_default_constructible : ::std::__and_< ::std::is_default_constructible<_Tp>, ::std::__is_implicitly_default_constructible_safe<_Tp> >
  {
  };
  template < typename _Tp >
  struct  is_trivially_copy_constructible : ::std::__and_< ::std::is_copy_constructible<_Tp>, ::std::integral_constant<bool, __is_trivially_constructible(_Tp, const _Tp &)> >
  {
  };
  template < typename _Tp >
  struct  is_trivially_move_constructible : ::std::__and_< ::std::is_move_constructible<_Tp>, ::std::integral_constant<bool, __is_trivially_constructible(_Tp, _Tp &&)> >
  {
  };
  template < typename _Tp, typename _Up >
  struct  is_trivially_assignable : ::std::__and_< ::std::is_assignable<_Tp, _Up>, ::std::integral_constant<bool, __is_trivially_assignable(_Tp, _Up)> >
  {
  };
  template < typename _Tp >
  struct  is_trivially_copy_assignable : ::std::__and_< ::std::is_copy_assignable<_Tp>, ::std::integral_constant<bool, __is_trivially_assignable(_Tp &, const _Tp &)> >
  {
  };
  template < typename _Tp >
  struct  is_trivially_move_assignable : ::std::__and_< ::std::is_move_assignable<_Tp>, ::std::integral_constant<bool, __is_trivially_assignable(_Tp &, _Tp &&)> >
  {
  };
  template < typename _Tp >
  struct  is_trivially_destructible : ::std::__and_< ::std::is_destructible<_Tp>, ::std::integral_constant<bool, __has_trivial_destructor(_Tp)> >
  {
  };
  template < typename _Tp >
  struct __attribute__((__deprecated__))  has_trivial_default_constructor : ::std::integral_constant<bool, __has_trivial_constructor(_Tp)>
  {
  };
  template < typename _Tp >
  struct __attribute__((__deprecated__))  has_trivial_copy_constructor : ::std::integral_constant<bool, __has_trivial_copy(_Tp)>
  {
  };
  template < typename _Tp >
  struct __attribute__((__deprecated__))  has_trivial_copy_assign : ::std::integral_constant<bool, __has_trivial_assign(_Tp)>
  {
  };
  template < typename _Tp >
  struct  has_virtual_destructor : ::std::integral_constant<bool, __has_virtual_destructor(_Tp)>
  {
  };
  template < typename _Tp >
  struct  alignment_of : ::std::integral_constant<unsigned long int, alignof(_Tp)>
  {
  };
 /* Instantiation of class template '::std::integral_constant<unsigned long int, 0>' */ 
  template < typename __type_tpl__param_1_0__ >
  struct  rank : ::std::integral_constant<unsigned long int, 0>
  {
  };
  template < typename _Tp, ::std::size_t _Size >
  struct  rank<_Tp [_Size]> : ::std::integral_constant<unsigned long int, 1 + rank<_Tp>::value>
  {
  };
  template < typename _Tp >
  struct  rank<_Tp []> : ::std::integral_constant<unsigned long int, 1 + rank<_Tp>::value>
  {
  };
  template < typename __type_tpl__param_1_0__, unsigned int _Uint >
  struct  extent : ::std::integral_constant<unsigned long int, 0>
  {
  };
  template < typename _Tp, unsigned int _Uint, ::std::size_t _Size >
  struct  extent<_Tp [_Size], _Uint> : ::std::integral_constant<unsigned long int, _Uint == 0 ? _Size : extent<_Tp, _Uint - 1>::value>
  {
  };
  template < typename _Tp, unsigned int _Uint >
  struct  extent<_Tp [], _Uint> : ::std::integral_constant<unsigned long int, _Uint == 0 ? 0 : extent<_Tp, _Uint - 1>::value>
  {
  };
  template < typename __type_tpl__param_1_0__, typename __type_tpl__param_1_1__ >
  struct  is_same : ::std::integral_constant<bool, false>
  {
  };
  template < typename _Tp >
  struct  is_same<_Tp, _Tp> : ::std::integral_constant<bool, true>
  {
  };
  template < typename _Base, typename _Derived >
  struct  is_base_of : ::std::integral_constant<bool, __is_base_of(_Base, _Derived)>
  {
  };
  template < typename _From, typename _To, bool __nontype_tpl_param_1_2__ = __or_< ::std::is_void<_From>, ::std::is_function<_To>, ::std::is_array<_To> >::value >
  struct  __is_convertible_helper
  {
      typedef typename ::std::is_void<_To>::type type;
  };
  template < typename _From, typename _To >
  class  __is_convertible_helper<_From, _To, false>
  {
      template < typename _To1 >
      static void __test_aux(_To1);
      template < typename _From1, typename _To1, typename __type_tpl__param_2_2__ = decltype(__test_aux<_To1>(std::declval<_From1>())) >
      static ::std::true_type __test(int);
      template < typename __type_tpl__param_2_0__, typename __type_tpl__param_2_1__ >
      static ::std::false_type __test(...);
    public:
      typedef decltype(__test<_From, _To>(0)) type;
  };
  template < typename _From, typename _To >
  struct  is_convertible : ::std::__is_convertible_helper<_From, _To>::type
  {
  };
  template < typename _Tp >
  struct  remove_const
  {
      typedef _Tp type;
  };
  template < typename _Tp >
  struct  remove_const<const _Tp>
  {
      typedef _Tp type;
  };
  template < typename _Tp >
  struct  remove_volatile
  {
      typedef _Tp type;
  };
  template < typename _Tp >
  struct  remove_volatile<volatile _Tp>
  {
      typedef _Tp type;
  };
  template < typename _Tp >
  struct  remove_cv
  {
      typedef typename ::std::remove_const<typename ::std::remove_volatile<_Tp>::type>::type type;
  };
  template < typename _Tp >
  struct  add_const
  {
      typedef const _Tp type;
  };
  template < typename _Tp >
  struct  add_volatile
  {
      typedef volatile _Tp type;
  };
  template < typename _Tp >
  struct  add_cv
  {
      typedef typename ::std::add_const<typename ::std::add_volatile<_Tp>::type>::type type;
  };
  template < typename _Tp >
  struct  remove_reference
  {
      typedef _Tp type;
  };
  template < typename _Tp >
  struct  remove_reference<_Tp &>
  {
      typedef _Tp type;
  };
  template < typename _Tp >
  struct  remove_reference<_Tp &&>
  {
      typedef _Tp type;
  };
  template < typename _Tp, bool __nontype_tpl_param_1_1__ = __is_referenceable<_Tp>::value >
  struct  __add_lvalue_reference_helper
  {
      typedef _Tp type;
  };
  template < typename _Tp >
  struct  __add_lvalue_reference_helper<_Tp, true>
  {
      typedef _Tp &type;
  };
  template < typename _Tp >
  struct  add_lvalue_reference : ::std::__add_lvalue_reference_helper<_Tp>
  {
  };
  template < typename _Tp, bool __nontype_tpl_param_1_1__ = __is_referenceable<_Tp>::value >
  struct  __add_rvalue_reference_helper
  {
      typedef _Tp type;
  };
  template < typename _Tp >
  struct  __add_rvalue_reference_helper<_Tp, true>
  {
      typedef _Tp &&type;
  };
  template < typename _Tp >
  struct  add_rvalue_reference : ::std::__add_rvalue_reference_helper<_Tp>
  {
  };
  template < typename _Unqualified, bool _IsConst, bool _IsVol >
  struct __cv_selector;
  template < typename _Unqualified >
  struct  __cv_selector<_Unqualified, false, false>
  {
      typedef _Unqualified __type;
  };
  template < typename _Unqualified >
  struct  __cv_selector<_Unqualified, false, true>
  {
      typedef volatile _Unqualified __type;
  };
  template < typename _Unqualified >
  struct  __cv_selector<_Unqualified, true, false>
  {
      typedef const _Unqualified __type;
  };
  template < typename _Unqualified >
  struct  __cv_selector<_Unqualified, true, true>
  {
      typedef const volatile _Unqualified __type;
  };
  template < typename _Qualified, typename _Unqualified, bool _IsConst = is_const<_Qualified>::value, bool _IsVol = is_volatile<_Qualified>::value >
  class  __match_cv_qualifiers
  {
      typedef ::std::__cv_selector<_Unqualified, _IsConst, _IsVol> __match;
    public:
      typedef typename ::std::__cv_selector<_Unqualified, _IsConst, _IsVol>::__type __type;
  };
  template < typename _Tp >
  struct  __make_unsigned
  {
      typedef _Tp __type;
  };
  template <>
  struct  __make_unsigned<char>
  {
      typedef unsigned char __type;
  };
  template <>
  struct  __make_unsigned<signed char>
  {
      typedef unsigned char __type;
  };
  template <>
  struct  __make_unsigned<short int>
  {
      typedef unsigned short int __type;
  };
  template <>
  struct  __make_unsigned<int>
  {
      typedef unsigned int __type;
  };
  template <>
  struct  __make_unsigned<long int>
  {
      typedef unsigned long int __type;
  };
  template <>
  struct  __make_unsigned<long long int>
  {
      typedef unsigned long long int __type;
  };
  template <>
  struct  __make_unsigned<wchar_t> : ::std::__make_unsigned<int>
  {
  };
  template < typename _Tp, bool _IsInt = is_integral<_Tp>::value, bool _IsEnum = is_enum<_Tp>::value >
  class __make_unsigned_selector;
  template < typename _Tp >
  class  __make_unsigned_selector<_Tp, true, false>
  {
      typedef ::std::__make_unsigned<typename ::std::remove_cv<_Tp>::type> __unsignedt;
      typedef typename ::std::__make_unsigned<typename ::std::remove_cv<_Tp>::type>::__type __unsigned_type;
      typedef ::std::__match_cv_qualifiers<_Tp, typename ::std::__make_unsigned_selector<_Tp, true, false>::__unsigned_type> __cv_unsigned;
    public:
      typedef typename ::std::__match_cv_qualifiers<_Tp, typename ::std::__make_unsigned_selector<_Tp, true, false>::__unsigned_type>::__type __type;
  };
  template < typename _Tp >
  class  __make_unsigned_selector<_Tp, false, true>
  {
      typedef unsigned char __smallest;
      static const bool __b0 = sizeof(_Tp) <= sizeof(typename ::std::__make_unsigned_selector<_Tp, false, true>::__smallest);
      static const bool __b1 = sizeof(_Tp) <= sizeof(unsigned short int);
      static const bool __b2 = sizeof(_Tp) <= sizeof(unsigned int);
      static const bool __b3 = sizeof(_Tp) <= sizeof(unsigned long int);
      typedef ::std::conditional< ::std::__make_unsigned_selector<_Tp, false, true>::__b3, unsigned long int, unsigned long long int> __cond3;
      typedef typename ::std::conditional< ::std::__make_unsigned_selector<_Tp, false, true>::__b3, unsigned long int, unsigned long long int>::type __cond3_type;
      typedef ::std::conditional< ::std::__make_unsigned_selector<_Tp, false, true>::__b2, unsigned int, typename ::std::__make_unsigned_selector<_Tp, false, true>::__cond3_type> __cond2;
      typedef typename ::std::conditional< ::std::__make_unsigned_selector<_Tp, false, true>::__b2, unsigned int, typename ::std::__make_unsigned_selector<_Tp, false, true>::__cond3_type>::type __cond2_type;
      typedef ::std::conditional< ::std::__make_unsigned_selector<_Tp, false, true>::__b1, unsigned short int, typename ::std::__make_unsigned_selector<_Tp, false, true>::__cond2_type> __cond1;
      typedef typename ::std::conditional< ::std::__make_unsigned_selector<_Tp, false, true>::__b1, unsigned short int, typename ::std::__make_unsigned_selector<_Tp, false, true>::__cond2_type>::type __cond1_type;
      typedef typename ::std::conditional< ::std::__make_unsigned_selector<_Tp, false, true>::__b0, unsigned char, typename ::std::__make_unsigned_selector<_Tp, false, true>::__cond1_type>::type __unsigned_type;
      typedef ::std::__match_cv_qualifiers<_Tp, typename ::std::__make_unsigned_selector<_Tp, false, true>::__unsigned_type> __cv_unsigned;
    public:
      typedef typename ::std::__match_cv_qualifiers<_Tp, typename ::std::__make_unsigned_selector<_Tp, false, true>::__unsigned_type>::__type __type;
  };
  template < typename _Tp >
  struct  make_unsigned
  {
      typedef typename ::std::__make_unsigned_selector<_Tp>::__type type;
  };
  template <>
  struct make_unsigned<bool>;
  template < typename _Tp >
  struct  __make_signed
  {
      typedef _Tp __type;
  };
  template <>
  struct  __make_signed<char>
  {
      typedef signed char __type;
  };
  template <>
  struct  __make_signed<unsigned char>
  {
      typedef signed char __type;
  };
  template <>
  struct  __make_signed<unsigned short int>
  {
      typedef short int __type;
  };
  template <>
  struct  __make_signed<unsigned int>
  {
      typedef int __type;
  };
  template <>
  struct  __make_signed<unsigned long int>
  {
      typedef long int __type;
  };
  template <>
  struct  __make_signed<unsigned long long int>
  {
      typedef long long int __type;
  };
  template <>
  struct  __make_signed<char16_t> : ::std::__make_signed<unsigned short int>
  {
  };
  template <>
  struct  __make_signed<char32_t> : ::std::__make_signed<unsigned int>
  {
  };
  template < typename _Tp, bool _IsInt = is_integral<_Tp>::value, bool _IsEnum = is_enum<_Tp>::value >
  class __make_signed_selector;
  template < typename _Tp >
  class  __make_signed_selector<_Tp, true, false>
  {
      typedef ::std::__make_signed<typename ::std::remove_cv<_Tp>::type> __signedt;
      typedef typename ::std::__make_signed<typename ::std::remove_cv<_Tp>::type>::__type __signed_type;
      typedef ::std::__match_cv_qualifiers<_Tp, typename ::std::__make_signed_selector<_Tp, true, false>::__signed_type> __cv_signed;
    public:
      typedef typename ::std::__match_cv_qualifiers<_Tp, typename ::std::__make_signed_selector<_Tp, true, false>::__signed_type>::__type __type;
  };
  template < typename _Tp >
  class  __make_signed_selector<_Tp, false, true>
  {
      typedef typename ::std::__make_unsigned_selector<_Tp>::__type __unsigned_type;
    public:
      typedef typename ::std::__make_signed_selector<typename ::std::__make_signed_selector<_Tp, false, true>::__unsigned_type>::__type __type;
  };
  template < typename _Tp >
  struct  make_signed
  {
      typedef typename ::std::__make_signed_selector<_Tp>::__type type;
  };
  template <>
  struct make_signed<bool>;
  template < typename _Tp >
  struct  remove_extent
  {
      typedef _Tp type;
  };
  template < typename _Tp, ::std::size_t _Size >
  struct  remove_extent<_Tp [_Size]>
  {
      typedef _Tp type;
  };
  template < typename _Tp >
  struct  remove_extent<_Tp []>
  {
      typedef _Tp type;
  };
  template < typename _Tp >
  struct  remove_all_extents
  {
      typedef _Tp type;
  };
  template < typename _Tp, ::std::size_t _Size >
  struct  remove_all_extents<_Tp [_Size]>
  {
      typedef typename ::std::remove_all_extents<_Tp>::type type;
  };
  template < typename _Tp >
  struct  remove_all_extents<_Tp []>
  {
      typedef typename ::std::remove_all_extents<_Tp>::type type;
  };
  template < typename _Tp, typename __type_tpl__param_1_1__ >
  struct  __remove_pointer_helper
  {
      typedef _Tp type;
  };
  template < typename _Tp, typename _Up >
  struct  __remove_pointer_helper<_Tp, _Up *>
  {
      typedef _Up type;
  };
  template < typename _Tp >
  struct  remove_pointer : ::std::__remove_pointer_helper<_Tp, typename ::std::remove_cv<_Tp>::type>
  {
  };
  template < typename _Tp, bool __nontype_tpl_param_1_1__ = __or_< ::std::__is_referenceable<_Tp>, ::std::is_void<_Tp> >::value >
  struct  __add_pointer_helper
  {
      typedef _Tp type;
  };
  template < typename _Tp >
  struct  __add_pointer_helper<_Tp, true>
  {
      typedef typename ::std::remove_reference<_Tp>::type *type;
  };
  template < typename _Tp >
  struct  add_pointer : ::std::__add_pointer_helper<_Tp>
  {
  };
  template < ::std::size_t _Len >
  struct  __aligned_storage_msa
  {
      union  __type
      {
          unsigned char __data[_Len];
          struct __attribute__((__aligned__))  mcc_struct_anon_20
          {
          };
          typename ::std::__aligned_storage_msa<_Len>::__type::mcc_struct_anon_20 __align;
      };
  };
  template < ::std::size_t _Len, ::std::size_t _Align = alignof(typename ::std::__aligned_storage_msa<_Len>::__type) >
  struct  aligned_storage
  {
      union  type
      {
          unsigned char __data[_Len];
          struct __attribute__((aligned(/* ??? */_Align)))  mcc_struct_anon_21
          {
          };
          typename ::std::aligned_storage<_Len, _Align>::type::mcc_struct_anon_21 __align;
      };
  };
  template < typename ..._Types >
  struct  __strictest_alignment
  {
      static const ::std::size_t _S_alignment = 0;
      static const ::std::size_t _S_size = 0;
  };
  template < typename _Tp, typename ..._Types >
  struct  __strictest_alignment<_Tp, _Types ...>
  {
      static const ::std::size_t _S_alignment = (alignof(_Tp)) > __strictest_alignment<_Types ...>::_S_alignment ? alignof(_Tp) : __strictest_alignment<_Types ...>::_S_alignment;
      static const ::std::size_t _S_size = sizeof(_Tp) > __strictest_alignment<_Types ...>::_S_size ? sizeof(_Tp) : __strictest_alignment<_Types ...>::_S_size;
  };
  template < ::std::size_t _Len, typename ..._Types >
  struct  aligned_union
  {
    private:
      static_assert((sizeof...(_Types)) != 0, "At least one type is required");
      typedef ::std::__strictest_alignment<_Types ...> __strictest;
      static const ::std::size_t _S_len = _Len > __strictest::_S_size ? _Len : __strictest::_S_size;
    public:
      static const ::std::size_t alignment_value = __strictest::_S_alignment;
      typedef typename ::std::aligned_storage< ::std::aligned_union<_Len, _Types ...>::_S_len, ::std::aligned_union<_Len, _Types ...>::alignment_value>::type type;
  };
  template < ::std::size_t _Len, typename ..._Types >
  const ::std::size_t aligned_union<_Len, _Types ...>::alignment_value;
  template < typename _Up, bool _IsArray = is_array<_Up>::value, bool _IsFunction = is_function<_Up>::value >
  struct __decay_selector;
  template < typename _Up >
  struct  __decay_selector<_Up, false, false>
  {
      typedef typename ::std::remove_cv<_Up>::type __type;
  };
  template < typename _Up >
  struct  __decay_selector<_Up, true, false>
  {
      typedef typename ::std::remove_extent<_Up>::type *__type;
  };
  template < typename _Up >
  struct  __decay_selector<_Up, false, true>
  {
      typedef typename ::std::add_pointer<_Up>::type __type;
  };
  template < typename _Tp >
  class  decay
  {
      typedef typename ::std::remove_reference<_Tp>::type __remove_type;
    public:
      typedef typename ::std::__decay_selector<typename ::std::decay<_Tp>::__remove_type>::__type type;
  };
  template < typename _Tp >
  class reference_wrapper;
  template < typename _Tp >
  struct  __strip_reference_wrapper
  {
      typedef _Tp __type;
  };
  template < typename _Tp >
  struct  __strip_reference_wrapper< ::std::reference_wrapper<_Tp> >
  {
      typedef _Tp &__type;
  };
  template < typename _Tp >
  struct  __decay_and_strip
  {
      typedef typename ::std::__strip_reference_wrapper<typename ::std::decay<_Tp>::type>::__type __type;
  };
  template < bool __nontype_tpl_param_1_0__, typename _Tp = void >
  struct  enable_if
  {
  };
  template < typename _Tp >
  struct  enable_if<true, _Tp>
  {
      typedef _Tp type;
  };
  template < typename ..._Cond >
  using _Require = typename ::std::enable_if<__and_<_Cond ...>::value>::type;
  template < bool _Cond, typename _Iftrue, typename _Iffalse >
  struct  conditional
  {
      typedef _Iftrue type;
  };
  template < typename _Iftrue, typename _Iffalse >
  struct  conditional<false, _Iftrue, _Iffalse>
  {
      typedef _Iffalse type;
  };
  template < typename ..._Tp >
  struct common_type;
  struct  __do_common_type_impl
  {
      template < typename _Tp, typename _Up >
      static ::std::__success_type<typename ::std::decay<decltype(true ? std::declval<_Tp>() : std::declval<_Up>())>::type> _S_test(int);
      template < typename __type_tpl__param_1_0__, typename __type_tpl__param_1_1__ >
      static ::std::__failure_type _S_test(...);
  };
  template < typename _Tp, typename _Up >
  struct  __common_type_impl : private ::std::__do_common_type_impl
  {
      typedef decltype(_S_test<_Tp, _Up>(0)) type;
  };
  struct  __do_member_type_wrapper
  {
      template < typename _Tp >
      static ::std::__success_type<typename _Tp::type> _S_test(int);
      template < typename __type_tpl__param_1_0__ >
      static ::std::__failure_type _S_test(...);
  };
  template < typename _Tp >
  struct  __member_type_wrapper : private ::std::__do_member_type_wrapper
  {
      typedef decltype(_S_test<_Tp>(0)) type;
  };
  template < typename _CTp, typename ..._Args >
  struct  __expanded_common_type_wrapper
  {
      typedef ::std::common_type<typename _CTp::type, _Args ...> type;
  };
  template < typename ..._Args >
  struct  __expanded_common_type_wrapper< ::std::__failure_type, _Args ...>
  {
      typedef ::std::__failure_type type;
  };
  template < typename _Tp >
  struct  common_type<_Tp>
  {
      typedef typename ::std::decay<_Tp>::type type;
  };
  template < typename _Tp, typename _Up >
  struct  common_type<_Tp, _Up> : ::std::__common_type_impl<_Tp, _Up>::type
  {
  };
  template < typename _Tp, typename _Up, typename ..._Vp >
  struct  common_type<_Tp, _Up, _Vp ...> : ::std::__expanded_common_type_wrapper<typename ::std::__member_type_wrapper< ::std::common_type<_Tp, _Up> >::type, _Vp ...>::type
  {
  };
  template < typename _Tp >
  struct  underlying_type
  {
      typedef __underlying_type(_Tp) type;
  };
  template < typename _Tp >
  struct  __declval_protector
  {
      static const bool __stop = false;
      static typename ::std::add_rvalue_reference<_Tp>::type __delegate();
  };
  template < typename _Tp >
  inline typename ::std::add_rvalue_reference<_Tp>::type declval() noexcept
  {
    static_assert(__declval_protector<_Tp>::__stop, "declval() must not be used!");
    return __declval_protector<_Tp>::__delegate();
  }
  template < typename _Signature >
  class result_of;
  struct  __invoke_memfun_ref
  {
  };
  struct  __invoke_memfun_deref
  {
  };
  struct  __invoke_memobj_ref
  {
  };
  struct  __invoke_memobj_deref
  {
  };
  struct  __invoke_other
  {
  };
  template < typename _Tp, typename _Tag >
  struct  __result_of_success : ::std::__success_type<_Tp>
  {
      typedef _Tag __invoke_type;
  };
  struct  __result_of_memfun_ref_impl
  {
      template < typename _Fp, typename _Tp1, typename ..._Args >
      static ::std::__result_of_success<decltype((std::declval<_Tp1>().*std::declval<_Fp>())(std::declval<_Args>() ...)), ::std::__invoke_memfun_ref> _S_test(int);
      template < typename ...__type_tpl__param_1_0__ >
      static ::std::__failure_type _S_test(...);
  };
  template < typename _MemPtr, typename _Arg, typename ..._Args >
  struct  __result_of_memfun_ref : private ::std::__result_of_memfun_ref_impl
  {
      typedef decltype(_S_test<_MemPtr, _Arg, _Args ...>(0)) type;
  };
  struct  __result_of_memfun_deref_impl
  {
      template < typename _Fp, typename _Tp1, typename ..._Args >
      static ::std::__result_of_success<decltype((*std::declval<_Tp1>().*std::declval<_Fp>())(std::declval<_Args>() ...)), ::std::__invoke_memfun_deref> _S_test(int);
      template < typename ...__type_tpl__param_1_0__ >
      static ::std::__failure_type _S_test(...);
  };
  template < typename _MemPtr, typename _Arg, typename ..._Args >
  struct  __result_of_memfun_deref : private ::std::__result_of_memfun_deref_impl
  {
      typedef decltype(_S_test<_MemPtr, _Arg, _Args ...>(0)) type;
  };
  struct  __result_of_memobj_ref_impl
  {
      template < typename _Fp, typename _Tp1 >
      static ::std::__result_of_success<decltype(std::declval<_Tp1>().*std::declval<_Fp>()), ::std::__invoke_memobj_ref> _S_test(int);
      template < typename __type_tpl__param_1_0__, typename __type_tpl__param_1_1__ >
      static ::std::__failure_type _S_test(...);
  };
  template < typename _MemPtr, typename _Arg >
  struct  __result_of_memobj_ref : private ::std::__result_of_memobj_ref_impl
  {
      typedef decltype(_S_test<_MemPtr, _Arg>(0)) type;
  };
  struct  __result_of_memobj_deref_impl
  {
      template < typename _Fp, typename _Tp1 >
      static ::std::__result_of_success<decltype(*std::declval<_Tp1>().*std::declval<_Fp>()), ::std::__invoke_memobj_deref> _S_test(int);
      template < typename __type_tpl__param_1_0__, typename __type_tpl__param_1_1__ >
      static ::std::__failure_type _S_test(...);
  };
  template < typename _MemPtr, typename _Arg >
  struct  __result_of_memobj_deref : private ::std::__result_of_memobj_deref_impl
  {
      typedef decltype(_S_test<_MemPtr, _Arg>(0)) type;
  };
  template < typename _MemPtr, typename _Arg >
  struct __result_of_memobj;
  template < typename _Res, typename _Class, typename _Arg >
  struct  __result_of_memobj<_Res _Class::*, _Arg>
  {
      typedef typename ::std::remove_cv<typename ::std::remove_reference<_Arg>::type>::type _Argval;
      typedef _Res _Class::*_MemPtr;
      typedef typename ::std::conditional<__or_< ::std::is_same<typename ::std::__result_of_memobj<_Res _Class::*, _Arg>::_Argval, _Class>, ::std::is_base_of<_Class, typename ::std::__result_of_memobj<_Res _Class::*, _Arg>::_Argval> >::value, ::std::__result_of_memobj_ref<typename ::std::__result_of_memobj<_Res _Class::*, _Arg>::_MemPtr, _Arg>, ::std::__result_of_memobj_deref<typename ::std::__result_of_memobj<_Res _Class::*, _Arg>::_MemPtr, _Arg> >::type::type type;
  };
  template < typename _MemPtr, typename _Arg, typename ..._Args >
  struct __result_of_memfun;
  template < typename _Res, typename _Class, typename _Arg, typename ..._Args >
  struct  __result_of_memfun<_Res _Class::*, _Arg, _Args ...>
  {
      typedef typename ::std::remove_cv<typename ::std::remove_reference<_Arg>::type>::type _Argval;
      typedef _Res _Class::*_MemPtr;
      typedef typename ::std::conditional<__or_< ::std::is_same<typename ::std::__result_of_memfun<_Res _Class::*, _Arg, _Args ...>::_Argval, _Class>, ::std::is_base_of<_Class, typename ::std::__result_of_memfun<_Res _Class::*, _Arg, _Args ...>::_Argval> >::value, ::std::__result_of_memfun_ref<typename ::std::__result_of_memfun<_Res _Class::*, _Arg, _Args ...>::_MemPtr, _Arg, _Args ...>, ::std::__result_of_memfun_deref<typename ::std::__result_of_memfun<_Res _Class::*, _Arg, _Args ...>::_MemPtr, _Arg, _Args ...> >::type::type type;
  };
  template < typename _Res, typename _Class, typename _Arg >
  struct  __result_of_memobj<_Res _Class::*, ::std::reference_wrapper<_Arg> > : ::std::__result_of_memobj_ref<_Res _Class::*, _Arg &>
  {
  };
  template < typename _Res, typename _Class, typename _Arg >
  struct  __result_of_memobj<_Res _Class::*, ::std::reference_wrapper<_Arg> &> : ::std::__result_of_memobj_ref<_Res _Class::*, _Arg &>
  {
  };
  template < typename _Res, typename _Class, typename _Arg >
  struct  __result_of_memobj<_Res _Class::*, const ::std::reference_wrapper<_Arg> &> : ::std::__result_of_memobj_ref<_Res _Class::*, _Arg &>
  {
  };
  template < typename _Res, typename _Class, typename _Arg >
  struct  __result_of_memobj<_Res _Class::*, ::std::reference_wrapper<_Arg> &&> : ::std::__result_of_memobj_ref<_Res _Class::*, _Arg &>
  {
  };
  template < typename _Res, typename _Class, typename _Arg >
  struct  __result_of_memobj<_Res _Class::*, const ::std::reference_wrapper<_Arg> &&> : ::std::__result_of_memobj_ref<_Res _Class::*, _Arg &>
  {
  };
  template < typename _Res, typename _Class, typename _Arg, typename ..._Args >
  struct  __result_of_memfun<_Res _Class::*, ::std::reference_wrapper<_Arg>, _Args ...> : ::std::__result_of_memfun_ref<_Res _Class::*, _Arg &, _Args ...>
  {
  };
  template < typename _Res, typename _Class, typename _Arg, typename ..._Args >
  struct  __result_of_memfun<_Res _Class::*, ::std::reference_wrapper<_Arg> &, _Args ...> : ::std::__result_of_memfun_ref<_Res _Class::*, _Arg &, _Args ...>
  {
  };
  template < typename _Res, typename _Class, typename _Arg, typename ..._Args >
  struct  __result_of_memfun<_Res _Class::*, const ::std::reference_wrapper<_Arg> &, _Args ...> : ::std::__result_of_memfun_ref<_Res _Class::*, _Arg &, _Args ...>
  {
  };
  template < typename _Res, typename _Class, typename _Arg, typename ..._Args >
  struct  __result_of_memfun<_Res _Class::*, ::std::reference_wrapper<_Arg> &&, _Args ...> : ::std::__result_of_memfun_ref<_Res _Class::*, _Arg &, _Args ...>
  {
  };
  template < typename _Res, typename _Class, typename _Arg, typename ..._Args >
  struct  __result_of_memfun<_Res _Class::*, const ::std::reference_wrapper<_Arg> &&, _Args ...> : ::std::__result_of_memfun_ref<_Res _Class::*, _Arg &, _Args ...>
  {
  };
  template < bool __nontype_tpl_param_1_0__, bool __nontype_tpl_param_1_1__, typename _Functor, typename ..._ArgTypes >
  struct  __result_of_impl
  {
      typedef ::std::__failure_type type;
  };
  template < typename _MemPtr, typename _Arg >
  struct  __result_of_impl<true, false, _MemPtr, _Arg> : ::std::__result_of_memobj<typename ::std::decay<_MemPtr>::type, _Arg>
  {
  };
  template < typename _MemPtr, typename _Arg, typename ..._Args >
  struct  __result_of_impl<false, true, _MemPtr, _Arg, _Args ...> : ::std::__result_of_memfun<typename ::std::decay<_MemPtr>::type, _Arg, _Args ...>
  {
  };
  struct  __result_of_other_impl
  {
      template < typename _Fn, typename ..._Args >
      static ::std::__result_of_success<decltype(std::declval<_Fn>()(std::declval<_Args>() ...)), ::std::__invoke_other> _S_test(int)