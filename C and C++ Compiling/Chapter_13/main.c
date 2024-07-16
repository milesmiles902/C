#define _GNU_SOURCE
#include <link.h>
#include <stdio.h>
#include <dlfcn.h>
#include "sharedLib1Functions.h"
#include "sharedLib2Functions.h"

struct PFUNC{

};

static const char* segment_type_to_string(uint32_t type){
  switch(type){
    case PT_NULL:
      return "Unused";
      break;
    case PT_LOAD:
      return "Loadable Program Segment";
      break;
    case PT_DYNAMIC:
      return "Dynamic linking information";
      break;
    case PT_INTERP:
      return "Program interpreter";
      break;
    case PT_NOTE:
      return "Auxiliary information";
      break;
    case PT_SHLIB:
      return "Reserved";
      break;
    case PT_PHDR:
      return "Entry for header table itself";
      break;
    case PT_TLS:
      return "Thread-local storage segment";
      break;
      case PT_LOOS:
	return "Start of OS-specific";
	break;
      case PT_GNU_EH_FRAME: 
	return "GCC .eh_frame_hdr segment";
	break;
      case PT_GNU_STACK:
	return "Indicates stack executability";
	break;
      case PT_GNU_RELRO:
	return "Read-only after relocation";
	break;
      case PT_SUNWBSS:
	return "Sun Specific segment";
	break;
      case PT_SUNWSTACK:
	return "Sun Stack segment";
	break;
      default:
	return "???";
  }
}
static const char* flags_to_string(uint32_t flags){
  switch(flags){
    case 1:
      return "--x";
      break;
    case 2:
      return "-w-";
      break;
    case 3:
      return "-wx";
      break;
    case 4:
      return "r--";
      break;
    case 5:
      return "r-x";
      break;
    case 6:
      return "rw-";
      break;
    case 7:
      return "rwx";
      break;
    default:
      return "???";
      break;
    }
}

static int header_handler(struct dl_phdr_info* info, size_t size, void* data){
  int j;
  printf("name=%s (%d segments) address=%p\n",
  info->dlpi_name, info->dlpi_phnum, (void*)info->dlpi_addr);
  for (j = 0; j < info->dlpi_phnum; j++) {
    printf("\t\t header %2d: address=%10p\n", j,
    (void*) (info->dlpi_addr + info->dlpi_phdr[j].p_vaddr));
    printf("\t\t\t type=0x%X (%s),\n\t\t\t flags=0x%X (%s)\n",
    info->dlpi_phdr[j].p_type,
    segment_type_to_string(info->dlpi_phdr[j].p_type),
    info->dlpi_phdr[j].p_flags,
    flags_to_string(info->dlpi_phdr[j].p_flags));
  }
  printf("\n");
  return 0;
}

int main(int argc, char* argv[]){
  // function from statically aware loaded library
  sharedLib1Function(argc);

  void* pLibHandle = dlopen("libdemo2.so", RTLD_NOW);
  if(NULL == pLibHandle){
    printf("Failed loading libdemo2.so, error = %s\n", dlerror());
    return -1;
  }
  void (*pFunc)() = 0;
  pFunc = (void(*)())dlsym(pLibHandle, "sharedLib1Function");
  
  dl_iterate_phdr(header_handler, NULL);
  
  return 0;
}
