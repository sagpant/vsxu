#ifndef VSX_LOG_A_H_
#define VSX_LOG_A_H_

// logging
extern int log_level;
extern vsx_string log_dir;
void log_a(vsx_string message, int level = 1);

#define LOG_A(mess) log_a(mess);
#define LOG2_A(mess, lvl) 
//log_a(mess, lvl);

  

#endif /*VSX_LOG_A_H_*/