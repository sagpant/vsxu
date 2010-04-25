//#include <string>
//#ifdef FOO
#include <map>
#include "vsx_gl_global.h"
#include "vsx_texture_info.h"
#include "vsx_texture.h"
#include "vsx_math_3d.h"
#include "vsx_timer.h"
#include "logo_intro.h"

// logo animation settings
float startanim = 0;
//float animlen = 12;
float animlen = 5;
float fade = 1;

float inalpha = 1;//(logo_time-startanim)/(fade*0.5);
float alpha;

bool finished = false;

void vsx_logo_intro::draw(bool always) {
    if (logo_time > animlen)
    {
      if (finished)
      {
        return;
      }
      else 
      {
        luna->unload();
        luna_bkg->unload();
        finished = true;
      }
    }

    float dtime = timer.dtime();
    if (always) dtime = 0;

    logo_rot1 += dtime*0.01;
    logo_rot2 -= dtime*0.014;
    logo_rot3 += dtime*0.005;
    logo_time += dtime*2;

    if (inalpha > 1) inalpha = 1;
//    if (logo_time-startanim < 1) {
//      alpha = inalpha;
//    } else
    alpha = 1-(logo_time-((animlen-fade)/(fade<1?1:fade)));

    float b_alpha = 1-(logo_time-((animlen-fade)/(fade<1?1:fade)));
//    float c_alpha = 1-(logo_time-((animlen-fade*0.7)/(fade*0.7<1?1:fade*0.7)));
    if (alpha > 1) alpha = 1;
    if (alpha < 0) alpha = 0;
//    if (c_alpha < 0) c_alpha = 0;
      glEnable(GL_BLEND);

      glDepthMask(GL_TRUE);

      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
  		GLint viewport[4];
  		glGetIntegerv(GL_VIEWPORT, viewport);
  		float screenx = (float)(viewport[2]-viewport[0]);
  		float screeny = (float)(viewport[3]-viewport[1]);
  		gluPerspective(45, screenx/screeny, 0.001, 100.0);

      //gluPerspective(45,(float)window_width/(float)window_height,0.001,100.0);
      //gluPerspective(45,1,0.001,100.0);
//      gluPerspective(45,1,0.001,100.0);
      glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();
      gluLookAt(0,0,20,0,0,0.0,0.0,1.0,0.0);
      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      vsx_vector luna_size;
      luna_size.x = 15;
      luna_size.y = 15;
      logo_pos.x = 0;
      logo_pos.y = 0;
      logo_pos.z = 1.1;
      logo_size.x = 20;
      logo_size.y = 20;
    	if (logo_time < animlen) {
        glDisable(GL_DEPTH_TEST);

        glColor4f(0,0,0,b_alpha);
          glBegin(GL_QUADS);
          	glTexCoord2f(0, 1);
            glVertex3f(logo_pos.x-logo_size.x*1.5/2,logo_pos.y-logo_size.y/2,logo_pos.z);
          	glTexCoord2f(0, 0);
            glVertex3f(logo_pos.x-logo_size.x*1.5/2,logo_pos.y+logo_size.y/2,logo_pos.z);
          	glTexCoord2f(1, 0);
            glVertex3f(logo_pos.x+logo_size.x*1.5/2,logo_pos.y+logo_size.y/2,logo_pos.z);
          	glTexCoord2f(1, 1);
            glVertex3f(logo_pos.x+logo_size.x*1.5/2,logo_pos.y-logo_size.y/2,logo_pos.z);
          glEnd();
        float alphab = alpha*0.4;
      	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
        luna_bkg->bind();
          glPushMatrix();
        	glColor4f(0.298,0.368,0.41,alphab);
          glRotatef(logo_rot1*360,0,0,1);
          glBegin(GL_QUADS);
          	glTexCoord2f(0, 1);
            glVertex3f(logo_pos.x-logo_size.x/2,logo_pos.y-logo_size.y/2,logo_pos.z);
          	glTexCoord2f(0, 0);
            glVertex3f(logo_pos.x-logo_size.x/2,logo_pos.y+logo_size.y/2,logo_pos.z);
          	glTexCoord2f(1, 0);
            glVertex3f(logo_pos.x+logo_size.x/2,logo_pos.y+logo_size.y/2,logo_pos.z);
          	glTexCoord2f(1, 1);
            glVertex3f(logo_pos.x+logo_size.x/2,logo_pos.y-logo_size.y/2,logo_pos.z);
          glEnd();
          glPopMatrix();
          glPushMatrix();
          glRotatef(360*logo_rot2,0,0,alphab);
          glBegin(GL_QUADS);
          	glTexCoord2f(0, 1);
            glVertex3f(logo_pos.x-logo_size.x/2,logo_pos.y-logo_size.y/2,logo_pos.z);
          	glTexCoord2f(0, 0);
            glVertex3f(logo_pos.x-logo_size.x/2,logo_pos.y+logo_size.y/2,logo_pos.z);
          	glTexCoord2f(1, 0);
            glVertex3f(logo_pos.x+logo_size.x/2,logo_pos.y+logo_size.y/2,logo_pos.z);
          	glTexCoord2f(1, 1);
            glVertex3f(logo_pos.x+logo_size.x/2,logo_pos.y-logo_size.y/2,logo_pos.z);
          glEnd();
          glPopMatrix();
          glPushMatrix();
        	glColor4f(0.15,0.433,0.46,alphab);
          glRotatef(360*logo_rot3,0,0,1);
          glBegin(GL_QUADS);
          	glTexCoord2f(0, 1);
            glVertex3f(logo_pos.x-logo_size.x/2,logo_pos.y-logo_size.y/2,logo_pos.z);
          	glTexCoord2f(0, 0);
            glVertex3f(logo_pos.x-logo_size.x/2,logo_pos.y+logo_size.y/2,logo_pos.z);
          	glTexCoord2f(1, 0);
            glVertex3f(logo_pos.x+logo_size.x/2,logo_pos.y+logo_size.y/2,logo_pos.z);
          	glTexCoord2f(1, 1);
            glVertex3f(logo_pos.x+logo_size.x/2,logo_pos.y-logo_size.y/2,logo_pos.z);
          glEnd();
          glPopMatrix();
          glPushMatrix();
          logo_size.x = 22;
          logo_size.y = 22;

        	glColor4f(0.433,0.25,0.56,alphab);
          glRotatef(360*logo_rot3*0.5,0,0,1);
          glBegin(GL_QUADS);
          	glTexCoord2f(0, 1);
            glVertex3f(logo_pos.x-logo_size.x/2,logo_pos.y-logo_size.y/2,logo_pos.z);
          	glTexCoord2f(0, 0);
            glVertex3f(logo_pos.x-logo_size.x/2,logo_pos.y+logo_size.y/2,logo_pos.z);
          	glTexCoord2f(1, 0);
            glVertex3f(logo_pos.x+logo_size.x/2,logo_pos.y+logo_size.y/2,logo_pos.z);
          	glTexCoord2f(1, 1);
            glVertex3f(logo_pos.x+logo_size.x/2,logo_pos.y-logo_size.y/2,logo_pos.z);
          glEnd();
          glPopMatrix();
        luna_bkg->_bind();
      	glColor4f(1,1,1,alpha*0.8);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE);

        luna->bind();
          glBegin(GL_QUADS);
          	glTexCoord2f(0, 0);
            glVertex3f(logo_pos.x-luna_size.x/2,logo_pos.y-luna_size.y/2,logo_pos.z);
          	glTexCoord2f(0, 1);
            glVertex3f(logo_pos.x-luna_size.x/2,logo_pos.y+luna_size.y/2,logo_pos.z);
          	glTexCoord2f(1, 1);
            glVertex3f(logo_pos.x+luna_size.x/2,logo_pos.y+luna_size.y/2,logo_pos.z);
          	glTexCoord2f(1, 0);
            glVertex3f(logo_pos.x+luna_size.x/2,logo_pos.y-luna_size.y/2,logo_pos.z);
          glEnd();
        luna->_bind();
        glEnable(GL_DEPTH_TEST);
  }
}

vsx_logo_intro::vsx_logo_intro() {
  logo_time = 0;
  logo_rot1 = 0;
  logo_rot2 = 0.13;
  logo_rot3 = 0.3;
  // sweet sweet luuuuuu <3
  luna = new vsx_texture;
  luna->locked = true;
  luna->init_opengl_texture();
  luna->load_jpeg(PLATFORM_SHARED_FILES+"gfx/vsxu_logo_artiste.jpg",false);
  luna_bkg = new vsx_texture;
  luna_bkg->locked = true;
  luna_bkg->init_opengl_texture();
  luna_bkg->load_jpeg(PLATFORM_SHARED_FILES+"gfx/vsxu_logo_bkg.jpg",false);
  timer.start();
}

void vsx_logo_intro::reinit() {
  //luna->load_png_thread("_gfx/vsxu_logo.png",false);
  //luna_bkg->load_png_thread("_gfx/vsxu_logo_bkg.png",false);
}
//#endif
