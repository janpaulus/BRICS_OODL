/*!
 * \file SickS300BufferMonitor.hh
 * \brief Defines a class for monitoring the receive
 *        buffer when interfacing w/ a Sick S300
 *        laser range finder.
 *
 * Code by Jason C. Derenick and Thomas H. Miller.
 * Contact derenick(at)lehigh(dot)edu
 *
 * The Sick LIDAR Matlab/C++ Toolbox
 * Copyright (c) 2008, Jason C. Derenick and Thomas H. Miller
 * All rights reserved.
 *
 * This software is released under a BSD Open-Source License.
 * See http://sicktoolbox.sourceforge.net
 */

#ifndef SICK_S300_BUFFER_MONITOR_HH
#define SICK_S300_BUFFER_MONITOR_HH

#define DEFAULT_SICK_S300_BYTE_TIMEOUT      (35000)  ///< Max allowable time between consecutive bytes

/* Definition dependencies */
#include "SickS300Message.h"
#include "SickBufferMonitor.h"
#include "SickException.h"

/* Associate the namespace */
namespace SickToolbox {

  /*!
   * \brief A class for monitoring the receive buffer when interfacing with a Sick S300 LIDAR
   */
  class SickS300BufferMonitor : public SickBufferMonitor< SickS300BufferMonitor, SickS300Message > {

  public:

    /** A standard constructor */
    SickS300BufferMonitor( );

    /** A method for extracting a single message from the stream */
    void GetNextMessageFromDataStream( SickS300Message &sick_message ) throw( SickIOException );

    /** A standard destructor */
    ~SickS300BufferMonitor( );

  };
    
} /* namespace SickToolbox */

#endif /* SICK_S300_BUFFER_MONITOR_HH */
