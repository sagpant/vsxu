#ifndef VSX_COMP_H
#define VSX_COMP_H

#include "vsx_comp_abs.h"
/*includes required for including this file:
  
#include "vsx_command.h"
#include "vsx_module.h"
#include "vsx_math_3d.h"
#include "gfx_prod/vsx_param_abstraction.h"

*/
vsx_string process_module_param_spec(vsx_string& input);


class vsx_channel;

// create component
// create another component
// join another component with the first
// 

class vsx_comp : public vsx_comp_abs {
protected:
	enum frame_status_enum {
		initial_status,
		prepare_called,
		prepare_finished,
		run_finished,
		frame_failed
	};

	frame_status_enum frame_status;
  
  bool all_valid;
	bool output_finished;
	vsx_timer run_timer;
	
public:

  // is internal critical to vsx_engine?
  bool internal_critical;
  
  // parameter lists filled out by the module
	vsx_module_param_list* in_module_parameters;
  vsx_module_param_list* out_module_parameters;
  

  // our channels, one per parameter  
	std::vector <vsx_channel*> channels;
  
  // to know what components are pulling data from our module parameters
  std::map<vsx_module_param_abs*, std::list<vsx_channel*> > out_map_channels;
  
  void* vsxl_modifier;
	
  //---- g u i   s t u f f -------------------------------------------------------------------------
  // the relative position in the gui, just stored here
  vsx_vector position;
  // the size of the macro (only macros support scaling)
  float size;
  
  // if this is a macro, children will be stored here, this is not the way the engine
  // processes the components, it's just serves the purpouse to map components' relations
  // to each other.
  std::list<vsx_comp*> children; 

  //------------------------------------------------------------------------------------------------
  
	//void load_module(vsx_string module_class, vsx_string name);

	void load_module(module_dll_info* module_dll);
	void unload_module(module_dll_info* module_dll);
	void init_module();
	
	bool prepare(); // pre-parade!

	bool run(vsx_module_param_abs* param);
	bool stop();
	bool start();

	//bool connect(vsx_string param_name, vsx_comp_abs* other_component, vsx_string other_param_name, int* ord = 0);
//	bool connect_(vsx_comp_abs* other_component, vsx_string other_param_name, vsx_string param_name);

	bool disconnect(vsx_string param_name, vsx_comp_abs* other_component, vsx_string other_param_name);
	void disconnect(vsx_string param_name);
	
  bool engine_info(vsx_module_engine_info* engine);
  
  void re_init_in_params();
  void re_init_out_params();
  void init_channels();

	void reset_frame_status() {
    output_finished = false;
#ifdef VSXU_MODULE_TIMING    
    time_output = new_time_output;
    time_run = new_time_run;
    new_time_output = 0.0f;
    new_time_run = 0.0f;
#endif
    //if (frame_status != initial_status)
    //{
      /*if (dtime+vtime == 0)
      {
        local_engine_info.dtime = -local_engine_info.vtime+local_engine_info.dtime;
        local_engine_info.vtime = 0;
      } else  */
      //		local_engine_info.vtime += local_engine_info.dtime = time_multiplier*dtime;
/*      local_engine_info.real_vtime = e->real_vtime;
      local_engine_info.real_dtime = e->real_dtime;
      local_engine_info.vtime = e->vtime;
      local_engine_info.dtime = e->dtime;
      local_engine_info.state = e->state;
    }		*/
		frame_status = initial_status;
	}
  vsx_comp();
  ~vsx_comp();
};


#endif
