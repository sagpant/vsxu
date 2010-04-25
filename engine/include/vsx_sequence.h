#ifndef VSX_SEQUENCE_H
#define VSX_SEQUENCE_H

class vsx_sequence_item {
public:
  float value;
  float delay; // in seconds (float)
  int interpolation;
  vsx_vector handle1;
  vsx_vector handle2;

  vsx_string f2s(float in)
  {
    char string_res[256];
    sprintf(string_res,"%f",in);
    return vsx_string(string_res);
  }

  vsx_string get_value() {
    if (interpolation == 4) {
      return f2s(value)+":"+f2s(handle1.x)+","+f2s(handle1.y)+":"+f2s(handle2.x)+","+f2s(handle2.y);
    } else {
      return f2s(value);
    }
  }

  vsx_sequence_item():value(1),delay(1),interpolation(0) {}
};

class vsx_sequence {
	vsx_bezier_calc bez_calc;
public:
  vsx_avector<vsx_sequence_item> items;
  float i_time;
  float cur_val;
  float cur_delay;
  int cur_interpolation;
  long line_cur;

  float to_val;
  float line_time;
  int i_cur;

  long timestamp;
  vsx_sequence();
  vsx_sequence(const vsx_sequence& seq);
  vsx_sequence(vsx_sequence& seq);
  virtual ~vsx_sequence();

  vsx_sequence& operator=(vsx_sequence& ss);

  void reset();

  void set_time(float time) {
    execute(time-i_time);
  }

  float execute_absolute(float time) {
  	return execute(time-i_time);
  }

  float execute(float t_incr);
  #ifndef VSX_NO_SEQUENCE
  vsx_string get_string();
  void set_string(vsx_string str);
  #else
  virtual vsx_string get_string() = 0;
  virtual void set_string(vsx_string str) = 0;
  #endif
};

#endif
