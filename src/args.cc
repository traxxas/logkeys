/*
  Copyleft (ɔ) 2009 Kernc
               2015 wb@tuome.la 
  This program is free software. It comes with absolutely no warranty whatsoever.
  See COPYING for further information.
  
  Project homepage: https://github.com/traxxas/logkeys/
*/

#ifndef _ARGS_H_
#define _ARGS_H_

#include <cstring>

namespace logkeys {

struct arguments
{
  bool start;          // start keylogger, -s switch
  bool kill;           // stop keylogger, -k switch
  bool us_keymap;      // use default US keymap, -u switch
  std::string logfile;      // user-specified log filename, -o switch
  std::string keymap;       // user-specified keymap file, -m switch or --export-keymap
  std::string device;       // user-specified input event device, given with -d switch
  int flags;           // holds the following option flags
#define FLAG_EXPORT_KEYMAP    0x1  // export keymap obtained from dumpkeys, --export-keymap is used
#define FLAG_NO_FUNC_KEYS     0x2  // only log character keys (e.g. 'c', '2', etc.) and don't log function keys (e.g. <LShift>, etc.), --no-func-keys switch
#define FLAG_NO_TIMESTAMPS    0x4  // don't log timestamps, --no-timestamps switch
} args = {0};  // default all args to 0x0 or ""


void process_command_line_arguments(int argc, char **argv)
{
  int flags;
  
  struct option long_options[] = {
    {"start",     no_argument,       0, 's'},
    {"keymap",    required_argument, 0, 'm'},
    {"output",    required_argument, 0, 'o'},
    {"us-keymap", no_argument,       0, 'u'},
    {"kill",      no_argument,       0, 'k'},
    {"device",    required_argument, 0, 'd'},
    {"help",      no_argument,       0, '?'},
    {"export-keymap", required_argument, &flags, FLAG_EXPORT_KEYMAP},
    {"no-func-keys",  no_argument,       &flags, FLAG_NO_FUNC_KEYS},
    {"no-timestamps", no_argument,       &flags, FLAG_NO_TIMESTAMPS},
    {0}
  };
  
  char c;
  int option_index;
  
  while ((c = getopt_long(argc, argv, "sm:o:ukd:?", long_options, &option_index)) != -1)
  {
    switch (c) 
    {
      case 's': args.start = true;     break;
      case 'm': args.keymap = optarg;  break;
      case 'o': args.logfile = optarg; break;
      case 'u': args.us_keymap = true; break;
      case 'k': args.kill = true;      break;
      case 'd': args.device = optarg;  break;
      
      case  0 : 
        args.flags |= flags;
        switch (flags) 
        {
          case FLAG_EXPORT_KEYMAP: args.keymap = optarg; break;
        }
        break;
      
      case '?': usage(); exit(EXIT_SUCCESS);
      default : usage(); exit(EXIT_FAILURE);
    }
  } // while
  
  while(optind < argc)
    error(0, 0, "Non-option argument %s", argv[optind++]);
}

} // namespace logkeys
#endif  // _ARGS_H_
