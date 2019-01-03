#include "stdafx.h"

mono_thread_attach do_mono_thread_attach;
mono_get_root_domain do_mono_get_root_domain;
mono_assembly_open do_mono_assembly_open;
mono_assembly_get_image do_mono_assembly_get_image;
mono_class_from_name do_mono_class_from_name;
mono_class_get_method_from_name do_mono_class_get_method_from_name;
mono_runtime_invoke do_mono_runtime_invoke;
mono_assembly_close do_mono_assembly_close;


void LoadMonoAssembly()
{

	HMODULE mono = GetModuleHandleA("mono.dll");
	do_mono_thread_attach = (mono_thread_attach)GetProcAddress(mono, "mono_thread_attach");
	do_mono_get_root_domain = (mono_get_root_domain)GetProcAddress(mono, "mono_get_root_domain");
	do_mono_assembly_open = (mono_assembly_open)GetProcAddress(mono, "mono_assembly_open");
	do_mono_assembly_get_image = (mono_assembly_get_image)GetProcAddress(mono, "mono_assembly_get_image");
	do_mono_class_from_name = (mono_class_from_name)GetProcAddress(mono, "mono_class_from_name");
	do_mono_class_get_method_from_name = (mono_class_get_method_from_name)GetProcAddress(mono, "mono_class_get_method_from_name");
	do_mono_runtime_invoke = (mono_runtime_invoke)GetProcAddress(mono, "mono_runtime_invoke");
	do_mono_assembly_close = (mono_assembly_close)GetProcAddress(mono, "mono_assembly_close");


	//change these 
	char hack_namespace[256] = { 0 };
	strcpy(hack_namespace, "MonoAssembly");

	char hack_class[256] = { 0 };
	strcpy(hack_class, "Poof");

	char hack_method[256] = { 0 };
	strcpy(hack_method, "DoLoad");


	//patch mono_assembly_invoke_load_hook to return on first instruction
	PVOID invoke_load_hook_addr = GetProcAddress(mono, "mono_assembly_invoke_load_hook");
	DWORD old_prot;
	VirtualProtect(invoke_load_hook_addr, 1, PAGE_EXECUTE_READWRITE, &old_prot);
	memcpy(invoke_load_hook_addr, (void*)"\xc3", 1);


	PVOID mono_root_domain = do_mono_get_root_domain();
	do_mono_thread_attach(mono_root_domain);


	PVOID mono_assembly = do_mono_assembly_open((char*)"C:\\Users\\Admin\\Desktop\\PoofMemes\\MonoAssembly\\MonoAssembly\\bin\\x86\\Release\\MonoAssembly.dll", NULL); //change to your mono dll
	PVOID mono_image = do_mono_assembly_get_image(mono_assembly);
	PVOID mono_class = do_mono_class_from_name(mono_image, hack_namespace, hack_class);
	PVOID mono_class_method = do_mono_class_get_method_from_name(mono_class, hack_method, 0);
	do_mono_runtime_invoke(mono_class_method, NULL, NULL, NULL); //everything set, load


	//restore mono_assembly_invoke_load_hook 
	memcpy(invoke_load_hook_addr, (void*)"\x48", 1);
	VirtualProtect(invoke_load_hook_addr, 1, old_prot, &old_prot);


}