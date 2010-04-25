#ifndef VSX_NO_CLIENT
#ifndef vsx_widget_base_controller_H
#define vsx_widget_base_controller_H

#define sizeunit 0.014f //the basic building block unit multiplier

const float ALMOST_ZERO=0.00001;

class vsx_widget_base_controller : public vsx_widget
{
  float r_time;
protected:

public:
  vsx_string command_suffix;
  vsx_widget* hint;

  int mouse_moves;
  double smx, smy; // coordinate where mouse has been clicked
  double mdx, mdy; // delta mouse move
  bool controlling, isolate;
  //float xd;
  vsx_vector parentpos;
  vsx_vector deltamove,remPointer,remWorld;
  float temp;
  std::map<vsx_string,vsx_string>* param_spec;
//----
  float snap(float newval);
  void set_value(float val,bool cap=true);

  // show the destination value visually?
  bool dest_value;

  vsx_string in_param_spec,target_param /*used if sending data to complex anchor*/;
  vsx_color bgcolor;
  float value, target_value, presentation_value, send_value;
  bool bSnap;
  float old_snap_value;
  bool capmin, capmax;
  float capminv, capmaxv;
  bool lcapmin, lcapmax;
  float lcapminv, lcapmaxv;
  float min, max;
  float smoothness;
  //float sizeunit;
  float darkshade,lightshade;
  bool drawconnection;
  bool owned;

  vsx_widget_base_controller();
  ~vsx_widget_base_controller();
  virtual void generate_menu();
  virtual void init();
  virtual void before_delete();
  virtual bool key_down(signed long key, bool alt, bool ctrl, bool shift);
  virtual void vsx_command_process_b(vsx_command_s *t);
  virtual void event_mouse_down(vsx_widget_distance distance,vsx_widget_coords coords,int button);
  virtual void event_mouse_double_click(vsx_widget_distance distance,vsx_widget_coords coords,int button);
  //virtual void event_mouse_down(vsx_widget_distance distance,vsx_widget_coords coords,int button);
  virtual void event_mouse_move(vsx_widget_distance distance,vsx_widget_coords coords);
  virtual void event_mouse_move_passive(vsx_widget_distance distance,vsx_widget_coords coords);
  virtual void event_mouse_up(vsx_widget_distance distance,vsx_widget_coords coords,int button);
  virtual void cap_value();
  virtual void get_value();
  virtual void smooth(float newval);
  virtual void get_in_param_spec(std::pair<vsx_string,vsx_string> parampair); //used in param retrieval for letting child classes deal with unothodox params
  virtual void send_to_server();

  void set_command_suffix(vsx_string new_val)
  {
  	command_suffix = new_val;
  }


  //virtual void init();
  virtual void i_draw();
};

//#############################''''''''''##################################
//############################  3D hint   #################################
//#############################..........##################################
class vsx_widget_3d_hint : public vsx_widget
{
double startTime, endTime;

public:
	float secdelay;
  vsx_widget_3d_hint();
  ~vsx_widget_3d_hint();
  void draw();
  void popup();
};

#endif
#endif

