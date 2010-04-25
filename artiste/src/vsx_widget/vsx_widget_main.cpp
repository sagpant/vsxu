#ifndef VSX_NO_CLIENT
#include <map>
#include <list>
#include <vector>
#include <math.h>
#include "vsx_gl_global.h"
#include "vsx_math_3d.h"
#include "vsx_texture_info.h"
#include "vsx_texture.h"
#include "vsx_command.h"
#include "vsx_font.h"
#include "vsx_param.h"
#include "vsx_module.h"

// local includes
#include "vsx_widget_base.h"
#include "window/vsx_widget_window.h"
#include "helpers/vsx_widget_object_inspector.h"
#include "helpers/vsx_widget_preview.h"
#include "helpers/vsx_widget_assistant.h"
#include "helpers/vsx_widget_console.h"
#include "lib/vsx_widget_lib.h"
//#include "vsx_widget_comp.h"
#include "server/vsx_widget_anchor.h"
#include "server/vsx_widget_server.h"
//#include "vsx_widget_module_chooser.h"
#include "dialogs/vsx_widget_window_statics.h"
#include "lib/vsx_widget_panel.h"
#include "lib/vsx_widget_base_edit.h"

#include "vsx_widget_main.h"

#ifndef _WIN32
#include "GL/glfw.h"
#endif

// VSX_WIDGET_DESKTOP **************************************************************************************************
// VSX_WIDGET_DESKTOP **************************************************************************************************
// VSX_WIDGET_DESKTOP **************************************************************************************************
// VSX_WIDGET_DESKTOP **************************************************************************************************
void vsx_widget_desktop::init() {

	//title = "vsx ultra::system menu";
	//menu = add(new vsx_widget_popup_menu,"desktop_menu");
	//menu->commands.adds(VSX_COMMAND_MENU, "connect to new server", "server_connect","");
	//menu->commands.adds(VSX_COMMAND_MENU, "quit (kill this client)", "system.shutdown","");
	//menu->commands.adds(VSX_COMMAND_MENU, "help;getting started", "a","");
	//menu->commands.adds(VSX_COMMAND_MENU, "help;about", "b","");
	//menu->size.x = 0.3;
	//menu->size.y = 0.5;

	//menu->commands["connect new server"] = 0;
	//menu->commands["exit"] = 1;

	// popup window
	add(new vsx_window_object_inspector(),"object_inspector");

#ifndef VSXU_PLAYER
	assistant = add(new vsxu_assistant(),"luna");
	front(assistant);
#endif

	enabled = true;
	name = "desktop";
	widget_type = VSX_WIDGET_TYPE_DESKTOP;

	init_children();

	log("welcome to vsxu");

	init_run = true;
	logo_time = 0;
	first_draw = true;
}

void vsx_widget_desktop::reinit() {
	vsx_widget::reinit();
#ifndef VSXU_PLAYER
mtex.init_opengl_texture();
mtex.load_jpeg(skin_path+"desktop.jpg");
//    mtex.load_png(skin_path+"desktop.png");
#endif
}

bool vsx_widget_desktop::key_down(signed long key, bool n_alt, bool n_ctrl, bool n_shift) {
	this->alt = n_alt;
	this->ctrl = n_ctrl;
	this->shift = n_shift;
	char test[2]; test[0] = (char)key; test[1] = 0;
	//printf("key as char: %s\n", test);
	//printf("got key: %d\n", key);
  if (k_focus) {
    if (k_focus->event_key_down(key,alt,ctrl,shift)) {
      if (ctrl) {
#ifdef _WIN32
        switch (tolower(abs(key))) {
#else
        switch (tolower(key)) {
#endif
          case ' ':
            ((vsx_window_texture_viewer*)tv)->run = !((vsx_window_texture_viewer*)tv)->run;
            break;
          // fullwindow
          case 'F':
          case 'f': // F
          	//printf("going fullwindow\n");
            ((vsx_window_texture_viewer*)tv)->fullwindow = !((vsx_window_texture_viewer*)tv)->fullwindow;
            if (((vsx_window_texture_viewer*)tv)->fullwindow) mouse.hide_cursor(); else mouse.show_cursor();
            if (!((vsx_window_texture_viewer*)tv)->fullwindow) this->performance_mode = false;
            //if (alt) this->performance_mode = !this->performance_mode;
          break;
          // close all controllers
          case 'c':
            delete_all_by_type(VSX_WIDGET_TYPE_CONTROLLER);
          break;
          // close all open anchors
          case 'd':
            for (std::map<int, vsx_widget*>::iterator it = ilist.begin();  it != ilist.end(); ++it) {
              if ((*it).second->widget_type == VSX_WIDGET_TYPE_ANCHOR) {
              	if ((*it).second->parent)
                if ((*it).second->parent->widget_type == VSX_WIDGET_TYPE_COMPONENT) {
                  ((vsx_widget_anchor*)(*it).second)->toggle(1);
                }
              }
            }
          break;
        }
      }

      if (alt)
      {
#ifdef _WIN32
        switch (tolower(abs(key))) {
#else
        switch (tolower(key)) {
#endif
          case 'F':
          case 'f': // F
          	if (((vsx_window_texture_viewer*)tv)->fullwindow)
          	{
          		mouse.show_cursor();
          		this->performance_mode = !this->performance_mode;
          	}

          default:
          	break;
        }
      }

      if (!ctrl && !alt)
#ifdef _WIN32
      switch (tolower(abs(key))) {
#else
      switch (abs(key)) {
#endif
      case 0x08:
        case ' ': {
          //if (a_focus->type >= 100)
          {
            if (a_focus->widget_type != VSX_WIDGET_TYPE_SERVER) {
              vsx_vector a = a_focus->get_pos_p();
              move_camera(vsx_vector(a.x,a.y,2.0f));
            } else move_camera(vsx_vector(xp,yp,2.0f));
            /*zp = 2;
            xp = a.x;
            yp = a.y;
            xps = 0;
            yps = 0;
            zps = 0;*/
          }
        }
        break;
        case 'E': case 'e':{ interpolating = false;ypd=1.0;} break;
        case 'D': case 'd':{ interpolating = false;ypd=-1.0;} break;
        case 's': case 'S':{ interpolating = false;xpd=-1.0;} break;
        case 'F': case 'f':{ interpolating = false;xpd=1.0;} break;
        case 'R': case 'r':{ interpolating = false;zpd=-1.0;} break;
        case 'W': case 'w':{ interpolating = false;zpd=1.0;} break;
#ifndef VSXU_PLAYER
#ifndef _WIN32
        case GLFW_KEY_TAB:
#else
        case 0x09:
#endif
        {
          ((vsxu_assistant*)assistant)->toggle_size();
        } break;
#endif
      } // switch
    } else {
      return true;
    }
  } else return true;
  return false;
}


bool vsx_widget_desktop::key_up(signed long key, bool alt, bool ctrl, bool shift) {
  this->ctrl = ctrl;
  if (k_focus) {
    if (k_focus->event_key_up(key,alt,ctrl,shift)) {
      //if (!ctrl)
      switch (key) {
        case 'E': case 'e': ypd=0.0; break;
        case 'D': case 'd': ypd=0.0; break;
        case 'S': case 's': xpd=0.0; break;
        case 'F': case 'f': xpd=0.0; break;
        case 'R': case 'r': zpd=0.0; break;
        case 'W': case 'w': zpd=0.0; break;
        //case 'c': tcp_main_client.connect(578); break;
      }
    } else {
      return false;
    }
  } else return true;
  return false;
}

void vsx_widget_desktop::event_mouse_wheel(float y) {

	//if (y > 0)
	zps += -y;

	if (zps > 2.0f) zps = 2.0f;
	if (zps < -2.0f) zps = -2.0f;
	//else
	//zps += ;
}

void vsx_widget_desktop::move_camera(vsx_vector world) {
  camera_target = world;
  interpolating = true;
}

void vsx_widget_desktop::draw() {
  if (!init_run) return;
  // this is designed to be root, so set up things

  // Deal with movement around the desktop

	#define SGN(N) (N >= 0 ? 1 : -1)
	#define MAX(N, M) ((N) >= (M) ? (N) : (M))
	#define MIN(N, M) ((N) <= (M) ? (N) : (M))
	#define CLAMP(N, L, U) (MAX(MIN((N), (U)), (L)))
	//if (logo_time > animlen) {
	if (!interpolating) {
		double acc = 4, dec = 3, spd = global_key_speed;
		// interpolation falloff control
		float tt = dtime*interpolation_speed*global_interpolation_speed;
		if (tt > 1) { tt = 1; }

		if(zpd != 0.0) {
			double sgn = SGN(zpd);
			zps += dtime * acc * sgn * global_interpolation_speed;
			zps = CLAMP(zps, -1.2f, 1.2f);
		}
		if(zpd == 0.0) {
			double sgn = SGN(zps);
			zps -= dtime * dec * sgn * global_interpolation_speed;
			zps = MAX(zps * sgn, 0) * sgn;
		}

		zp += zps * fabs(zp - 1.1)* spd * dtime + zpp*(zp - 1.0f);
		zpp = zpp*(1-tt);

		if (zp > 100) {zp = 100; zps = 0;}
		if (zp < 1.2) {zp = 1.2; zps = 0;}

		if(xpd != 0.0) {
			double sgn = SGN(xpd);
			xps += dtime * acc * sgn * global_interpolation_speed;
			xps = CLAMP(xps, -1, 1);
		}
		if(xpd == 0.0) {
			double sgn = SGN(xps);
			xps -= dtime * dec * sgn * global_interpolation_speed;
			xps = MAX(xps * sgn, 0) * sgn;
		}
		xp += xps * fabs(zp - 1.1)* spd * dtime*0.6 + xpp*(zp-1.0f);
		xpp = xpp*(1-tt);

		if (xp > 10) {xp = 10; xps = 0;}
		if (xp < -10) {xp = -10; xps = 0;}

		if(ypd != 0.0) {
			double sgn = SGN(ypd);
			yps += dtime * acc * sgn * global_interpolation_speed;
			yps = CLAMP(yps, -1, 1);
		}
		if(ypd == 0.0) {
			double sgn = SGN(yps);
			yps -= dtime * dec * sgn * global_interpolation_speed;
			yps = MAX(yps * sgn, 0) * sgn;
		}
		yp += yps * fabs(zp - 1.1)* spd * dtime*0.6 + ypp*(zp-1.0f);
		ypp = ypp*(1-tt);

		if (yp > 10) {yp = 10; yps = 0;}
		if (yp < -10) {yp = -10; yps = 0;}
//    			printf("xp: %f xps: %f xpd %f dt %f::",xp,xps,xpd,tt);

	}
	else {
		float tt = dtime*10.0f*global_interpolation_speed;
		if (tt > 1) { tt = 1; interpolating = false;}
		xp = xp*(1-tt)+camera_target.x*tt;
		yp = yp*(1-tt)+camera_target.y*tt;
		zp = zp*(1-tt)+camera_target.z*tt;
		if (
			(round(xp*2000) == round(camera_target.x*2000)) &&
			(round(yp*2000) == round(camera_target.y*2000)) &&
			(round(zp*2000) == round(camera_target.z*2000))
		) interpolating = false;
	}

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45,screen_x/screen_y,0.001,120.0);

	gluLookAt(xp,yp,zp-1.1f,xp,yp,-1.1f,0.0,1.0,0.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// PERFORMANCE_MODE_CHANGE
	// if (performance_mode)
	//  glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	//else
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//
	//return;
	glEnable(GL_BLEND);
	//glClear(GL_COLOR_BUFFER_BIT);
	if (!performance_mode)
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
//glEnable(GL_LINE_SMOOTH);
	if (!performance_mode)
	{
		glDisable(GL_DEPTH_TEST);
		glDepthMask(GL_FALSE);
		glColor4f(1,1,1,1);
		#ifndef VSXU_PLAYER
    if (!mtex.bind())
		#endif
    glColor4f(skin_color[13].r,skin_color[13].g,skin_color[13].b,skin_color[13].a);
    //else
     	glBegin(GL_QUADS);
      	glTexCoord2f(0, 0);
        glVertex3f(pos.x-size.x/2,pos.y-size.y/2,-10.0f);
      	glTexCoord2f(0, 1);
        glVertex3f(pos.x-size.x/2,pos.y+size.y/2,-10.0f);
      	glTexCoord2f(1, 1);
        glVertex3f(pos.x+size.x/2,pos.y+size.y/2,-10.0f);
      	glTexCoord2f(1, 0);
        glVertex3f(pos.x+size.x/2,pos.y-size.y/2,-10.0f);
      glEnd();
		#ifndef VSXU_PLAYER
    mtex._bind();
		#endif
	}
  draw_children();
}




void vsx_widget_desktop::draw_2d() {

  GLint	viewport[4];
  glGetIntegerv(GL_VIEWPORT, viewport);
  screen_x = (float)viewport[2];
  screen_y = (float)viewport[3];

  //if (!performance_mode)
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glDisable(GL_DEPTH_TEST);
  glDepthMask(GL_FALSE);
	glMatrixMode(GL_PROJECTION);

  glLoadIdentity();
  screen_aspect = 1.0f;//screen_x/screen_y;
  //screen_aspect = screen_x/screen_y;
  gluOrtho2D(0, screen_aspect, 0, 1);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  vsx_widget::draw_2d();

  // get the mouse area done
  glEnable(GL_DEPTH_TEST);
  glDepthMask(GL_TRUE);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45,(float)screen_x/(float)screen_y,0.001,120.0);
  //gluPerspective(45,1,0.001,100.0);
  glMatrixMode(GL_MODELVIEW);
  //gluLookAt(xp,yp,zp,xp,yp,0.0,0.0,1.0,0.0);
	gluLookAt(xp,yp,zp-1.1f,xp,yp,0.0-1.1f,0.0,1.0,0.0);

  glBlendFunc(GL_ONE, GL_ONE);
  glDepthMask(GL_TRUE);
  glClear(GL_DEPTH_BUFFER_BIT);

  glColor4f(0,0,0,1.0f);
	glBegin(GL_QUADS);
    glVertex3f(-800,-800,0.0);
		glVertex3f(-800,800,0.0);
		glVertex3f(800,800,0.0);
		glVertex3f(800,-800,0.0);
  glEnd();
}


void vsx_widget_desktop::load_configuration()
{
  vsx_command_list main_conf;
#if PLATFORM_FAMILY == PLATFORM_FAMILY_UNIX
  struct stat st;
  char* home_dir = getenv ("HOME");
  vsx_string config_dir(home_dir);
  config_dir += "/.vsxu";
  if (stat(config_dir.c_str(),&st) != 0)
  mkdir(config_dir.c_str(),0700);
  vsx_string config_file = config_dir + "/vsxu.conf";
  if (stat(config_file.c_str(),&st) == 0)
  {
    main_conf.load_from_file(config_file.c_str(),true,0);
  } else
  {
    main_conf.load_from_file(PLATFORM_SHARED_FILES+"vsxu.conf",true,0);
  }
  printf("conf: %s\n", (PLATFORM_SHARED_FILES+"vsxu.conf").c_str());
#else
  main_conf.load_from_file("./vsxu.conf",true,0);
#endif
  main_conf.reset();
  vsx_command_s* mc = 0;
  auto_undo = 1;
  while (mc = main_conf.get()) {
    if (mc->cmd == "skin") {
      skin_path = PLATFORM_SHARED_FILES+vsx_string("gfx/")+mc->cmd_data+"/";
      printf("skin path: %s\n",skin_path.c_str());
    } else
    if (mc->cmd == "global_interpolation_speed") {
      global_interpolation_speed = s2f(mc->cmd_data);
    } else
    if (mc->cmd == "automatic_undo") {
      auto_undo = s2i(mc->cmd_data);
    } else
    if (mc->cmd == "global_framerate_limit") {
      global_framerate_limit = s2f(mc->cmd_data);
    } else
    if (mc->cmd == "global_key_speed") {
      global_key_speed = s2f(mc->cmd_data);
    }
    if (mc->cmd != "" && mc->cmd != "#")
    configuration[mc->cmd] = mc->cmd_data;
  }
}

void vsx_widget_desktop::save_configuration() {
  // final destination for the configuration data
  vsx_string save_filename;
#if PLATFORM_FAMILY == PLATFORM_FAMILY_UNIX
  struct stat st;
  char* home_dir = getenv ("HOME");
  vsx_string config_dir(home_dir);
  config_dir += "/.vsxu";
  if (stat(config_dir.c_str(),&st) != 0)
  mkdir(config_dir.c_str(),0700);
  vsx_string config_file = config_dir + "/vsxu.conf";
  save_filename = config_file;
#else
  save_filename = "./vsxu.conf";
#endif

  vsx_command_list s_conf;
  for (std::map<vsx_string, vsx_string>::iterator it = configuration.begin(); it != configuration.end(); ++it) {
    s_conf.add_raw((*it).first+" "+(*it).second);
  }
  s_conf.save_to_file(save_filename);
}

  void vsx_widget_desktop::vsx_command_process_b(vsx_command_s *t) {
    if (
      t->cmd == "system.shutdown" ||
      t->cmd == "fullscreen" ||
      t->cmd == "fullscreen_toggle"
    ) {
      system_command_queue->addc(t);
    }
    else
    if (t->cmd == "conf") {
      //printf("conf %s\n",t->parts[1].c_str());
      configuration[t->parts[1]] = t->parts[2];
      save_configuration();
      load_configuration();
    }
#ifdef VOVOID
    else
    if (t->cmd == "gui") {
      if (t->cmd_data == "dump")
        {
          log("---------- gui dump -------------");
          for (children_iter=children.begin(); children_iter != children.end(); ++children_iter)
          log((*children_iter)->name);
        }
    } else
    if (t->cmd == "server_connect") {
      f("server_connect_host")->show();
      return;
    } else
    if (t->cmd == "server_connect_host") {
      if (t->cmd_data == "") t->cmd_data = "localhost";
      vsx_widget* sv = add(new vsx_widget_server,t->cmd_data);
      if (!sv)
      {
        log("you fool! we're already connected to this server!");
        return;
      }
      sv->color.r = (double)(rand()%1000)/1000.0;
      sv->color.g = (double)(rand()%1000)/1000.0;
      sv->color.b = (double)(rand()%1000)/1000.0;

      sv->init();
      sv->command_q_b.add(t);
      sv->vsx_command_queue_b(sv);
      //sv->visible = 1;
      return;
      /*stringstream d;
      d << rand();
      vsx_widget* sv = add(new vsx_widget_server,name+".msrv."+d.str());
      sv->p["r"] = (double)(rand()%1000)/1000.0;
      sv->p["g"] = (double)(rand()%1000)/1000.0;
      sv->p["b"] = (double)(rand()%1000)/1000.0;
      sv->size.x = 5;
      sv->size.y = 5;


      vsx_widget* t = sv->add(new vsx_widget_component,sv->name+"test");
      t->size.x = 0.2;
      t->pos.y = 0;
      t->pos.x = 0;


      t = sv->add(new vsx_widget_component,sv->name+"test2");
      t->size.x = 0.2;
      t->pos.y = 1;
      t->pos.x = 1;


      t = sv->add(new vsx_widget_component,sv->name+"test3");
      t->size.x = 0.2;
      t->pos.y = 0;
      t->pos.x = 1;

      sv->init();
      //delete t;*/
    }
#endif
  }

  //void vsx_widget_desktop::event_mouse_move_passive(vsx_vector world, vsx_vector screen) {
//    glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
//  }

vsx_widget_desktop::vsx_widget_desktop() {

  interpolating = false;
  root = this;
  enabled = false;

  // messing with the configuration
  skin_path = "_gfx/vsxu/";
  vsx_command_list modelist;
  vsx_command_s* mc = 0;
  load_configuration();
  myf.init(skin_path+"font/font-ascii.png");
  vsx_command_list skin_conf;
  skin_conf.load_from_file(skin_path+"skin.conf",true,4);
#ifdef VSXU_PLAYER
  if (!skin_conf.count()) {
    skin_conf.add_raw("color 0 0.3,0.3,0.5,0.4");
    skin_conf.add_raw("color 1 0.2,0.2,0.3,0.4");
    skin_conf.add_raw("color 2 0.2,0.2,0.4,1");
    skin_conf.add_raw("color 3 1,1,1,1");
    skin_conf.add_raw("color 4 0.5,0.5,0.7,1");
    skin_conf.add_raw("color 5 0.5,0.5,0.5,1");
    skin_conf.add_raw("color 6 0.4,0.4,0.5,1");
    skin_conf.add_raw("color 7 0.2,0.3,0.8,1");
    skin_conf.add_raw("color 8 0,0,1,0.0");
    skin_conf.add_raw("color 9 1,1,1,0.75");
    skin_conf.add_raw("color 10 1,1,1,0.75");
    skin_conf.add_raw("color 11 1,1,1,0");
    skin_conf.add_raw("color 12 1,1,1,1");
    skin_conf.add_raw("color 13 1,1,1,1");
  }
#endif
  skin_conf.reset();
  while (mc = skin_conf.get()) {
    if (mc->cmd == "color") {
      vsx_avector<vsx_string> parts;
      vsx_string deli = ",";
      explode(mc->parts[2],deli, parts);
      vsx_color p;
      p.r = s2f(parts[0]);
      p.g = s2f(parts[1]);
      p.b = s2f(parts[2]);
      p.a = s2f(parts[3]);
      skin_color[s2i(mc->parts[1])] = p;
    }
  }
  // server widget
  sv = add(new vsx_widget_server,"desktop_local");
  ((vsx_widget_server*)sv)->stype = 1;
  sv->color.b = 255.0/255.0;
  sv->color.g = 200.0/255.0;
  sv->color.r = 200.0/255.0;
  //sv->p["a"] = 0.4;
  sv->size.x = 5;
  sv->size.y = 5;

  // preview window
  tv = add(new vsx_window_texture_viewer(),"vsxu_preview");
  tv->init();
  ((vsx_window_texture_viewer*)tv)->set_server(sv);
  //---
  a_focus = sv;
  m_focus = sv;
  k_focus = sv;

//  ((vsx_window_texture_viewer*)tv)->engine = (void*)vme;
//  main_conf.reset();
/*  while (mc = main_conf.get()) {
    if (mc->cmd == "modestring_default") {
      ((vsx_window_texture_viewer*)tv)->modestring_default = mc->cmd_data;
    } else
    if (mc->cmd == "modestring") {
      ((vsx_window_texture_viewer*)tv)->modestring_commands.addc(mc);
    }
  }*/
  //front(tv);


  console =  add(new vsx_widget_2d_console,"system_console");

  ((vsx_widget_2d_console*)console)->set_destination(sv);

#ifndef VSXU_PLAYER
  mtex.init_opengl_texture();
  mtex.load_jpeg(skin_path+"desktop.jpg");
#endif


  //tv->topmost = true;
  //front(tv);

  k_focus = this;
  m_focus = this;
//  a_focus = this;


  zpf = 0.0;
  zpa = 0.0;
  xpd = 0.0;
  ypd = 0.0;
  zpd = 0.0;
  zps = 0.0;
  yps = 0.0;
  xps = 0.0;
  yp = 0.0;
  xp = 0.0;
  zp = 2.0;
  ypp = zpp = xpp = 0.0f;


}
#endif