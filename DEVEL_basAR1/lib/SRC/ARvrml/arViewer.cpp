/*
modif:
version 0.14.3

remove vrmlScene since we use reference now.
remove culling pb
*/

#include <iostream>
#include <math.h>
#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif
#include "arViewer.h"

using namespace openvrml;

arVrmlViewer::arVrmlViewer(openvrml::browser& browser) : gl::viewer(browser)
{
    internal_light = true;

    translation[0] = 0.0;
    translation[1] = 0.0;
    translation[2] = 0.0;

    rotation[0] = 0.0;
    rotation[1] = 0.0;
    rotation[2] = 0.0;

    scale[0] = 1.0;
    scale[1] = 1.0;
    scale[2] = 1.0;
}

arVrmlViewer::~arVrmlViewer()
{
  
}

void arVrmlViewer::timerUpdate()
{ 
  this->update(0.0);
}



void arVrmlViewer::setInternalLight(bool flag)
{
    internal_light = flag;
}

void arVrmlViewer::redraw()
{
	double start = browser::current_time();
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslated( translation[0], translation[1], translation[2] );
    if (rotation[0] != 0.0) { glRotated(rotation[0], 1.0, 0.0, 0.0); }
	if (rotation[1] != 0.0) { glRotated(rotation[1], 0.0, 1.0, 0.0); }
	if (rotation[2] != 0.0) { glRotated(rotation[2], 0.0, 0.0, 1.0); }
    glScaled(scale[0], scale[1], scale[2]);
	
#if USE_STENCIL_SHAPE
    glEnable(GL_STENCIL_TEST);
    glStencilFunc(GL_ALWAYS, 1, 1);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
#endif
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_FOG);          // this is a global attribute
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);
	
	if (internal_light) {
		if (lit) glEnable(GL_LIGHTING);
		glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
		glEnable(GL_NORMALIZE);
		glDisable(GL_COLOR_MATERIAL);
		glDisable(GL_BLEND);
		glShadeModel(GL_SMOOTH);
		
		for (int i = 0; i < max_lights; ++i) {
			light_info_[i].type = light_unused;
			GLenum light = (GLenum) (GL_LIGHT0 + i);
			glDisable(light);
		}
	}
	
    objects = 0;
    nested_objects = 0;
    sensitive = 0;
	
    this->browser.render(*this);
	
	if (internal_light) {
		if (lit) glDisable(GL_LIGHTING);
	}
    glDisable(GL_BLEND);
    glDisable(GL_CULL_FACE);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}

void  arVrmlViewer::post_redraw()
{

}
void  arVrmlViewer::set_cursor(cursor_style c)
{

}

void  arVrmlViewer::swap_buffers()
{

}

void  arVrmlViewer::set_timer(double t)
{

}


void arVrmlViewer::set_viewpoint(const openvrml::vec3f & position,
				 const openvrml::rotation & orientation,
				 float fieldOfView,
				 float avatarSize,
				 float visibilityLimit)
{

}

viewer::object_t arVrmlViewer::insert_background(const std::vector<float> & groundAngle,
                              const std::vector<openvrml::color> & groundColor,
                              const std::vector<float> & skyAngle,
                              const std::vector<openvrml::color> & skyColor,
                              size_t * whc,
                              unsigned char ** pixels)
{
	return 0;
}

viewer::object_t arVrmlViewer::insert_dir_light(float ambientIntensity,
				  float intensity,
				  const openvrml::color & color,
				  const openvrml::vec3f & direction)
{
    if (internal_light) return gl::viewer::insert_dir_light(ambientIntensity, intensity, color, direction);
    return 0;
}

viewer::object_t arVrmlViewer::insert_point_light(float ambientIntensity,
				    const openvrml::vec3f & attenuation,
				    const openvrml::color & color,
				    float intensity,
				    const openvrml::vec3f & location,
				    float radius)
{
	if (internal_light) return gl::viewer::insert_point_light(ambientIntensity, attenuation, color, intensity, location, radius);

    return 0;
}

 
viewer::object_t arVrmlViewer::insert_spot_light(float ambientIntensity,
				   const openvrml::vec3f & attenuation,
				   float beamWidth,
				   const openvrml::color & color,
				   float cutOffAngle,
				   const openvrml::vec3f & direction,
				   float intensity,
				   const openvrml::vec3f & location,
				   float radius)
{
    if (internal_light) return gl::viewer::insert_spot_light(ambientIntensity, attenuation, beamWidth, color,cutOffAngle, direction, intensity, location, radius);
    return 0;
}

 bounding_volume::intersection
arVrmlViewer::intersect_view_volume(const bounding_volume & bvolume) const
{
  // if( d_cull ) {
  //return  openvrml::viewer::intersect_view_volume(bvolume);
	// }
	// else {
         return bounding_volume::inside;
	//}
}
