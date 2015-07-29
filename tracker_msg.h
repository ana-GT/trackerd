/**
 * @file tracker_msg.h
 * @brief Last modified: Wednesday, July 29th, 2015
 * @author A. Huaman Quispe <ahuaman3 at gatech dot edu>
 */
#pragma once

#include <sns.h>

#ifdef __cplusplus
extern "C" {
#endif

  /**
   * @struct sns_msg_tracker
   * @brief Carries the marker position of known joints with marker in the robot frame
   */
  struct sns_msg_tracker {
    struct sns_msg_header header;
    struct {
      float x; float y; float z;
      float qw; float qx; float qy; float qz;
      int id;
    } u[1];
  };

  SNS_DEF_MSG_VAR( sns_msg_tracker, u );
  
  // Declarations
  struct sns_msg_tracker* sns_msg_tracker_alloc( uint32_t _n );
  
  void sns_msg_tracker_dump( FILE* _out,
			     const struct sns_msg_tracker *_msg );


  

#ifdef __cplusplus
}
#endif
