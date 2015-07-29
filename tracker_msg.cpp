
/**
 * @file tracker_msg.cpp
 * @brief
 */
#include "tracker_msg.h"

/**
 *
 */
struct sns_msg_tracker* sns_msg_tracker_alloc( uint32_t _n ) {
  return sns_msg_tracker_heap_alloc( _n );
}

void sns_msg_tracker_dump( FILE* _out,
			   const struct sns_msg_tracker *_msg ) {
  fprintf( _out, "Num of tracker pads: %d \n", _msg->header.n );
  for( int i = 0; i < _msg->header.n; ++i ) {
    fprintf( _out, "[%d] p: %f %f %f -- q: %f %f %f %f \n",
	     _msg->u[i].id,
	     _msg->u[i].x, _msg->u[i].y, _msg->u[i].z,
	     _msg->u[i].qw, _msg->u[i].qx, _msg->u[i].qy, _msg->u[i].qz );
  } 
}
