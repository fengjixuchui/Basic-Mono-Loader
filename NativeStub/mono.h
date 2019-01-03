#pragma once


typedef void* (*mono_thread_attach)(PVOID domain);
typedef void* (*mono_get_root_domain)();
typedef void* (*mono_assembly_open)(PCHAR file, PVOID stat);
typedef void* (*mono_assembly_get_image)(PVOID assembly);
typedef void* (*mono_class_from_name)(PVOID image, PCHAR name_space, PCHAR name);
typedef void* (*mono_class_get_method_from_name)(PVOID klass, PCHAR name, DWORD param_count);
typedef void* (*mono_runtime_invoke)(PVOID method, PVOID instance, PVOID *params, PVOID exc);
typedef void* (*mono_assembly_close)(PVOID assembly);


extern "C" mono_thread_attach do_mono_thread_attach;
extern "C" mono_get_root_domain do_mono_get_root_domain;
extern "C" mono_assembly_open do_mono_assembly_open;
extern "C" mono_assembly_get_image do_mono_assembly_get_image;
extern "C" mono_class_from_name do_mono_class_from_name;
extern "C" mono_class_get_method_from_name do_mono_class_get_method_from_name;
extern "C" mono_runtime_invoke do_mono_runtime_invoke;
extern "C" mono_assembly_close do_mono_assembly_close;


extern "C" void LoadMonoAssembly();