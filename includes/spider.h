//
// Created by exilio016 on 10/04/18.
//

#ifndef ARANHA2D_SPIDER_H
#define ARANHA2D_SPIDER_H

#include <GL/gl.h>

class spider {
   public:
      typedef struct {
         GLdouble x;
         GLdouble y;
      } t_point;

      typedef struct {
         t_point center;
         double radius;
      } circle;

      typedef struct {
         t_point orig;
         t_point articulation;
         t_point end;
      } leg;

      circle **eyes;
      circle *cephalothorax;
      circle *abdomen;
      leg **legs;
      t_point *center;

   private:
      typedef enum {
         stopped,
         walking_left,
         walking_dir
      } state;

      state currentState;
      state oldState;
      int it;

      void draw_circle(circle *c);
      void draw_leg(leg *l);

   public:
      spider(t_point *pos);

      void move_spider(GLint, GLint);

      void rotate_spider(GLdouble);
      t_point aux_rotate(GLdouble, t_point);

      void animate();
      void draw();
};

#endif
