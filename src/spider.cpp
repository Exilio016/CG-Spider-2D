//
// Created by exilio016 on 10/04/18.
//

#include <spider.h>
#include <cmath>
#include "spider.h"

#define TORAXSIZE 100
#define EYESIZE 15
#define LEGSIZE 100
#define ARTICANG 15

spider::spider(spider::t_point *pos) {
    this->abdomen = new circle;
    this->cephalothorax = new circle;
    this->legs = new leg*[8];
    this->eyes = new circle*[2];
    this->center = pos;

    this->abdomen->center.y = pos->y - TORAXSIZE + TORAXSIZE/10;
    this->abdomen->center.x = pos->x;
    this->abdomen->radius = TORAXSIZE;

    this->cephalothorax->center.y = pos->y + TORAXSIZE/2;
    this->cephalothorax->center.x = pos->x;
    this->cephalothorax->radius = TORAXSIZE/2;

    this->eyes[0] = new circle;
    this->eyes[0]->center.y = pos->y + TORAXSIZE - EYESIZE;
    this->eyes[0]->center.x = pos->x - EYESIZE;
    this->eyes[0]->radius = EYESIZE;

    this->eyes[1] = new circle;
    this->eyes[1]->center.y = pos->y + TORAXSIZE - EYESIZE;
    this->eyes[1]->center.x = pos->x + EYESIZE;
    this->eyes[1]->radius = EYESIZE;

    int k = 0;
    for(int i = 0; i < 8; i++){
        this->legs[i] = new leg;
        if(k%3 == 0)
            k++;

        this->legs[i]->orig.x = this->cephalothorax->center.x
                               + cos(k*M_PI/6)
                                 * this->cephalothorax->radius;

        this->legs[i]->orig.y = this->cephalothorax->center.y
                               + sin(k*M_PI/6)
                                 * this->cephalothorax->radius;

        if(k < 3 || k > 9) {
            this->legs[i]->end.x = this->legs[i]->orig.x + LEGSIZE;
            this->legs[i]->articulation.x = this->legs[i]->orig.x + LEGSIZE/2;
        }
        else{
            this->legs[i]->end.x = this->legs[i]->orig.x - LEGSIZE;
            this->legs[i]->articulation.x = this->legs[i]->orig.x - LEGSIZE/2;
        }
        this->legs[i]->end.y = this->legs[i]->orig.y - ARTICANG;


        this->legs[i]->articulation.y = this->legs[i]->orig.y + ARTICANG;
        k++;
    }
}
